#include<stdio.h>
#include<stdlib.h>


int ** allocate(int,int);
void fillinMatrix(int**,int,int,FILE*);
void printMatrix(int**, int, int);
int** multiply(int**, int**, int, int, int, int);


int main(int argc, char** argv) {
	if(argc < 2) {
		return 0;
	}
	int** matrixuno;
	int** matrixdos;
	FILE* fp = fopen(argv[1], "r");
	if(fp==NULL) {
		return 0;
	}
	int rows= 0;
	int colums=0;
	if(fscanf(fp,"%d %d\n", &rows, &colums) == EOF) {
		return 0; //empty file
	}
	matrixuno = allocate(rows,colums); // allocate space for first matrix

	fillinMatrix(matrixuno,rows,colums,fp); // fill matrix in with values
	
	//printMatrix(matrixuno,rows,colums); // test to print the matrix
	
	int rowsdos, columnsdos;	//rows and columns for second matrix
			
	fscanf(fp,"%d %d\n", &rowsdos, &columnsdos); //scan the matrix dimensions
	
	matrixdos = allocate(rowsdos, columnsdos); // allocate space for second matrix
	
	fillinMatrix(matrixdos, rowsdos, columnsdos, fp); // fill matrix with values
	
	//printMatrix(matrixdos, rows, colums); // test check matrix
	
	if(colums != rowsdos) {
		printf("bad-matrices\n");
		return 0;
	}
	else {
		int** result = multiply(matrixuno, matrixdos, rows, colums, rowsdos, columnsdos);
		printMatrix(result, rows, columnsdos);
	}


	fclose(fp); // close file
return 0;
}
// allocate function, learned in Class...
int** allocate(int rows, int cols) {
	int** returnMatrix = malloc(rows*sizeof(int*));
	for(int i= 0; i < rows; i++) {
		returnMatrix[i] = malloc(cols*sizeof(int));
	}
return returnMatrix;
}

void fillinMatrix(int** matrix, int rows, int columns, FILE* fp) {
	int j;
	int storage=0;
	for(int i = 0; i < rows; i++) {
		for(j=0; j<columns; j++) {
			fscanf(fp,"%d", &storage);
			matrix[i][j]= storage;
		}
	}
}

void printMatrix(int** matrix, int rows, int c) {
	for(int i=0; i < rows; i++) {
		for(int j=0; j<c; j++) {
			printf("%d\t",matrix[i][j]);
		}
	printf("\n");
	}

}
int** multiply(int** uno, int** dos, int rowsuno, int rowsdos, int columnsuno, int columnsdos) {
	int ** result;
	int sum=0;
	result = allocate(rowsuno, columnsdos);
	for(int i= 0; i < rowsuno; i++) {
		for(int j=0; j<columnsdos; j++) {
			for(int k=0; k<rowsdos; k++) {
				sum = sum + uno[i][k]*dos[k][j];
			}
			result[i][j] = sum;
			sum = 0;
		}
	}
return result;
}
// multiply the two matricies and return the resulting matrix. ^^
