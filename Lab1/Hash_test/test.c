/* strtok example */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void updateM(double** A, int m, int n){
  for(int i = 0; i< m; i++){
    for(int j = 0; j< n; j++)
      A[i][j] += 1.0;
  }
}

void printM(double** A, int m, int n){
  for(int i = 0; i<m; i++){
    for(int j = 0; j<n; j++){
      printf("%lf ", A[i][j]);
    }
    printf("\n");
  }    
}

int main ()
{
  char str[] ="- This, a sample string.";
  char *str1  =  str;
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str1," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }

  double **v;
  v = (double **)malloc(5*sizeof(double*));
  for(int i = 0; i<5; i++){
    v[i] = (double* )malloc(5*sizeof(double));
    printf("%.2lf\n", v[i][i]);
  }

  updateM(v, 5, 5);
  printM(v, 5, 5);


  return 0;
}