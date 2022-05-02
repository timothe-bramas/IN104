#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "magnitude.h"
//#include "magnitude.c"


int main(int argc,char* argv[]) {


/*
if (argc < 2) {
      printf("No wave file specified\n");
      return;
    }

double* magn = magnitude(argv[1]);
*/




char* genres[] = {"blues.00000.wav","classical.00000.wav","country.00000.wav","disco.00000.wav","hiphop.00000.wav","jazz.00000.wav","metal.00000.wav","pop.00000.wav","reggae.00000.wav","rock.00000.wav"};


for (int i = 0 ; i<10 ; i++) { // Boucle sur les 10 genres
int len_temp=strlen(genres[i]); // +10 caractères car on ajoute ".00000.wav"
char temp[len_temp];
strcpy(temp,genres[i]); // temp contiendra le nom de la musique numéro l du genre i


for (int l=0 ; l<100 ; l++) { // Boucle sur le numéro de la musique
    char c1 = l%10 + '0'; // Chiffre des unités
    char c2 = (l%100 - l%10)/10 + '0'; // Chiffre des dizaines
    temp[len_temp-1-4]=c1;
    temp[len_temp-2-4]=c2;


// TO DO DE TIMTIM : Faire subir stft à temp qui contient le nom de la musique (sans doute rajouter le chemin)

printf("%s\n",temp);
}}}