#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char** argv) {

	for(int i=1; i< argc; i++) {
		int x = strlen(argv[i]);
		printf("%c", argv[i][x-1]);	
	}
	
	printf("\n");


return 0;
}
