
#include <iostream>
#include <complex>
using namespace std;

//===== FftCalc Class =========================================================

class FftCalc{
public:
	FftCalc(){};
	~FftCalc(){
		delete g_;
	};
	FftCalc(int numberOfPoints);
	void				fftExe(complex<double>* xn, complex<double>* u_);
protected:
	void				Execute(complex<double>* xn);
	int					Reorder(int n); 
	complex<double>*	TwiddleFactor();
	int*				BitReverse();
	void				ErrorMessage(string message);
	int					nFft_;		// FFT の点数
	int					mask_;		// IFFT の場合に Reorder() で使用
	double				nInverse_;	// FFT の点数の逆数
	complex<double>*	wTable_;	// 回転子用
	int*				bTable_;	// ビット逆順用
	complex<double>*	g_;			// 作業領域

};
