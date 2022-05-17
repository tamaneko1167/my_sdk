
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
	int					nFft_;		// FFT �̓_��
	int					mask_;		// IFFT �̏ꍇ�� Reorder() �Ŏg�p
	double				nInverse_;	// FFT �̓_���̋t��
	complex<double>*	wTable_;	// ��]�q�p
	int*				bTable_;	// �r�b�g�t���p
	complex<double>*	g_;			// ��Ɨ̈�

};
