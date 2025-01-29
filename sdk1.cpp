// sdk1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

//======= UsbB204 ===============================================================================

UsbB204 :: UsbB204(MiRadar* p, int port )
{
	miRadarData(p);

	ftHandle=(FT_HANDLE)UsbOpen(port, msg);
	puts(msg);

	fpw=NULL;
}

UsbB204 :: ~UsbB204()
{
	UsbPortClose();
	if(fpw!=NULL)
		fclose(fpw);
}


long UsbB204 :: UsbOpen(int portNumber, char* msg)
{
	long  locIdBuf[16];
	int   numDevs;

	//UsbDeviceList(locIdBuf, &numDevs);
	//printf("%d\n",numDevs);
	//if(portNumber<=numDevs){
	//	ftHandle=(FT_HANDLE)UsbPortOpenEx(locIdBuf[portNumber] );
	//}
	//else{
		ftHandle=(FT_HANDLE)UsbPortOpenNo(portNumber);
	//}
	if(ftHandle<(void *)0){
		sprintf(msg,"Can not open ftHandle.");
		return(-1);
	}
	else{
		if(UsbPortSet()<0){
			sprintf(msg,"Can not set port.");
			return(-2);
		}
		if(UsbAdSyncMode()<0){
			sprintf(msg,"Can not set syncronous mode.");
			return(-3);
		}
	}
	sprintf(msg,"USB Port Opened.");
	return((long)ftHandle);
}


void UsbB204 :: UsbDeviceList(long* locIdBuf, int* numDevs)
{
    //long locIdBuf[16];
    //int  numDevs,n;

    //�f�o�C�X���X�g
    FT_ListDevices(locIdBuf,numDevs,FT_LIST_ALL|FT_OPEN_BY_LOCATION);
}

long UsbB204 :: UsbPortOpenEx(long dwLoc )
{
	FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    ftStatus = FT_OpenEx((void*)dwLoc, FT_OPEN_BY_LOCATION,&ftHandle);
    if (!FT_SUCCESS(ftStatus)){
        //printf("Can't open DEV_0x%X\n",dwLoc);
	    return(-1);             // Port Handler
    }
	ftStatus = FT_SetLatencyTimer(ftHandle, 1);
	return((long)ftHandle);
}

long UsbB204 :: UsbPortOpenNo(int no )
{
	FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    //�|�[�g�I�[�v��
    ftStatus = FT_Open(no,&ftHandle);
    if (!FT_SUCCESS(ftStatus)){
        //printf("Can't open DEV_0x%X\n",dwLoc);
        return(-1) ;
    }
	ftStatus = FT_SetLatencyTimer(ftHandle, 1);
	return((long)ftHandle);

}


