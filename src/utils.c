#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double moyenne(double*data, int length){
    double s=0;
    for(int i=0;i<length;i++){s+=data[i];}
    double res = s/length;
    return res;
}



double* reduction_vect(double*data,  int height, int width){
    double moy;
    double ecart_type;
    double*colonne=malloc(height*sizeof(double));
    double* tab=malloc(2*width*sizeof(double));
    for(int j=0; j<width; j++){
        for(int i=0;i<height;i++){colonne[i]=data[j*height+i]; // Récupération de la colonne
        // if (j==0) printf("MAGN %f\n",data[j*height+i]);
        }   
        moy=moyenne(colonne, height);
        // if (j==0) printf("MOY %f\n",moy);
        
        tab[2*j]=moy;
        for(int i=0;i<height;i++){colonne[i]=(colonne[i]-moy)*(colonne[i]-moy);}
        ecart_type=sqrt(moyenne(colonne, height));
        tab[2*j+1]=ecart_type;
        }
    return tab;    
    }

void reduction_vect2(double*arr, int nCol, int nRow, double* mean, double*std){
    double sum=0;
    double sumsq=0;
    for (int i = 0; i < nRow; i++){
        sum=0;
        sumsq=0;
        for (int j = 0; j < nCol; j++){
            sum=sum+ arr[i+j*nRow];
            sumsq= sumsq + arr[i + j * nRow] * arr[i + j * nRow];
        }
        mean[i]=sum/nCol;
        std[i]=sqrt(sumsq/nCol - mean[i]*mean[i]);
    }
}