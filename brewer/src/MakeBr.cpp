
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCutG.h>

#include "Brewer.hpp"

// add vals also to GlobalValue.hpp
Bool_t bripsmode = false;
Bool_t achromaticmode = false;
Bool_t dispersivemode = false;

static void usage();

Int_t main(Int_t argc, Char_t *argv[])
{
	 Char_t *dir_in = (Char_t *)"ground/";
	 Char_t *name_in = (Char_t *)"run";
	 Char_t *dir_out = (Char_t *)"coffee/";
	 Char_t *name_out = (Char_t *)"run";
	 Int_t nevents = 100000000;
	 Int_t first = 0;
	 Int_t runnumber;
	 Int_t c;

	 while ((c = getopt(argc, argv, "hi:r:o:x:n:f:bad")) != -1)
	 {
			switch (c)
			{
				 case 'h' :
						usage();
						exit(0);
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
						nevents = (Int_t)atoi(optarg);
						break;
				 case 'f' :
						first = (Int_t)atoi(optarg);
						break;
				 case 'b' :
						bripsmode = true;
						break;
				 case 'a' :
						achromaticmode = true;
						break;
				 case 'd' :
						dispersivemode = true;
						break;
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

	 Brewer *br = new Brewer();
	 br->Br(dir_in, name_in, dir_out, name_out, nevents, first, runnumber);
	 delete br;

	 return 0;
};

static void usage()
{
	 std::cout << " usage: ./bin/Brew [options] [run number]" << std::endl;
	 std::cout << " options" << std::endl;
	 std::cout << " -h: show this help" << std::endl;
	 std::cout << " -i [dir]: directory of input files (X/*.root), default: ground" << std::endl;
	 std::cout << " -r [name]: prefix of input files (ground/X*.root), default: run" << std::endl;
	 std::cout << " -o [dir]: directory of output files (X/*.root), default: coffee" << std::endl;
	 std::cout << " -x [name]: prefix of output files (coffee/X*.root), default: run" << std::endl;
	 std::cout << " -n [num]: number of events to be analyzed, default: 100000000" << std::endl;
	 std::cout << " -f [num]: first entry for analysis, default: 0" << std::endl;
	 std::cout << " -b: only BigRIPS branches are written." << std::endl;
	 std::cout << " -a: also ZDS achromatic branches are written." << std::endl;
	 std::cout << " -d: also ZDS dispersive branches are written." << std::endl;

	 return;
}
