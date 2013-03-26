#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <byteswap.h>
#include <bitset>
#include <string>

using namespace std;

int main()
{
    int32_t ivalue = 12345678; 
    printf("xxxx %d %d\n", bswap_32(ivalue), ivalue);

    string str = "1010101010"; 
    bitset<32> bitvalue(str);
    ivalue = (int32_t) bitvalue.to_ulong();
    printf("haha %d %d\n", (int32_t) bswap_32(ivalue), ivalue);
    
    return 0;
}