BOOL UsbB204 :: UsbPortSetSub(TFtConfigData *ftData)
{
    ULONG BaudRate;
    UCHAR WordLength;
    UCHAR StopBits;
    USHORT FlowControl;
    UCHAR XonChar;
    UCHAR XoffChar;
    FT_STATUS ftStatus;

	ftStatus = FT_ResetDevice(ftHandle);
    if (!FT_SUCCESS(ftStatus)) {
        goto close;
    }

    switch (ftData->BaudRate) {
    case 0 :
		BaudRate = 300;
        break;
    case 1 :
		BaudRate = 600;
        break;
    case 2 :
		BaudRate = 1200;
        break;
    case 3 :
		BaudRate = 2400;
        break;
    case 4 :
		BaudRate = 4800;
        break;
    case 5 :
		BaudRate = 9600;
        break;
    case 6 :
		BaudRate = 14400;
        break;
    case 7 :
		BaudRate = 19200;
        break;
    case 8 :
		BaudRate = 38400;
        break;
    case 9 :
		BaudRate = 57600;
        break;
    case 10 :
    	BaudRate = 115200;
        break;
    case 11 :
    	BaudRate = 230400;
        break;
    case 12 :
    	BaudRate = 460800;
        break;
    case 13 :
    	BaudRate = 921600;
        break;
    default :
    	BaudRate = 115200;
        break;
	}

	ftStatus = FT_SetBaudRate(ftHandle,BaudRate);
    if (!FT_SUCCESS(ftStatus)) {
        goto close;
    }

    WordLength = (UCHAR) (ftData->DataBits + FT_BITS_7);

    switch (ftData->StopBits) {
    default :
        StopBits = FT_STOP_BITS_1;
        break;
    case 1 :
        StopBits = FT_STOP_BITS_2;
        break;
    }

    ftStatus = FT_SetDataCharacteristics(
                    ftHandle,
                    WordLength,
                    StopBits,
                    (UCHAR) ftData->Parity
                    );
    if (!FT_SUCCESS(ftStatus)) {
        goto close;
    }

    FlowControl = FT_FLOW_NONE;
    XonChar = 0;
    XoffChar = 0;

    switch (ftData->FlowControl) {

    case 0 :	// NONE
    default :
        break;

	case 1 :	// RTS
        FlowControl = FT_FLOW_RTS_CTS;
    	break;

	case 2 :	// DTR
        FlowControl = FT_FLOW_DTR_DSR;
    	break;

	case 3 :	// XON/XOFF
        FlowControl = FT_FLOW_XON_XOFF;
        XonChar = ftData->Xon;
        XoffChar = ftData->Xoff;
    	break;

    }

    ftStatus = FT_SetFlowControl(
                    ftHandle,
                    FlowControl,
                    XonChar,
                    XoffChar
                    );
    if (!FT_SUCCESS(ftStatus)) {
        goto close;
    }

    ftStatus = FT_SetChars(
                    ftHandle,
                    ftData->EventChar,
                    ftData->EventCharEnabled ? (UCHAR) 1 : (UCHAR) 0,
                    ftData->ErrorChar,
                    ftData->ErrorCharEnabled ? (UCHAR) 1 : (UCHAR) 0
                    );
    if (!FT_SUCCESS(ftStatus)) {
        goto close;
    }

    FT_SetEventNotification(ftHandle,ftData->EventMask,NULL);

    if (ftData->DtrHi) {
    	FT_SetDtr(ftHandle);
	}
    else {
    	FT_ClrDtr(ftHandle);
    }

    if (ftData->RtsHi) {
    	FT_SetRts(ftHandle);
	}
    else {
    	FT_ClrRts(ftHandle);
    }

    FT_SetTimeouts(ftHandle,ftData->RxTimeout,ftData->TxTimeout);

    FT_Purge(ftHandle,FT_PURGE_TX | FT_PURGE_RX);

    return 0;

close:

    return -1;
}

int UsbB204 :: UsbPortSet()
{
    FT_STATUS ftStatus;
    TFtConfigData configData;

    //�|�[�g�ݒ�
    //configData.BaudRate = FT_INDEX_BAUD_115200;
    configData.BaudRate = FT_INDEX_BAUD_921600;
    //configData.BaudRate = FT_INDEX_BAUD_9600;
    configData.DataBits = FT_INDEX_DATA_BITS_8;
    configData.StopBits = FT_INDEX_STOP_BITS_1;
    configData.Parity = FT_INDEX_PARITY_NONE;
    configData.FlowControl = FT_INDEX_FLOW_NONE;
    configData.RtsHi = true;
    configData.DtrHi = true;
    configData.Xon = 0x11;
    configData.Xoff = 0x13;
    configData.EventChar = 0;
    configData.ErrorChar = 0;
    configData.EventCharEnabled = false;
    configData.ErrorCharEnabled = false;
    configData.CtsHi = false;
    configData.DsrHi = false;
    configData.DcdHi = false;
    configData.RingHi = false;
    configData.RxTimeout = FT_DEFAULT_RX_TIMEOUT;
    configData.TxTimeout = FT_DEFAULT_TX_TIMEOUT;
    configData.EventMask = 0;

    //FT_SetTimeouts((FT_HANDLE)ftHandle,1000,1000);              // �^�C���A�E�g�ݒ� 1sec
    int res=UsbPortSetSub(&configData);
    FT_SetTimeouts((FT_HANDLE)ftHandle,2000,2000);              // �^�C���A�E�g�ݒ� 2sec    220429
	return(res);

}

