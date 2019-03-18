build: main.c ./Interface/interface.c ./List/list.c
	gcc -Wall main.c ./Interface/interface.c ./List/list.c -o main

clean:
	rm main