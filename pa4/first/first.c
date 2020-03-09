#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
/*    ./first cachesize blocksize cachepolicy associativity prefetchsize tracefile.

    cache size is the total size of the cache in bytes, should be power of 2.
    block size is power of two that specifies the size of the cache block in bytes.
    cache policy: fifo or lru
    associativity: direct, assoc, assoc:n
    prefetch size: number of adjacent blocks that should be prefetched by the prefetcher incase of a miss
    trace file is the input of the trace file.
    look at 8 for other details in making the MAKEFILE And more
*/

struct block_node {
  long index; 
  long tag;
  long offset;
  char* valid;
  struct block_node* next;
};

int cache_miss;
int cache_hit;
int mem_write;
int mem_read;
int cache_miss_pre; // for pre
int cache_hit_pre; // for pre
//int mem_write_pre; // for pre
int mem_read_pre; // for pre

void delete_by_fifo(struct block_node*, struct block_node*); //no
bool searchCache(struct block_node*,int, struct block_node*); //no
bool insertInCache(struct block_node*, int, struct block_node*); //no
int check_asso(char *,int,int); //no/maybe THIS HAS PROBLEM with the other sort of associations
long binary_to_decimal(char*);// def no
char* hex_to_binary(char*); //def no
struct block_node* createBlock(char*,int,int, int); //no
struct block_node* createHash(int,int,int); // THIS HAS PROBLEMS
void prefetching(char*, int, int, int, struct block_node*, int); //counters maybe
char* decimal_to_binary(int); // no
char* hex_and_dec(char* hexNum, int decimal);

int main(int argc, char** argv) {
  
    if(argc < 7) {
        printf("error\n");
        return 0;
    }
    FILE* fp = fopen(argv[6], "r");
    if(fp == NULL) {
        printf("error\n");
        return 0;
    }
    int size_of_cache = atoi(argv[1]); //for both ways
    int size_of_block = atoi(argv[2]); // for both ways
    int prefetch_size = atoi(argv[5]); // for prefetch way   
    //char* cache_policy = argv[3];
   

    char* accociation = argv[4];    
    int assoc =0;
    int indicies =0;

    // sets assoc and indicies based on the argv[4] input use this for code assoc part and indicies part
    if(strcmp(accociation, "direct") == 0) {
	assoc = 1;
	indicies = size_of_cache/size_of_block;
    }
    else if(strcmp(accociation, "assoc") == 0) {
	indicies = 1;
	assoc = size_of_cache/size_of_block;
    }else {
	assoc = atoi(&accociation[6]);
	indicies = size_of_cache/(size_of_block * assoc);
    }
	//int assoc = check_asso(accociation, size_of_cache, size_of_block); // for both ways
    char* hexNumber= malloc(sizeof(char)*23);
    char c;
    struct block_node* secondary_cache= createHash(size_of_block, size_of_cache, indicies);
    struct block_node* primary_cache = createHash(size_of_block, size_of_cache, indicies); 
    while (1) {
	int x = fscanf(fp, "%c %s\n", &c, hexNumber);
	if(x == EOF) {
		break;
	}
	if(c == '#') {
		break;
	}
	if(c=='W') {mem_write++;}
	char* binary_string = hex_to_binary(hexNumber); // make hex string from file into binary...
	struct block_node* second_block = createBlock(binary_string, size_of_cache, assoc, size_of_block);
	struct block_node* first_block = createBlock(binary_string, size_of_cache, assoc, size_of_block); //using binary string make first BlockNODE
	bool searched = searchCache(primary_cache, assoc, first_block);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(searched == true) {cache_hit++;}
	if(searched == false) {
		cache_miss++;
		mem_read++;
		bool inserted_tf = insertInCache(primary_cache, assoc, first_block);
		if(inserted_tf == false) {
			delete_by_fifo(primary_cache, first_block);
			inserted_tf = insertInCache(primary_cache, assoc, first_block);
		}
	}
////////////////////////////////////////////// Makes the non-prefetch data ///////////////////////////////////////////////////////////////////////////
        bool pre_search = searchCache(secondary_cache, assoc, second_block);
	if(pre_search == true) {cache_hit_pre++;}
	if(pre_search == false) {
		cache_miss_pre++;
		mem_read_pre++;
		bool inserted_ft = insertInCache(secondary_cache, assoc, second_block);
		if(inserted_ft == false) {
			delete_by_fifo(secondary_cache, second_block);
                        inserted_ft = insertInCache(secondary_cache, assoc, second_block);
		}
		prefetching(hexNumber,size_of_cache, size_of_block, prefetch_size, secondary_cache, assoc);
	}
    }
    printf("no-prefetch\n");
    printf("Memory reads: %d\n", mem_read);
    printf("Memory writes: %d\n", mem_write);
    printf("Cache hits: %d\n", cache_hit);
    printf("Cache misses: %d\n", cache_miss);
    printf("with-prefetch\n");
    printf("Memory reads: %d\n", mem_read_pre);
    printf("Memory writes: %d\n", mem_write);
    printf("Cache hits: %d\n", cache_hit_pre);
    printf("Cache misses: %d\n", cache_miss_pre);
    return 0;
}

