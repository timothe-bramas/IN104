double moyenne(double*data, int length);
double* reduction_vect(double*data, int height, int weight);
double* reduction_vect2(double*arr, int nCol, int nRow, double*mean, double*std);
double* produit_mat(double* mat1, double* mat2, int m, int n, int p);
double* somme_mat(double* mat1, double* mat2, int m, int n);
double* read_csv(char* filename, int nRow, int nCol);
int find_max(double*tab, int n);
