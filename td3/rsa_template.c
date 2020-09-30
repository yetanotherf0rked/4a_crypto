#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef unsigned long long int huge;

static huge modexp(huge a, huge b, huge N) {
    return 1;
}
static huge RSAcrypt(huge m, huge e, huge N) {
    return 1;
}
static huge RSAdecrypt(huge c, huge d, huge N) {
    return 1;
}
// static huge pgcd(huge a, huge b){
// }
// void  bezout(huge a, huge b, huge N, huge* u, huge* v){
// }
// void keyGen(huge p, huge q, huge * N, huge * e, huge * d){
// }

int main()
{
    huge N = 4247;
    huge e = 967;
    huge d = 2983;
    huge m = 3;
    
    srand((unsigned)time(NULL));
    printf("-taille short = %d\n", (int) sizeof( short ));
    printf("-taille unsigned short = %d\n",  (int) sizeof( unsigned short ));
    printf("-taille int = %d\n", (int) sizeof( int ));
    printf("-taille unsigned int = %d\n",  (int) sizeof( unsigned int ));
    printf("-taille long int = %d\n", (int) sizeof( long int ));
    printf("-taille unsigned long int = %d\n",  (int) sizeof( unsigned long int ));
    printf("-taille long long int = %d\n", (int) sizeof( long long int ));
    printf("-taille unsigned long long int = %d\n", (int) sizeof( unsigned long long int ));

    printf("N=%lld,e=%lld,d=%lld\n",N,e,d);
    printf("m=%lld\n",m);
    printf("RSAcrypt(m,e,N)=%lld\n",RSAcrypt(m,e,N));
    printf("RSAdecrypt(c,d,N)=%lld\n",RSAdecrypt(RSAcrypt(m,e,N),d,N));
    
    huge p = 51109; 
    huge q = 51131; 
    huge u,v;
    
//     keyGen(p,q,&N,&e,&d);
//     
//     printf("N=%lld,e=%lld,d=%lld\n",N,e,d);
//     printf("m=%lld\n",m);
//     printf("RSAcrypt(m,e,N)=%lld\n",RSAcrypt(m,e, N));
//     printf("RSAdecrypt(c,d,N)=%lld\n",RSAdecrypt(RSAcrypt(m,e,N),d,N));

    return 1;
}

