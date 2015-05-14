
encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c -o encrypt.o

checksum.o: checksum.c checksum.h
	gcc -c checksum.c -o checksum.o

libhfsecurity.a: encrypt.o checksum.o
	ar -rcs libhfsecurity.a encrypt.o checksum.o

test_code: libhfsecurity.a  test_code.c
	gcc -o test_code.out test_code.c -I. -L. -lhfsecurity
