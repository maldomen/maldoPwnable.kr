#include <stdio.h>
#include <stdint.h>

#define TEST 1

#if TEST
#include <string.h>

unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char* p){
        int* ip = (int*)p;
        int i;
        int res=0;
        for(i=0; i<5; i++){
                res += ip[i];
        }
        return res;
}

char buffer[256] = {0};

#endif


/**
 * Program to dump raw hex 4 byte vector to file as char representation
 */

//Vector definition
#define vectorLen 5
uint32_t dataVector [vectorLen] = {0x1D010101, 0x01D90101, 0x01010501, 0x010101E8, 0x01010101};
int main(){
    FILE *file;
    file = fopen("rawData.bin", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    //sweep data vector
    for(uint64_t i = 0; i < vectorLen; i++){
        //sweep each byte
        for(int8_t j = 0; j < 4; j++){
            //log into file the byte resulting from the conversion to char pointer shifted j bytes of dataVector[i] 
            fprintf(file, "%c", * ( ( (char *) (&dataVector[i]) ) + j )  );

            #if TEST
            buffer[ (i*4) + (j) ] = * ( ( (char *) (&dataVector[i]) ) + j )  ;
            #endif
        }
        
    }
    
    /** 
    for(uint8_t i = 0; i < 4; i++){
        fprintf(file, "%c", 0x00  );
    } */

    // Close the file
    fclose(file);

    #if TEST

    if(strlen(buffer) != 20){
            printf("passcode length should be 20 bytes\n");
            return 0;
    }

    if(hashcode == check_password( buffer )){
            printf("/bin/cat flag");
            return 0;
    } else printf("wrong password\n");

    #endif
    
    return 0;
}