void prefetching(char* address,int cache_size, int block_size, int size_of_pre, struct block_node* cache, int association) {
        char* prefetch_addy = address;	
        for(int i=0; i< size_of_pre; i++) {
		/*int other_prefetch_addy=0;
		other_prefetch_addy = binary_to_decimal(prefetch_addy);
                other_prefetch_addy = other_prefetch_addy + block_size;
		char* new = decimal_to_binary(other_prefetch_addy);
		*/
		prefetch_addy = hex_and_dec(prefetch_addy, block_size);
		char* binary = hex_to_binary(prefetch_addy);
		struct block_node* this_block = createBlock(binary, cache_size, association, block_size);
                bool searched = searchCache(cache, association, this_block);
		if(searched == false) {
                        bool inserted_tf = insertInCache(cache, association, this_block);
			if(inserted_tf == false) {
				delete_by_fifo(cache, this_block);
				inserted_tf = insertInCache(cache, association, this_block);
			}
			mem_read_pre++;
                }

        }
}

/*char* decimal_to_binary(int decimal_val) {
	char* bin_number = malloc(sizeof(char)*50);
	int rem;
	int counter =47;
	while(decimal_val != 0) {
		rem = decimal_val%2;
		bin_number[counter] = rem +'0';
		decimal_val/=2;
		counter--;
	}
	int z=0;
	while(bin_number[z] != '1' && z<=47) {
		bin_number[z] = '0';
		z++;
	}
return bin_number;
}*/

char* hex_and_dec(char* hexNum, int decimal) {
	char* str = malloc(sizeof(char)*15);
	for(int i=2; i<strlen(hexNum); i++) {
		str[i-2] = hexNum[i];
	}	
	long in = strtol(str,NULL,16);
	long tot = in +decimal;
	char* strr = malloc(sizeof(char)*15);
	sprintf(strr,"%lx", tot);
	char* rep = malloc(sizeof(char)*15);
	rep[1] = 'x';
	rep[0] = '0';
	strcat(rep,strr);
	return rep;
}

/*Method that creates the blocks that will be inputted into the cache -- method works well*/
struct block_node* createBlock(char* binary_string, int sizeofCache, int association, int blocksize) {
	struct block_node* newNode = malloc(sizeof(struct block_node));
	int asso = association;
	int offsetbits = log2(blocksize);
	int indexbits = log2(sizeofCache/(asso*blocksize));
	int tagbits = 48 - offsetbits - indexbits;
	char* returntagString = malloc((sizeof(char)*tagbits*5));
	char* returnindexString = malloc((sizeof(char)*indexbits*5));
	char* offsetbitsString = malloc((sizeof(char)*offsetbits*5));

	for(int i=0; i< tagbits; i++) {
		returntagString[i]= binary_string[i]; 
	}
	newNode->tag = binary_to_decimal(returntagString);
	
	for(int j=0; j< indexbits; j++) {
		returnindexString[j] = binary_string[j+tagbits];
	}
	newNode->index = binary_to_decimal(returnindexString);
	
	for(int k=0; k<offsetbits; k++) {
		offsetbitsString[k] = binary_string[k+tagbits+indexbits];
	}
	newNode->offset = binary_to_decimal(offsetbitsString);
	newNode->next = NULL;
	return newNode;
} 





