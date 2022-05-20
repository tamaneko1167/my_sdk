

//===== FftData Class =========================================================

class FftData{
public:
	FftData(int, int, int);
	~FftData();
	complex<double>*	ptr(int, int, int =0);
	double*				absData(int, int);
	double				absData(int, int, int);
	double*				argData(int, int);
	double				argData(int, int, int);
	void				compensate(int, int, double, double);

protected:
	int					blockNum, chNum, adDataNum;
	complex<double>*	data;
	double				*absDat, *argDat;
};

FftData :: FftData(int block, int ch, int ad){
	blockNum=block;
	chNum=ch;
	adDataNum=ad;
	data=new complex<double>[blockNum * adDataNum * chNum];
	absDat=new double[adDataNum];
	argDat=new double[adDataNum];
};

FftData :: ~FftData(){
	delete data;
	delete absDat;
	delete argDat;
};

complex<double>* FftData :: ptr(int block, int ch, int ad ){
	return(&data[block*chNum*adDataNum + ad + ch*adDataNum]);
}

double* FftData :: absData(int n, int m)
{
	for(int p=0;p<adDataNum;p++){
		absDat[p]=abs(*ptr(n, m, p));
	}
	return(absDat);
}

double FftData :: absData(int n, int m, int p)
{
	return abs(*ptr(n, m, p));
}

double* FftData :: argData(int n, int m)
{
	for(int p=0;p<adDataNum;p++){
		argDat[p]=arg(*ptr(n, m, p));
	}
	return(argDat);
}

double FftData :: argData(int n, int m, int p)
{
	return arg(*ptr(n, m, p));
}

void FftData :: compensate(int n, int m, double amp, double ph){
	absData(n,m);
	argData(n,m);
	for(int p=0;p<adDataNum;p++){
		absDat[p]=absDat[p]*amp;
		argDat[p]=argDat[p]+ph;
		*ptr(n, m, p)=polar(absDat[p], argDat[p]);
	}
}

//===== MiRadarFftData Class =========================================================

class MiRadarFftData : public MiRadarData{
public:
	MiRadarFftData(){};
	MiRadarFftData(MiRadar* p);
	~MiRadarFftData();
	void				fftExe(int ,int);
	int					csvFileWrite();
	complex<double>*	fftDataPtr(int, int, int);
	complex<double>		getFftData(int, int, int);
	double*				absDataPtr(int, int);
	double*				argDataPtr(int, int);
protected:
	FftData*			fftData;
	FftCalc*			fft;
	int					fftMag;
};

MiRadarFftData :: MiRadarFftData(MiRadar* p){
	miRadarData(p);
	fftMag=2;
	fftData =new FftData(blockNum, chNum*2, adDataNum * fftMag);
	fft		=new FftCalc(adDataNum * fftMag);
};

MiRadarFftData :: ~MiRadarFftData(){
	delete fftData;
	delete fft;
};

complex<double>* MiRadarFftData :: fftDataPtr(int block, int ch, int ad)
{
	return(fftData->ptr(block, ch, ad));
};

complex<double> MiRadarFftData :: getFftData(int block, int ch, int ad)
{
	return(*fftData->ptr(block, ch, ad));
};

double* MiRadarFftData :: absDataPtr(int block, int ch)
{
	return(fftData->absData(block, ch));
};

double* MiRadarFftData :: argDataPtr(int block, int ch)
{
	return(fftData->argData(block, ch));
};

void MiRadarFftData :: fftExe(int n, int m)
{
	complex<double>* data= new complex<double>[adDataNum * fftMag];

	for(int p=0;p<adDataNum;p++){
		data[p] = complex<double>(getAdData(n, m, p) , 0.);
		
		if(p<150)
			data[p]=data[p]*(double)p/150.;
		if(p>adDataNum-216)
			data[p]=data[p]*(double)(adDataNum-p)/150.;
		
	}

	fft->fftExe(data, fftData->ptr(n, m));

	fftData->compensate(n, m, ampMag[m], phaseOffset[m]);
	//printf("%d %d  %lf %lf\n", n, m, ampMag[m], phaseOffset[m]);
}

int MiRadarFftData :: csvFileWrite()
{
	for(int m=0;m<adDataNum;m++){
		for(int n=0;n<blockNum;n++){
			for(int o=0;o<chNum *2;o++){
				fprintf(fpwCsv,"%lf,",fftData->absData(n, o, m));
			}
		}
		fprintf(fpwCsv,"\n");
	}
	fprintf(fpwCsv,"\n");
	return(0);
}

