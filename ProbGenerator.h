//
//  ProbGenerator.h
//  RatioProtectivePut
//
//  Created by Aman on 2014-07-12.
//  Copyright (c) 2014 Aman. All rights reserved.
//

#ifndef __RatioProtectivePut__ProbGenerator__
#define __RatioProtectivePut__ProbGenerator__

#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class ProbGenerator {
private:
    double currPrice;           //Current stock price
    double putPremium;          //Put premium
    double numberOfPutContracts;//Number of put contracts
    double numberOfStocks;      //Number of stocks
    double strikePrice;         //Put strike price
    double risk_free_rate;      //Risk free rate
    double daysToExp;           //Days to expiration of put
    
public:

    ProbGenerator(const double _currPrice, const double _putPremium, const double _numberOfPutContracts,
                  const double _numberOfStocks, const double _strikePrice, const double _risk_free_rate, const double _daysToExp);
    
    double GenerateProb();
    
};


double norm_pdf(const double x);
double norm_cdf(const double x);
double d_j (const int j, const double S, const double K, const double r, const double v, const double T);
double put_price (const double S, const double K, const double r, const double v, const double T);
template<typename T> double interval_bisection(double y_target, double m, double n, double epsilon, T g);


class BlackScholesPut {
private:
    double S;
    double K;
    double r;
    double T;
    
public:
    BlackScholesPut(double _S, double _K, double _r, double _T);
    
    double operator()(double sigma) const;
};

#endif /* defined(__RatioProtectivePut__ProbGenerator__) */
