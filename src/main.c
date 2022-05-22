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



int nRow;
int nCol;
FILE* f=fopen(argv[1], "wb");
double* magn=malloc(257*sizeof(double));
double* mean=malloc(257*sizeof(double));
double* std;
double*magncorr;
char* genres[] = {"../../genres/blues/blues.00000.wav","../../genres/classical/classical.00000.wav","../../genres/country/country.00000.wav","../../genres/disco/disco.00000.wav","../../genres/hiphop/hiphop.00000.wav","../../genres/jazz/jazz.00000.wav","../../genres/metal/metal.00000.wav","../../genres/pop/pop.00000.wav","../../genres/reggae/reggae.00000.wav","../../genres/rock/rock.00000.wav"};
char temp[256];

//magn = magnitude("../../genres/blues/blues.00000.wav", &height, &width);
//printf("%d %d\n",height,width);}




for (int i = 0 ; i<5 ; i++) { // Boucle sur les 10 genres
int len_temp=strlen(genres[i]);
strcpy(temp,genres[i]); // temp contiendra le nom de la musique numéro l du genre i


for (int l=5 ; l<100 ; l++) { // Boucle sur le numéro de la musique
    char c1 = l%10 + '0'; // Chiffre des unités
    char c2 = (l%100 - l%10)/10 + '0'; // Chiffre des dizaines
    temp[len_temp-1-4]=c1;
    temp[len_temp-2-4]=c2;
    magn = magnitude(temp, &nCol, &nRow);
    reduction_vect2(magn, nCol, nRow, mean, std);
    double mean[nRow];
    double std[nRow];
    fprintf(f, "%d;", i);
    for(int k=0; k<nRow*2; k++){fprintf(f, "%.2f, %.2f, ", mean[0], std[0]); }
    fprintf(f, "\n");
  }   
}
}