/*  warpfns.h

    Mark Jenkinson, FMRIB Image Analysis Group

    Copyright (C) 2001 University of Oxford  */

/*  Part of FSL - FMRIB's Software Library
    http://www.fmrib.ox.ac.uk/fsl
    fsl@fmrib.ox.ac.uk
    
    Developed at FMRIB (Oxford Centre for Functional Magnetic Resonance
    Imaging of the Brain), Department of Clinical Neurology, Oxford
    University, Oxford, UK
    
    
    LICENCE
    
    FMRIB Software Library, Release 3.3 (c) 2006, The University of
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
    innovation@isis.ox.ac.uk quoting reference DE/1112. */

#if !defined(__warpfns_h)
#define __warpfns_h

#include <string>
#include <iostream>
#define WANT_STREAM
#define WANT_MATH

#include "newmatap.h"
#include "newmatio.h"
#include "newimageall.h"

using namespace NEWMAT;
using namespace NEWIMAGE;

namespace NEWIMAGE {

//////////////////////////////////////////////////////////////////////////

int affine2warp(const Matrix& affmat, volume4D<float>& warpvol,
		const volume<float>& outvol);

int shift2warp(const volume<float>& shiftmap, 
	       volume4D<float>& warp, const string& shiftdir);

int convertwarp_rel2abs(volume4D<float>& warpvol);
int convertwarp_abs2rel(volume4D<float>& warpvol);
  // try to determine if the warp is stored in absolute (vs relative) convention
bool is_abs_convention(volume4D<float>& warpvol);
bool is_abs_convention(const volume4D<float>& warpvol);

int concat_warps(const volume4D<float>& prewarp, 
                 const volume4D<float>& postwarp,
		 volume4D<float>& totalwarp);

int apply_warp(const volume<float>& invol, volume<float>& outvol,
	       const volume4D<float>& warpvol);

int apply_warp(const volume<float>& invol, volume<float>& outvol,
	       const volume4D<float>& warpvol, 
	       const Matrix& premat, const Matrix& postmat);

int raw_apply_warp(const volume<float>& invol, volume<float>& outvol,
		   const volume4D<float>& warpvol, 
		   const Matrix& premat, const Matrix& postmat);

  // default value for gammabar is for rad/s units; te in seconds; 
  //   lrgrad in rad/s/voxel
volume<float> calc_sigloss(volume4D<float>& lrgrad, float te, 
			   float gammabar=0.5/M_PI);


//////////////////////////////////////////////////////////////////////////

void jacobian_check(volume4D<float>& jvol,
		    ColumnVector& jacobian_stats, 
		    const volume4D<float>& warp,
		    float minJ, float maxJ, bool use_vol=true);

volume4D<float> jacobian_check(ColumnVector& jacobian_stats, 
			       const volume4D<float>& warp,
			       float minJ, float maxJ);

ColumnVector jacobian_quick_check(const volume4D<float>& warp,
				  float minJ, float maxJ); 


void constrain_topology(volume4D<float>& warp, float minJ, float maxJ);

void constrain_topology(volume4D<float>& warp);

//////////////////////////////////////////////////////////////////////////

}

#endif
