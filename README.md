#Ratio Protective Put

##Purpose
The purpose of this C++ program is to calculate the probability of ending up in-the-money based on the Ratio Protective Put option trading strategy. The greeks for the put option are also calculated.

##Background
The ratio protective put strategy involves purchasing 2 at-the-money put options for every one underlying stock. The payoff of this strategy is a V-shape. The strategy will end up in-the-money if either one of the 2 (one located below and one above) break-even price points are breached. This program calculates the break-even points and gives the probability of passing either one of the two break-even points before the expiration of the put option.

##Algorithm
This program uses a Monte-Carlo simulation to calculate the probability that one of the two break-even points will be breached before the expiration date. The Black-Scholes option pricing is used to calculate the implied volatility.

##Input
The input is a CSV file consisting in the following format:

Underlying Price, Put Premium, Number of Put Options per Contract, Number of Stocks, Strike Price, Risk Free Rate, Days to expiration

Example:

593.25,3.8,100,1000,592.5,0.03,3

##Output
The output is a CSV file consisting in the following format:

Probability, Delta, Gamma, Vega, Theta, Rho

Example:

0.563, -0.462796, 0.0374018, 21.3633, -248.264, -2.28785


##Note
Please specificy the input and output file paths in the main.cpp file before using.

##Reference
The algorithms used in this program can be found in the book:

Michael L. Halls-Moore. _C++ For Quantitative Finance._ 


