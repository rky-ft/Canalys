
#include <SetPara.hpp>

SetPara::SetPara(Char_t *f)
{
	 fileParTable = f;
};

std::string SetPara::GetFileName(Int_t run)
{
	 std::string filename;
	 std::ifstream fin;

	 fin.open(fileParTable, std::ifstream::in);
	 if (!fin.is_open())
	 {
			std::cout << "Parameter file, " << fileParTable << ", cannot be opened." << std::endl;
	 }

	 std::string buf;
	 Bool_t filefound = false;
	 while (getline(fin, buf))
	 {
			if (buf.compare(0, 2, "//") == 0 || buf.size() == 0)
			{
				 continue; // comment
			}

			std::stringstream ss;
			Int_t run1, run2;
			ss << buf.c_str();
			ss >> run1 >> run2;
			if (run >= run1 && run <= run2)
			{
				 ss >> filename;
				 filefound = true;

				 break;
			}
	 }
	 if (filefound == false)
	 {
			std::cout << "Parameter file is not found for run " << run << ": " << fileParTable << std::endl;
			exit(1);
	 }

	 return filename;
};
