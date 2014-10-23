//
//  main.cpp
//  RatioProtectivePut
//
//  Created by Aman on 2014-07-12.
//  Copyright (c) 2014 Aman. All rights reserved.
//



#include <vector>
#include "ProbGenerator.h"
#include "PutDelta.h"
#include "PutGamma.h"
#include "PutVega.h"
#include "PutTheta.h"
#include "PutRho.h"

using namespace std;

typedef vector<double> record_t;
typedef vector<record_t> data_t;

////READ CSV FILE
//Overload input operator to read fields
istream& operator >> (istream& ins, record_t& record) {
    
    //Clear record
    record.clear();
    
    //Read line into string
    string line;
    getline(ins, line);
    
    //Separate fields out of line
    stringstream ss(line);
    string field;
    while (getline(ss, field, ',')) {
        
        //Convert each field into a double
        stringstream fs(field);
        double f = 0.0;
        fs >> f;
        
        //Add to end of record
        record.push_back(f);
    }
    return ins;
}

//Overload input operator to read records
istream& operator >> (istream& ins, data_t& data) {
    
    //Clear data
    data.clear();
    
    //Read record and append to data
    record_t record;
    while (ins >> record) {
        data.push_back(record);
    }
    return ins;
}

//-----------------------------------------------------------------------------//

int main(int argc, const char * argv[])
{
    
    //Outfile file handle
    ofstream outFile("/Users/Aman/Documents/GitHub/RatioProtectivePut/outFile.txt");
    
    //The data that we want
    data_t data;
    
    //CSV file containing the data
    ifstream infile("/Users/Aman/Documents/GitHub/RatioProtectivePut/InputFile.csv");
    infile >> data;
    
    //Complain if something went wrong
    if (!infile.eof()) {
        cout << "Unable to open file!\n";
        return 1;
    }
    
    //Close file
    infile.close();

    //Create Stock object
    ProbGenerator stock1(data[0][0],data[0][1],data[0][2],data[0][3],data[0][4],data[0][5],data[0][6]);
    
    //Initialize probability
    double prob;
    
    //Calculate the probability
    prob = stock1.GenerateProb();
    
    //Initialize the greeks
    double delta;
    double gamma;
    double vega;
    double theta;
    double rho;
    
    //Initialize greek input parameters
    double S = data[0][0];
    double putPremium = data[0][1];
    double K = data[0][4];
    double r = data[0][5];
    double daysToExp = data[0][6];
    
    //Interval Bisection parameters
    double low_vol = 0.001;
    double high_vol = 1000;
    double epsilon = 0.001;
    double v;
    
    //Black Scholes model
    BlackScholesPut::BlackScholesPut bsc(S, K, r, daysToExp / 365);
    
    //Implied volatility
    v = interval_bisection(putPremium, low_vol, high_vol, epsilon, bsc);
    
    
    //Calculate the greeks
    delta = put_delta (S, K, r,  v, daysToExp / 365);
    gamma = put_gamma (S, K, r,  v, daysToExp / 365);
    vega = put_vega (S, K, r,  v, daysToExp / 365);
    theta = put_theta (S, K, r,  v, daysToExp / 365);
    rho = put_rho (S, K, r,  v, daysToExp / 365);
    
    //Write output file
    outFile << prob << ", " << delta << ", " << gamma << ", " << vega << ", " << theta <<  ", " << rho << endl;
    
    return 0;
}

