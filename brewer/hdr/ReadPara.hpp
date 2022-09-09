
#ifndef ReadPara_hpp
#define ReadPara_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <TROOT.h>

class ReadPara
{
 private:
 public:
	 ReadPara() {};
	 ~ReadPara() {};

	 std::string ReadParameterList(const Char_t *filename, Int_t run);
	 std::string ReadParameterList(const Char_t *filename, Int_t run, std::string keyword);
};
#endif
