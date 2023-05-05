#include <string>
#include <vector>
#include <iostream>
#include <climits>

#include "Trie.hpp"
#include "LZ78.hpp"

#define MAXBYTEVALUE UCHAR_MAX

unsigned int numBytes(int num){
    unsigned int bytes;
    bytes = 1;
    while((num > MAXBYTEVALUE) && (bytes < sizeof(int))){
        num /= (MAXBYTEVALUE + 1);
        bytes++;
    }
    return bytes;
}

void lz78_compress(std::ifstream& input, std::ofstream& output) {

    std::vector<std::pair<unsigned int, unsigned char>> outputPairs;

    Dictionary dict;

    unsigned int code;
    code = 1;

    unsigned int maxCodeSave;
    maxCodeSave = 0;
    
    TrieNode *curr;
    curr = dict.getRoot();

    TrieNode *currAux;
    currAux = dict.getRoot();

    std::string str;
    str = "";

    std::string buffer;
    buffer = "";

    char ch;

    while (input.get(ch)) {
        buffer = str + ch;

        curr = dict.find(curr, ch);
        
        if (curr == currAux) {
            
            outputPairs.push_back({currAux->code, ch});

            dict.insert(curr, code, ch, false);

            str = "";
            code++;

            if(currAux->code > maxCodeSave){
                maxCodeSave = currAux->code;
            }
                
            curr = dict.getRoot();
            currAux = dict.getRoot();

        } else {
            str = buffer;
            currAux = curr;
        }
    }
    if (!str.empty()) {
        unsigned int code = dict.findString(str)->code;

        outputPairs.push_back({code, '\0'});

        if(code > maxCodeSave)
            maxCodeSave = currAux->code;
    }

    output.write((char*)(&maxCodeSave), sizeof(unsigned int));
    output.write("\n", sizeof(const char));

    unsigned int numbytes2code;
    numbytes2code = numBytes(maxCodeSave);

    std::cout << maxCodeSave << " " << numbytes2code << std::endl;

    for (auto it = outputPairs.begin(); it != outputPairs.end(); ++it){
        output.write((char*)(&it->first), numbytes2code);
        output.write((char*)(&it->second),sizeof(unsigned char));
        std::cout << it->second<< std::endl;
    }
}


void lz78_decompress(std::ifstream& input, std::ofstream& output){

    Dictionary dict;

    int maxCodeSave;
    input.read((char*)&maxCodeSave, sizeof(unsigned int));
    input.get(); //remove '\n'

    unsigned int numbytes2code;
    numbytes2code = numBytes(maxCodeSave);
    std::cout << maxCodeSave << " " << numbytes2code << std::endl;

    unsigned int code;
    code = 1;
    unsigned int preffixCode;

    unsigned char chCode;
    unsigned char ch;

    while(input.read((char*)&chCode, numbytes2code)
       && input.read((char*)&ch, sizeof(unsigned char))){

        preffixCode = chCode;
        TrieNode* curr = dict.findCode(preffixCode);
        
        if(curr == nullptr){
            std::cerr << "Code " << preffixCode << " not found" << std::endl;
            exit(1);
        }
        else{
            output << dict.getStringToNode(curr) << ch;
            dict.insert(curr, code, ch, true);
            code++;
        }
    }
}