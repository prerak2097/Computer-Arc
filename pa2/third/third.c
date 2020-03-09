#include <stdlib.h>
#include <stdio.h>

double** allocate(int, int); // function to allocate space for matrix
void fill_Matrix(double**,int,int,FILE*);
void printMatrix(double**, int, int);
double** fill_price_Matrix(double**,double**,int,int);
double** transpose_Matrix(double**,int,int);
void ones_and_zeros(double**,int,int,double**,int);
double** findInverse(double** matrix, int row, int col);
double** multiply(double**,double**,int,int,int,int);
void fill_fin_Matrix(double**,int,int,FILE*);
void top_half(double**,int,int,double**);

int main(int argc, char** argv) {
    if(argc < 3) {
        return 0; // not enough arguments. 
    }
    FILE* train_file = fopen(argv[1],"r"); // podoubleer to train file
    FILE* test_file = fopen(argv[2], "r"); // podoubleer to test file
    if(train_file == NULL) {
        return 0; // wrong file name
    }
    if(test_file == NULL) {
        return 0; //wrong file name
    }
    double** trainingMatrix;
    int columns = 0; //# of attributes.
    int rows=0; //# of rows.
    fscanf(train_file, "%d", &columns);
    columns = columns+1;
    fscanf(train_file, "%d\n", &rows);
    trainingMatrix = allocate(rows, columns);
    fill_Matrix(trainingMatrix,rows,columns,train_file);
    double** X_matrix = allocate(rows,columns);
    for(int i=0; i< rows;i++) {
        X_matrix[i][0]=1;
        for(int k=1;k<columns;k++) {
            X_matrix[i][k]=trainingMatrix[i][k-1];
        }
    }
    /* X MATRIX IS COMPLETE NOTHING LEFT TO DO UP TOP */

    int stuff =0;
    fscanf(test_file, "%d\n", &stuff);
    double** test_Matrix = allocate(stuff,columns);
    fill_fin_Matrix(test_Matrix,stuff,columns,test_file);     
    //printMatrix(test_Matrix,stuff,columns);

    /* TEST MATRIX IS COMPLETE NOTHING LEFT TO DO UP TOP */

    double** y_Matrix = allocate(rows,1); 
    fill_price_Matrix(trainingMatrix,y_Matrix,rows,columns);
    //printMatrix(y_Matrix,rows,1);

    /*PRICE MATRIX IS NOW COMPLETE NOTHING ELSE TO DO ABOVE*/

    double** X_transpose = transpose_Matrix(X_matrix,rows,columns);
    //printMatrix(X_transpose,columns,rows);
    //exit(0);
    /* TRANSPOSE IS COMPLETE*/
    int t_row = columns;
    int t_cols = rows;
    double** transpose_by_X = multiply(X_transpose, X_matrix, t_row, rows, t_cols, columns);
    int transpose_by_x_row = t_row; 
    int transpose_by_x_col = columns;
    double** inverse_t_x = findInverse(transpose_by_X, transpose_by_x_row,transpose_by_x_col);
    double** inv_t_x_by_Xt = multiply(inverse_t_x, X_transpose, columns,columns,columns,rows);
    double** W_matrix = multiply(inv_t_x_by_Xt, y_Matrix,columns,rows,rows,1);
    double** finalAnswerMatrix = multiply(test_Matrix,W_matrix,stuff,columns,columns,1);
    printMatrix(finalAnswerMatrix,stuff,1);


    free(X_matrix);
    free(test_Matrix);
    free(finalAnswerMatrix);
    free(W_matrix);
    free(inv_t_x_by_Xt);
    free(inverse_t_x);
    free(transpose_by_X);
    free(X_transpose);
    free(trainingMatrix);
    free(y_Matrix);
    return 0;
}

