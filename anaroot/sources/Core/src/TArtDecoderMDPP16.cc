/*
 * @file TArtDecoderMDPP16.cc
 *--------------------------------------------------------
 *    Comment : 
 *    
 *--------------------------------------------------------
 */
#include "TArtDecoderMDPP16.hh"
#include "TArtDecoderFactory.hh"
#include "TArtCore.hh"
#include <stdio.h>
TArtDecoderMDPP16::TArtDecoderMDPP16()
   : TArtDecoder(kID) {
}

TArtDecoderMDPP16::~TArtDecoderMDPP16()
{
}

TArtDecoder* TArtDecoderMDPP16::Instance()
{
   static TArtDecoderMDPP16 instance;
   return &instance;
}

int TArtDecoderMDPP16::Decode(unsigned char* &buf, const unsigned int& size,
			      TArtRawSegmentObject* rawseg)
{
   unsigned int *evtdata = (unsigned int*) buf;
   unsigned int evtsize = size/sizeof(unsigned int);
   int i, igeo, ich, msk, submsk, tmpsize;

   igeo = -1;
   for (i=0; i<evtsize; i++) {
     msk = (evtdata[i]&0xc0000000)>>30;
     submsk = (evtdata[i]&0x30000000)>>28;
     //printf("%d : msk=%08x submsk=%08x %08x\n", i, msk, submsk, evtdata[i]);
     switch(msk){
     case 0x01:
       // Hedaer
       igeo = (evtdata[i]&0x00ff0000)>> 16;
       tmpsize = evtdata[i]&0x000003ff;
       if(tmpsize + 1 != evtsize)
	 TArtCore::Info("TArtDecoderMDPP16","Error igeo: %d, size in header:%d, size of data %d\n", igeo, tmpsize, evtsize);
	 //printf("header igeo=%d, size=%d, %d\n", igeo, tmpsize, evtsize);
       break;
     case 0x00:
       if(igeo != -1){
	 // Event
	 ich = (evtdata[i]&0x001f0000) >> 16;
	 TArtRawDataObject *rdata = new TArtRawDataObject(igeo,ich,evtdata[i]&0xffff);
	 //printf("igeo=%d, ich=%d, data=%d\n", igeo, ich, evtdata[i]&0xffff);
	 rawseg->PutData(rdata);
       }
       break;
     case 0x11:
       //printf("ender\n", igeo);
       // Ender
       igeo = -1;
     }
   }
   return 0;
}
