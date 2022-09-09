
#ifndef SETPARA_HPP
#define SETPARA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <TROOT.h>

class SetPara
{
 private:
	 Char_t *fileParTable;

 public:
	 SetPara(Char_t *f);
	 ~SetPara() {};

	 std::string GetFileName(Int_t run);
};

#endif
