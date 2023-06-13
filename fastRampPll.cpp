

#include "stdafx.h"

//int UsbB204 :: UsbFastRampPll(double freq0, double deltaFreq, double uChirpTime, double dChirpTime,
//							  int uFDevDiv,  int dFDevDiv,  int pllRamp, char* fName)
int UsbB204 :: UsbFastRampPll(double freq0, double deltaFreq, double uChirpTime, double dChirpTime,
							  int fDevDiv,  int pllRamp, char* fName)
{
	unsigned long uReg[8], dReg[8];
	if(UsbFastRampPllSub(uReg, freq0, deltaFreq, uChirpTime, fDevDiv, 1, pllRamp)<0)
		return(-1);
	if(UsbFastRampPllSub(dReg, freq0, deltaFreq, dChirpTime, fDevDiv, 0, pllRamp)<0)
		return(-1);

	FILE* fp=fopen(fName,"w");
	UsbSetPllSub(fp,uReg[7]);
	UsbSetPllSub(fp,uReg[6]);
	UsbSetPllSub(fp,dReg[6]);
	UsbSetPllSub(fp,uReg[5]);
	UsbSetPllSub(fp,dReg[5]);
	UsbSetPllSub(fp,uReg[4]);
	UsbSetPllSub(fp,dReg[4]);
	UsbSetPllSub(fp,uReg[3]);
	UsbSetPllSub(fp,uReg[2]);
	UsbSetPllSub(fp,uReg[1]);
	UsbSetPllSub(fp,uReg[0]);
	fclose(fp);

	return(0);
}			

