//
//
/*!
  \file
  \ingroup evaluation

  \brief Implementation of class stir::ROI_values

  \author Damiano Belluzzo
  \author Kris Thielemans
  \author PARAPET project
*/
/*
    Copyright (C) 2000 PARAPET partners
    Copyright (C) 2000- 2009, Hammersmith Imanet Ltd
    This file is part of STIR.

    SPDX-License-Identifier: Apache-2.0 AND License-ref-PARAPET-license

    See STIR/LICENSE.txt for details
*/

#include "stir/evaluation/ROIValues.h"
#include "stir/NumericInfo.h"
#include <math.h>
#include <sstream>

using std::endl;
using std::ends;

START_NAMESPACE_STIR

void
ROIValues::init()
{

  NumericInfo<float> float_limits;

  roi_volume = 0;
  integral = 0;
  integral_of_square = 0;
  min_value = float_limits.max_value();
  max_value = float_limits.min_value();

  mean_value = 0;
  variance_value = 0;
  std_value = 0;
}

void
ROIValues::update()
{
  if (roi_volume == 0)
    {
      // ill_defined case...
      mean_value = 0;
      variance_value = 0;
      std_value = 0;
    }
  else
    {
      mean_value = integral / roi_volume;
      const float square_mean = square(mean_value);

      variance_value = (integral_of_square / roi_volume - square_mean);
      if (fabs(variance_value) < 10E-5 * square_mean)
        variance_value = 0;
      std_value = sqrt(variance_value);
    }
}

std::string
ROIValues::report() const
{
  std::ostringstream s;
  s << " Volume of ROI              = " << roi_volume << endl;
  s << " Integral of density        = " << integral << endl;
  s << " Integral of square density = " << integral_of_square << endl;
  s << " Min value = " << min_value << endl;
  s << " Max value = " << max_value << endl;
  s << " Mean      = " << mean_value << endl;
  s << " Variance  = " << variance_value << endl;
  s << " Std       = " << std_value << endl;
  s << ends;
  return s.str();
}

#if 0
ostream &operator ( ostream &stream, ROIValues val)
{

//stream << " Volume of ROI:";             
//stream << val.roi_volume<<endl;
//stream <<" Integral of density        = " 
//stream << val.integral<<endl;
//stream <<" Integral of square density = " 
//stream << val.integral_of_square<<endl;
//stream <<  " Min value = "
//stream << val.min_value<<endl;
//stream << " Max value = "
//stream << val.max_value<<endl;
//stream << " Mean      = " 
stream << val.mean_value<< endl;
//stream << " Variance  = "
stream << val.variance_value <<endl;
//stream <<  " Std       = " 
stream << val.std_value<<endl;

return stream;

  }

#endif

END_NAMESPACE_STIR
