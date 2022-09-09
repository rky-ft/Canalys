
#ifndef CONSTRF11_HPP
#define CONSTRF11_HPP

#include <iostream>
#include <string>

#include <TROOT.h>
#include <TTree.h>
#include <TMath.h>

#include "TArtCalibPPAC.hh"
#include "TArtCalibPlastic.hh"
#include "TArtCalibIC.hh"
#include "TArtCalibFocalPlane.hh"
#include "TArtPPAC.hh"
#include "TArtPlastic.hh"
#include "TArtIC.hh"
#include "TArtFocalPlane.hh"

#include "TArrayPPAC.hpp"
#include "TArrayPla.hpp"
#include "TArrayIC.hpp"

#include "GlobalValue.hpp"

class ConstrF11
{
 public:
	 TTree *otree;
	 TArtCalibPPAC *cppac;
	 TArtCalibPlastic *cpla;
	 TArtCalibFocalPlane *cfpl;
	 TArtCalibIC *cic;

	 TArrayPPAC *appac;
	 TArrayPla *apla;
	 TArrayIC *aic;

	 ConstrF11()
	 {
	 }
	 virtual ~ConstrF11()
	 {
	 }
	 void SetTree(TTree *t)
	 {
			otree = t;
	 }
	 void SetCalibPPAC(TArtCalibPPAC *c)
	 {
			cppac = c;
	 }
	 void SetCalibPlastic(TArtCalibPlastic *c)
	 {
			cpla = c;
	 }
	 void SetCalibFocalPlane(TArtCalibFocalPlane *c)
	 {
			cfpl = c;
	 }
	 void SetCalibIC(TArtCalibIC *c)
	 {
			cic = c;
	 }

	 void MakeBranch();
	 void Clear();
	 void CopyVal();
};

#endif