void UsbB204 :: UsbPortClose()
{
	if( ftHandle>(void *)0){
		FT_Close(ftHandle);
		ftHandle=0;
	}
}

int UsbB204 :: UsbAdSyncMode()
{
	int sts1;
    UCHAR Mask = 0xff;
    UCHAR Mode = 0x40; // Set synchronous 245 FIFO mode

    sts1 = FT_SetBitMode((FT_HANDLE)ftHandle, Mask, Mode);
    if (sts1 == FT_OK) {
        // 0xff written to device
        return(0);
        //printf("Sync mode OK. \n");
    }
    else {
        // FT_SetBitMode FAILED!
        return(-1);
        //printf("Sync mode NG. \n");
    }
}

long UsbB204 :: UsbWrite( unsigned char* dat ,long byteNum)
{
    ULONG bytesWritten;

	FT_Write( (FT_HANDLE)ftHandle,dat,byteNum,&bytesWritten);
	return(bytesWritten);
}

void UsbB204 :: UsbSetCmd(  unsigned char* dat ,long byteNum)
{
	int chksum=0;
	int n;

	for(n= 0;n<byteNum;n++){
		chksum=chksum+dat[n];
	}

	chksum=chksum%256;
	byteNum=byteNum+1;
	dat[byteNum-1]=chksum;
	if(byteNum%2){
		byteNum=byteNum+1;
		dat[byteNum-1]=0;
	}

    ULONG bytesWritten;
	FT_Write( (FT_HANDLE)ftHandle,dat,byteNum,&bytesWritten);
}

long UsbB204 :: UsbRead(  unsigned char* dat ,long byteNum)
{
    ULONG bytesRead;

	FT_Read( (FT_HANDLE)ftHandle,dat,byteNum,&bytesRead);
	return(bytesRead);
}



int UsbB204 :: UsbResponseRead( int* FPGAver, int* pll_lock, unsigned char* data)
{
	//unsigned char data[1000];
	unsigned int  bytes;
	ULONG         bytesRead;
	int			  OK,res_error,n;

	//[data b c]=mxRead(ftHandle,4);  %�����@�|�[�g�ԍ��A�ǂݏo���o�C�g��  �߂�l  1:�f�[�^ , 2:�o�C�g��, 3:FT_Read�̃X�e�[�^�X
	FT_Read( (FT_HANDLE)ftHandle,data,4,&bytesRead);
	bytes=data[2]*256+data[3]+1;
	if( bytes%2 )
		bytes=bytes+1;

	//[data2 b c]=mxRead(ftHandle,bytes);  %�����@�|�[�g�ԍ��A�ǂݏo���o�C�g��  �߂�l  1:�f�[�^ , 2:�o�C�g��, 3:FT_Read�̃X�e�[�^�X
	FT_Read( (FT_HANDLE)ftHandle,&data[4],bytes,&bytesRead);
	//data=[data data2];


	OK=0;
	res_error= 0;
    
	if(data[0]==02 && data[1]==255) {  // % 0x02 ff
		if(data[4]==1){  // % �ʐM���ʉ���  0x02 ff 00 03 01 
			if(data[5]==0){
				OK=1;
			}
			else{
				if(data[5]==1){
					printf("FPGA check sum error\n"); 
				}
				else{
					if(data[5]==2)
						printf("FPGA time out error\n"); 
					else
						printf("Un Known Error\n"); 
				}
			}
		}
		else if(data[4]==2){  //% Status�v������    0x02 ff 00 03 02
			*FPGAver=(int)(data[5]);
			*pll_lock=(int)(data[6]);
			OK=1;
			printf("Status Reqest Responce: "); 
			printf("FPGAver %d  PLL Lock 0x%02x\n", *FPGAver, *pll_lock); 
		}
		else{
			printf("�����̎��(01,02�ȊO) \n"); 
			res_error=1;
		}
	}
	else if (data[0]==02 && data[1]==0xfe){    //% 0x02 fe   register read response
		if(data[4]==2){  //% ADC
			printf("ADC Register Read: ");
			for(n=0;n<bytes+4;n++)
				printf("%02x ",data[n]);
			printf("\n");
		}
		else if(data[4]==3){  //% EEPROM
			printf("EEPROM Read: ");
			for(n=0;n<bytes+4;n++)
				printf("%02x ",data[n]);
			printf("\n");
		}
	}
	else{
		printf("header(02ff�ȊO) %x%x \n",data[0],data[1]); 
		res_error=1;
		//%pause(1);
	}
	return(res_error);
}


