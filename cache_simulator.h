
#ifndef cache_simulator_h
#define cache_simulator_h

#define CacheSize_Exp       15
#define CacheSize_Nbr       (1 << CacheSize_Exp)

#define AddressSize_Exp     32

#define Associativity_Exp   1
#define Associativity       (1 << Associativity_Exp)

#define BlockSize_Exp       6
#define BlockSize           (1 << BlockSize_Exp)

#define Lines_Exp           ((CacheSize_Exp) - (Associativity_Exp + BlockSize_Exp))
#define LineNbr             (1 << Lines_Exp)
#define Lines_Mask          (LineNbr - 1)

#define Tag_Exp             (AddressSize_Exp - BlockSize_Exp - Lines_Exp)
#define TagNbr              (1 << Tag_Exp)
#define Tag_Mask            (TagNbr - 1)


//
//Struct used to represent a single line or block in a cache. Contains
//a variable to determine it's validity, and one to hold a tag.
//

typedef struct CacheLine
{
	int valid;
	int tag;
} CacheLine; 

//
//Globally declared cache, as a 2D array of CacheLine (block) structs
//

CacheLine cache[LineNbr][Associativity];

//
// Variables needed for cache metrics
//

double hits = 0, misses = 0;
float hitRatio = 0;

#endif
