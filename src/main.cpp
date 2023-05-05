#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "LZ78.hpp"

struct options{
  bool COMPRESSION;
  std::string fileName;
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
  inFile = openInFile(opt->fileName, opt->COMPRESSION);

  std::ofstream outFile;
  outFile = openOutFile(opt->outputFileName, opt->COMPRESSION);

  lz78_compress(inFile, outFile);
  
  inFile.close();
  outFile.close();
}

void decompress(options* opt){
  std::ifstream inFile;
  inFile = openInFile(opt->fileName, opt->COMPRESSION);

  std::ofstream outFile;
  outFile = openOutFile(opt->outputFileName, opt->COMPRESSION);
  
  lz78_decompress(inFile, outFile);

  inFile.close();
  outFile.close();
}

void getOptions(int& argc, char **argv, options* opt){

  if (argc != 3) {
    std::cerr << "Error: Incorrect number of arguments passed." 
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
    std::cerr << "Error: Invalid option selected" 
              << "Please choose either compression '-c' or decompression '-x'." << std::endl;
    exit(1);
  }

  opt->fileName = argv[2];
  
  std::string txtExt = ".txt";
  std::string z78Ext = ".z78";

  if ((opt->fileName.length() >= txtExt.length()) &&
      (opt->fileName.substr(opt->fileName.length() - txtExt.length()) == txtExt) &&
      (opt->COMPRESSION)) {
    opt->outputFileName = opt->fileName.substr(0, opt->fileName.length() - txtExt.length()).append(z78Ext);
  }
  else if ((opt->fileName.length() >= z78Ext.length()) &&
           (opt->fileName.substr(opt->fileName.length() - z78Ext.length()) == z78Ext) &&
           (!opt->COMPRESSION)) {
    opt->outputFileName = opt->fileName.substr(0, opt->fileName.length() - z78Ext.length()).append(txtExt);
  }
  else {
    std::cerr << "Error: The argument does not end with .txt or .z78 ";
    std::cerr << "or the input file does not match the specified option." << std::endl;
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