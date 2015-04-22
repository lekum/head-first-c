message_hider: encrypt.o message_hider.o
	gcc encrypt.o message_hider.o -o message_hider.out

encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c

message_hider.o: message_hider.c encrypt.h
	gcc -c message_hider.c

