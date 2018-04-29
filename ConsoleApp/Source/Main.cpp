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
#include "Authenticate.hpp"
#include "PostData.hpp"
#include "MemoryStruct.h"

int main(int argc, char **argv){
    if(argc < 3){
        fprintf(stderr, "Usage: ConsoleApp\n");
        return 1;
    }

    /* In windows, this will init the winsock stuff */
    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    /* Check for errors */
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_global_init() failed: %s\n", curl_easy_strerror(res));
        return 1;
    }
    
    MemoryStruct wikiData;
    char* wikiPage = argv[2];
    if ( getWikiContent(&wikiData, wikiPage) == 0){
        printf("%s\n", wikiData.memory);
    }
    
    MemoryStruct authData;
    char *url = argv[1];
    if ( authenticateUser(&authData, url) == 0){
        printf("%s\n", authData.memory);
    }
    
    char* uploadUrl= argv[3];
    if ( postData(&wikiData, uploadUrl) == 0){
        printf("Uploaded data succefully");
    }
    
    curl_global_cleanup();
    
    return 0;
}
