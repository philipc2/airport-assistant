/*  PARSER CLASS:
    Description: Reads in airport / flight data from .dat file and prepares it for processing in our tree.
    Each function should (in one way or another): read in the right amount of data from the .dat file,
    construct a vector of airport pointers pointing to airports we make on the heap, and return said vector.
    It can:
    - Read in ALL airports
    - Read in all airports from [0,last]
    - Read in all airports in range [first,last]  

*/
#pragma once
#include "airport.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;


//vector containing airport pointers to dynamically allocated airports.
//return that vector!

int binarySearch1(vector<int> airportIDs, int ourAirport);

std::vector<Airport*> parseAirportsAll();

//std::vector<Airport*> parseAirportsUpTo(unsigned last);

vector<Airport*> parseAirports();

//return true if good, false if file empty
int parseRoutes(vector<Airport*> airportList, vector<int> airportIDs);
