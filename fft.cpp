
#include "stdafx.h"


FftCalc :: FftCalc(int numberOfPoints)
{
	nFft_ = numberOfPoints;

	if (nFft_ < 2) ErrorMessage("データ数が２以上");
	int pw2 = nFft_;
	while ((pw2 & 0x1) == 0) pw2 = pw2 >> 1;
	if (!(pw2 == 0x1)) ErrorMessage("データ数が２のべき乗");

	mask_ = nFft_ - 1;
	nInverse_ = 1.0/nFft_;

	wTable_ = TwiddleFactor();	// 回転子の数表を取得
	bTable_ = BitReverse();		// ビット逆順の数表を取得

	g_ = new complex<double>[nFft_];
	//u_ = new complex<double>[nFft_];
}


// FFT の実行
//		xn		： 入力データ（複素信号）
//		u_		： FFT の結果（複素数）
void FftCalc :: fftExe(complex<double>* xn, complex<double>* u_)
{
	//if (xn->Length != nFft_) return 0;
	Execute(xn);
	// ビット逆順の並べ替え
	for (int n=0; n<nFft_; n++) u_[n] = g_[bTable_[n]];
}

// FFT の基本部分の実行
void FftCalc :: Execute(complex<double>* xn)
{
	for (int n=0; n<nFft_; n++) g_[n] = xn[n];
	int increment = nFft_;

	for (int stage=1; stage<nFft_; stage<<=1)
	{
		int half = increment/2;
		for (int m=0; m<nFft_; m+=increment)
		{
			int k = 0;
			for (int n=m; n<m+half; n++)
			{
				complex<double> tmp = g_[n];
				g_[n]	   =  tmp + g_[n+half];
				g_[n+half] = (tmp - g_[n+half])*wTable_[k];
				k = k + stage;
			}
		}
		increment = half;
	}
}

// IFFT の並べ替え用
int FftCalc :: Reorder(int n) { return bTable_[(nFft_-n) & mask_]; }

// 回転子の数表作成
complex<double>* FftCalc :: TwiddleFactor()
{
	double pi = 3.14159265359;
	complex<double> arg = -2.0*pi*(complex<double>(0.,1.))*nInverse_;
	complex<double>* w = new complex<double>[nFft_/2];
	for (int k=0; k<nFft_/2 ;k++) w[k] = exp(arg*(double)k);
	return w;
}

// ビット逆順の並べ替え用の数表作成
int* FftCalc :: BitReverse()
{
	int offset = nFft_ >> 1;
	int* br = new int[nFft_];
	br[0] = 0;
	for (int n=1; n<nFft_; n<<=1)
	{
		for (int k=0; k<n; k++) br[k+n] = br[k] + offset;
		offset = offset >> 1;
	}
	return br;
}

// エラーメッセージを表示し，強制終了
void FftCalc :: ErrorMessage(string message)
{
	cout<<(message+"ではないので強制終了します", "エラー");
}