int UsbB204 :: UsbSetSub( char* fileName, int* res1  , int* res2  )
{
	long dataNum=0;
	long byteNum=0;
	long n=0,m=0;
	int  startFlag=0;
	FILE* fpr;
	char str[1000], str1[1000];
	double wt;
	unsigned char dat[100],data[1000];
	ULONG bytesWritten;
	int chksum;
	char fileName2[200];

	fpr=fopen(fileName,"r");
	if(fpr<=(void *)0){
		printf("%s not found.\n", fileName);
		return(-1);
	}

	while(!feof(fpr)){ // ~feof(fpr) % && (byteNum==0 || n<byteNum)
		fgets(str,1000,fpr);
		sscanf(str,"%s",str1);
		if(strncmp(str1,"#start",6)==0)
			startFlag=1;
		else if(strncmp(str1,"#wait",5)==0){
			sscanf(str,"%s %lf",str1,&wt);
			Sleep((long)(wt*1000));
		}
		else if(strncmp(str1,"#include",8)==0){
			sscanf(str,"%s %s",str1,fileName2);
			UsbSetSub(  fileName2 , res1, res2 );
		}
		else if(strncmp(str1,"//",2)!=0 && strcmp(str1,"")!=0 && startFlag==1){
			m=0;
			while(str1[m]!='\n' && str1[m]!='\0' && str1[m]!='\t' && str1[m]!=' '){
				if(str1[m]=='/' && str1[m-1]=='/'){
					str1[m]=' ';
					str1[m-1]=' ';
					break;
				}
				m++;
			}

			if(strncmp(str1,"0x",2)==0)
				sscanf(&str1[2],"%x",&dat[n]);
			else
				sscanf(str1,"%d",&dat[n]);
			
			if(n==3)
				byteNum=256*dat[2]+dat[3]+4;
			
			if(byteNum>0 && n+1>=byteNum){
				chksum=0;
				for(n= 0;n<byteNum;n++){
					chksum=chksum+dat[n];
				}
				chksum=chksum%256;
				byteNum=byteNum+1;
				dat[byteNum-1]=chksum;
				if(byteNum%2){
					byteNum=byteNum+1;
					dat[byteNum-1]=0;
				}

				
				FT_Write( (FT_HANDLE)ftHandle,dat,byteNum,&bytesWritten);
				UsbResponseRead( res1, res2, data);
				
				dataNum=dataNum+1;
				byteNum=0;
				n=0;
				startFlag=0;
			}
			else
				n++;
		}
	}           
	fclose(fpr);

	if(n<byteNum){
		printf("\ndata of '%s' is insufficient.\n\n",fileName);
		dataNum=-2;
	}

	return(dataNum);
}

