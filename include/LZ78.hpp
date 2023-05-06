#ifndef LZ78
#define LZ78

#include <string>
#include <vector>
#include <fstream>

void LZ78Compress(std::ifstream& input, std::ofstream& output);
void LZ78Decompress(std::ifstream& input, std::ofstream& output);

#endif