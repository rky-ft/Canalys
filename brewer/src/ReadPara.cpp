
#include <ReadPara.hpp>

std::string ReadPara::ReadParameterList(const Char_t *filename, Int_t run)
{
	 std::ifstream fin;
	 fin.open(filename, std::ifstream::in);
	 if (!fin.is_open())
	 {
			std::cout << "Parameter file, " << filename << ", cannot be opened." << std::endl;
			exit(1);
	 }

	 std::string buf;
	 Bool_t is_read = false;
	 std::string parameterlist;

	 while (getline(fin, buf))
	 {
			if (buf.compare(0, 2, "//") == 0 || buf.size() == 0)
			{
				 continue; // comment
			}

			std::stringstream ss;
			ss << buf.c_str();

			for (Int_t i = 0; i < 2; i++)
			{
				 std::string test;
				 ss >> test;
				 Int_t size = test.size();
				 for (Int_t j = 0; j < size; j++)
				 {
						if (!isdigit(test[j]))
						{
							 std::cout << "Error: format error, first two values should be digit (run number): " << filename << std::endl;
							 exit(1);
						}
				 }
			}

			ss.seekg(0, ss.beg); // go to begin

			Int_t run1, run2;
			ss >> run1 >> run2;
			if (run >= run1 && run <= run2)
			{
				 if (is_read)
				 {
						std::cout << "Error: two kinds of parameters for run " << run << " are found in " << filename << "." << std::endl;
						exit(1);
				 }
				 else
				 {
						getline(ss, parameterlist);
				 }
				 is_read = true;
			}
	 }
	 // if parameters can not be found for run, use default values.
	 fin.close();

	 return parameterlist;
};

std::string ReadPara::ReadParameterList(const Char_t *filename, Int_t run, std::string keyword)
{
	 std::ifstream fin;
	 fin.open(filename, std::ifstream::in);
	 if (!fin.is_open())
	 {
			std::cout << "Parameter file, " << filename << ", cannot be opened." << std::endl;
			exit(1);
	 }

	 std::string buf;
	 Bool_t is_read = false;
	 std::string parameterlist;

	 while (getline(fin, buf))
	 {
			if (buf.compare(0, 2, "//") == 0 || buf.size() == 0)
			{
				 continue; // comment
			}

			std::stringstream ss;
			ss << buf.c_str();

			std::string test;
			ss >> test;
			if (isdigit(test[0]))
			{
				 std::cout << "Error: format error, first value should be keyword: " << filename << std::endl;
				 exit(1);
			}

			ss.seekg(0, ss.beg); // go to begin

			Int_t run1, run2;
			std::string keyword_read;
			ss >> keyword_read >> run1 >> run2;
			if (run >= run1 && run <= run2)
			{
				 if (keyword_read.compare(keyword) == 0)
				 {
						if (is_read)
						{
							 std::cout << "Error: two kinds of parameters for run " << run << " are found in " << filename << "." << std::endl;
							 exit(1);
						}
						else
						{
							 getline(ss, parameterlist);
						}
						is_read = true;
				 }
			}
	 }
	 // if parameters can not be found for run, use default values.
	 fin.close();

	 return parameterlist;
}