void UsbB204 :: UsbAdcStart(int start)
{
	unsigned char dat[100], data[1000];
	int result=0;
	int status=0;
	int n;

	for(n=0;n<100;n++)
		dat[n]=0;

	dat[0]=2;
	dat[1]=3;
	dat[3]=13;
	dat[4]=1;
	dat[5]=start;
	dat[6]=chNum;
	dat[7]=1;
	dat[8]=1;
	dat[9]=adDataNum/256;
	dat[10]=adDataNum%256;
	dat[14]=1;
	UsbSetCmd(dat,17);
	//UsbSetCmd(ftHandle,[02 03 00 13 1 03 chNum 01 01 floor(adDataNum/256) rem(adDataNum,256) 00 00 00 01 00 00]);
	Sleep(5);
    UsbResponseRead( &result, &status, data);
}

int UsbB204 :: UsbOneData()
{
	unsigned char dat[100];
	int result=0;
	int status=0;
	int n;
	long bytesRead;

	for(n=0;n<100;n++)
		dat[n]=0;
	dat[0]=2;
	dat[1]=5;
	dat[3]=2;
	dat[4]=adDataNum/256;
	dat[5]=adDataNum%256;
	UsbSetCmd(  dat, 6 );  //% Rx Power Down
    //[result status]=B204UsbSetCmd(ftHandle,[02 05 00 02 00 reqNum]);
	//Sleep(5);

	bytesRead=UsbRead(  usbData , readNum*blockNum );

    if(bytesRead<readNum*blockNum)
        return(-1);
    else
        return(0);

}

int UsbB204 :: UsbReadData(int block)
{
	long bytesRead;

	bytesRead=UsbRead(  &usbData[readNum*block] , readNum );

	if(fpw>(void *)0){
		clk=clock();
		fprintf(fpw,"%ld",time(&tim));
		fprintf(fpw,".%ld ",clk); 
		printf("%lf %s\n",(double)clk/CLK_TCK,ctime(&tim));
		for(int m=0;m<readNum;m++){
			fputc(*usbDataPtr(block, m), fpw);
		}
	}

    if(bytesRead<readNum)
        return(-1);
    else
        return(0);

}

int UsbB204 :: UsbReadData()
{
	int res=0;
	for(int n=0;n<blockNum;n++){
		if(UsbReadData(n)<0){
			printf("AD read time out.\n");
			res=-1;
		}
	}
	return(res);
}


FT_HANDLE UsbB204 :: port()
{
	return(ftHandle);
};

int UsbB204 :: rawFileSave(char* fn)
{
	if((fpw=fopen(fn,"wb"))==NULL){
		return(-1);
	}
	else{
		fprintf(fpw,"%d %d %d %d ",blockNum,chNum,adDataNum,baseWords);
		for(int n=0;n<8;n++){
			fprintf(fpw,"%lf ",ampMag[n]);
		}
		for(int n=0;n<8;n++){
			fprintf(fpw,"%lf ",phaseOffset[n]);
		}
		return(0);
	}
}



unsigned int UsbB204 :: UsbE2ReadSub(unsigned int adr)
{
	unsigned char dat[100];

	for(int n=0;n<100;n++)
		dat[n]=0;
	dat[0]=2;
	dat[1]=53;
	dat[3]=2;
	dat[4]=adr/256;
	dat[5]=adr%256;
	UsbSetCmd(dat, 6);  

	Sleep(10);

	int result, status;
	unsigned char data[1000];
	UsbResponseRead(&result, &status, data);
	return(data[6]*256+data[7]);
}

