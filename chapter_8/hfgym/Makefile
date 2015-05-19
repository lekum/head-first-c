elliptical.o: elliptical.c
	gcc -c elliptical.o elliptical.c -Iincludes

hfcal_uk: hfcal_UK.c
	gcc -c -fPIC hfcal_UK.c -Iincludes -o hfcal.o

hfcal: hfcal.c
	gcc -c -fPIC hfcal.c -Iincludes -o hfcal.o

libhfcal.so:
	gcc -shared -o libs/libhfcal.so hfcal.o

elliptical.out: libhfcal.so elliptical.o
	gcc -o elliptical.out elliptical.o -Llibs -lhfcal
