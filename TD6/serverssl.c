#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"
#include "sys/socket.h"

#include "stdio.h"
#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>

#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>

#define SERV_TCP_PORT   7000
#define SERV_HOST_ADDR	"127.0.0.1"	/* host addr for server */

int sockfd;

int main()
{
	SSL * ssl;
	SSL_CTX * ctx;
	int err;
	int			 newsockfd, clilen;
	struct sockaddr_in	cli_addr, serv_addr;
	


	/* Set up the library */
	ERR_load_BIO_strings();
	SSL_load_error_strings();
	SSL_library_init();


	/* Set up the SSL context */
	ctx = SSL_CTX_new(SSLv23_method());
	if (! ctx){
		SSL_load_error_strings();
		ERR_print_errors_fp(stderr);
		return 0;
	}

	/* Set the certificate to be used */
	printf("Load certificate\n");
	if(! SSL_CTX_use_certificate_file(ctx, "ssl_new/certs/server.crt", SSL_FILETYPE_PEM))
	{
		fprintf(stderr, "Error loading trust store\n");
		ERR_print_errors_fp(stderr);
		SSL_CTX_free(ctx);
		return 0;
	}

	/*Load the password for the Private Key*/
	printf("Load private key\n");
	SSL_CTX_set_default_passwd_cb_userdata(ctx,"");

	/*Indicate the key file to be used*/
	if (SSL_CTX_use_PrivateKey_file(ctx, "ssl_new/private/server.key", SSL_FILETYPE_PEM) <= 0) {
		printf("Error setting the key file.\n");
		exit(0);
	}


	/*Make sure the key and certificate file match*/
	if (!SSL_CTX_check_private_key(ctx)) {
		printf("Private key does not match the certificate public key\n");
		exit(0);
	}

	/*Used only if client authentication will be used*/
	SSL_CTX_set_verify(ctx,SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT,NULL);

	/* Set the list of trusted CAs based on the file and/or directory provided*/
	if(SSL_CTX_load_verify_locations(ctx,"ssl_new/certs/ca.crt",NULL)<1){
		printf("Error setting the verify locations.\n");
		exit(0);
	}

	/*Create new ssl object*/
	ssl=SSL_new(ctx);

	if(!ssl){
		printf("Error creating SSL structure.\n");
		exit(0);
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("server: can't open stream socket\n");

	/*
	 * 	 * Bind our local address so that the clien can send to us.
	 * 	 	 */

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	serv_addr.sin_port		= htons(SERV_TCP_PORT);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		printf("server: can't bind local address\n");

	listen(sockfd, 5);

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
			&clilen);
	if (newsockfd < 0)
		printf("server: accept error\n");



	/* Bind the ssl object with the socket*/
	SSL_set_fd(ssl, newsockfd);

	/*Do the SSL Handshake*/
	err=SSL_accept(ssl);

	/* Check for error in handshake*/
	if (err<1) {
		err=SSL_get_error(ssl,err);
		printf("SSL error #%d in accept,program terminated\n",err);
		SSL_CTX_free(ctx);
		exit(0);
	}

	/*Print out connection details*/
	printf("SSL connection on socket %x,Version: %s, Cipher: %s\n",
			newsockfd,
			SSL_get_version(ssl),
			SSL_get_cipher(ssl));

	
	//TODO TRAITEMENT DU SERVEUR
	char buf[] = "Hello world";
	if(SSL_write(ssl, buf, sizeof(buf))<=0){
		err=SSL_get_error(ssl,err);
		printf("SSL write error\n");
		SSL_CTX_free(ctx);
		exit(0);
	}

	SSL_free(ssl);
	close(newsockfd);
	SSL_CTX_free(ctx);
	exit(0);

}
