
/** Cache Simulator written in C **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cache_simulator.h"


void createCache()
{
    cache = malloc(sizeof(CacheLine) * LineNbr);

    for(int i = 0; i < LineNbr; i++)
    {
        cache[i].valid = 0;
        cache[i].tag = (char *)malloc(sizeof(char) * 81);
        cache[i].tag = "-";
        cache[i].set = i / Associativity;
        cache[i].recent = 0;
        cache[i].dirty = 0;
        cache[i].tagLength = 1;
    }
}

void cacheRead(char address[])
{
    int setIndex = 
    
}
int main(void)
{
    //Declare variables

    FILE *traceFile;
    char* filePath = "";
    int indexOption = 0;
    char address[32];
    
    //Menu options for easy usability

    printf("Welcome to Cache Simulator!\n\n");
    printf("Please choose a binary file:\n");
    printf("1) First Index\n");
    printf("2) Last Index\n");
    printf("3) Random Index\n");
    scanf("%d", &indexOption);

    //Decide, based on user input, which file to open

    switch(indexOption){
        case 1:
            filePath = "./AddressTrace_FirstIndex.bin";
            break;
        case 2:
            filePath = "./AddressTrace_LastIndex.bin";
            break;
        case 3:
            filePath = "./AddressTrace_RandomIndex.bin";
            break;
 
    }

    //Open file

    traceFile = fopen(filePath, "r");
    
    //Initialize global cache
    
    createCache();
    
    //Reading the cache while scanning the file
    
    while(fscanf(traceFile, "%s", address) != EOF);
    {
        cacheRead(address);
    }
    //Information about cache metrics
    
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Hit Ratio: %d\n", hitRatio);

    return 0;

}
