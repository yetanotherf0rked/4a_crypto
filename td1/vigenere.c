#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100
#define LONG_SIZE 300
#define SMALL_SIZE 11
#define INC 0
#define DEC 1
#define KEY_LENGTH 9
#define MAX_KEY_LENGTH 50
#define NB_MSG 10

char * str = "LESUJETDECETPSERALETUDEDESCHIFFREMENTSDEBASEILAFALLUPLUSIEURSSIECLESAVANTDEDECOUVRIRUNEATTAQUEEFFICACEAUCHIFFREMENTDEVIGENEREMERCIMONSIEURKAISISKITESLEMEILLEURBROCHANGEPASLEMOTEURLOVE";

char tabl[NB_MSG][SMALL_SIZE] = {
    "TPAZERTYY", 
    "BONJOURRR", 
    "HELLOOOOO", 
    "CAVAAAAAA", 
    "CRYPTOOOO", 
    "QUATRESTI", 
    "ILOVEINFO", 
    "MESSAGEPT", 
    "SECREEEET", 
    "VIGENEREU"
};

int pgcd(int nbr1, int nbr2){
    int pgcd, i;
  
    for(i=1; i <= nbr1 && i <= nbr2; ++i)
    {
        if(nbr1%i==0 && nbr2%i==0)
            pgcd = i;
    }

    /** printf("pgcd(%d,%d) = %d", nbr1,nbr2,pgcd);  */
    return pgcd;
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

int most_likely_pgcd(int * nbr, int len){
  int pgcds[MAX_KEY_LENGTH] = {0};
  for(int i = 0;i<len-1 && nbr[i]!=-1;i++){
    if (i==-1)
      break;
    for (int j=i;j<len && nbr[j]!=-1;j++){
      int my_pgcd =pgcd(nbr[i],nbr[j]);
      if (my_pgcd != 1)
        pgcds[my_pgcd]++;
    }
  }
  /** for (int i=0;i<MAX_KEY_LENGTH;i++) */
  /**     printf("%d : %d\n", i, pgcds[i]); */
  return max(pgcds, MAX_KEY_LENGTH);
}

void find_repeated_substrings_within_string(char * str){
  
  int len = strlen(str);

  // On sauvegarde les indices d'apparition de chaque lettre dans un tableau
  int alphabet_ind[26][30];
  // On initialise chaque case par -1. Si une case vaut -1, càd que ce n'est pas
  // un indice ou bien que c'est une case vide
  memset((void *)alphabet_ind, -1, 30*26*sizeof(int));
  printf("Redondances :\n");
  int distances[20];
  memset((void *)distances, -1, 20*sizeof(int));

  // Pour chaque lettre du mot chiffré
  for(int i=0;i<len;i++){
    int j = 0;
    int actual_letter = str[i] - 'A';

    // On enregistre l'indice d'apparition de la lettre dans le tableau
    // alphabet_ind
    while(1){
      if(alphabet_ind[actual_letter][j] == -1){
        alphabet_ind[actual_letter][j] = i;
        break;
      }
      j++;
    }

    // si on rencontre une lettre déjà flagée et dont l'indice est différent
    j = 1;
    while(alphabet_ind[actual_letter][j] != -1 && alphabet_ind[actual_letter][j] != i){
      int k = 0;
      // on compare les lettres qui suivent à la recherche d'un pattern
      while(str[i+k] == str[alphabet_ind[actual_letter][j]+k]){
        k++;
      }
      // si le pattern fait au moins 3 lettres, on l'affiche
      if (k>2){
        for (int l=0;l<k;l++)
          printf("%c", str[l+i]);
      // et on enregistre la distance entre les deux apparitions
        int l = 0;
        while (1){
          if (distances[l] == -1){
            distances[l] = i-alphabet_ind[actual_letter][j];
            break;
          }
          l++;
        }
        printf(" (%d)\n",distances[l]);
      }
      j++;
    }
  }

  // debug distances
  /** for (int i=0 ; i<20 ; i++) { */
  /**   printf("%d\t",distances[i]); */
  /** } */
  /** printf("\n\n"); */

  printf("Most likely key size : %d",most_likely_pgcd(distances, 20));

  // affichage des indices
  /** for (int i=0;i<26;i++){ */
  /**   printf("%c :", 'A' + i); */
  /**   for (int j=0;j<30;j++) */
  /**     if (alphabet_ind[i][j] != -1) */
  /**       printf("%d, ", alphabet_ind[i][j]); */
  /**   printf("\n"); */
  /** } */
}

char * generate_key(int len){
  char * key = malloc((len+1)*sizeof(char));
  int i=0;
  for (i=0;i<len;i++)
    key[i] = 'A' + rand() % 26;
  key[i] = '\0';
  return key;
}

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


void encrypt(char * key, char * plain, char * cipher){
  strcpy(cipher, plain);
  int key_len = strlen(key);
  for(int i=0;cipher[i]!='\0';i++)
    cipher[i] = cyclicIncrementDecrement(cipher[i], key[i%key_len] - 'A', INC);
}

void decrypt(char * key, char * plain, char * cipher){
  strcpy(plain, cipher);
  int key_len = strlen(key);
  for(int i=0;plain[i]!='\0';i++)
    plain[i] = cyclicIncrementDecrement(cipher[i], key[i%key_len] - 'A', DEC);
}

void generate_challenge_1(char * cipher_r, char * cipher_s){
  char * key = generate_key(KEY_LENGTH);
  char plain_r[SMALL_SIZE], plain_s[SMALL_SIZE];
  strcpy(plain_r,tabl[rand() % NB_MSG]);
  strcpy(plain_s,tabl[rand() % NB_MSG]);
  encrypt(key, plain_r, cipher_r);
  encrypt(key, plain_s, cipher_s);
  printf("\nCHALLENGE 1\n\n");
  printf("Key : %s\nPlain_r : %s\nPlain_s : %s\nCipher_r : %s\nCipher_s : %s\n",key, plain_r, plain_s,cipher_r,cipher_s);
}

void attack_1(char * cipher_r,char * cipher_s){

}

void generate_challenge_2(char * cipher){
  char * key = generate_key(KEY_LENGTH);
  encrypt(key, str, cipher);
  printf("\nCHALLENGE 2\n\n");
  printf("Key : %s\nPlain : %s\nChiffré : %s\n",key,str,cipher);
}

void attack_2(char * cipher){
    find_repeated_substrings_within_string(cipher);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char * key = generate_key(KEY_LENGTH);
    
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
    
    printf("Clé : %s \nMessage : %s \nChiffré : %s \nDéchiffré : %s \n", key, plain, cipher, plainRes);
    
    char cipher_r[SIZE];
    char cipher_s[SIZE];
    generate_challenge_1(cipher_r, cipher_s);
    attack_1(cipher_r,cipher_s);
    generate_challenge_2(cipher);
    attack_2(cipher);

    return 0;
}
