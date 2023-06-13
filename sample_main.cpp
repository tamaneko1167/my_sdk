
#include "stdafx.h"
#include "sample.h"

void Sleep(double t)
{
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = (long)(t*1000000.);
	nanosleep(&ts, NULL);
}

int main(int argc, char* argv[])
{
	int Number;
	char str[100];

	printf("Input number: ");
	fgets(str,100,stdin);
	sscanf(str,"%d",&Number);

	switch (Number){
		case 0:		
		{			
			printf("Preparing USB Port\n");

			Sample* sample1 = new Sample(); //Sampleオブジェクト生成

			sample1->usbOpen(); //miRadarモジュールの設定
			int adDataNum=sample1->adDataNum, chNum=sample1->chNum, blockNum=sample1->blockNum;

			printf("Reading USB Data\n");

			for(int p=0;p<100;p++){
				sample1->usbReq();
				for(int m=0;m<blockNum;m++){
					sample1->usbRead(m);
					//printf("%lf %s\n",(double)sample1->usb1->getClock()/CLK_TCK,ctime(sample1->usb1->getTime()));
				}
			};
			
			sample1->usbClose();
			delete sample1;
			break;
		}

		case 1:			
		{ 
			printf("Load Raw Data\n");

			Sample* sample1 = new Sample();

			sample1->loadOpen();
			int adDataNum=sample1->adDataNum, chNum=sample1->chNum, blockNum=sample1->blockNum;

			while((sample1->load())==0){
				sample1->raw1->csvFileWrite();
				//Printf("%lf %s\n",(double)sample1->raw1->getClock()/CLK_TCK,ctime(sample1->raw1->getTime()));
			};

			sample1->loadClose();
			delete sample1;
			break;
		}

		case 2:			
		{				
			printf("Load Raw Data\n");

			Sample* sample1 = new Sample();

			sample1->fftOpen();
			int adDataNum=sample1->adDataNum, chNum=sample1->chNum, blockNum=sample1->blockNum;

			while((sample1->fft())==0){
				//Printf("%lf %s\n",(double)sample1->raw1->getClock()/CLK_TCK,ctime(sample1->raw1->getTime()));
				for(int n=0;n<chNum;n++){
					for(int m=0;m<blockNum;m++){
						sample1->fft1->fftExe(m, n);
						sample1->fft1->fftExe(m, n+chNum);
					}
				}
				sample1->fft1->csvFileWrite();
			};

			sample1->fftClose();
			delete sample1;
			break;
		}

	}

	printf("completed\n");
	getchar();

}

