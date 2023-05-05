#ifndef LZ78
#define LZ78

#include <string>
#include <vector>
#include <fstream>

void lz78_compress(std::ifstream& input, std::ofstream& output);
void lz78_decompress(std::ifstream& input, std::ofstream& output);

#endif