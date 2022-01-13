#include "catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

#include "airport.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "pagerank.h"
#include "parser.h"
using namespace std;

// Before anything else, we should create our list of airports (parse from file) and make sure it works correctly...
// Vector of airport pointers
  static vector<Airport*> airportList = parseAirports();
  // Vector of airportID's used for binary search
  static vector<int> airportIDs;
  // Parse through all the routes
  static int routeCount;

TEST_CASE("Parser: Sanity check -- Size of AirportList equals the number of filled lines in file", "[weight=0][part=1][part=1a]"){
  //first initialize airportIDs and routeCount
  for (unsigned long i = 0; i < airportList.size(); i++)
    airportIDs.push_back(airportList[i]->getID());
  routeCount = parseRoutes(airportList,airportIDs);
  //now the testing:
  unsigned numLines = 7678;
  REQUIRE(airportList.size() == numLines);
  //same thing with routeCount...
  unsigned numRoutes = 66444;
  REQUIRE(routeCount == numRoutes);

}


TEST_CASE("BFS test 1: make sure BFS is traversing correctly", "[weight=0][part=1][part=1a]"){
  string ORD = "Chicago OHare International Airport";
  string DTW = "Detroit Metropolitan Wayne County Ariport";
  string LGA = "La Guardia Airport";
  Airport* start = new Airport(3830,ORD,41.9786, -87.9048); 
  Airport* out1 =  new Airport(3645,DTW, 42.212,-83.353); 
  Airport* out2 =  new Airport(3697,LGA, 40.777,-73.87); 
  vector<Airport*> airportList = parseAirports();
  // Vector of airportID's used for binary search
  vector<int> airportIDs;
  
  for (unsigned long i = 0; i < airportList.size(); i++)
    airportIDs.push_back(airportList[i]->getID());
  
  BFS test1(airportList,airportIDs,start,5); 
  start->addOutgoing(out1); 
  start->addOutgoing(out2); 
  vector <Airport*> final_output = test1.algorithm(); 
  int out3 = 0; 
  int out4 = 0; 
  for(unsigned i = 0; i < final_output.size();i++){
    if((final_output[i])->getID() == out1->getID()){
      out3 = out1->getID(); 
    }
    if((final_output[i])->getID() == out2->getID()){
      out4 = out2->getID();
    }
  }
  REQUIRE(out3 == out1->getID());
  REQUIRE(out4 == out2->getID()); 
  delete start; 
  delete out1; 
  delete out2; 
}
TEST_CASE("BFS test 2: make sure edge cases work", "[weight=0][part=1][part=1b]"){
  string YQV = "Yorktown Municipal Airport";
  Airport* start = new Airport(123,YQV,41.9786, -87.9048); 
  vector<Airport*> airportList = parseAirports();
  // Vector of airportID's used for binary search
  vector<int> airportIDs;
  
  for (unsigned long i = 0; i < airportList.size(); i++)
    airportIDs.push_back(airportList[i]->getID());
  
  BFS test1(airportList,airportIDs,start,1); 
  vector <Airport*> final_output = test1.algorithm(); 

  REQUIRE(final_output.size() == 1);
  delete start; 
 
}

/* Dijkstra's Algorithm: Test cases description:
  - Willard to Ohare, and back: Does it return the direct flight (each way)?
      - Does the flight there EQUAL the flight back (since they do have flights both ways).
  - Detroit to Delhi: Does the flight path generated match the shortest distance flight path we found online?
  - Disconnected components: Does our algorithm gracefully handle two airports that have no connection between them at all?
    Ohare and 
  - Same source and destination: Does our algorithm handle passing in the same airport for source and destination? (Ben Gurion)

*/

TEST_CASE("Dijkstra 1: Champaign to Chicago direct flight and back.", "[weight=0][part=2][part=2a]"){
  //parser bullcrap(...)
  int willardID = 4049;
  int OHareID = 3830;
  Airport* Willard = airportList[DJbinarySearch(airportIDs, willardID)];
  Airport* OHare = airportList[DJbinarySearch(airportIDs, OHareID)];
  vector<Airport*> result = DijkstraSSSP(airportList,airportIDs,Willard,OHare);
  vector<Airport*> solution;
  solution.push_back(Willard);
  solution.push_back(OHare);
  REQUIRE(result == solution);
  //now, the other way.
  result = DijkstraSSSP(airportList,airportIDs,OHare,Willard);
  solution.clear();
  solution.push_back(OHare);
  solution.push_back(Willard);
  REQUIRE(result == solution);
}

TEST_CASE("Dijkstra 2: Detroit, MI to Delhi, India", "[weight=0][part=2][part=2b]"){
  //parser bullcrap(...)
  Airport* Detroit = airportList[DJbinarySearch(airportIDs, 3645)]; //ID: 3645
  Airport* Delhi = airportList[DJbinarySearch(airportIDs, 3093)]; // ID: 3093
  Airport* Toronto = airportList[DJbinarySearch(airportIDs, 193)]; //ID: 193
  Airport* Pakistan = airportList[DJbinarySearch(airportIDs, 2207)]; //ID: 2207
  vector<Airport*> result = DijkstraSSSP(airportList,airportIDs,Detroit,Delhi);
  vector<Airport*> solution;
  //we searched online and found this path to be the shortest (by distance) between these two airports.
  solution.push_back(Detroit);
  solution.push_back(Toronto);
  solution.push_back(Pakistan);
  solution.push_back(Delhi);
  REQUIRE(result == solution);
}

