//
//  main.cpp
//  markov
//
//  Created by Jake Screen on 3/08/20.
//  Copyright © 2020 Jake Screen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdio.h>
using namespace std;

std::vector<std::string> readInFile(string name){ //opens up supplied filename and reads in text into vector
    ifstream infile;
    string word;
    std::vector<std::string> fileInput;
    int i = 0;
    infile.open(name);
    if(!infile){ //if opening file failed
        cout << "cant open file";
        exit(1);
    }
    while(infile >> word){ // while there are words left in file
        fileInput.insert(fileInput.begin() + i, word);
        i++;
    }
    infile.close(); // close the file
    return fileInput;
}


std::vector<std::string> genPrefixes(std::vector<std::string> words){ //generate all prefixes, unique words
    std::vector<std::string>  prefixes;
    int j = 0;
    for(std::size_t i = 0; i < words.size(); ++i){
        if(std::count(prefixes.begin(), prefixes.end(), words.at(i))){ // check if word already exists in prefix vector
        }
        else{
            prefixes.insert(prefixes.begin() + j, words.at(i));
            j++;
        }
    }
    return prefixes;
}

std::vector< std::vector<std::string> > genSuffixes(std::vector<std::string> words, std::vector<std::string> prefix){
    std::vector< std::vector<std::string> > suffixes;
    std::vector<std::string> blank;
    for(int i = 0; i < prefix.size(); ++i){
        suffixes.insert(suffixes.begin() + i, blank); // adds a black vector to each index of suffix, fixes out-of-array issues
    }

    for(std::size_t i = 0; i < words.size(); ++i){
        //get index of words location in prefix vector
        std::vector<string>::iterator it = std::find(prefix.begin(), prefix.end(), words.at(i));
        int index = std::distance(prefix.begin(), it); //
        for(int k = 1; k < 4 && (i+k) < words.size(); ++k){ // look at next 3 words, add them to the vector at index of suffix vector
            suffixes.at(index).insert(suffixes.at(index).begin() + (k-1), words.at(i+k));
        }
    }
    return suffixes;
}


void generateText(int nwords, std::vector<std::string> prefixes, std::vector< std::vector<std::string> > suffixes){
    int index = rand() % prefixes.size(); // grab a random first word
    string firstWord = prefixes.at(index);
    cout << firstWord + " ";
    ofstream outputFile;
    outputFile.open("output.txt"); // make and open output file
    for(int i = 0; i < nwords; ++i){ // till the specified number of words has been made
        int oldIndex = index; // save current index for next loop
        index = rand() % suffixes.at(oldIndex).size(); // get a random next possible suffix
        string word = suffixes.at(oldIndex).at(index);
        outputFile << word + " "; // add word to output file
        cout << word + " "; // print for debug
    }
    outputFile.close();
    
}


int main(int argc, const char * argv[]) {
    std::vector<std::string> originalWords; //vector of all words from file
    originalWords = readInFile(argv[1]); //what sample text to pull from
    std::vector<std::string> prefixess = genPrefixes(originalWords); // all possible prefixes, first word in a chain
    std::vector< std::vector<std::string> > suffixess = genSuffixes(originalWords, prefixess); //all possible
    //words that could follow the word at the same index as prefixwss vector
    srand(time(NULL));// seed randomness
    generateText(55, prefixess, suffixess); // generate random text, 55 words since average word length is 5
    cout << "Saved to output.txt"<<endl;
    return 0;
}


