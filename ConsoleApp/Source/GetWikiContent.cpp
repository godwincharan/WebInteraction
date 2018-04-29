//
//  GetWikiContent.c
//  ConsoleApp - ConsoleApp
//
//  Created by Charan DSouza on 29/04/18.
//

#include "GetWikiContent.h"
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

int getWikiContent(MemoryStruct* chunk,char* title){
    int iReturnValue = -1;
    /* get a curl handle */
    CURL *curl = curl_easy_init();
    
    if(curl) {
        std::string postFileds("action=query&prop=revisions&rvprop=content&rvsection=0&format=json&titles=");
        postFileds += title;
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://en.wikipedia.org/w/api.php");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFileds.c_str());
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk);
        
        /* some servers don't like requests that are made without a user-agent
         field, so we provide one */
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        /* Now run off and do what you've been told! */
        CURLcode res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            iReturnValue = 0;
        }
                
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return iReturnValue;
}
