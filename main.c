#include <stdio.h>
#include <string.h>
#include "magnitude.h"
#include "magnitude.c"


int main(int argc,char* argv[]) {

if (argc < 2) {
      printf("No wave file specified\n");
      return;
    }

double* magn = magnitude(argv[1]);





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


}}}