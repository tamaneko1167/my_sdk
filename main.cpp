#include "stdafx.h"
#include "sample.h"
#include "unistd.h"

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
	fgets(str, 100, stdin);
	sscanf(str, "%d", &Number);

	switch(Number){
		case 0:
		{
			printf("Preparing USB port\n");

    		Sample* sample1 = new Sample();
    		sample1->usbOpen();
			int blockNum = sample1->blockNum;
			int adDataNum=sample1->adDataNum;
			printf("%d %d\n", blockNum, adDataNum);
	
			for(int i = 0; i < 20; i++){
				sample1->usbReq(); //1データ分（指定ブロック数分）のデータを要求するコマンドをUSBポートに送信
				for(int n = 0; n < blockNum; n++){
					sample1->usbRead(n); //各ブロックのデータを、usbオブジェクト→adDataオブジェクトに格納。生データファイルにも保存。
				}
				//sleep(1);
			}
			sample1->usbClose();
			delete sample1;
			printf("dat file saved\n");
			break;
		}

		case 1:
		{
			printf("Load Raw Data\n");

			Sample* sample1 = new Sample();
			sample1->loadOpen();
			int adDataNum=sample1->adDataNum;
			int chNum=sample1->chNum;
			int blockNum=sample1->blockNum;
			while((sample1->load())==0){
				sample1->raw1->csvFileWrite();
			}
			sample1->loadClose();

			sample1->fftOpen();
			while((sample1->fft())==0){
				for(int m = 0; m < chNum; m++){
					for(int n = 0; n < blockNum; n++){
						sample1->fft1->fftExe(n, m);
						sample1->fft1->fftExe(n, m + chNum);
					}
				}
				sample1->fft1->csvFileWrite();
			};
			sample1->fftClose();
	
			delete sample1;
			printf("rawdata and fftdata saved\n");
			break;
		}
	}
	printf("%lf\n", (double)clock()/CLK_TCK);
	printf("completed\n");
	return 0;
}