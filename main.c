#include <stdio.h>
#include "magnitude.h"
#include "magnitude.c"


int main(int argc,char* argv[]) {

if (argc < 2) {
      printf("No wave file specified\n");
      return;
    }

double* magn = magnitude(argv[1]);




}