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

void CreateMidiMessageSequence(char*,char*);

int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "Usage: ConsoleApp WikiSearchKey\n");
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
    char* wikiPage = argv[1];
    if ( getWikiContent(&wikiData, wikiPage) == 0){
        printf("%s\n", wikiData.memory);
    }
    
    MemoryStruct authData;
    char url[255]="https://httpbin.org/digest-auth/auth/AudioWorks/Charlie/MD5/never";
    if ( authenticateUser(&authData, url) == 0){
        printf("%s\n", authData.memory);
    }

    char uploadUrl[255]="https://httpbin.org/post";
    if ( postData(&wikiData, uploadUrl) == 0){
        printf("Uploaded data succefully");
    }
    
    CreateMidiMessageSequence(wikiData.memory,wikiPage);
    curl_global_cleanup();
    
    return 0;
}

void makeAllNoteOff(MidiMessageSequence& sequence ){
    sequence.addEvent( MidiMessage::allNotesOff(1));
    sequence.addEvent( MidiMessage::allNotesOff(2));
    sequence.addEvent( MidiMessage::allNotesOff(3));
    sequence.addEvent( MidiMessage::allNotesOff(4));
    sequence.addEvent( MidiMessage::allNotesOff(5));
    sequence.addEvent( MidiMessage::allNotesOff(6));
    sequence.addEvent( MidiMessage::allNotesOff(7));
    sequence.addEvent( MidiMessage::allNotesOff(8));
    sequence.addEvent( MidiMessage::allNotesOff(9));
    sequence.addEvent( MidiMessage::allNotesOff(10));
    sequence.addEvent( MidiMessage::allNotesOff(11));
    sequence.addEvent( MidiMessage::allNotesOff(12));
    sequence.addEvent( MidiMessage::allNotesOff(13));
    sequence.addEvent( MidiMessage::allNotesOff(14));
    sequence.addEvent( MidiMessage::allNotesOff(15));
    sequence.addEvent( MidiMessage::allNotesOff(16));
}

