/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "GetWikiContent.h"

int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "URL not specified\n");
        return 1;
    }

    /* In windows, this will init the winsock stuff */
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    /* Check for errors */
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_global_init() failed: %s\n", curl_easy_strerror(res));
        return 1;
    }
    
    MemoryStruct chunk;
    char* wikiPage = argv[2];
    if ( getWikiContent(&chunk, wikiPage) == 0){
        printf("%s\n", chunk.memory);
    }
    /* get a curl handle */
    CURL *curl = curl_easy_init();
    
    if(curl) {
        char *url = argv[1];
        
        /* specify target URL*/
        curl_easy_setopt(curl, CURLOPT_URL, url);
        
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
        
        /* set user name and password for the authentication */
        curl_easy_setopt(curl, CURLOPT_USERPWD, "AudioWorks:Charlie");
        
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        /* Now run off and do what you've been told! */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    return 0;
}
