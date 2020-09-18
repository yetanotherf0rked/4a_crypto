#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define SIZE 11
#define NB_MSG 10

char tabl[NB_MSG][SIZE] = {
    "TP1 18/09", 
    "bonjour..", 
    "Hello! ;)", 
    "ça va ?? ", 
    "crypto <3", 
    "4A -- STI", 
    "I <3 info", 
    "message  ", 
    "secret ??", 
    "Vigenère "
};

void Xor(char * x, char * y, char * z){
    int i = 0;
    for (i=0; x[i]!='\0'; i++)
        z[i]=x[i]^y[i];
    z[i] = '\0';
}

void dist(char *x, char *y, char *z){
    int i = 0;
    for (i=0; x[i]!='\0'; i++)
        z[i]=abs(x[i]-y[i]);
    z[i] = '\0';
}
void encrypt(char * key, char * plain, char * cipher){
    Xor(plain, key, cipher);
}

void decrypt(char * key, char * plain, char * cipher){
    Xor(cipher, key, plain);
}

void generate_challenge(char * cipher_r, char * cipher_s){
    
    // On génère une clé aléatoire :
    char key[SIZE];
    int i;
    for (i = 0; i < SIZE - 1; i ++){
        int c = 33 +(rand() % 92); // 33 -> 125 caractères affichables
        key[i] = c;
    }
    key[i] = '\0';

    // On choisit deux mots au hasard du tableau tabl
    char plain_r[SIZE];
    char plain_s[SIZE];
    int ind_r = rand()%10;
    int ind_s;
    do {
        ind_s = rand()%10;
    } while(ind_s == ind_r);

    strcpy(plain_r, tabl[ind_r]);
    strcpy(plain_s, tabl[ind_s]);

    // On chiffre 
    encrypt(key, plain_r, cipher_r);
    encrypt(key, plain_s, cipher_s);

    // Sortie standard :
    print("\n\nGENERATION CHALLENGE\n\n");
    printf("Key : %s\nPlain_s : %s\nPlain_r : %s\nCipher_s : %s\nCipher_r :%s\n",key,plain_s,plain_r,cipher_s,cipher_r);
}

void attack(char * cipher_r, char * cipher_s){
    // Pour chaque mot, on compare la distance entre les lettres de cipher_r et
    // cipher_s et après on compare les résultats
    int i, j, dist_r[NB_MSG][SIZE],dist_s[NB_MSG][SIZE];
    // soit i le nombre de messages
    for (i=0;i<NB_MSG;i++)
       dist(key, cipher_r, dist_r[i]);
}


int main(int argc, char *argv[]) {
    srand( time( NULL ) );
    
    char key[SIZE]; // Key generator
    int i;
    for (i = 0; i < SIZE - 1; i ++){
        int c = 33 +(rand() % 92); // 33 -> 125 caractères affichables
        key[i] = c;
    }
    key[i] = '\0';
    
    char plain[SIZE]; // Plaintext
    printf("Message à chiffrer :\n");
    scanf("%s", plain);
    
    char plainRes[SIZE];
    char cipher[SIZE];
    plainRes[0] = '\0';
    cipher[0] = '\0';
    
    encrypt(key, plain, cipher); 
    decrypt(key, plainRes, cipher);
    
    printf("Clé : %s \nMessage : %s \nChiffré : %s \nDéchiffré : %s \n", key, plain, cipher, plainRes);
    
    char cipher_r[SIZE];
    char cipher_s[SIZE];
    
    generate_challenge(cipher_r,cipher_s);
    attack(cipher_r,cipher_s);
    
    return 0;
}
