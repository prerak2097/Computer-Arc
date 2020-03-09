#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

int** allocate(int);
int** readMatrix(FILE*, int);
void printMatrix(int**,int);
int duplicatesQ(int**, int);
int colserows(int**, int);
int diagonals(int**, int);




int main(int argc, char** argv) {
	int** matrix;
	if(argc < 2) {
		printf("insufficient args: ");
		return(0);	
	}
	FILE* fp = fopen(argv[1],"r");
	if(fp == NULL) {
		printf("fileisEmpty");
		return(0);
	}
	else {
		// first number in the file.
		int nbyn = 0;
		fscanf(fp,"%d\n",&nbyn);
		// the program...
		matrix = readMatrix(fp, nbyn);
		if(duplicatesQ(matrix,nbyn) == TRUE) {
			printf("not-magic\n");
		  	return 0;	
		}
		int cSumrSum;	
		cSumrSum = colserows(matrix,nbyn);
		int dsum = 0;
		dsum = diagonals(matrix, nbyn);
		if(dsum == cSumrSum) {
			printf("magic\n");
			return 0;
		}
		printf("not-magic\n");		
	}
	
return 0;
}

// allocate matrix memory
int** allocate(int n) {
	int** allocated = malloc(n*sizeof(int*));
	for(int i=0; i < n; i++) {
		allocated[i] = malloc(n*sizeof(int));
	}
	return allocated;
}
int** readMatrix(FILE* fp, int n) {
	int** matrix;
	int val;
	matrix = allocate(n);
	for(int i=0; i < n; i ++) {
		for(int j=0; j<n; j++) {
			fscanf(fp, "%d", &val);
			matrix[i][j] = val;
		}
	}
return matrix; 
}
void printMatrix(int** Matrix, int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			printf("%d\t", Matrix[i][j]);
		}
	printf("\n");
	}
}
int duplicatesQ(int** Matrix, int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j <n; j++) {
			for(int k=i+1; k<n;k++) {
				for(int l=0;l<n;l++) {
					if(Matrix[i][j]==Matrix[k][l]) {return TRUE;}
				}
			}
		}
	}
return FALSE;
}
int colserows(int** matrix, int n) {
	int* sum = malloc(n*sizeof(int));
	int* sums = malloc(n*sizeof(int));
	for(int i =0; i < n; i ++) {
		sum[i]=0;
		for(int j=0;j<n;j++) {
		sum[i]=sum[i]+matrix[i][j];
		}	
	}
	for(int k=0; k <n; k++) {
		for(int l=0;l<n;l++) {
			if(sum[k] != sum[l]) {
				return FALSE;
			}
		}
	}
	for(int i=0; i<n; i ++) {
		sums[i] =0;
		for(int j=0; j<n; j++) {
			sums[i]=sums[i]+matrix[j][i];
		}
	}
	for(int k=0; k<n; k++) {
		for(int l=0; l<n; l++) {
			if(sums[k] != sums[l]) {
				return FALSE;
			}
		}
	}
	if(sums[0] != sum[0]) {return FALSE;}
return sum[0];
}
int diagonals(int ** matrix, int n) {
	int sum=0;
	for(int i=0; i<n; i ++) {
		for(int j=0; j <n; j ++) {
			if(i==j) {
				sum = sum+matrix[i][j];
			}
			else {
				continue;
			}
		}
	}
	int otherDiag = 0;
	for(int x=n-1; x>=0; x--) {
		for(int y=n-1; y>=0; y--) {
			if(x==y) {
				otherDiag = otherDiag+matrix[x][y];	
			}
			else {
				continue;
			}
		}
	}
	if(sum != otherDiag) {
		return FALSE;
	}	
return sum;
}

















