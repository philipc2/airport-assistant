#pragma once

#include <queue>
#include <vector>
#include "airport.h"
/* BFS graph traversal class, for our Flight Tracker Project...
 Notes: ???

 */

class BFS{
private:
  /* data */
  queue<Airport*> q;
  vector<bool> visited;
  vector<Airport*> final_airports;
  vector<int> AirportID;
  int it_count;
  Airport* curAirport;
  Airport* startAirport; 
public:
  BFS();
  BFS(vector<Airport*> AirportList, vector<int> AirportIDs, Airport* start, int count);
  int BinaryBFS(vector<int> AirportIDs, int ourAirport);
  vector<Airport*> algorithm();
};
