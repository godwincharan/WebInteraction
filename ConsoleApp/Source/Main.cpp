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

void CreateMidiMessageSequence(char*);

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
    
    CreateMidiMessageSequence(wikiData.memory);
    curl_global_cleanup();
    
    return 0;
}

void CreateMidiMessageSequence(char* data){
    String str;
    var mainVar = JSON::parse (String(data));
    if (DynamicObject* mainObj = mainVar.getDynamicObject()){
        NamedValueSet& mainProps (mainObj->getProperties());
        for ( auto begin = mainProps.begin(), end = mainProps.end();begin != end; ++begin){
            if( begin->name == StringRef("query")){
                var queryVar (mainProps[begin->name]);
                if ( DynamicObject* queryObj = queryVar.getDynamicObject()){
                    NamedValueSet& queryProps (queryObj->getProperties());
                    for (auto begin= queryProps.begin(), end = queryProps.end();begin!= end; ++begin){
                        if( begin->name == StringRef("pages")){
                            var pagesVar (queryProps[begin->name]);
                            if ( DynamicObject* pagesObj = pagesVar.getDynamicObject()){
                                NamedValueSet& pagesProps (pagesObj->getProperties());
                                for (auto begin= pagesProps.begin(), end = pagesProps.end();begin!= end; ++begin ){
                                    var pageNumberVar (pagesProps[begin->name]);
                                    if ( DynamicObject* pageNumberObj = pageNumberVar.getDynamicObject()){
                                        NamedValueSet& pageNumberProps (pageNumberObj->getProperties());
                                        for (auto begin= pageNumberProps.begin(), end = pageNumberProps.end();begin!= end; ++begin){
                                            if( begin->name == StringRef("extract")){
                                                var pageExtractVar (pageNumberProps[begin->name]);
                                                if ( pageExtractVar.isString()){
                                                    str = pageExtractVar.toString();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("\nMidiMessage string\n%s\n", str.toRawUTF8());
}