TEST_CASE("Dijkstra 3: Handles multiple components (aka no path bt airports)", "[weight=0][part=2][part=2c]"){
  //parser bullcrap(...)
  Airport* OHare = airportList[DJbinarySearch(airportIDs, 3830)];
  Airport* Yorkton = airportList[DJbinarySearch(airportIDs, 123)];
  vector<Airport*> result = DijkstraSSSP(airportList,airportIDs,OHare,Yorkton);
  REQUIRE(result.size() == 0);
}

TEST_CASE("Dijkstra 4: Handles same source and destination airport", "[weight=0][part=2][part=2d]"){
  //parser bullcrap(...)
  Airport* LaGuardia = airportList[DJbinarySearch(airportIDs, 3697)];//ID: 3697
  vector<Airport*> result = DijkstraSSSP(airportList,airportIDs,LaGuardia,LaGuardia);
  vector<Airport*> solution;
  solution.push_back(LaGuardia);
  REQUIRE(result == solution);
}



/* Haversine (getDistance()) test cases:
    -a normal calcualtion. Same continent.
    -East/West,same hemisphere, different continent.
    - North /South, same hemisphere.
    -Mixed (all the way around the world, essentially)
    -degernate cases:
        -distance to itself (zero)
        -distance from north pole to south pole
        -distance halfway around the world
*/


TEST_CASE("Haversine 1: Willard to Ohare: check that roundtrip distance is the same.", "[weight=0][part=3][part=3a]"){
    Airport * Willard = new Airport(4049,"University of Illinois Willard Airport",40.03919983,-88.27809906);
    Airport * OHare = new Airport(3830,"Chicago O'Hare International Airport",41.9786,-87.9048);
    double WillardtoOhare = Willard->getDistance(OHare);
    double OharetoWillard = OHare->getDistance(Willard);
    //check that each distance is correct, and that they're the same.
    double truedistance = 218000; //(meters)
    REQUIRE(WillardtoOhare == OharetoWillard);
    REQUIRE(abs(WillardtoOhare - truedistance) <= 1000);
    REQUIRE( abs(OharetoWillard - truedistance) <= 1000 );
    delete Willard; 
    delete OHare; 
}

TEST_CASE("Haversine 2: East-West", "[weight=0][part=3][part=3b]"){
    Airport *  Lester = new Airport(193,"Lester B. Pearson International Airport",43.6772003174,-79.63059997559999);   
    Airport *  Narita = new Airport(2279,"Narita International Airport",35.7647018433,140.386001587);

    double LestertoNarita = Lester->getDistance(Narita);
    double NaritatoLester = Narita->getDistance(Lester);

    double truedistance = 10311000; //(meters)
    REQUIRE(LestertoNarita == NaritatoLester);
    REQUIRE(abs(LestertoNarita - truedistance) <= 1000);
    REQUIRE( abs(NaritatoLester - truedistance) <= 1000 );
    delete Lester; 
    delete Narita; 
}

TEST_CASE("Haversine 3: North-South", "[weight=0][part=3][part=3c]"){
    Airport * OHare = new Airport(3830,"Chicago O'Hare International Airport",41.9786,-87.9048);
    Airport * Milwaukee = new Airport(3717,"General Mitchell International Airport",42.947200775146484,-87.89659881591797);

    double OharetoMilwaukee = OHare->getDistance(Milwaukee);
    double MilwaukeetoOhare = Milwaukee->getDistance(OHare);
    //check that each distance is correct, and that they're the same.
    double truedistance = 108000; //(meters)
    REQUIRE(OharetoMilwaukee == MilwaukeetoOhare);
    REQUIRE(abs(OharetoMilwaukee - truedistance) <= 1000);
    REQUIRE( abs(MilwaukeetoOhare - truedistance) <= 1000 );
    delete OHare; 
    delete Milwaukee; 
}

TEST_CASE("Haversine 4: Airport to itself distance is 0", "[weight=0][part=3][part=3e]"){
    Airport * Willard = new Airport(4049,"University of Illinois Willard Airport",40.03919983,-88.27809906);
    double selfDist = Willard->getDistance(Willard);
    REQUIRE(selfDist == 0);
    delete Willard; 
}

/* Page Rank: test cases
    - Check to see that it matches some accepted lists for most popular airports ???

*/

TEST_CASE("Page Rank 1: Does it match accepted records for most popular airports?", "[weight=0][part=4][part=4a]") {
    // Vector of airport pointers
    static vector<Airport*> airportList = parseAirports();
    // Vector of airportID's used for binary search
    static vector<int> airportIDs;
    for(unsigned long i = 0; i < airportList.size(); i++){
      airportIDs.push_back(airportList[i]->getID());
    }
    static int routeCount = parseRoutes(airportList, airportIDs);
    //Get ranks
    vector<double> ranks = PageRankNew(airportList, airportIDs, 100);
    //Now need to use distance and create the table with this rank order
    //Then fix it
    vector<string> rankList;
    for(int k=0;k<10;k++){
        string curr = airportList[std::distance(ranks.begin(), max_element(ranks.begin(), ranks.end()))]->getName();

        rankList.push_back(curr);
        ranks[std::distance(ranks.begin(), max_element(ranks.begin(), ranks.end()))] = 0.0;
    }
   
    //ACTUAL ANSWER VECTOR    
    vector<string> answer{"\"ATL\"","\"DFW\"","\"ORD\"","\"LAX\"","\"CDG\"","\"LHR\"","\"PEK\"","\"FRA\"","\"JFK\"","\"SIN\""};
    //Size of vectors must match for them to match
    REQUIRE(rankList.size() == answer.size());
    //Now loop and check that each element matches
    for(size_t i=0;i<rankList.size();i++){
        REQUIRE(!rankList[i].compare(answer[i]));
    }
    
    for(size_t i = 0; i < airportList.size(); i++){
      delete airportList[i]; 
    }
}

