#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
// methods
void printMatrix(char[16][16]);
void fill_matrix(char[16][32], FILE*);
bool does_it_fit(char[16][16], char, int, int);
bool solver(char[16][16],int,int);
char originalMatrix[16][32];
bool originalChecker(char[16][16]);
char otherMatrix[16][16];
//matrix declared
// array of the (0-F) values
char matchArray[16] = {'1','2','3','4','5','6','7','8','9','0','A','B','C','D','E','F'};

int main(int argc, char** argv) {
    // if not enough args and if wrong file name
    if(argc < 2) {
        printf("error\n");
        return 0;
    }
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("file name wrong\n");
        return 0;
    }
    //fill the matrix with values from file
    fill_matrix(originalMatrix,fp);
    int counter = 0;
    for (int q = 0; q < 16; q++) {
        for (int zay = 0; zay < 32; zay=zay+2)
        {
            otherMatrix[q][counter] = originalMatrix[q][zay];
            counter++;
            
        }
        counter = 0;
        
    }
    
    solver(otherMatrix,0,0);
    for(int i =0; i < 16; i++) {
        for (int j=0; j<16; j++) {
            if(otherMatrix[i][j] == '-') {
                printf("no-solution");
                return 0;
            }
        }
    }
    if(originalChecker(otherMatrix)==false) {
        printf("no-solution");
    }
    else {
        printMatrix(otherMatrix);
    }
    
    fclose(fp);

return 0;
}
void fill_matrix(char matrixTofill[16][32], FILE* fpp) { // is good
    for(int i=0;i<16;i++) {
        for(int j=0;j<32;j++) {
            fscanf(fpp, "%c", &matrixTofill[i][j]);
        }
    }
}
void printMatrix(char matrixToPrint[16][16]) { // is good
    for(int i=0; i < 16; i++) {
        for(int j = 0 ; j<16; j++) {
            if(j==15) {
                printf("%c", matrixToPrint[i][j]);
            }
            else {
            printf("%c\t", matrixToPrint[i][j]);
            }
        }
        printf("\n");
    }
}
bool does_it_fit(char matrix[16][16], char myChar, int currRow, int currColumn) { // this method works fine
    /* we have to check here for three cases
    1) does the row already have it?
    2) does the column already have it? 
    3) finally, does the sub 4x4 matrix already contain the char?
    */
   // iterating through the column and keeping row stagnant meaning going through the ROW
   
   int c = currColumn;
   for(c = 0; c<16; c++) {
       if(matrix[currRow][c] == myChar) {
           return false;
       }   
   }
   // iteration through the rows and keeping col stagnant meaning going through the COLS
   int r = currRow;
   for(r = 0; r<16; r++) {
       if(matrix[r][currColumn] == myChar) {
           return false;
       }
   }
   // finally we have to check the sub matricies and to do that we have to find the top left row and col indices
   int reee  = currRow/4;
   int ceee = currColumn/4;
   int top_left_row = reee * 4;   // top left index row
   int col_top_left = ceee * 4;   // top left inex col
   for(int i =0; i < 4; i++) {
       for(int j=0 ; j< 4; j++) {
           if(myChar == matrix[i+top_left_row][j+col_top_left]) {
               return false;
           }
       }
   }
   return true;
}
// code is good so far in terms of compilation
// solve using backtracking for efficiency
bool solver(char matrix[16][16], int r, int c) {
    //base case
    if(c == 16) {
        r++;
        c=0;
        if(r == 16) {
            return true;
        }
    }

    if(matrix[r][c] != '-') {
        return solver(matrix, r, c+1);
    }

    for(int i=0; i < 16; i++) {
        if(matrix[r][c] == '\t' || matrix[r][c]=='\n') {
            break;
        }
        else if(does_it_fit(matrix,matchArray[i],r, c) == true) {
            matrix[r][c] = matchArray[i];
            if(solver(matrix,r,c+1)==true) {
                return true;
            }
        }
    }
    matrix[r][c]='-';
    return false;
}
bool originalChecker (char matrixxxx[16][16]) {
    for (int i = 0; i < 16; i++)
    {
        /* code */
        for (int z = 0; z < 16; z++)
        {
            /* code */
            char myCharacter = matrixxxx[i][z];
            matrixxxx[i][z] = '-';
            if(does_it_fit(matrixxxx,myCharacter,i,z)!=true) {
                return false;
            }
            matrixxxx[i][z]=myCharacter;
        }
    }
    return true;
}
