#include <stdio.h>
#include <stdlib.h>

#define KEY_LENGTH 4

void generate_key(char * key){
  int i = 0;
  for (i=0; i<KEY_LENGTH; i++)
    key[i] = 'A' + rand() % 26;
  key[i] = '\0';
}
int main()