int UsbB204 :: UsbSetPllSub(FILE* fp,unsigned long REG)
{
	fprintf(fp,"#start \n0x02 \n0x06  \n0x00  \n0x05  \n0x00 \n");
	fprintf(fp,"0x%x\n",(REG>>24)&0xff);
	fprintf(fp,"0x%x\n",(REG>>16)&0xff);
	fprintf(fp,"0x%x\n",(REG>> 8)&0xff);
	fprintf(fp,"0x%x\n",(REG    )&0xff);
	return(0);
}

							  
int UsbB204 :: UsbFastRampPllSub(unsigned long* REG, double freq0, double deltaFreq, double chirpTime, int fDevDiv, int ud, int pllRamp)
{
	//‚e‚l‚b‚v@‚o‚k‚kÝ’è
	int			res=1;
	double			fmax,fmin,fDEV,frange,fPFD,fRES,fDEV_RES;
	//unsigned long	NStep,CLK2,CLK1,DEV_OFFSET,DEV;
	unsigned long	NStep,          DEV_OFFSET,DEV;
	unsigned long	N12,F25,M4,R1,P12,PA1,D1_12,R5,U1_1,U2_1,PS1,CPI4,CR1;
	unsigned long	U7_1,U8_1,U9_1,U10_1,U11_1,FSK1,PSK1,RM2,U12_1,NS1,L1,DB17,NB1,NB3;
	unsigned long	CS1,D2_12,C2,RS5,S5,LS1,D16,DO4,DS1,DR1,FSKR1,I2,PR1,TR1,TI1;
	unsigned long	S20,SSE1,DS12,DSE1,DC1,RD1,RDF1,FR1,TDT1,ST1,TD1,TDTD1;

	fPFD=100e6;
	if(ud==0)
		fDevDiv=chirpTime*fPFD/CLK2/CLK1+0.5;
	fmax=(freq0+0.5*deltaFreq)/1e6;
	fmin=(freq0-0.5*deltaFreq)/1e6;
	fDEV=(fmax/2-fmin/2)*pow(10.,6.)/fDevDiv;
	frange=(fmax-fmin)/2*1e6;
	//fPFD=100e6;
	fRES=fPFD/pow(2.,25.);
	DEV_OFFSET=(unsigned long)ceil(log10(fDEV/(fRES*pow(2.,15.)))/log10(2.0));
	fDEV_RES=fRES*pow(2.,(double)DEV_OFFSET);
	DEV=(unsigned long)((fDEV/(fRES*pow(2.,(double)DEV_OFFSET)))+0.5);
	NStep=(unsigned long)((frange/(fRES*DEV*pow(2.,(double)DEV_OFFSET)))+0.5);
	CLK2=1;
	if(ud==1)
		CLK1=(unsigned long)(((chirpTime/NStep)*fPFD/CLK2)+0.5);

	if(DEV_OFFSET>=9){
		printf("DEV_OFFSET Error %d>=9\n",DEV_OFFSET);
		res=0;
	}
	if(DEV>=32767){
		printf("DEV Error %d>=32767\n",DEV);
		res=0;
	}
	if(NStep>=1048575){
		printf("NStep Error %d>=1048575\n",NStep);
		res=0;
	}
	if(CLK1>=4095){
		printf("CLK1 Error %d>=4095\n",CLK1);
		res=0;
	}
	if(CLK2>=4095){
		printf("CLK2 Error %d>=4095\n",CLK2);
		res=0;
	}
 
	if(res==0)
		return(-1);
	

	double freq=fmin;
	//%---- R0 ----
	//% INTEGER VALUE (INT)
		//%N12=300;
		N12=floor(freq/(fPFD*2/1e6));
	//% FRACTIONAL VALUE (FRAC)
		//%F25=20971520;
		F25=(unsigned long)((freq/(fPFD*2/1e6)-N12)*pow(2.,25.)+0.5);
	//% MUXOUT CONTROL    
		M4=6;          //% DIGITAL LOCK DETECT
	//% RAMP ON
		if(pllRamp==1)
			R1=1;  //% FMCW 1:ramp ON,  CW 0: ramp OFF
		else
			R1=0;

	//%---- R1 ----
	//% PHASE VALUE
		P12=0;
	//% PHASE ADJUST
		PA1=0;
    
	//%---- R2 ----
	//% CLK1 DIVIDER VALUE
		//%D1_12=1;     //% FMCW:1@ŒvŽZ’l@, CW :0 
		D1_12=CLK1;  //% FMCW:1@ŒvŽZ’l@, CW :0 
	//% R COUNTER
		//R5=25;
		//R5=5;
		R5=1;
	//% REFERENCE DOUBLER DBB
		//U1_1=0;
		U1_1=1;
	//% RDIV2 DBB
		U2_1=0;
	//% PRESCALER
		//PS1=0;
		PS1=1;
	//% CP CURRENT SETTING
		//CPI4=7;    //% 2.5mA: 7  PLLƒ‹[ƒvƒtƒBƒ‹ƒ^[’è”‚ÆŠÖ˜A—L‚è
		CPI4=15;   
	//% CSR
		CR1=0;
    
	//%---- R3 ----
	//% COUNTER RESET
		U7_1=0;
	//% CP THREE-STATE
		U8_1=0;
	//% POWER-DOWN
		U9_1=0;
	//% PD POLARITY
		//U10_1=0;
		U10_1=1;
	//% LDP
		U11_1=0;   //% 0: 14nsec , 0: 6nsec
	//% FSK
		FSK1=0;
	//% PSK
		PSK1=0;
	//% RAMP MODE
		RM2=3;    //% FMCW:3, CW :0
	//% SD RESET
		U12_1=0;
	//% N SEL
		NS1=0;
	//% LOL
		L1=0;
	// Reserved
		DB17=1;
	//% NEG BLEED ENABLE
		NB1=0;
	//% NEG BLEED CURRENT
		NB3=0;
    
	//%---- R4 ----
	//% CLK DIV SEL
		if(ud==1)
			CS1=0;
		else
			CS1=1;
	//% CLK2 DIVIDER VALUE
		//%D2_12=2;    //% FMCW : 2  ŒvŽZ’l  ,  CW:0
		D2_12=CLK2;    //% FMCW : 2  ŒvŽZ’l  ,  CW:0
	//% CLK DIV MODE
		C2=3;       //% FMCW:3 Ramp Divider  ,  CW:0
	//% RAMP STATUS
		//RS5=0;
		RS5=3;
	//% ƒ°-ƒ¢MODULATOR MODE
		S5=0;
	//% LE SEL
		LS1=0;
    
	//%---- R5 ----
	//% DEVIATION WORD
		//%D16=6712;   // % FMCW : 6712  ŒvŽZ’l  ,  CW:0
		D16=DEV;    //% FMCW : 6712  ŒvŽZ’l  ,  CW:0
	//% DEVIATION OFFSET WORD
		//%DO4=1;       //% FMCW :1 ŒvŽZ’l  ,  CW:0
		DO4=DEV_OFFSET;       //% FMCW :1 ŒvŽZ’l  ,  CW:0
	//% DEV SEL
		if(ud==1)
			DS1=0;
		else
			DS1=1;
	//% DUAL RAMP
		DR1=0;
	//% FSK RAMP
		FSKR1=0;
	//% INTERRUPT
		I2=0;
	//% PARABOLIC RAMP
		PR1=0;
	//% TX RAMP CLK
		TR1=0;
	//% TX DATA INVERT
		TI1=0;
    
	//%---- R6 ----
	//% STEP WORD
		//%S20=4999;    //% FMCW : 4999  ŒvŽZ’l  ,  CW:0
		S20=NStep;    //% FMCW : 4999  ŒvŽZ’l  ,  CW:0
	//% STEP SEL
		if(ud==1)
			SSE1=0;
		else
			SSE1=1;
    
	//%---- R7 ----
	//% DELAY START WORD
		DS12=0;
	//% DEL START EN
		DSE1=0;
	//% DEL CLK SEL
		DC1=0;
	//% RAMP DELAY
		RD1=0;
	//% RAMP DELAY FL
		RDF1=0;
	//% FAST RAMP
		//FR1=0;
		FR1=1;
	//% TX DATA TRIGGER
		TDT1=1;  //% FMCW 1,  CW 0
	//% SING FULL TRI
		ST1=1;  //% FMCW 1,  CW 0
	//% TRI DELAY
		TD1=0;
	//% TX DATA TRIGGER DELAY
		TDTD1=0;

    
	//% PLL0Ý’è
	//double freq=fmin;
	int pll=0;

	//------------------------------------------------------

	//FMCWsetPLLsub;
	
	int C3;
	//unsigned long REG[8];

	//% INTEGER VALUE (INT)
	//N12=(unsigned long)(freq/80);
	//% FRACTIONAL VALUE (FRAC)
	//F25=(unsigned long)(((freq/80-N12)*pow(2.,25))+0.5);
	//%fprintf('%f\n',F25);

	C3=0;
	REG[0]=C3+((F25>>13)<<3)+(N12<<15)+(M4<<27)+(R1<<31);
	//%fprintf('%lx\n',REG(1));

	C3=1;
	REG[1]=C3+(P12<<3)+((F25&0x1fff)<<15)+(PA1<<28);
	//%fprintf('%lx\n',REG(2));

	C3=2;
	REG[2]=C3+(D1_12<<3)+(R5<<15)+(U1_1<<20)+(U2_1<<21)+(PS1<<22)+(CPI4<<24)+(CR1<<28);
	//%fprintf('%lx\n',REG(3));

	C3=3;
	REG[3]=C3+(U7_1<<3)+(U8_1<<4)+(U9_1<<5)+(U10_1<<6)+(U11_1<<7)+(FSK1<<8)+(PSK1<<9)
		   +(RM2<<10)+(U12_1<<14)+(NS1<<15)+(L1<<16)+(DB17<<17)+(NB1<<21)+(NB3<<22);
	//%fprintf('%lx\n',REG(4));

	C3=4;
	REG[4]=C3+(CS1<<6)+(D2_12<<7)+(C2<<19)+(RS5<<21)+(S5<<26)+(LS1<<31);
	//%fprintf('%lx\n',REG(5));

	C3=5;
	REG[5]=C3+(D16<<3)+(DO4<<19)+(DS1<<23)+(DR1<<24)+(FSKR1<<25)+(I2<<26)+(PR1<<28)+(TR1<<29)+(TI1<<30);
	//%fprintf('%lx\n',REG(6));

	C3=6;
	REG[6]=C3+(S20<<3)+(SSE1<<23);
	//%fprintf('%lx\n',REG(7));

	C3=7;
	REG[7]=C3+(DS12<<3)+(DSE1<<15)+(DC1<<16)+(RD1<<17)+(RDF1<<18)+(FR1<<19)+(TDT1<<20)
		 +(ST1<<21)+(TD1<<22)+(TDTD1<<23);
	//%fprintf('%lx\n',REG(8));


	return(0);


}

