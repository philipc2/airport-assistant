#pragma once

#include "airport.h"
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <set>
#include <limits>
using std::vector;
using std::queue;
using std::map;
using std::pair;
using std::set;

#define INF std::numeric_limits<double>::max()

//vector<Airport * > DijkstraSSSP(vector<Airport*> AirportList, Airport* source, Airport* destination);
//and, alternatively:
vector<Airport * > DijkstraSSSP(vector<Airport*> AirportList, vector<int> AirportIDs, Airport* source, Airport* destination);
//helper functions:
int DJbinarySearch(vector<int> AirportIDs, int ourAirport);
