#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double moyenne(double*data, int length){
    double s=0;
    for(int i=0;i<length;i++){s+=data[i];}
    double res = s/length;
    return res;
}


//Trace du timtim

double* reduction_vect(double*data, int height, int width){
    double moy;
    double ecart_type;
    double*ligne=malloc(width*sizeof(double));
    double* tab=malloc(2*height*sizeof(double));
    for(int i=0; i<height; i++){
        for(int j=0;j<width;j++){ligne[j]=data[i*width+j]; // Récupération de la ligne
        // if (i==0) printf("MAGN %f\n",data[i*width+j]);
        }   
        moy=moyenne(ligne, width);
        // if (i==0) printf("MOY %f\n",moy);
        
        tab[2*i]=moy;
        for(int j=0;j<width;j++){ligne[j]=(ligne[j]-moy)*(ligne[j]-moy);}
        ecart_type=sqrt(moyenne(ligne, width));
        tab[2*i+1]=ecart_type;
        }
    return tab;    
    }