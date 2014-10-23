//
//  PutDelta.cpp
//  RatioProtectivePut
//
//  Created by Aman on 2014-10-08.
//  Copyright (c) 2014 Aman. All rights reserved.
//

#include "PutDelta.h"

//Calculate Euro vanilla Put Delta
double put_delta (const double S, const double K, const double r, const double v, const double T) {
    return norm_cdf(d_j(1, S, K, r, v, T)) - 1;
}
