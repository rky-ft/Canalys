
#include <iostream>
#include <string>
#include <time.h>
#include <signal.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include <TROOT.h>
//#include <omp.h>

#include "Grinder.hpp"

// add vals also to GlobalValue.hpp
Bool_t compression = false;
Bool_t bripsmode = false;
Bool_t debugmode = false;

static void usage();

Int_t main(Int_t argc, Char_t *argv[])
{
	 Char_t *dir_in = (Char_t *)"bean/";
	 Char_t *name_in = (Char_t *)"run";
	 Char_t *dir_out = (Char_t *)"ground/";
	 Char_t *name_out = (Char_t *)"run";
	 Int_t nevents = 100000000;
	 Int_t first = 0;
	 Int_t runnumber;
	 Int_t c;

	 while ((c = getopt(argc, argv, "hzi:r:o:x:n:f:bd")) != -1)
	 {
			switch (c)
			{
				 case 'h' :
						usage();
						exit(0);
				 case 'z' :
						compression = true;
						break;
				 case 'i' :
						dir_in = (Char_t *)optarg;
						break;
				 case 'r' :
						name_in = (Char_t *)optarg;
						break;
				 case 'o' :
						dir_out = (Char_t *)optarg;
						break;
				 case 'x' :
						name_out = (Char_t *)optarg;
						break;
				 case 'n' :
						nevents = (Int_t)atof(optarg);
						break;
				 case 'f' :
						first = (Int_t)atof(optarg);
						break;
				 case 'b' :
						bripsmode = true;
						break;
				 case 'd' :
						debugmode = true;
				 case 0 :
						break;
				 default :
						usage();
						exit(1);
			}
	 }
	 argc -= optind;
	 argv += optind;

	 if (argc != 1)
	 {
			usage();
			exit(1);
	 }

	 runnumber = (Int_t)atoi(argv[0]);

	 Grinder *gr = new Grinder();
	 gr->Gr(dir_in, name_in, dir_out, name_out, nevents, first, runnumber);
	 delete gr;

	 return 0;
};

static void usage()
{
	 std::cout << " usage: ./bin/Grind [options] [run number]" << std::endl;
	 std::cout << " [run number] -> 0, online mode" << std::endl;
	 std::cout << " options" << std::endl;
	 std::cout << " -h: show this help" << std::endl;
	 std::cout << " -z: input compressed files (*.ridf.gz)" << std::endl;
	 std::cout << " -i [dir]: directory of input files (X/*.ridf), default: bean" << std::endl;
	 std::cout << " -r [name]: prefix of input files (bean/X*.ridf), default: run" << std::endl;
	 std::cout << " -o [dir]: directory of output files (X/*.root), default: ground" << std::endl;
	 std::cout << " -x [name]: prefix of output files (ground/X*.root), default: run" << std::endl;
	 std::cout << " -n [num]: number of events to be analyzed, default: 100000000" << std::endl;
	 std::cout << " -f [num]: first entry for analysis, default: 0" << std::endl;
	 std::cout << " -b: only BigRIPS branches are written." << std::endl;
	 std::cout << " -d: all anaroot branches are written." << std::endl;

	 return;
}
