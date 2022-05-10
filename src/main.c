#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "magnitude.h"
#include "utils.h"


// gcc main.c utils.c magnitude.c stft.c -lfftw3 -lm
// ./a.out blues.00000.wav test.txt


int main(int argc,char* argv[]) {

if (argc < 2) {
      printf("No out file specified\n");
      return 1;
    }



int height;
int width;
FILE* f=fopen(argv[1], "wb");
double* magn;
double* magncorr;
char* genres[] = {"../../genres/blues/blues.00000.wav","../../genres/classical/classical.00000.wav","../../genres/country/country.00000.wav","../../genres/disco/disco.00000.wav","../../genres/hiphop/hiphop.00000.wav","../../genres/jazz/jazz.00000.wav","../../genres/metal/metal.00000.wav","../../genres/pop/pop.00000.wav","../../genres/reggae/reggae.00000.wav","../../genres/rock/rock.00000.wav"};


for (int i = 0 ; i<10 ; i++) { // Boucle sur les 10 genres
int len_temp=strlen(genres[i]); // +10 caractères car on ajoute ".00000.wav"
char temp[len_temp];
strcpy(temp,genres[i]); // temp contiendra le nom de la musique numéro l du genre i


for (int l=0 ; l<100 ; l++) { // Boucle sur le numéro de la musique
    char c1 = l%10 + '0'; // Chiffre des unités
    char c2 = (l%100 - l%10)/10 + '0'; // Chiffre des dizaines
    temp[len_temp-1-4]=c1;
    temp[len_temp-2-4]=c2;
    magn = magnitude(temp, &height, &width);
    magncorr=reduction_vect(magn, height, width);
    fprintf(f, "%d; ", i);
    for(int k=0; k<height*2; k++){fprintf(f, "%f; ", magncorr[k]);}
    fprintf(f, "\n");
  }   
}
}
