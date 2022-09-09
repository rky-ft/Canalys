
#ifndef SetPara_hpp
#define SetPara_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <TROOT.h>

class SetPara
{
 public:
	 SetPara(std::string f);
	 ~SetPara() {};

	 std::string GetFileName(Int_t run);
	 std::string GetFileAndGateName(Int_t run);

 private:
	 std::string fileParTable;
};

#endif
