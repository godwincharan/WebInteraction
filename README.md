This project is for getting content from wiki page provided by the user. Example "Pizza"
This project authenticates the user to https://httpbin.org.
This project then uploads the wiki content to https://httpbin.org/post route.
This project then creates random Midi messages from the wiki page text.

Libraries used for this projects are:
Curl -> User for getting wiki content, Authentication and uploading the data.
JUCE -> Used for general memory handlingI(MemoryBlock) and for createing the Midi messages and creating the Midi message sequence. Its also used for writting the mdi messages to .mid file.


Usage: 
ConsoleApp wikiSearchKey

Example:
ConsoleApp pizza
JUCE v5.3.1
==================================== Getting Wiki Content =========================================
================================ Wiki contents for pizza is =======================================
{"batchcomplete":"","query":{"normalized":[{"from":"pizza","to":"Pizza"}],"pages":{"24768":{"pageid":24768,"ns":0,"title":"Pizza","extract":"Pizza is a traditional Italian dish consisting of a yeasted flatbread typically topped with tomato sauce and cheese and baked in an oven. It can also be topped with additional vegetables, meats, and condiments, and can be made without cheese.\nThe term pizza was first recorded in the 10th century, in a Latin manuscript from the Southern Italian town of Gaeta in Lazio, on the border with Campania. Modern pizza was invented in Naples, and the dish and its variants have since become popular and common in many areas of the world. In 2009, upon Italy's request, Neapolitan pizza was registered with the European Union as a Traditional Speciality Guaranteed dish. The Associazione Verace Pizza Napoletana (True Neapolitan Pizza Association), a non-profit organization founded in 1984 with headquarters in Naples, aims to \"promote and protect... the true Neapolitan pizza\".\nPizza is one of the most popular foods in the world and a common fast food item in Europe and North America. Many independent or chain restaurants, cafes, and fast food outlets offer pizza. Restaurants or chains specializing in pizza are pizzerias. Pizza delivery is common in some parts of the world.\nPizza is sold fresh or frozen, either whole or in portions. Various types of ovens are used to cook them and many varieties exist. Several similar dishes are prepared from ingredients commonly used in pizza preparation, such as calzone and stromboli. In the United States, pizza is usually eaten out of hand after dividing into slices from a large pizza or small pizzetta as a whole. In Italy, pizza is eaten with a fork and knife in restaurants, but is also sold to take away and eaten out of hand. Frozen pizza became popular in the late 20th century."}}}}
============================== Getting Wiki data success =======================================


================================ Authenticatiing user =========================================
================================ Authentication Result ========================================
{
  "authenticated": true, 
  "user": "AudioWorks"
}

================================ Authentication success ========================================


==================================== Postiung Data ============================================
{
  "args": {}, 
  "data": "", 
  "files": {}, 
  "form": {
    "{\"batchcomplete\":\"\",\"query\":{\"normalized\":[{\"from\":\"pizza\",\"to\":\"Pizza\"}],\"pages\":{\"24768\":{\"pageid\":24768,\"ns\":0,\"title\":\"Pizza\",\"extract\":\"Pizza is a traditional Italian dish consisting of a yeasted flatbread typically topped with tomato sauce and cheese and baked in an oven. It can also be topped with additional vegetables, meats, and condiments, and can be made without cheese.\\nThe term pizza was first recorded in the 10th century, in a Latin manuscript from the Southern Italian town of Gaeta in Lazio, on the border with Campania. Modern pizza was invented in Naples, and the dish and its variants have since become popular and common in many areas of the world. In 2009, upon Italy's request, Neapolitan pizza was registered with the European Union as a Traditional Speciality Guaranteed dish. The Associazione Verace Pizza Napoletana (True Neapolitan Pizza Association), a non-profit organization founded in 1984 with headquarters in Naples, aims to \\\"promote and protect... the true Neapolitan pizza\\\".\\nPizza is one of the most popular foods in the world and a common fast food item in Europe and North America. Many independent or chain restaurants, cafes, and fast food outlets offer pizza. Restaurants or chains specializing in pizza are pizzerias. Pizza delivery is common in some parts of the world.\\nPizza is sold fresh or frozen, either whole or in portions. Various types of ovens are used to cook them and many varieties exist. Several similar dishes are prepared from ingredients commonly used in pizza preparation, such as calzone and stromboli. In the United States, pizza is usually eaten out of hand after dividing into slices from a large pizza or small pizzetta as a whole. In Italy, pizza is eaten with a fork and knife in restaurants, but is also sold to take away and eaten out of hand. Frozen pizza became popular in the late 20th century.\"}}}}": ""
  }, 
  "headers": {
    "Accept": "*/*", 
    "Connection": "close", 
    "Content-Length": "1878", 
    "Content-Type": "application/x-www-form-urlencoded", 
    "Expect": "100-continue", 
    "Host": "httpbin.org"
  }, 
  "json": null, 
  "origin": "183.82.17.87", 
  "url": "https://httpbin.org/post"
}
============================== Succefully Posted data =========================================



