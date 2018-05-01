//
//  PostData.cpp
//  ConsoleApp - ConsoleApp
//
//  Created by Charan DSouza on 29/04/18.
//
#include "../JuceLibraryCode/JuceHeader.h"
#include "PostData.hpp"
#include <curl/curl.h>

size_t dataCopiedSoFar =0;
static size_t read_callback(void *dest, size_t size, size_t nmemb, MemoryBlock* pMemoryBlock){
    size_t buffer_size = size*nmemb;
    
    if(pMemoryBlock->getSize()-dataCopiedSoFar) {
        /* copy as much as possible from the source to the destination */
        size_t copy_this_much = pMemoryBlock->getSize() - dataCopiedSoFar;
        if(copy_this_much > buffer_size){
            copy_this_much = buffer_size;
        }
        pMemoryBlock->copyTo(dest,(int)dataCopiedSoFar, copy_this_much);
        dataCopiedSoFar += copy_this_much;
        return copy_this_much; /* we copied this many bytes */
    }
    return 0; /* no more data left to deliver */
}


int postData(MemoryBlock* pMemoryBlock, const char* url){
    int iReturnValue = -1;
    /* get a curl handle */
    CURL *curl = curl_easy_init();
    
    if(curl) {
        /* specify target URL, and note that this URL should also include a file
         name, not only a directory (as you can do with GTP uploads) */
        curl_easy_setopt(curl, CURLOPT_URL, url);
        

        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        
        /* we want to use our own read function */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        
        /* pointer to pass to our read function */
        dataCopiedSoFar = 0;
        curl_easy_setopt(curl, CURLOPT_READDATA, pMemoryBlock);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)pMemoryBlock->getSize());

        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        /* Now run off and do what you've been told! */
        CURLcode res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else{
            iReturnValue = 0;
        }
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return iReturnValue;
}
