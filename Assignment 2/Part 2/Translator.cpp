
/*
Translator.cpp
Description: A Translator Program using the Dictionary.
               // Reads a file, stores it in a Dictionary, 
               // then either finds the translation from user
               // or displays all of the translations
Author: Asheesh Yadav + Eshaan Virk
Date: March 15, 2024
*/

#include "Dictionary.h"  
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std; 

//helper function to display word translations
void display(WordPair &pair) {
    cout << pair << endl;
}


int main(int argc, char *argv[]) {

    // make sure user enters more than 2 inputs
    if (argc < 2) {
        cout << "Error: Incorrect Format" << endl;
        cout<< "Correct Format(1): ./translator <filename> [display]" << endl;
        cout<<"or"<<endl; 
        cout<<"Correct Format(2): ./translator <filename>"<<endl; 
        cout<< "(1) for all the translations "; 
        cout<< "(2)for specfiic translations" <<endl; 
        return 1;
    }

    // Open the file containing word pairs
    char *dataFileName = argv[1];
    ifstream dataFile(dataFileName);

    // Check if there was an error opening the file
    if (dataFile.is_open()==false) {
        cout << "Unable to open your file" << dataFileName << endl;
        cout<<"Please check the file name and try again"<<endl;
        return 1;
    }

    // Create an instance of the Dictionary class
    Dictionary translatorDictionary;  

    string dictWords;
    // Load word pairs into the dictionary
    while (getline(dataFile, dictWords)) {

    // Use stringstream in a means to 
    //extract the file for the word 
    // and the translation
    stringstream ss(dictWords);
    string userWord;
    string fileTranslation;

    //using the colon as the splitter
    // we find it to find the english word
    // and the translation
    size_t colonPos = dictWords.find(':');
    if (colonPos != string::npos) {

        //format logic: <word>:<translation>
        //find the ":" and 0 to ":" is the word
        // and ":" + 1 to the end is the translation
        userWord = dictWords.substr(0, colonPos);
        fileTranslation = dictWords.substr(colonPos + 1);

        WordPair pair(userWord, fileTranslation);
        try {
            // Insert the word pair into the dictionary
            translatorDictionary.put(pair); 

            // Catch exceptions: if the word pair cannot be inserted
            // or it already exists

        } catch (UnableToInsertException &anExcep) {

            cout << "Cannot Insert this" << userWord <<anExcep.what() << endl;
            // Skip this iteration and move to the next line
            continue;  

        } catch (ElementAlreadyExistsException &anExcep) {

            cout << "**Element Duplicate Detected** "<<userWord<< endl;
            continue; 
        }
    }
}
    //make sure there are 3 arguments and the 3rd word(or 2nd index in the argv[])
    // is display
    if (argc == 3 && string(argv[2]) == "display") {
        try {
            // Display the content of the dictionary
            translatorDictionary.displayContent(display);  
            // Catch exceptions: if the dictionary is empty
        } catch (EmptyDataCollectionException &anExcep) {
            cout << "**Data Collection is Empty** " << anExcep.what() << endl;
        }
    } else {
        // Translate English words entered by the user
        cout << "Enter an English word (CTRL+D to exit):" << endl;
        string englishWord;
        while (getline(cin, englishWord)) {
            
            if (cin.eof()==false) {
                // Only the English word is used for lookup
                WordPair targetPair(englishWord, ""); 

                try {
                    char colon = ':'; 

                    // Retrieve translation from the dictionary
                    WordPair translation = translatorDictionary.get(targetPair);  
                    cout << englishWord << colon << translation.getTranslation() << endl;

                  // Catch exceptions: if the dictionary is empty 
                  // or the word does not exist
                } catch (EmptyDataCollectionException &anExcep) {
                    cout << "**The Dictionary is Empty**" << endl;
                } catch (ElementDoesNotExistException &anExcep) {
                    cout << "**Not Found**"<<endl;
                }
            }
        }
    }

    return 0;
}
