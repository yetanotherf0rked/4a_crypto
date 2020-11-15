#
##

CC	=	gcc 
CFLAGS	=  	-Wall
CFLAGS  += 	-DDEBUG -D_GNU_SOURCE
CFLAGS  += 	-g

PREFIX ?= 	${DESTDIR}/usr
LIBDIR	=	${PREFIX}/lib
INCDIR	=	${PREFIX}/include 
LIBS    =       -lm

CIBLES	=	client server

all: $(CIBLES)

clean: 
	$(RM) -f core *.o $(CIBLES) *~


client: client.o des.o bit.o 
	$(CC) $(CFLAGS) -o $@ client.o des.o bit.o  $(LIBS)

server: server.o des.o bit.o 
	$(CC) $(CFLAGS) -o $@ server.o des.o bit.o  $(LIBS)

server.o: server.c
		$(CC) $(CFLAGS) -c server.c

client.o: client.c
		$(CC) $(CFLAGS) -c client.c

des.o: des.c
		$(CC) $(CFLAGS) -c des.c

bit.o: bit.c
		$(CC) $(CFLAGS) -c bit.c
