//
//  PutDelta.h
//  RatioProtectivePut
//
//  Created by Aman on 2014-10-08.
//  Copyright (c) 2014 Aman. All rights reserved.
//

#ifndef __RatioProtectivePut__PutDelta__
#define __RatioProtectivePut__PutDelta__

#include "ProbGenerator.h"

//Calculate Euro vanilla Put Delta
double put_delta (const double S, const double K, const double r, const double v, const double T);
    
#endif /* defined(__RatioProtectivePut__PutDelta__) */
