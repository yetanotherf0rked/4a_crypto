// Client : Alice


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include "encrypt.h"

void error(char *msg)
{
    perror(msg);
    exit(0);
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
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    /** printf("Please enter the message: "); */
    /** bzero(buffer,256); */
    /** fgets(buffer,255,stdin); */

    // ENVOI D UN MESSAGE
    /** n = write(sockfd,buffer,strlen(buffer)); */

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

    // on définit les paramètres g, p et a d'alice
    alice.g = 3;
    alice.p = 23;
    long long int a = 6;

    // on calcule A
    alice.A = modexp(alice.g, a, alice.p);

    // on envoie (g, p, A)
    n = write(sockfd, (void *)&alice,sizeof(clientkey));
    if (n < 0) 
         error("ERROR writing to socket");

    /** bzero(buffer,256); */

    // on reçoit B
    n = read(sockfd,(void *)&bob,sizeof(serverkey));
    if (n < 0) 
         error("ERROR reading from socket");

    // on calcule et on affiche K
    long long int K = modexp(bob.B, a, alice.p);
     printf("K = %d\n", K); 

    // QUESTION 7 : envoi d'un paquet chiffré
    // Saisie du message
     printf("Please enter the message: ");
     bzero(buffer,256);
     fgets(buffer,255,stdin);

    // Chiffrement du message
     char cipher[256];
     bzero(cipher,256);
     char key[sizeof(long long int)+1];
     sprintf(key, "%d", K);
     des_encipher(buffer, cipher, key);


    // Envoi du message chiffré
    n = write(sockfd, cipher, strlen(cipher));
    if (n < 0) 
         error("ERROR writing to socket");

    return 0;
}
