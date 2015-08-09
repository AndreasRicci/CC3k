#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#include <iostream>
#include <string>
#include <map>

// The following describe the languages available to use
const int numLanguages = 1;
const std::string english = "english";
const std::string availableLanguages[numLanguages] = {english};

class Language {
private:
    static std::map<std::string, std::map<std::string, std::string>* > languageToDictionary; // All languages
    static std::map<std::string, std::string> englishDictionary;                             // All English text
    static bool languageInitialized;                                                         // Is our language ready to use?
    
    Language();
    ~Language();
    
    static void initLanguage();                                                              // Set up all of the dictionaries
public:
    static std::string getText(std::string shorthand, std::string language = english);       // Get full text given a shorthand
};

#endif
