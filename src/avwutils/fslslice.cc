/*  avwslice.cc

    Tim Behrens and Matthew Webster, FMRIB Image Analysis Group

    Copyright (C) 2000-2007 University of Oxford  */

/*  Part of FSL - FMRIB's Software Library
    http://www.fmrib.ox.ac.uk/fsl
    fsl@fmrib.ox.ac.uk
    
    Developed at FMRIB (Oxford Centre for Functional Magnetic Resonance
    Imaging of the Brain), Department of Clinical Neurology, Oxford
    University, Oxford, UK
    
    
    LICENCE
    
    FMRIB Software Library, Release 5.0 (c) 2012, The University of
    Oxford (the "Software")
    
    The Software remains the property of the University of Oxford ("the
    University").
    
    The Software is distributed "AS IS" under this Licence solely for
    non-commercial use in the hope that it will be useful, but in order
    that the University as a charitable foundation protects its assets for
    the benefit of its educational and research purposes, the University
    makes clear that no condition is made or to be implied, nor is any
    warranty given or to be implied, as to the accuracy of the Software,
    or that it will be suitable for any particular purpose or for use
    under any specific conditions. Furthermore, the University disclaims
    all responsibility for the use which is made of the Software. It
    further disclaims any liability for the outcomes arising from using
    the Software.
    
    The Licensee agrees to indemnify the University and hold the
    University harmless from and against any and all claims, damages and
    liabilities asserted by third parties (including claims for
    negligence) which arise directly or indirectly from the use of the
    Software or the sale of any products based on the Software.
    
    No part of the Software may be reproduced, modified, transmitted or
    transferred in any form or by any means, electronic or mechanical,
    without the express permission of the University. The permission of
    the University is not required if the said reproduction, modification,
    transmission or transference is done without financial return, the
    conditions of this Licence are imposed upon the receiver of the
    product, and all original and amended source code is included in any
    transmitted product. You may be held legally responsible for any
    copyright infringement that is caused or encouraged by your failure to
    abide by these terms and conditions.
    
    You are not permitted under this Licence to use this Software
    commercially. Use for which any financial return is received shall be
    defined as commercial use, and includes (1) integration of all or part
    of the source code or the Software into a product for sale or license
    by or on behalf of Licensee to third parties or (2) use of the
    Software or any derivative of it for research with the final aim of
    developing software products for sale or license to a third party or
    (3) use of the Software or any derivative of it for research with the
    final aim of developing non-software products for sale or license to a
    third party, or (4) use of the Software to provide any service to an
    external organisation for which payment is received. If you are
    interested in using the Software commercially, please contact Isis
    Innovation Limited ("Isis"), the technology transfer company of the
    University, to negotiate a licence. Contact details are:
    innovation@isis.ox.ac.uk quoting reference DE/9564. */

#include "newimage/newimageall.h"
#include "newimage/fmribmain.h"
#include "miscmaths/miscmaths.h"

using namespace NEWIMAGE;
using namespace MISCMATHS;


string zeropad_numeric_string(string in,unsigned int len){
  string out=in;
  while(out.length() < len){
    out="0"+out;
  }
  return out;
}


template <class T>
int fmrib_main(int argc, char *argv[])
{
  volume4D<T> grot;
  volume4D<T> tmp;
  string iname=string(argv[1]);
  read_volume4D(grot,iname);
  string base;
  
  if(argc==2)
    base=iname;
  else
    base=string(argv[2]);
  
  make_basename(base);
  
  for(int z=0;z<grot.zsize();z++){
    grot.setROIlimits(grot.minx(),grot.miny(),z,grot.mint(),grot.maxx(),grot.maxy(),z,grot.maxt());
    grot.activateROI();
    tmp=grot.ROI();
    string oname=base+"_slice_"+zeropad_numeric_string(num2str(z),4);
    //cout<<"writing slice "<<z<<'\r';
    save_volume4D(tmp,oname);
  }
  //cout<<'\n';
  return 0;
}

int main(int argc,char *argv[])
{
  
  Tracer tr("main");
  
  if(argc<2){
    cout <<"Usage: fslslice <volume>"<<endl;
    cout<<endl;
    cout <<"Usage: fslslice <volume> <output basename>"<<endl;
    cout<<endl; 
    return -1;
  }
  string iname=string(argv[1]);
  return call_fmrib_main(dtype(iname),argc,argv);
}