void CreateMidiMessageSequence(char* data,char* fileName){
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
    if ( str.length()){
        MidiFile midiFile;
        
        float velocity = 0;
        int channelNumber = 1;
        int noteNumber = 0;
        int programNumber = 0;
        int controllerNumber=0;
        int controllerValue = 0;
        MidiMessageSequence sequence;
        bool isNoteOn = false;
        for(int i = 0 ; i < str.length(); i++){
            switch(tolower(str[i])  ){
                case 'q': case 'r': case 's': case 't': case 'v': case 'w': case 'x': case 'y': case 'z':{
                    if ( isNoteOn){
                        sequence.addEvent( MidiMessage::noteOff(channelNumber, noteNumber, velocity));
                        isNoteOn = false;
                    }
                    velocity = 0;
                    break;
                }
                case 'g': case 'h': case 'j': case 'k': case 'l': case 'm': case 'n': case 'p':{
                    if ( !isNoteOn){
                        sequence.addEvent( MidiMessage::noteOn(channelNumber, noteNumber, velocity));
                        isNoteOn= true;
                    }
                    velocity = 0;
                    break;
                }
                case ' ':{
                    //Kept program number and note number as same variable as they change from 0 -127
                    sequence.addEvent( MidiMessage::programChange(channelNumber, programNumber));
                    break;
                }
                case '~': case '!': case '@': case '#': case '$': case '^': case '&': case '(': case ')':{
                    controllerNumber = (controllerNumber+5)%120;
                    controllerValue = (controllerValue+16)%128;
                    break;
                }
                case '*': case '/': case '+': case '-': case '%':{
                    sequence.addEvent( MidiMessage::controllerEvent(channelNumber,controllerNumber,controllerValue));
                    break;
                }
                case 'i': case 'o': case 'u':{
                    if ( !isNoteOn){
                        noteNumber = (noteNumber+16)%128;
                    }
                    programNumber = (programNumber+16)%128;
                    break;
                }
                case '0':{
                    if ( !isNoteOn){
                        channelNumber = 1;
                    }
                    break;
                }
                case '1':{
                    if ( !isNoteOn){
                        channelNumber = 2;
                    }
                    break;
                }
                case '2':{
                    if ( !isNoteOn){
                        channelNumber = 3;
                    }
                    break;
                }
                case '3':{
                    if ( !isNoteOn){
                        channelNumber = 4;
                    }
                    break;
                }
                case '4':{
                    if ( !isNoteOn){
                        channelNumber = 5;
                    }
                    break;
                }
                case '5':{
                    if ( !isNoteOn){
                        channelNumber = 6;
                    }
                    break;
                }
                case '6':{
                    if ( !isNoteOn){
                        channelNumber = 7;
                    }
                    break;
                }
                case '7':{
                    if ( !isNoteOn){
                        channelNumber = 8;
                    }
                    break;
                }
                case '8':{
                    if ( !isNoteOn){
                        channelNumber = 9;
                    }
                    break;
                }
                case '9':{
                    if ( !isNoteOn){
                        channelNumber = 10;
                    }
                    break;
                }
                case 'a':{
                    if ( !isNoteOn){
                        channelNumber = 11;
                    }
                    break;
                }
                case 'b':{
                    if ( !isNoteOn){
                        channelNumber = 12;
                    }
                    break;
                }
                case 'c':{
                    if ( !isNoteOn){
                        channelNumber = 13;
                    }
                    break;
                }
                case 'd':{
                    if ( !isNoteOn){
                        channelNumber = 14;
                    }
                    break;
                }
                case 'e':{
                    if ( !isNoteOn){
                        channelNumber = 15;
                    }
                    break;
                }
                case 'f':{
                    if ( !isNoteOn){
                        channelNumber = 16;
                    }
                    break;
                }
                case '.':{
                    makeAllNoteOff(sequence);
                    midiFile.addTrack(sequence);
                    sequence.clear();
                    isNoteOn = false;
                    break;
                }
                case '\n':{
                    sequence.addEvent( MidiMessage::midiClock());
                    break;
                }
                case '\0':{
                    makeAllNoteOff(sequence);
                    sequence.addEvent( MidiMessage::endOfTrack());
                    midiFile.addTrack(sequence);
                    sequence.clear();
                    isNoteOn = false;
                    break;
                }
                default:{
                    velocity = jmax(velocity+0.25,1.0);
                    break;
                }
            }
        }
        File outFile(File::getCurrentWorkingDirectory().getFullPathName() + File::getSeparatorString() + (const char*)fileName + ".mid");
        FileOutputStream stream(outFile);
        midiFile.writeTo(stream);
    }
}

//{"batchcomplete":"","query":{"normalized":[{"from":"pizza","to":"Pizza"}],"pages":{"24768":{"pageid":24768,"ns":0,"title":"Pizza","extract":"Pizza is a traditional Italian dish consisting of a yeasted flatbread typically topped with tomato sauce and cheese and baked in an oven. It can also be topped with additional vegetables, meats, and condiments, and can be made without cheese.\nThe term pizza was first recorded in the 10th century, in a Latin manuscript from the Southern Italian town of Gaeta in Lazio, on the border with Campania. Modern pizza was invented in Naples, and the dish and its variants have since become popular and common in many areas of the world. In 2009, upon Italy's request, Neapolitan pizza was registered with the European Union as a Traditional Speciality Guaranteed dish. The Associazione Verace Pizza Napoletana (True Neapolitan Pizza Association), a non-profit organization founded in 1984 with headquarters in Naples, aims to \"promote and protect... the true Neapolitan pizza\".\nPizza is one of the most popular foods in the world and a common fast food item in Europe and North America. Many independent or chain restaurants, cafes, and fast food outlets offer pizza. Restaurants or chains specializing in pizza are pizzerias. Pizza delivery is common in some parts of the world.\nPizza is sold fresh or frozen, either whole or in portions. Various types of ovens are used to cook them and many varieties exist. Several similar dishes are prepared from ingredients commonly used in pizza preparation, such as calzone and stromboli. In the United States, pizza is usually eaten out of hand after dividing into slices from a large pizza or small pizzetta as a whole. In Italy, pizza is eaten with a fork and knife in restaurants, but is also sold to take away and eaten out of hand. Frozen pizza became popular in the late 20th century."}}}}
