#include <stdio.h>
#include <string.h>
#include "magnitude.h"
#include "utils.h"
#include <stdlib.h>

int main(int argc,char* argv[]) {

if (argc < 3) {
      printf("No wave file specified\n");
      return 1;
    }
int height;
int weight;
double* magn = magnitude(argv[1], &height, &weight);
printf("magn fait\n");
double* magncorr=reduction_vect(magn, height, weight);
printf("reduction faite\n");

FILE* f=fopen(argv[2], "wb");
for(int i=0; i<height*weight; i++){
  fprintf(f, "%f ; ", magncorr[i]);
}
}
/*
char* genres[] = {"blues","classical","country","disco","hiphop","jazz","metal","pop","reggae","rock"};


for (int i = 0 ; i<10 ; i++) {
int len_temp=strlen(genres[i])+6;
char temp[len_temp];
char num[6]=".00000";


for (int l=0 ; l<len_temp ; l++) { // Initialisation de temp au genre donné
if (l<len_temp-6) {temp[l]=genres[i][l];}
else {temp[l]=num[l];}}

for (int l=0 ; l<100 ; l++) { // Incrémentation au sein du genre
    char c1 = l%10 + '0';
    char c2 = (l%100 - l%10)/10 + '0';
    temp[len_temp-1]=c1;
    temp[len_temp-2]=c2;



// Faire subir stft à temp qui contient le nom de la musique (sans doute rajouter le chemin)

return 0;
}
}

*/