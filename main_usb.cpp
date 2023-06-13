#include "stdafx.h"
#include "sample.h"
#include "unistd.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>

void Sleep(double t)
{
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = (long)(t*1000000.);
	nanosleep(&ts, NULL);
}

int main(int argc, char* argv[])
{
	printf("Preparing USB port\n");

    Sample* sample1 = new Sample();
    sample1->usbOpen();
	int blockNum = sample1->blockNum;
	int adDataNum=sample1->adDataNum;
	int chNum=sample1->chNum;
	printf("%d %d\n", blockNum, adDataNum);
	
	for(int i = 0; i < 500; i++){
		sample1->usbReq(); //1データ分（指定ブロック数分）のデータを要求するコマンドをUSBポートに送信
		for(int n = 0; n < blockNum; n++){
			sample1->usbRead(n); //各ブロックのデータを、usbオブジェクト→adDataオブジェクトに格納。生データファイルにも保存。
		}
		//sleep(1);
	}
	sample1->usbClose();
	printf("dat file saved\n");

	string flag;
	flag = cin.get();
	
	printf("Load Raw Data\n");
	sample1->loadOpen();

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
	rename("./data.dat", "./../send/data.dat");
	rename("./raw_data.csv", "./../send/raw_data.csv");
	rename("./fft_data.csv", "./../send/fft_data.csv");
	
	char parent_dir[] = "./../send";
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);
	char now_time[128]="";
	sprintf(now_time,"%02d-%02d-%02d-%02d-%02d/",pnow->tm_mon+1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);

	char parent_dir2[] = "/media/pi/ESD-USB";
	stringstream command;
	command << "cd " << parent_dir2 << " && mkdir " << now_time;
    system(command.str().c_str());
	stringstream command2;
	command2 << "cd " << parent_dir << " && mv data.dat raw_data.csv fft_data.csv " << parent_dir2 << now_time;
	system(command2.str().c_str());

	printf("%lf\n", (double)clock()/CLK_TCK);
	printf("completed\n");
	return 0;
}