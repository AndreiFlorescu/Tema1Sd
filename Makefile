build: main.c ./Interface/interface.c ./List/list.c ./Tasks/tasks.c
	gcc -Wall main.c ./Interface/interface.c ./List/list.c ./Tasks/tasks.c -o tema1 -lm

clean:
	rm tema1