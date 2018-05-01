//
//  GetWikiContent.h
//  ConsoleApp - ConsoleApp
//
//  Created by Charan DSouza on 29/04/18.
//

#ifndef GetWikiContent_h
#define GetWikiContent_h

/** returns the content of the wiki page in MemoryStruck. The wiki page title needs to be passed as argument.

    @param chunk   The memory structure to fill with content. The internal memory will be expanded as per the wiki content.
    @param title   Title of the wiki page to get the content.
    @returns       0 if success -1 for failure.
 */
int getWikiContent(MemoryBlock* pMemoryBlock, char* title);
#endif /* GetWikiContent_h */
