//
//  MemoryStruct.h
//  ConsoleApp
//
//  Created by Charan DSouza on 29/04/18.
//

#ifndef MemoryStruct_h
#define MemoryStruct_h
#include "../JuceLibraryCode/JuceHeader.h"
#include <stdlib.h>

typedef struct MemoryStruct {
    char *memory;
    int size;
    MemoryStruct(){
        size = 0; /* no data at this point */
        memory = (char*)malloc(size+1); /* will be grown as needed by the realloc above */
        if (memory == NULL) {
            fprintf(stderr, "malloc() failed\n");
            exit(EXIT_FAILURE);
        }
        memory[0] = '\0';
    }
    
    MemoryStruct(const MemoryStruct& inData){
        size = inData.size;
        memory = (char*)malloc(inData.size);
        if (memory == NULL) {
            fprintf(stderr, "malloc() failed\n");
            exit(EXIT_FAILURE);
        }
        memcpy(memory, inData.memory, inData.size);
    }
    
    ~MemoryStruct(){
        free(memory);
    }
}MemoryStruct;
#endif /* MemoryStruct_h */
