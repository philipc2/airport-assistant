#pragma once

#include "airport.h"

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <functional>


using namespace std;

int pageBFS(vector<int> airportIDs, int ourAirport);

vector<double> PageRankNew(vector<Airport*> airportList, vector<int> airportIDs, int stepSize);