/*block_node* cache_create(char* asso,int cache_size,int block_size) {
	block_node* cache = createHash(block_size, cache_size, asso);
}*/


long binary_to_decimal (char* binary) {
     
     int number = strlen(binary);
	long v =0;
	int n =0;
	int i;
	for(i = number-1; i>-1; i--) {
		int value = binary[i]-'0';
		v += pow(2,n)*(value);
		n++;
	}
	return v;
}
	
bool searchCache(struct block_node* cache,int asso, struct block_node* block) {
	int index = block->index;
        if(cache[index].next == NULL) { return false; }
	else {
		struct block_node* ptr = cache[index].next;
			while(ptr != NULL) {
				if(ptr->tag == block->tag) {
					return true;
				}
				ptr= ptr->next;
			}
	}

return false;
}
bool insertInCache(struct block_node* cache,int asso, struct block_node* block_to_insert) {	
	int index = block_to_insert->index;
	if(cache[index].next == NULL) {
		cache[index].next = block_to_insert;
		return true;
	}
	else {
		struct block_node* ptr = cache[index].next;
		struct block_node* prev = NULL;
		int i=0;
		for(i=0; i<asso; i++) {
			if(ptr == NULL) {
				prev->next = block_to_insert;
				//block_to_insert -> offset = 6;           ////////////////////////////////////Made change
				return true;
			}
			else {
				prev = ptr;
				ptr=ptr->next;
			}
		}
		/*if(i>= asso) {
			struct block_node* thing = cache[index].next;
			cache[index].next = thing->next;
			printf("deleted by fifo when cache was full: CHECK returning false\n");
			return false;
		}*/
	}
return false;
}
/*void delete_by_lru(struct block node*cache, struct block_node* block_to_insert) {
	int index = block_to_insert->index;
	

}*/
void delete_by_fifo(struct block_node* cache, struct block_node* block_to_insert) {
	int index = block_to_insert->index;
	struct block_node* thing = cache[index].next;
	cache[index].next = thing->next;
}







/*Method that creates the HashArray of pointers for our cache -- this method works*/
struct block_node* createHash(int blocksize,int cacheSize, int indicies) {
	struct block_node* hashpointer = malloc(sizeof(struct block_node)*indicies);
	return hashpointer;
}    /// Creates our hash table with pointers.





/*Method that checks the string of association and find the int of the association-- this method works*/
/*int check_asso(char * asso, int size_of_cache, int size_of_block) { method didnt work.
   int what_type = 0;
   char* assos = asso;
   if(strcmp(asso, "direct") == 0) {
	what_type = 1;
   }
   else if( strcmp( asso, "assoc") == 0) {
	what_type = size_of_cache/size_of_block ;
   }
   
   else {
	what_type = atoi(&assos[6]);
   } 
  return what_type;
}*/
		







/*Method that converts the hex-value-string into a binary-value-string--this method works*/
char* hex_to_binary(char* hex) {
    int i;
    int length = strlen(hex);
    char* binString = malloc(sizeof(char)*50);

    if(length < 14) {
	int z;
	for(z = length; z< 14; z++) {
	     strcat(binString, "0000");
	}
    }
    for(i=2;i<length;i++) {
        switch(hex[i]) {
            case '0':
                strcat(binString, "0000");
            break; 

            case '1':
                strcat(binString, "0001");
            break;
            
            case '2':
                strcat(binString, "0010");
            break;
            
            case '3':
                strcat(binString, "0011");
            break;

            case '4':
                strcat(binString, "0100");
            break;

            case '5':
                strcat(binString, "0101");
            break;
            
            case '6':
                strcat(binString, "0110");
            break;

            case '7':
                strcat(binString, "0111");
            break;

            case '8':
                strcat(binString, "1000");
                break;
            case '9':
                strcat(binString, "1001");
            break;

            case 'a':
                strcat(binString, "1010");
            break;

            case 'b':
                strcat(binString, "1011");
            break;

            case 'c':
                strcat(binString, "1100");
            break;

            case 'd':
                strcat(binString, "1101");
            break;

            case 'e':
                strcat(binString, "1110");
            break;

            case 'f':
                strcat(binString, "1111");
            break;
            
            default:
                break;
        }
        
    }
    return (char*)binString;
}
