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
    printf("\n\nGENERATION CHALLENGE\n\n");
    printf("Key : %s\nPlain_s : %s\nPlain_r : %s\nCipher_s : %s\nCipher_r :%s\n",key,plain_s,plain_r,cipher_s,cipher_r);
}

void attack(char * cipher_r, char * cipher_s){
    char xored_ciphers[SIZE];
    Xor(cipher_r, cipher_s, xored_ciphers);
    char xored_plains[SIZE];
    char keys_candidates[4][SIZE];
    for (int i=0; i<NB_MSG-1; i++)
      for (int j=i+1; j<NB_MSG; j++) {
        Xor(tabl[i], tabl[j], xored_plains);
        if (!strcmp(xored_plains,xored_ciphers)){
          printf("Found message 1 : \"%s\" and 2 \"%s\"\n", tabl[i], tabl[j]);
          printf("Possible keys :\n");
          Xor(tabl[i], cipher_r, keys_candidates[0]);
          Xor(tabl[i], cipher_s, keys_candidates[1]);
          Xor(tabl[j], cipher_r, keys_candidates[2]);
          Xor(tabl[j], cipher_s, keys_candidates[3]);
          for(int k=0; k<4;k++){
            printf("%s\n",keys_candidates[k]);
          }
          break;
        }
      }
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