//===== Sample Class =========================================================
class Sample : public MiRadar{
public:
	Sample(){
		//reqNum=2*adDataNum/baseWords;
		//readNum=adDataNum*4*chNum+4;
        reqNum=2*adDataNum/baseWords;
        readNum=(8+adDataNum)*4*chNum+4;

		centerFreq=24.15e9;
		deltaFreq=180e6; //チャープ周波数幅[Hz]
		upSweepTime=310e-6;
		downSweepTime=10e-6;
		adDataNum=512; //1スイープでADサンプリングするポイント数
		baseWords=512; //miRadar8で基準になっている数値で512固定
		chNum=4; //ADのチャネル数
		blockNum=1; //繰り返すブロック数
		priRate=1; //PRI rateの時間[ms]
		//priRate=1001;
		txSw=0x59; //Tx1/2の信号出力のOn/Offを制御するスイッチ
		waitTime=0.001;
		alpha=5e-6;
		beta=3.2e-4;
		gamma=2e-4;
		//gamma=75e-3;
		delta=0;
		slave=0;
		interleave=1;

		//centerFreq=24.15e9;	deltaFreq=180e6;	upSweepTime=500e-6; downSweepTime=500e-6;
		//adDataNum=900; baseWords=512; chNum=4; blockNum=2; priRate=1; txSw=0x59;
		//waitTime=50e-3;alpha=10e-6;beta=1000e-6;gamma=10e-6;delta=0e-6;
		//slave=0;interleave=2;
	};
	~Sample(){};
	int				usbOpen();
	int				usbReq();
	int				usbRead(int);
	int				usbClose();
	int				loadOpen();
	int				load();
	int				loadClose();
	int				fftOpen();
	int				fft();
	int				fftClose();
	MiRadarFftData* fft1;
	MiRadarData*	raw1;
	UsbB204*		usb1;
protected:
	int				res1, res2;
	double			centerFreq, deltaFreq, upSweepTime, downSweepTime;
	double			waitTime,alpha,beta,gamma,delta;
	int				tx,slave,interleave;
};

int Sample :: usbOpen()
{
	usb1 = new UsbB204(this);

	if(usb1->port()>0){
		//UsbSetSub(ftHandle, "B204UsbStsReq.cmd", &res1, &res2 );

		usb1->UsbSetSub( "B204UsbSetting.cmd" );

		
		//usb1->UsbSetSub( "B204UsbCrcSet.cmd" );
		//usb1->UsbSetSub( "B204UsbVcoCal.cmd" );
		//usb1->UsbSetSub( "B204UsbRxInit.cmd" );
		//usb1->UsbSetSub( "B204UsbAdcPll.cmd" );
		//usb1->UsbSetSub( "B204UsbAdcPpi.cmd" );
		//usb1->UsbSetSub( "B204UsbSystem.cmd" );
		


		usb1->UsbSetSub( "B204UsbStsReq.cmd", &res1, &res2 );

		//usb1->UsbFastRampPll(centerFreq, deltaFreq, upSweepTime, downSweepTime, deltaFreq/1e5+0.5, 10*deltaFreq/1e7+0.5, 1, "B204PllSet.cmd");
		usb1->UsbFastRampPll(centerFreq, deltaFreq, upSweepTime, downSweepTime, deltaFreq/2e5+0.5,  1, "B204PllSet.cmd");
		usb1->UsbSetSub( "B204PllSet.cmd");

		usb1->UsbE2ReadComp();


		usb1->UsbSetSub( "B204UsbAdc1p8M.cmd" );
		//usb1->UsbSetSub( "B204UsbAdcEqOff.cmd");
		usb1->UsbSetSub( "B204UsbAdcEqOn.cmd");
		usb1->UsbSetSub( "B204UsbAdcEq32k.cmd");

		usb1->UsbSetSub( "B204UsbVcoReCalMax.cmd");
		//usb1->UsbSetSub( "B204UsbVcoReCalM4.cmd");

		usb1->UsbAdcStart( 03 ); // ADC Start

		//usb1->UsbSystemSet(txSw, waitTime, alpha, beta, gamma, delta, slave, interleave, reqNum);
		usb1->UsbSystemSet(txSw, waitTime, alpha, beta, gamma, delta, slave, interleave, blockNum);

		Sleep(1000);
		usb1->rawFileSave("data.dat");
		usb1->csvFileSave("data.csv");
	}
	return 0;
}

int Sample :: usbReq()
{
	usb1->UsbReqData();
	return 0;
}

int Sample :: usbRead(int n)
{
	usb1->UsbReadData(n);
	usb1->getOneData(n);
	return 0;
}

int Sample :: usbClose()
{
	delete(usb1);
	return(0);
}

int Sample :: fftOpen()
{
	fft1 = new MiRadarFftData(this);
	fft1->rawFileLoad("data.dat");
	fft1->getPara();
	fft1->csvFileSave("fft_data.csv");
	return(0);
}

int Sample :: fftClose()
{
	delete(fft1);
	return(0);
}

int Sample :: fft()
{
	if(fft1->rawFileRead()<0){
		return(-1);
	}
	else{
		fft1->getOneData();
		//fft1->csvFileWrite();
		return(0);
	}
}

int Sample :: loadOpen()
{
	raw1 = new MiRadarData(this);
	raw1->rawFileLoad("data.dat");
	raw1->getPara();
	raw1->csvFileSave("raw_data.csv");
	return(0);
}

int Sample :: loadClose()
{
	delete(raw1);
	return(0);
}

int Sample :: load()
{
	if(raw1->rawFileRead()<0){
		return(-1);
	}
	else{
		raw1->getOneData();
		//raw1->csvFileWrite();
		return(0);
	}
}

