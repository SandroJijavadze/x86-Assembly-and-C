#include <stdio.h>
#include <stdlib.h>
extern unsigned long lfsrasm(unsigned long seed);
unsigned long lfsr(unsigned long seed){
    if(seed == 0){
        seed = 0x5AA5FF00;
    }
    unsigned long result = seed;

     // This could be implemented in one line as following:
     //    result =  (seed >> 1) | ((((seed >> 0) ^ (seed >> 2) ^ (seed >> 6) ^ (seed >> 7))&1) << 31);
     // but it would be easier to translate to assembly if we did id in following way;
    result ^= (seed >> 2);
    result ^= (seed >> 6);
    result ^= (seed >> 7);
    result &= 1;
    result = result << 31;
    seed = seed >> 1;
    result = seed | result;

    return result;
    // NOTE: I even removed return seed; and it worked perfectly, probably because code produced by GCC used EAX for calculations
    // inside the function body and EAX is where the return value is stored.

}

int main()
{
    // NOTE the enumeration of the taps and bits are according to the wikipedia article that you linked.
    unsigned long seed = 0x5AA5FF00;
    printf("Initial Seed = %.4x\n",  seed);
    printf(" N     C      Assembly\n");
    for(int i = 0; i < 20; i++){
    printf("%2d  %10u  %10u\n", i+1, lfsr(seed), lfsrasm(seed));
    seed = lfsrasm(seed);
    }
    return 0;
}
