
/** Cache Simulator written in C **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "cache_simulator.h"

//
// This function initializes each of the values that are in each of the cache blocks
//
void createCache()
{
    for(int i = 0; i < LineNbr; i++)
    {
			for(int j = 0; j < Associativity; j++)
			{
        cache[i][j].valid = 0;
        cache[i][j].tag = 0;
			}
    }
}

//
// Printing all of the given macro information from the cache_simulator.h file
//
void printCacheData()
{
		printf("CacheSize_Exp: %d\n", CacheSize_Exp);
		printf("CacheSize_Nbr: %d\n", CacheSize_Nbr);
		printf("AddressSize_Exp: %d\n", AddressSize_Exp);
		printf("Associativity: %d\n", Associativity);
		printf("BlockSize_Exp: %d\n", BlockSize_Exp);
		printf("BlockSize: %d\n", BlockSize);
		printf("Lines_Exp: %d\n", Lines_Exp);
		printf("LineNbr: %d\n", LineNbr);
		printf("Lines_Mask: %d\n", Lines_Mask);
		printf("Tag_Exp: %d\n", Tag_Exp);
		printf("TagNbr: %d\n", TagNbr);
		printf("Tag_Mask: %d\n", Tag_Mask);
}

//
// This function serves as a way to convert the values found in the .bin files into
// true binary. The parameter 'character' is an individual address trace passed in
// to be converted.
//
long decimalToBinary(uint32_t character)
{
		//Values used in conversion
		long test = (unsigned char)(character);
		long remainder;
		long binary = 0;
		long j = 1;
			
				//Conversion process
				while(test != 0){
					remainder = test%2;
					test = test/2;
					binary = binary + (remainder * j);
					j = j*10;
				}

				return binary;
}

//
// Replacement algorithm: random. Fair, but perhaps less efficient. Utilizes 
// functions from <time.h> in order to calculate random values based on the 
// cache associativity and number of lines.
//
void randomReplacement(uint32_t address, uint32_t cacheTag)
{

		int randomLine = rand() % LineNbr;
		int randomBlock = 0;

		switch(Associativity){
			case 1:
				cache[randomLine][randomBlock].tag = cacheTag;
				break;
			case 2:
				randomBlock = rand() % 2;
				cache[randomLine][randomBlock].tag = cacheTag;
				break;
			case 4:
				randomBlock = rand() % 4;
				cache[randomLine][randomBlock].tag = cacheTag;
				break;
			case 8:
				randomBlock = rand() % 8;
				cache[randomLine][randomBlock].tag = cacheTag;
				break;
		}
}


int main(void)
{
    //Declare variables

    FILE *traceFile;
    char* filePath = "";
    int indexOption = 0;

		//Variable used to hold addresses from trace file. Chose uint32_t because
		//the addresses are each 32-bits.

    uint32_t address;
    
		//Start timer for random replacement algorithm. This only needs to be called once.

		srand(time(NULL));

    printf("\nWelcome to Cache Simulator!\n\n");

		//Macro information

		printCacheData();

		//Menu options for easy usability

    printf("\nPlease choose a binary file:\n");
    printf("1) First Index\n");
    printf("2) Last Index\n");
    printf("3) Random Index\n");
    scanf("%d", &indexOption);

    //Decide, based on user input, which .bin file to open
		
    switch(indexOption){
        case 1:
            filePath = "AddressTrace_FirstIndex.bin";
            break;
        case 2:
            filePath = "AddressTrace_LastIndex.bin";
            break;
        case 3:
            filePath = "AddressTrace_RandomIndex.bin";
            break;
 
    }
		
    //Open file

    if((traceFile = fopen(filePath, "rb")) == NULL)
		{
			printf("Error in opening file. Exiting...\n");
		}
    
    //Initialize global cache
    
    createCache();
    
    //Reading the cache while scanning the file
 
		//Values used to iterate through the cache when values are read from the .bin files

   	int blockIndex = 0;
		int foundVal = 0;
		long binary = 0;
		uint32_t cacheLine = 0;
		uint32_t cacheTag = 0;

		//Use fread to iterate through the binary file. Since fread returns 0 when the end of
		//the file is reached, this is used to determine when we break from the while loop.
    while((fread(&address, 4, 1, traceFile) != 0))
		{
				//Variables used to move through the cache, as well as select the proper tag values
				foundVal = 0;
				blockIndex = 0;
				cacheLine = (address >> BlockSize_Exp) & Lines_Mask;
				cacheTag = ((address >> (BlockSize_Exp + Lines_Exp)) & Tag_Mask);

				//Iterate through each line of the cache, checking each block for hits
				for(;blockIndex < Associativity; blockIndex++)
				{
						//If the tag of the cache matches our target tag, a hit is found.
						if(cache[cacheLine][blockIndex].tag == cacheTag)
						{
							//Increment the hits, break from for-loop.
							hits++;
							foundVal = 1;
							break;
						}
						else if(foundVal == 0 && blockIndex == Associativity - 1)
						{
							//This branch is only entered if each block in a line has yielded no hits.
							misses++;
		
							//If no hits, random replacement algorithm called, and current address passed in.
							randomReplacement(address, cacheTag);
						}
				}
		}
    
		//
    //Information about cache metrics
		//

    hitRatio = ((hits/(hits+misses))*100.0);
    printf("Hits: %.00f\n", hits);
    printf("Misses: %.00f\n", misses);
    printf("Hit Ratio: %.02f%%\n", hitRatio);

		//
		//Close the trace file
		//

		fclose(traceFile);

    return 0;

}
