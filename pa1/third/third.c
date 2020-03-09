#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
struct node {
	int data;
	struct node * next;
};
struct node* hashPointer[1000] = {NULL}; // create a pointer array of 1000 elements. 
int hashSize = 10;		// hash size of 10

struct node* createNode(int, struct node*);
void insertInHash(int);
int modFunction(int);
int isitDuplicate(int);
int searchHash(int);

int main(int argc, char** argv) {
	int i;
	for (i =0; i < hashSize; i++) {
        	hashPointer[i] = NULL;
	}
	if(argc<2) { // Not enough Arguments are Present
		printf("error\n");
		return 0;
	}
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL) { //invalid file name
		printf("error");
		return 0;
	}
	
	int c = fgetc(fp);
	if (c==EOF) { //valid file name but empty file
		printf("error\n");
		return 0;
	}
	else {
		char c;
		int num;
		FILE* lel = fopen(argv[1],"r");
		while(1) {
			int x = fscanf(lel, "%c %d\n", &c, &num);
			if(x==EOF) {break;}
			if(c == 'i') {  //fill out insert method
				if(isitDuplicate(num) == TRUE) { //if duplicate then do nothing just print duplicate
					printf("duplicate\n");	
					continue;
				}
				else{ // insert into th hash...
					insertInHash(num);
				}
			}
			else if (c == 's') { // fill out search method
				int x = searchHash(num);
				 if(x==TRUE) {printf("present\n");}
                                        else{printf("absent\n");}		
			}
		}
	fclose(lel);
	}

fclose(fp);

return 0;
}

struct node* createNode(int key, struct node* next) {
	struct node* temp = malloc(sizeof(struct node));
	temp-> data = key;
	temp->next = next;
	return temp;
}

int modFunction(int key) { 
    int mod = (key % 10 + 10) % 10;      //key%10;
	return mod;
}

void insertInHash(int key) { // insert function
	int remainder = modFunction(key);
	if(hashPointer[remainder] == NULL) { // if empty
		struct node* temp = createNode(key, NULL);
		hashPointer[remainder] = temp;
		printf("inserted\n"); 
	}
	else {					// if values present
		struct node* ptr = hashPointer[remainder];
		struct node* prev = NULL;
		while (ptr!= NULL) {
			prev = ptr;
			ptr = ptr->next;
		}
		struct node* temp = createNode(key, NULL);
		prev->next = temp;
		printf("inserted\n"); 
	}
} 

int isitDuplicate(int key) {
	int remainder = modFunction(key);
	struct node* ptr = hashPointer[remainder];
	while(ptr!= NULL) {
		if(ptr->data == key) {
			return TRUE; 
		}
	ptr=ptr->next;	
	}
return FALSE;
}

int searchHash (int key) {
	int remainder = modFunction(key);
	if(hashPointer[remainder] == NULL) { //if empty
		return FALSE;
	}
	else {
		struct node* ptr = hashPointer[remainder];
		while(ptr!= NULL) {
			if(ptr->data == key) {
				return TRUE;
				break;
			}
		ptr=ptr->next;
		}	
	}
return FALSE;
}










