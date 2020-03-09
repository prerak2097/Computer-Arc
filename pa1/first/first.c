#include <stdio.h>
#include <stdlib.h>

//check if prime or not...
void primeOrNot(int arr[], int size);

int main(int argc, char** argv) {
	// Are the arguments valid, if less than 2 then not valid and catch err
	if(argc < 2) {
		printf("insufficient arguments\n");
		return 0;
	}
	FILE* filepointer = fopen(argv[1], "r");
	// does the file exsist, if not then exit
	if(filepointer == NULL) {
		printf("No such File\n");
		return 0;
	}
	//if the file exsist, make sure its not empty...
	int size = 0;
	if(fscanf(filepointer, "%d\n", &size) == EOF) {
		printf("empty file bud");
		return 0;
	}
	//now size is the first line of the file...
	
	// time for dynamic array so we create pointer first
	int *ptr;
	ptr = (int*)malloc(size * sizeof(int));
	int i;
	// run for loop to allocate the numbers onto the array
	for(i=0; i<size; i++) {
		fscanf(filepointer, "%d\n", &ptr[i]);
	}
	//the array is getting the proper values and all code above this point is good to go!:)
	// implement the method we created to check if the number is prime truntrcatable or not...
	primeOrNot(ptr, size);
	return 0;
}

	// is it prime? method...
void primeOrNot(int arr[], int size) {
		
	int trueOrFalse=0; // 0 = false, 1= true...
		for(int i=0; i < size; i++) {
			// if number if 0 or 1, then it is not prime...
			if (arr[i] == 0 || arr[i] == 1) {
				trueOrFalse = 0; 	
			}
			else if(arr[i] == 2) {trueOrFalse = 1;} // is a right .. prime
			else if(arr[i] % 2 == 0) { trueOrFalse=0; } // if even number
			else{
				trueOrFalse = 1;
				int k;
				while (arr[i] > 10) {
				for(k=2; k< arr[i]; k++) {
					if(arr[i] % k ==0) {
						trueOrFalse = 0;
					}
				}
				arr[i] = arr[i]/10;
				}
			}
			if(trueOrFalse == 1) {
                        	printf("yes\n");
                	}
                	else {
                        	printf("no\n");
                	}
		}
		// final moment, if the number is prime truncatable then print yes otherwise print no
}

