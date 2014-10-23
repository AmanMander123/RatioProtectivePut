//
//  ProbGenerator.cpp
//  RatioProtectivePut
//
//  Created by Aman on 2014-07-12.
//  Copyright (c) 2014 Aman. All rights reserved.
//

#include "ProbGenerator.h"

//Standard normal probability density function
double norm_pdf(const double x) {
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
}

//An approximation to the cumulative dist. func. for the std. normal dist.
//Note: this is a recursive formula
double norm_cdf(const double x) {
    double k = 1.0/(1.0 + 0.2316419*x);
    double  k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k)))) ;
    if (x >= 0.0) {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    } else {
        return 1.0 - norm_cdf(-x);
    }
}

//This calculates d_j, for in j in {1,2}. This term appears in the closed form solution for Euro call or put price
double d_j (const int j, const double S, const double K, const double r, const double v, const double T) {
    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

// Calculate the European vanilla call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price (const double S, const double K, const double r, const double v, const double T) {
    return -S * norm_cdf(-d_j(1,S,K,r,v,T)) + K * exp(-r*T) * norm_cdf(-d_j(2,S,K,r,v,T));
}

//Black Scholes model
BlackScholesPut::BlackScholesPut(double _S, double _K, double _r, double _T) :
S(_S), K(_K), r(_r), T(_T) {}

double BlackScholesPut::operator()(double sigma) const {
    return put_price(S, K, r, sigma, T);
}

//Creating a function template
//Trying to find an x such as |g(x) - y| < epsilon starting with the interval (m,n)
template<typename T>
double interval_bisection(double y_target, double m, double n, double epsilon, T g) {
    //Creat initial x mid-point value
    //Find the mapped y value of g(x)
    double x = 0.5 * (m + n);
    double y = g(x);
    
    //While the diff btw y and y_targer value is greater than epsilon,
    //keep subdividing the interval into successively smaller halves and get new y
    int counter = 0;
    do {
        if (y < y_target) {
            m = x;
        }
        
        if (y > y_target) {
            n = x;
        }
        x = 0.5 * (m + n);
        y = g(x);
        counter++;
        
        
        if (counter > 1000) {
            return 0;
        }
    } while (fabs(y - y_target) > epsilon);
    return x;
}

ProbGenerator::ProbGenerator(const double _currPrice, const double _putPremium, const double _numberOfPutContracts,
                             const double _numberOfStocks, const double _strikePrice, const double _risk_free_rate,const double _daysToExp) {
    currPrice = _currPrice;
    putPremium = _putPremium;
    numberOfPutContracts = _numberOfPutContracts;
    numberOfStocks = _numberOfStocks;
    strikePrice = _strikePrice;
    risk_free_rate = _risk_free_rate;
    daysToExp = _daysToExp;
    
}

double ProbGenerator::GenerateProb() {
    
    int num_sims = 10000;
    double stkPrice = 0;
    double count = 0;
    double gauss_bm;
    double lowerBEPrice;
    
    if (strikePrice < currPrice) {
         lowerBEPrice = strikePrice - 2*putPremium - (currPrice - strikePrice);
    } else {
    lowerBEPrice = strikePrice - 2*putPremium + (strikePrice - currPrice);
    }
    double upperBEPrice = currPrice + 2*putPremium;
    
    
    for (int iter = 0; iter < num_sims; iter++) {
        stkPrice = currPrice;
        for (int dayCount = 0; dayCount < daysToExp; dayCount++) {
            
            //Generate Random Number
            double x= 0;
            double y= 0;
            double euclid_sq = 0.0;
            
            do {
                x = 2.0 * rand() / static_cast<double> (RAND_MAX) - 1;
                y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
                euclid_sq = x * x + y * y;
                
            } while (euclid_sq >= 1.0);
            gauss_bm = x*sqrt(-2*log(euclid_sq)/euclid_sq);
            
            //Calculate implied volatility
            
            //Interval Bisection parameters
            double low_vol = 0.001;
            double high_vol = 1000;
            double epsilon = 0.001;
            double sigma;
            
            BlackScholesPut bsc(currPrice, strikePrice, risk_free_rate, daysToExp / 365);
            
            //Implied volatility
            sigma = interval_bisection(putPremium, low_vol, high_vol, epsilon, bsc);
            
            //Update stock price
            stkPrice = stkPrice * exp(risk_free_rate / 365 + sigma * gauss_bm / sqrt(365));
          
            //Break when stock price breaks through one of the breakeven points
            if (stkPrice < lowerBEPrice || stkPrice > upperBEPrice) { count++; break;}
        }
        
    }
    
    //Return probability
    return count / num_sims;
}

