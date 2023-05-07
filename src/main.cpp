#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "LZ78.hpp"

struct options{
  bool COMPRESSION;
  std::string inputFileName;
  std::string outputFileName;
};

std::ifstream openInFile(std::string fileName, bool isCompress){
  std::ifstream inFile;
  if(isCompress)
    inFile.open(fileName);
  else
    inFile.open(fileName, std::ifstream::binary);

  if (!inFile.is_open()) {
    std::cerr << "Error: Failed to open input file. \'" << fileName << "\'" << std::endl;
    exit(1);
  }
  return inFile;
}

std::ofstream openOutFile(std::string fileName, bool isCompress){
  std::ofstream outFile;
  if(isCompress)
    outFile.open(fileName, std::ofstream::binary);
  else
    outFile.open(fileName);

  if (!outFile.is_open()) {
    std::cerr << "Error: Failed to open output file. \'" << fileName << "\'" << std::endl;
    exit(1);
  }
  return outFile;
}

void printOutFile(std::ofstream& outFile, std::string decompressText){
  outFile << decompressText << std::endl;
}

void compress(options* opt){
  std::ifstream inFile;
  inFile = openInFile(opt->inputFileName, opt->COMPRESSION);

  std::ofstream outFile;
  outFile = openOutFile(opt->outputFileName, opt->COMPRESSION);

  LZ78Compress(inFile, outFile);
  
  inFile.close();
  outFile.close();
}

void decompress(options* opt){
  std::ifstream inFile;
  inFile = openInFile(opt->inputFileName, opt->COMPRESSION);

  std::ofstream outFile;
  outFile = openOutFile(opt->outputFileName, opt->COMPRESSION);
  
  LZ78Decompress(inFile, outFile);

  inFile.close();
  outFile.close();
}

void getOptions(int& argc, char **argv, options* opt){

  int argsWFileOut;
  argsWFileOut = 5;

  int argsWOFileOut;
  argsWOFileOut = 3;

  if (argc != argsWOFileOut && argc != argsWFileOut) {
    std::cerr << "Error: Incorrect number of arguments passed. " 
              << "Please provide the correct number of arguments." << std::endl;
    exit(1);
  }

  std::string optionSelected;
  optionSelected = argv[1];

  if(optionSelected.compare("-c") == 0){
    opt->COMPRESSION = true;
  }
  else if(optionSelected.compare("-x") == 0){
    opt->COMPRESSION = false;
  }
  else{
    std::cerr << "Error: Invalid option selected. " 
              << "Please choose either compression \'-c\' or decompression \'-x\'." << std::endl;
    exit(1);
  }

  opt->inputFileName = argv[2];
  
  std::string txtExt = ".txt";
  std::string z78Ext = ".z78";

  if ((opt->inputFileName.length() >= txtExt.length()) &&
      (opt->inputFileName.substr(opt->inputFileName.length() - txtExt.length()) == txtExt) &&
      (opt->COMPRESSION)) {
    opt->outputFileName = opt->inputFileName.substr(0, opt->inputFileName.length() - txtExt.length()).append(z78Ext);
  }
  else if ((opt->inputFileName.length() >= z78Ext.length()) &&
           (opt->inputFileName.substr(opt->inputFileName.length() - z78Ext.length()) == z78Ext) &&
           (!opt->COMPRESSION)) {
    opt->outputFileName = opt->inputFileName.substr(0, opt->inputFileName.length() - z78Ext.length()).append(txtExt);
  }
  else {
    std::cerr << "Error: The argument does not end with .txt or .z78 "
              << "or the input file does not match the specified option." << std::endl;
    exit(1);
  }

  if(argc == argsWOFileOut)
    return;

  std::string specifyOutputFile;
  specifyOutputFile = argv[3];

  if(specifyOutputFile.compare("-o") == 0)
    opt->outputFileName = argv[4];
  else{
    std::cerr << "Error: Invalid option selected. " 
              << "Please choose the \'-o\' option if you want to specify an output file." << std::endl;
    exit(1);
  }
}

int main(int argc, char **argv){
  options opt;
  getOptions(argc, argv, &opt);

  if(opt.COMPRESSION){
    compress(&opt);
    
  } else{
    decompress(&opt);
  }

  return 0;
}