void UsbB204 :: UsbE2ReadComp()
{
	unsigned int adr=32;
	ampMag[0]=0.001*UsbE2ReadSub(adr+ 0);
	ampMag[1]=0.001*UsbE2ReadSub(adr+ 1);
	ampMag[2]=0.001*UsbE2ReadSub(adr+ 2);
	ampMag[3]=0.001*UsbE2ReadSub(adr+ 3);
	ampMag[4]=0.001*UsbE2ReadSub(adr+ 4);
	ampMag[5]=0.001*UsbE2ReadSub(adr+ 5);
	ampMag[6]=0.001*UsbE2ReadSub(adr+ 6);
	ampMag[7]=0.001*UsbE2ReadSub(adr+ 7);

	adr=adr+8;
	phaseOffset[0]=0.001*UsbE2ReadSub(adr+ 0)-2*M_PI;
	phaseOffset[1]=0.001*UsbE2ReadSub(adr+ 1)-2*M_PI;
	phaseOffset[2]=0.001*UsbE2ReadSub(adr+ 2)-2*M_PI;
	phaseOffset[3]=0.001*UsbE2ReadSub(adr+ 3)-2*M_PI;
	phaseOffset[4]=0.001*UsbE2ReadSub(adr+ 4)-2*M_PI;
	phaseOffset[5]=0.001*UsbE2ReadSub(adr+ 5)-2*M_PI;
	phaseOffset[6]=0.001*UsbE2ReadSub(adr+ 6)-2*M_PI;
	phaseOffset[7]=0.001*UsbE2ReadSub(adr+ 7)-2*M_PI;

	/*
	for(int n=0;n<8;n++)
		printf("%.1f ",ampMag[n]);
	printf("\n");
	for(int n=0;n<8;n++)
		printf("%.1f ",phaseOffset[n]);
    printf("\n");
	*/
}

//--------------------------------------------------------------------
void UsbB204 :: UsbSystemSet(int tx, double waitTime1, double alpha1, double beta1, double gamma1, double delta1,
							   int slave, int interleave, int reqNum)
{
	unsigned char dat[100], data[1000];
	int result=0;
	int status=0;
	int n;
	int waitTime, alpha, beta, gamma, delta;

    waitTime=waitTime1*1e3+0.5;
    alpha=alpha1*1e7+60+0.5;
    beta=beta1*1e7-60;
    gamma=gamma1*1e7;
    delta=delta1*1e7;

	for(n=0;n<100;n++)
		dat[n]=0;
	dat[0]=2;
	dat[1]=9;
	dat[3]=25;
	dat[9]=tx;
	dat[10]=waitTime/256;
	dat[11]=waitTime%256;
	dat[12]=delta/256;
	dat[13]=delta%256;
	dat[15]=reqNum/256;
	dat[16]=reqNum%256;
	dat[18]=alpha/256;
	dat[19]=alpha%256;
	dat[20]=gamma/256/256;
	dat[21]=gamma/256;
	dat[22]=gamma%256;
	dat[23]=slave;
	dat[24]=1;
	dat[25]=log((double)interleave)/log(2.);
	dat[26]=beta/256/256;
	dat[27]=beta/256;
	dat[28]=beta%256;
	UsbSetCmd( dat, 29 );  //% Rx Power Down
//  B204UsbSetCmd( Port1, [2 9 0 25 0 0 0 0 0 tx
//	                       floor(waitTime/256) mod(waitTime,256) ...
//                         floor(delta/256) mod(delta,256) 0   floor(reqNum/256) mod(reqNum,256)  0 ...
//                         floor(alpha/256) mod(alpha,256)  floor(gamma/256/256) floor(gamma/256) mod(gamma,256) slave   1  interleave  ...
//                         floor(beta/256/256) floor(beta/256) mod(beta,256)] );  
	Sleep(5);
	UsbResponseRead( &result, &status, data);
}

void UsbB204 :: UsbReqData()
{
	unsigned char dat[100];
	int n;

	for(n=0;n<100;n++)
		dat[n]=0;
	dat[0]=2;
	dat[1]=5;
	dat[3]=2;
	dat[4]=adDataNum/256;
	dat[5]=adDataNum%256;
	UsbSetCmd(  dat, 6 );  //% Rx Power Down
    //[result status]=B204UsbSetCmd(ftHandle,[02 05 00 02 00 reqNum]);
	//Sleep(5);
}


//======= MiRadarData ===============================================================================

