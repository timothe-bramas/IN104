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


double* produit_mat(double* mat1, double* mat2, int m, int n, int p){
    //fait le produit d'une matrice m n et d'une matrice n p
    double * mat = malloc(m*p*sizeof(double));
    int index;
    for(int i =0; i<m;i++){
        for(int j=0; j<p;j++){
            index=i+j*m;
            mat[index]=0;
            for(int k=0; k<n;k++){
                mat[index]=mat[index]+ (mat1[i+k*m] * mat2[i+k*n]);
            }
        }
    }
    return mat;
}

double* somme_mat(double* mat1,double* mat2,int m,int n){
    double* mat=malloc(m*n*sizeof(double));
    int index;
    for(int i =0; i<m;i++){
        for(int j=0;j<n;j++){
            index=i+j*m;
            mat[index]=mat1[index]+mat2[index];

        }
    }
    return mat;
}