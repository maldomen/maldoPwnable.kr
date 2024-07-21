#include <stdio.h>
#include <stdint.h>

/**
 * Program to dump raw hex 4 byte vector to file as char representation
 */

//Vector definition
#define vectorLen 4
uint32_t dataVector [vectorLen] = {0x21000000, 0x00DD0000, 0x00000900, 0x000000EC};
int main(){
    FILE *file;
    file = fopen("rawData", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    //sweep data vector
    for(uint64_t i = 0; i < vectorLen; i++){
        //sweep each byte
        for(int8_t j = 3; j >= 0; j--){
            //log into file the byte resulting from the conversion to char pointer shifted j bytes of dataVector[i] 
            fprintf(file, "%c", * ( ( (char *) (&dataVector[i]) ) + j )  );
        }
        
    }
    
    // Close the file
    fclose(file);
    
    return 0;
}