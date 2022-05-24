#include "magnitude.h"
#include "utils.h"
#include "stft.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    if (argc < 2) {
        printf("sound file specified\n");
        return 1;
        }

    double*w=read_csv("w.csv", 10, 514);
    double*b=read_csv("b.csv", 10,1);
    int nRow;
    int nCol;
    double*magn=magnitude(argv[1],&nCol,&nRow);
    char* genres[] = {"blues","classical","country","disco","hiphop","jazz","metal","pop","reggae","rock"};
    double* mean=malloc(nRow*sizeof(double));
    double* std=malloc(nRow*sizeof(double));
    double*magncorr=malloc(nCol*2*sizeof(double));
    reduction_vect2(magn,nCol,nRow,mean,std);
    for(int k=0;k<nCol;k++){magncorr[2*k]=mean[k]; magncorr[2*k+1]=std[k];}
    double*prod=produit_mat(w,magncorr, 2*nCol, 10, 1);
    double*res=somme_mat(prod,b,10,1);
    for(int k=0; k<10;k++){printf("%s : %f\n",genres[k], res[k]);}
    int index=find_max(res,10);
    printf("Le morceau est du genre : %s\n", genres[index]);
    }