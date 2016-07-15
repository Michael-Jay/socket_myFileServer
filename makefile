all: c s 
.PHONY:all

c:client.c
	gcc client.c -o c
s:server.c
	gcc server.c -o s
