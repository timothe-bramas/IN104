#include <stdio.h>
#include <stdlib.h>

double moyenne(double*data, int length){
    double s=0;
    for(int i=0;i<length;i++){s+=data[i];}
    double res = s/length;
    return res;
}


//Trace du timtim

double* reduction_vect(double*data, int height, int width){
    double moy;
    double var;
    double*ligne=malloc(width*sizeof(double));
    double* tab=malloc(2*height*sizeof(double));
    for(int i=0; i<height; i++){
        for(int j=0;j<width;j++){ligne[j]=data[i*width+j];}   //Récupération de la ligne
        moy=moyenne(ligne, width);
        tab[2*i]=moy;
        for(int j=0;j<width;j++){ligne[j]=(ligne[j]-moy)*(ligne[j]-moy);}
        var=moyenne(ligne, width);
        tab[2*i+1]=var;
        } 
    return tab;    
    }