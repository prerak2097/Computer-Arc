#include<stdio.h>
#include<stdlib.h>
#define TRUE 0
#define FALSE 1
struct node {
        int data;
        struct node* left;
        struct node* right;
};

struct node* head= NULL;


struct node* nodeCreation(struct node*, int, struct node*);
void insertion(int);
int search(int);
struct node* deleteNode(struct node*, int);
struct node* findMin(struct node*);
int findHeight(int);

int main(int argc, char** argv) {
        if(argc < 2) {
        printf("error");
        return 0;
        }
        FILE* fp = fopen(argv[1], "r");
        if (fp == NULL) {
                printf("error");
                return 0;
        }
        else {
        char c;
        int val;
                while(1) {
                        int x = fscanf(fp,"%c %d\n", &c, &val);
                        if(x == EOF) {
                                break;
                        }
                        else {
                                if(c == 'i') {
                                        insertion(val);
                                }
                                else if (c == 's'){
                                        int x =search(val);
					if(x == TRUE) {
						printf("present %d\n", findHeight(val));
					}else {
						printf("absent\n");
					}
                                }
				else if (c=='d') {
					if(search(val) == TRUE) {
						head = deleteNode(head, val);
						if(search(val) == TRUE) {
							printf("fail\n");
						}
						else {
							printf("success\n");
						}
					}else{
						printf("fail\n");
					}
				}
                        }
                }
        }
fclose(fp);
return 0;
}

struct node* nodeCreation(struct node* left, int data, struct node* right) {
        struct node* temp= malloc(sizeof(struct node));
        temp->data= data;
        temp->left = left;
        temp->right = right;
        return temp;
}

void insertion(int key) {
        int height=1;
        if(head==NULL) {
                struct node* temp= nodeCreation(NULL,key,NULL);
                head= temp;
                printf("inserted %d\n",height);
        }
        else {
                struct node* ptr= head;
                struct node* prev = NULL;
                while(ptr!=NULL) {
                        if(ptr->data==key) {
                                printf("duplicate\n");
                                break;
                        }
                        else if(key>ptr->data) {
                                prev = ptr;
                                ptr = ptr->right;
                                height++;
                        }
                        else{
                                prev = ptr;
                                ptr = ptr->left;
                                height++;
                        }
                }
        if(ptr==NULL) {
                struct node* temp = nodeCreation(NULL,key,NULL);
                if(temp->data > prev->data) {
                        prev->right = temp;
                        printf("inserted %d\n",height);
                }
                else {
                        prev->left = temp;
                        printf("inserted %d\n",height);
                }
        }
}
}
int search(int key) {
        struct node* ptr;
        ptr = head;
        int heights =1;
        while (ptr != NULL) {
                if(ptr->data == key) {
                        return TRUE;
                        break;
                }
                else {
                        if(ptr->data<key) {
                                ptr = ptr->right;
                                heights++;
                        }
                        else {
                                ptr = ptr->left;
                                heights++;
                        }
                }
        }
return FALSE;
}
int findHeight(int key) {
	struct node* ptr = head;
	int heights=1;
	while (ptr!= NULL) {
		if(ptr->data == key) {
			break;
		}
		else {
			if(ptr->data<key) {
				ptr=ptr->right;
				heights++;
			}
			else{
				ptr=ptr->left;
				heights++;
			}
		}	
	}	
return heights;
}

struct node* deleteNode(struct node* head, int key) {
	if(head == NULL) { return head;}
	
	if(key < head->data) {
		head->left = deleteNode(head->left, key);	
	}		
	else if(key > head->data) {
		head->right = deleteNode(head->right, key);	
	}
	else {
		if(head->left == NULL) {
			struct node* temp = head->right;
			free(head);
			return temp;	
		}
		else if(head->right ==NULL) {
			struct node* temp = head->left;
			free(head);
			return temp;
		}
		struct node* temp = findMin(head->right);
		head->data = temp->data;
		head->right = deleteNode(head->right, temp->data);
	}
return head;

}
struct node* findMin (struct node* nodee)  {
	struct node* ptr = nodee;
	while(ptr->left != NULL) {
		ptr = ptr->left;
	}
	return ptr;


}



