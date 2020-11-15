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

CIBLES	=	test_des

all: $(CIBLES)

clean: 
	$(RM) -f core *.o $(CIBLES) *~


test_des: test_des.o des.o bit.o 
	$(CC) $(CFLAGS) -o $@ test_des.o bit.o  $(LIBS)

test_des.o: test_des.c
		$(CC) $(CFLAGS) -c test_des.c

des.o: des.c
		$(CC) $(CFLAGS) -c des.c

bit.o: bit.c
		$(CC) $(CFLAGS) -c bit.c
