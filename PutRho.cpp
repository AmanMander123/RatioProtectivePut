//
//  PutRho.cpp
//  RatioProtectivePut
//
//  Created by Aman on 2014-10-23.
//  Copyright (c) 2014 Aman. All rights reserved.
//

#include "PutRho.h"

//Calculate Euro vanilla Put Rho
double put_rho (const double S, const double K, const double r, const double v, const double T) {
    return -T*K*exp(-r*T)*norm_cdf(-d_j(2, S, K, r, v, T));
}
