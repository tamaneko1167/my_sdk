compile:
	g++ main.cpp sdk1.cpp fft.cpp fastRampPll.cpp libftd2xx.a -lpthread -ldl -lrt;
compile_l:
	g++ main_l.cpp sdk1.cpp fft.cpp fastRampPll.cpp libftd2xx.a -lpthread -ldl -lrt;

unload:
	sudo rmmod ftdi_sio
	sudo rmmod usbserial
	sudo ./a.out
run:
	sudo ./a.out

raspush:
	git add .
	git commit -m "ras"
	git push origin master

winpush:
	git add .
	git commit -m "win"
	git push origin master

macpush:
	git add .
	git commit -m "mac"
	git push origin master

pull:
	git pull origin master