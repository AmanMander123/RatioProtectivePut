//
//  PutGamma.cpp
//  RatioProtectivePut
//
//  Created by Aman on 2014-10-23.
//  Copyright (c) 2014 Aman. All rights reserved.
//

#include "PutGamma.h"

//Calculate Euro vanilla Put Gamma
double put_gamma (const double S, const double K, const double r, const double v, const double T) {
    return norm_pdf(d_j(1, S, K, r, v, T))/(S*v*sqrt(T));
}
