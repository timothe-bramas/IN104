#include <stdio.h>
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
return 0;
}