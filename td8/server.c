// Server : Bob

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "encrypt.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

static long long modexp(long long a, long long b, long long n) {
    long long y;
    y = 1;
    while (b != 0) {
        if (b & 1)
            y = (y * a) % n;
        a = (a * a) % n;
        b = b >> 1;
    }
    return y;
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);

     // QUESTION 6 : échange des clés
     // définition des structures
     typedef struct clientkey{
       long long int g;
       long long int p;
       long long int A;    
     } clientkey;
     clientkey alice;

     typedef struct serverkey{
       long long int B;
     } serverkey;
     serverkey bob; 
    
     // b de Bob
     long long int b = 15;

     // on reçoit le triplet (g, p, A) d'alice
     n = read(newsockfd,(void *) &alice,sizeof(clientkey));
     if (n < 0) error("ERROR reading from socket");

     // on calcule B = g^b mod p
     bob.B = modexp(alice.g, b, alice.p);

     // on calcule la clé K = A^b mod p et on l'imprime
     long long int K = modexp(alice.A, b, alice.p);
     printf("K=%d\n", K); 

     // on envoie B à alice
     n = write(newsockfd, (void*) &bob, sizeof(serverkey));
     if (n < 0) error("ERROR writing to socket");

     // QUESTION 7 : réception d'un message chiffré
    // réception du message chiffré
    char cipher[256];
    bzero(cipher, 256);
    bzero(buffer, 256);
    n = read(newsockfd, cipher, sizeof(cipher)); 
    if (n < 0) error("ERROR reading from socket");

    // déchiffrement
    char key[sizeof(long long int) +1];
    sprintf(key, "%d", K);
    des_decipher(cipher, buffer, key);
    printf("Message reçu : %s", buffer);
    
     return 0; 
}
