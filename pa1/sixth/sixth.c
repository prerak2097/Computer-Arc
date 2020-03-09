#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
	int x = argc;
	for(int i=1; i< x; i++) {
		if(argv[i][0] == 'a' ||
		 argv[i][0] == 'e' || 
		argv[i][0] == 'i' ||
		 argv[i][0] == 'o' || 
		argv[i][0] =='u' ||
		argv[i][0] =='A' ||
		argv[i][0] == 'E' ||
		argv[i][0] == 'I' ||
		argv[i][0] == 'O' ||
		argv[i][0] == 'U') {
			printf("%syay ",argv[i]);
		}
		else{
			int counter=0;
			char first[50];
			char second[50];
			//printf("shit one");
			char * pointer = argv[i];
			int xxx =1;
			int otherCounter=0;
			//printf("shit 2");
			for(int j=0; j<strlen(argv[i]); j++) {
				if((pointer[j] == 'a' || pointer[j] == 'e' || pointer[j] == 'i' || pointer[j] == 'o' || pointer[j] == 'u' ||
				pointer[j] == 'A' || pointer[j] == 'E' || pointer[j] == 'I' || pointer[j] == 'O' || pointer[j] == 'U') || xxx ==0) {
					first[otherCounter] = pointer[j];
					otherCounter++;
					xxx=0;
				}
				else {
					second[counter] = pointer[j];
					counter++;
				}
			}
		for(int z=0; z<otherCounter; z++) {
			printf("%c", first[z]);	
		}
		for(int x=0; x<counter; x++) {
			printf("%c", second[x]);	
		}
		printf("ay ");
	}
	
	}
printf("\n");
return 0;
}

