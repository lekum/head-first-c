test_code: encrypt checksum
	gcc -o test_code.out test_code.c encrypt.o checksum.o

encrypt: encrypt.c encrypt.h
	gcc -c encrypt.c -o encrypt.o

checksum: checksum.c checksum.h
	gcc -c checksum.c -o checksum.o
