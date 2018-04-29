//
//  Authenticate.cpp
//  ConsoleApp - ConsoleApp
//
//  Created by Charan DSouza on 29/04/18.
//

#include "Authenticate.hpp"
#include <curl/curl.h>
#include <string.h>

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;
    
    mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = '\0';
    
    return realsize;
}

int authenticateUser(MemoryStruct* chunk,const char* url){
    int iReturnValue = -1;
    /* get a curl handle */
    CURL *curl = curl_easy_init();
    if(curl) {
        /* specify target URL*/
        curl_easy_setopt(curl, CURLOPT_URL, url);
        
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
        
        /* set user name and password for the authentication */
        curl_easy_setopt(curl, CURLOPT_USERPWD, "AudioWorks:Charlie");
        
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk);
        
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