void MiRadarData :: getOneDataSub(unsigned char* dat, int* data /* , FILE* fp */)
{
	*data = (*dat)*256 + *(dat+1);
	if(*data>32767)
		*data=*data-65536;
}

void MiRadarData :: getOneData()
{
	int n;
	for(n=0;n<blockNum;n++){
		getOneData( n );
	}
}

int MiRadarData :: csvFileSave(char* fn)
{
	if((fpwCsv=fopen(fn,"w"))==NULL){
		return(-1);
	}
	else{
		return(0);
	}
}

int MiRadarData :: rawFileLoad(char* fn)
{
	if((fprRaw=fopen(fn,"rb"))==NULL){
		return(-1);
	}
	else{
		fscanf(fprRaw,"%d %d %d %d ",&blockNum,&chNum,&adDataNum,&baseWords);
		reqNum=2*adDataNum/baseWords;
		readNum=(adDataNum+8)*4*chNum+4;
		for(int n=0;n<8;n++){
			fscanf(fprRaw,"%lf ",&ampMag[n]);
		}
		for(int n=0;n<8;n++){
			fscanf(fprRaw,"%lf ",&phaseOffset[n]);
		}

		return(0);
	}
}

int MiRadarData :: rawFileRead()
{
	long bytesRead;
	long    tim1,clk1;
	unsigned char c;

	if(fprRaw>(void *)0){

		for(int n=0;n<blockNum;n++){
			int err=fscanf(fprRaw,"%ld.%ld ",&tim1,&clk1);
			if(err<0)
				return(-1);
			tim=tim1;
			clk=clk1;
			printf("%lf %s\n",(double)clk1/CLK_TCK,ctime(&tim));
			for(int m=0;m<readNum;m++){
				c=getc(fprRaw);
				usbDataPut(n,m,c);
			}
		}
	}
	return(0);
}





int MiRadarData :: csvFileWrite()
{
	for(int m=0;m<adDataNum;m++){
		for(int n=0;n<blockNum;n++){
			for(int o=0;o<chNum *2;o++){
				fprintf(fpwCsv,"%d,",*adDataPtr(n, o, m));
			}
		}
		fprintf(fpwCsv,"\n");
	}
	fprintf(fpwCsv,"\n");
	return(0);
}

void MiRadarData :: miRadarData(MiRadar* p )
{
	parent=p;
	putPara();
	fpwCsv=NULL;
	fprRaw=NULL;
	usbData=new unsigned char[blockNum * readNum];
	adData =new AdData(blockNum, chNum*2, adDataNum);
}

void MiRadarData :: putPara()
{
	adDataNum=parent->adDataNum; 
	baseWords=parent->baseWords; 
	chNum    =parent->chNum; 
	blockNum =parent->blockNum; 
	priRate  =parent->priRate;
	txSw     =parent->txSw;
	reqNum=2*adDataNum/baseWords;
	readNum=(8+adDataNum)*4*chNum+4;
}

void MiRadarData :: getPara()
{
	parent->adDataNum=adDataNum; 
	parent->baseWords=baseWords; 
	parent->chNum    =chNum; 
	parent->blockNum =blockNum; 
	parent->priRate  =priRate;
	parent->txSw     =txSw;
	parent->reqNum=2*adDataNum/baseWords;
	parent->readNum=(8+adDataNum)*4*chNum+4;
}

//--------------------------------------------------------------------
void MiRadarData :: getOneData(int n)
{
	int m,l;
	for(m=0;m<chNum;m++){
		for(l=0;l<adDataNum;l++){
			getOneDataSub(&usbData[2* (n*(2*chNum*(adDataNum+8)+2)+(2*m+1)*(adDataNum+8) +l+10)],adData->ptr(n, m      , l));
			getOneDataSub(&usbData[2* (n*(2*chNum*(adDataNum+8)+2)+ 2*m   *(adDataNum+8) +l+10)],adData->ptr(n, m+chNum, l));
		}
	}
}

