#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	int mode;
	scanf("%d", &mode);

	//If the mode is 0, do the encode procedure
	if (mode == 0){
		int n, m;
		char data[1024];

		//store n, m, and data
		scanf("%d %d %s", &n, &m, data);
		char *p=&data[0]; //the pointer p point to the first address of the data;
		
		//compute the length of the data
		size_t len;
		len = strlen(data);
		int chunk_len = len/n;
		
		//splite the data into n chunks
		char chunk[1024][1024];
		for (int i = 0; i < n; i++){
			strncpy(chunk[i], p, chunk_len);
			p+=chunk_len;
			chunk[i][chunk_len] = '\0';
		}

		//print n chunks
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (i == j) printf ("1 ");
				else printf ("0 ");
			}
			printf ("%s\n", chunk[i]);
		}

		//print m chunks
		for (int i = 0; i < m; i++){
			int result = 0;
			int coff[1024];
			for (int j = 0; j < n; j++){
				coff[j] = pow((i+1),j); //use the function pow(a, b) to calculate a^b
				printf ("%d ", coff[j]);
			}
			for (int k = 0; k < n;k++){
				int temp;
				temp = atoi(chunk[k]);
				result = result + coff[k]*temp;
			}
			printf ("%d\n", result);
		}
		
	}


	//If the mode is 1, do the decode procedure
	else if (mode == 1){
		int n;
		scanf ("%d", &n);

		float coff[1024][1024];
		//store the coefficient of n equations
		//i:row  j:cloumn
		for (int i = 0; i < n; i++){
			for (int j = 0; j <= n; j++)
			scanf("%f", &coff[i][j]);
		}

		//use Gauss-Jordan elimination to reconstruct the data
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				float ratio;

				//If coff[i][i]=0, then change row i and row i+1
				if (coff[i][i] == 0){
					int x = 1;
					while (coff[i+x][i] == 0 && (i+x)<n) x++;
					for (int k = 0; k <= n; k++){
						float tmp;
						tmp = coff[i+x][k];
						coff[i+x][k] = coff[i][k];
						coff[i][k] = tmp;
					}
				}

				if (i != j){
					if (coff[i][i]!=1){
						float temp = coff[i][i];
						for (int l = 0; l <= n; l++){
							coff[i][l] = coff[i][l]/temp;
						}
					}

					//let the matrix to be reduced row echelon form
					ratio = coff[j][i]/coff[i][i];
					for (int k = 0; k <= n; k++){
						coff[j][k] = coff[j][k] - ratio*coff[i][k];
					}
				}
			}
		}
		
		//print the data
		for (int i = 0; i < n; i++){
			printf("%.0f", coff[i][n]);
		}
		printf("\n");


	}
}
