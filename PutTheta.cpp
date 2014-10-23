//
//  PutTheta.cpp
//  RatioProtectivePut
//
//  Created by Aman on 2014-10-23.
//  Copyright (c) 2014 Aman. All rights reserved.
//

#include "PutTheta.h"

//Calculate Euro vanilla Put Theta
double put_theta (const double S, const double K, const double r, const double v, const double T) {
    return -(S*norm_pdf(d_j(1, S, K, r, v, T))*v)/(2*sqrt(T)) + r*K*exp(-r*T)*norm_cdf(-d_j(2, S, K, r, v, T));
}
