#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100
#define INC 0
#define DEC 1

char * str = "LESUJETDECETPSERALETUDEDESCHIFFREMENTSDEBASE";

char cyclicIncrementDecrement(char ch, int amount, int mode)
{
    int newValue = (mode) ? (int)ch-(amount%26) : (int)ch+(amount%26);
    if (newValue < 'A') newValue += 26;
    if (newValue > 'Z') newValue -= 26;
    return (char)newValue;
}

void toupper_string(char * str){
  int i=0;
  while(str[i]) {
    str[i]=(char)toupper(str[i]);
    i++;
  }
}

int max(int * arr, int len){
  int max = arr[0];
  int ind;
  for (int i=0;i<len;i++)
    if (max<arr[i]){
      max = arr[i];
      ind = i;
    }
  return ind;
}

void encrypt(int key, char * plain, char * cipher){
  strcpy(cipher, plain);
  for(int i=0;cipher[i]!='\0';i++)
    cipher[i] = cyclicIncrementDecrement(cipher[i], key, INC);
}

void decrypt(int key, char * plain, char * cipher){
  strcpy(plain, cipher);
  for(int i=0;plain[i]!='\0';i++)
    plain[i] = cyclicIncrementDecrement(cipher[i], key, DEC);
}

void generate_challenge(char * cipher){
  int key = rand() % 26; // Key generator
  encrypt(key, str, cipher);
  printf("Key : %i\nPlain : %s\nChiffré : %s\n",key,str,cipher);
}

void attack(char * cipher){
  int alphabet[26] = {0};
  for (int i=0;cipher[i]!='\0';i++){
    alphabet[cipher[i]-'A']++; 
  }

  int guessed_key = (max(alphabet, 26)-('E'-'A')) % 26;
  printf("La clé est %i\n", guessed_key);
  
  char plain[SIZE];
  strcpy(plain, cipher);
  for (int i =0;plain[i]!='\0';i++)
    plain[i]=cyclicIncrementDecrement(plain[i], guessed_key, DEC);
  printf("Déchiffré : %s\n",plain);
}


int main(int argc, char *argv[]) {
    srand( time( NULL ) );
    int key = rand() % 26; // Key generator
    
    char plain[SIZE]; // Plaintext
    printf("Message à chiffrer :\n");
    scanf("%s", plain);
    toupper_string(plain);
    
    char plainRes[SIZE];
    char cipher[SIZE];
    plainRes[0] = '\0';
    cipher[0] = '\0';
    
    encrypt(key, plain, cipher); 
    decrypt(key, plainRes, cipher);
    
    printf("Clé : %i \nMessage : %s \nChiffré : %s \nDéchiffré : %s \n", key, plain, cipher, plainRes);
    
    generate_challenge(cipher);
    attack(cipher);
    
    return 0;
}