double** allocate(int rows, int cols) {
	double** returnMatrix = malloc(rows*sizeof(double*));
	for(int i= 0; i < rows; i++) {
		returnMatrix[i] = malloc(cols*sizeof(double));
	}
return returnMatrix;
}
void fill_Matrix(double** matrix_to_fill, int rows, int columns, FILE* fp) {
    int j;
	for(int i = 0; i < rows; i++) {
		for(j=0; j<columns; j++) {
			fscanf(fp,"%lf%*[,]", &matrix_to_fill[i][j]);
		}
	}
}

void printMatrix(double** matrix, int rows, int c) {
	for(int i=0; i < rows; i++) {
		for(int j=0; j<c; j++) {
			printf("%0.0lf\n",matrix[i][j]);
		}
	}

}
double** fill_price_Matrix (double** xMatrix, double** priceMatrix, int r, int c) {
    for(int i =0; i<r; i++) {
        priceMatrix[i][0] = xMatrix[i][c-1];
    }
    return priceMatrix;
}
double** transpose_Matrix(double** matrixToTranspose, int row, int col) {
    double** transpose = allocate(col,row);
    for(int i=0; i<row; i++) {
        for(int h=0;h<col;h++) {
            transpose[h][i]=matrixToTranspose[i][h];
        }
    }
    return transpose;
}

double** findInverse(double** matrix, int row, int col) { //finally works
    double** inverse_matrix = allocate(row,col);
    for(int i= 0; i<row; i++) {
        for(int j=0; j<col; j++) {
            if(i==j) {
                inverse_matrix[i][j]= 1;
            }
            else {
                inverse_matrix[i][j] = 0;
            } 
        }
    }
    // made the basic inverse matrix ^^
    // go through cols
    
    
   for(int iter = 0; iter<col; iter++) {
        ones_and_zeros(matrix,row,col,inverse_matrix,iter);
    }
    
    //printMatrix(matrix,5,5);
    //exit(0);
    top_half(matrix,row,col,inverse_matrix);
    //ClearTopVals(matrix,row,col,inverse_matrix);
    
    
    
    //printMatrix(inverse_matrix,4,4);
    //printf("\n");
    //printMatrix(matrix,4,4);
    //exit(0);
    
    return inverse_matrix;
}

void ones_and_zeros(double** origMatrix, int r, int c, double** inverse_matrix, int col_ctr) {
    double holder =0;
    for(int i = col_ctr; i<r; i++) {
        holder = origMatrix[i][col_ctr];
        for(int y =0; y<c; y++) {
            inverse_matrix[i][y] = inverse_matrix[i][y]/holder;
            origMatrix[i][y] = origMatrix[i][y]/holder;
        }
    }
    //printMatrix(origMatrix,5,5);
    //exit(0);

    // good so far

    for(int u=col_ctr; u<r; u++) {
        if(u==col_ctr) {
            continue;
        }
        for(int o=0;o<c;o++) {
            inverse_matrix[u][o]=inverse_matrix[u][o]-inverse_matrix[col_ctr][o]; 
            origMatrix[u][o]=origMatrix[u][o]-origMatrix[col_ctr][o];
        }  
    }
    
}

double** multiply(double** uno, double** dos, int rowsuno, int rowsdos, int columnsuno, int columnsdos) {
	double ** result;
	double sum=0;
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
void fill_fin_Matrix(double** matrix, int r, int c, FILE* pointer) {
    for(int i=0; i<r;i++) {
        for(int j=0;j<c;j++) {
            if(j==0) {
                matrix[i][j]=1;
                continue;
            }
            fscanf(pointer,"%lf%*[,]", &matrix[i][j]);
        }
    }
}

void top_half (double** matrix, int r, int c, double ** iden) {
    double storage = 0;
    for(int  l=r-1; l>=0; l--) {
        for(int m=l;m>=0;m-- ) {
            if(matrix[m][l]!= 0 && m!=l) {
                storage = matrix[m][l];
                for(int w=0; w<c; w++) {
                    matrix[m][w]= matrix[m][w]-(matrix[l][w])*storage;
                    iden[m][w] = iden[m][w]-(iden[l][w])*storage;
                }
            }

        }
    }
}