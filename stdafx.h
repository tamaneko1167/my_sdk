
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


//#include "targetver.h"

#include <stdio.h>
//#include <tchar.h>

// TODO: reference additional headers your program requires here

#define _USE_MATH_DEFINES

#include <string.h>
#include <stdlib.h>
//#include <windows.h>
#include <time.h>
#include <sys/time.h>
#include "ftd2xx.h"
#include "mxConfig.h"
#include <math.h>
#include "fft.h"

#define CLK_TCK CLOCKS_PER_SEC

extern void Sleep(double t);



class AdData{
public:
	AdData(int block, int ch, int ad){
		blockNum=block;
		chNum=ch;
		adDataNum=ad;
		data=new int[blockNum * adDataNum * chNum];
	};
	~AdData(){
		delete data;
	};
	int* ptr(int block, int ch, int ad){
		return(&data[block*chNum*adDataNum + ad + ch*adDataNum]);
	}

protected:
	int	blockNum, chNum, adDataNum;
	int* data;
};


class MiRadar{
public:
	MiRadar(){};
	~MiRadar(){};
	int  adDataNum, baseWords, chNum, blockNum, priRate, txSw;
	int  reqNum,readNum;
};


class MiRadarData : public MiRadar{
public:
	MiRadarData(){
		fpwCsv=NULL;
		fprRaw=NULL;
	};
	MiRadarData(MiRadar* p){
		miRadarData(p);
	};
	~MiRadarData(){
		delete usbData;
		delete adData;
		if(fpwCsv!=NULL){
			fclose(fpwCsv);
		}
		if(fprRaw!=NULL){
			fclose(fprRaw);
		}
	};

	void miRadarData(MiRadar* );
	void putPara();
	void getPara();

	void getOneDataSub(unsigned char* , int*  );
	void getOneData(int);
	void getOneData();
	int  csvFileSave(char*);
	int  csvFileWrite();
	int  rawFileLoad(char*);
	int  rawFileRead();
	int* adDataPtr(int block, int ch, int ad)
	{
		return(adData->ptr(block, ch, ad));
	};
	int getAdData(int block, int ch, int ad)
	{
		return(*adData->ptr(block, ch, ad));
	};
	unsigned char* usbDataPtr(int block, int byte)
	{
		return(&usbData[block*readNum + byte]);
	};
	void usbDataPut(int block, int byte, unsigned char c)
	{
		usbData[block*readNum + byte]=c;
	};
	time_t* getTime()
	{
		return(&tim);
	}
	clock_t getClock()
	{
		return(clk);
	}
	double getAmpMag(int n)
	{
		return(ampMag[n]);
	}
	double getPhaseOffset(int n)
	{
		return(phaseOffset[n]);
	}

protected:
	MiRadar*		parent;
	AdData*			adData;
	unsigned char*	usbData;
	FILE*			fpwCsv;
	FILE*			fprRaw;
	double			ampMag[8], phaseOffset[8];
	time_t			tim;
	clock_t			clk;
};

class UsbB204 : public MiRadarData{
public:
	UsbB204(){};
	UsbB204(MiRadar* ,int =0);
	~UsbB204();
	FT_HANDLE port();
	long UsbOpen(int , char* );
	void UsbDeviceList(long* , int* );
	long UsbPortOpenEx(long );
	long UsbPortOpenNo(int );
	BOOL UsbPortSetSub(TFtConfigData*);
	int  UsbPortSet();
	void UsbPortClose();
	int  UsbAdSyncMode();
	long UsbWrite(unsigned char* ,long );
	void UsbSetCmd(  unsigned char* ,long );
	long UsbRead( unsigned char*  ,long );
	int  UsbResponseRead( int* , int* , unsigned char* );
	int  UsbSetSub( char* , int*  =0 , int* =0 );
	//void UsbSystemSet(int, double);
	void UsbSystemSet(int, double, double, double, double, double, int, int, int);
	void UsbAdcStart(int );
	int  UsbOneData();
	void UsbReqData();
	int  UsbReadData(int);
	int  UsbReadData();
	int  rawFileSave(char*);
	int  UsbFastRampPllSub(unsigned long* , double, double, double, int, int, int);
	//int  UsbFastRampPll(double, double, double, double, int, int, int, char* );
	int  UsbFastRampPll(double, double, double, double, int, int, char* );
	int  UsbSetPllSub(FILE*,unsigned long);
	unsigned int UsbE2ReadSub(unsigned int);
	void UsbE2ReadComp();

protected:
	FT_HANDLE		ftHandle;
	char			msg[1000];
	FILE*			fpw;
	unsigned long	CLK2,CLK1;
};



