#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1

//Linked List Struct
struct node {
        int data;
        struct node * next;
};
struct node* head = NULL;

void insert (int);
void delete (int);
int isPresent (int);
struct node* createNode(int, struct node*);
int nodeCounter(struct node*);
void finalPrint(struct node*);
void free_list();
// main program...
int main (int argc, char** argv) {
	//if there is no argument present in the cmd line then just exit...
	if(argc < 2) {
		printf("error\n");
		return 0;
	}
	FILE* fp = fopen(argv[1], "r");
	//does the file exist? is the command file name even valid? if not then Err...
	if(fp == NULL) {
		printf("error\n");
		return 0;
	}
	//is there a char val in the file?
	int c = fgetc(fp);
	//if not then print 0 as the assignment says...
	if(c == EOF) {
		printf("%d\n",0);
	}
	else {	// else
		char c;
		int key;
		FILE* remake = fopen(argv[1],"r");
		while(1) {	// while EOF is unreached then...
			int x = fscanf(remake,"%c %i\n",&c,&key);
				if(x == EOF) { break;}
				if(c == 'i') {	//Insert
					if(isPresent(key)==TRUE) {
						continue;
					}
					else {
						insert(key);
					}			
				}
				else if(c == 'd') { //delete
					if(isPresent(key) == FALSE) {
						continue;
					}
					else {
						if(head == NULL) { continue; }
						else {
							delete(key);
						}
					}		
				}
			}
		fclose(remake);		
		}
	fclose(fp);
	int counter= nodeCounter(head);
	printf("%d\n",counter);
	finalPrint(head);
	free_list();
return 0; // last line of da main method
}

// is the key present in the linked list?
int isPresent(int key) {
	struct node* curr = head;
	while( curr != NULL) {
		if(curr->data == key) {
			return TRUE;
		}
		curr = curr->next;
	}
return FALSE;
}


void finalPrint(struct node* head) {
	struct node*ptr = head;
	while (ptr!= NULL) {
		if(ptr->next != NULL) {
			printf("%d\t",ptr->data);
		}
		else {
			printf("%d\n",ptr->data);
		}
	ptr= ptr->next;
	}
}

int nodeCounter(struct node* head) {
	struct node*ptr = head;
	int counter = 0;
	while( ptr != NULL) {
		counter++;
		ptr = ptr->next;
	}
return counter;
}

struct node* createNode(int data, struct node *next) {
	struct node* temp = malloc(sizeof(struct node));
	temp->data = data;
	temp->next = next;
	return temp;
}

void insert (int key) {
		struct node *ptr = head;
		struct node *prev = NULL;
		while(ptr != NULL && ptr->data<=key) {
			prev = ptr;
			ptr = ptr->next;
		}
		if(prev == NULL) { //insert before the first node
			struct node* temp = createNode(key,ptr);
			head = temp;
		}
		else if(ptr == NULL) { // if the end of the list is reached
			struct node* temp = createNode(key, NULL);
			prev->next = temp;
		}
		else {
			struct node* temp = createNode (key, ptr);
			prev->next = temp;
		}
}		

void delete (int target) {
	struct node * ptr= head;
	struct node * prev= NULL;
	while (ptr->data != target) {
		prev=ptr;
		ptr= ptr->next;
	}
	if(prev == NULL) { //first one
		head = ptr->next;
		ptr->next = NULL;
	}
	else {
		prev->next = ptr->next;
		ptr->next = NULL;
	}
}
void free_list() {
	struct node*temp = head;
	while(temp != NULL) {
		struct node * temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}


























