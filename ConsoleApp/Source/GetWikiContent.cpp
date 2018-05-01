//
//  GetWikiContent.c
//  ConsoleApp - ConsoleApp
//
//  Created by Charan DSouza on 29/04/18.
//
#include "../JuceLibraryCode/JuceHeader.h"
#include "GetWikiContent.h"
#include <curl/curl.h>

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, MemoryBlock* pMemoryBlock){
    size_t realsize = size * nmemb;
    pMemoryBlock->append(contents,realsize);
    return realsize;
}

int getWikiContent(MemoryBlock* pMemoryBlock,char* title){
    int iReturnValue = -1;
    /* get a curl handle */
    CURL *curl = curl_easy_init();
    
    if(curl) {
        std::string postFileds("format=json&action=query&prop=extracts&exintro=&explaintext=&titles=");
        postFileds += title;
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://en.wikipedia.org/w/api.php");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFileds.c_str());
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)pMemoryBlock);
        
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
