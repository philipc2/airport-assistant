/*  PARSER CLASS:
    Description: Reads in airport / flight data from .dat file and prepares it for processing in our tree. It can:
    - Read in ALL airports
    - Read in all airports from [0,last]
    - Read in all airports in range [first,last]

*/
#include "parser.h"
#include <string>
#include<sstream>
#include<cstring>
#include <algorithm>    // std::binary_search, std::sort
using namespace std;

int binarySearch1(vector<int> airportIDs, int ourAirport){
  auto it = lower_bound(airportIDs.begin(), airportIDs.end(), ourAirport);
  if (it == airportIDs.end() || *it != ourAirport)
      return -1;
  else{
    return distance(airportIDs.begin(), it);
  }
}

// Parses through all the airports in the airport.dat file and returns a vector
// of all the airports
vector<Airport*> parseAirports(){
    ifstream airports;
    airports.open("airports.dat");
    string line;
    vector<Airport*> airportVector;

    if (airports)                                // Keep going until we run into a blank line
    {
      while (getline(airports, line))            // Get each line
      {
        // Split amongst the comma
        vector<string> splitLine;
        stringstream s_stream(line);
        while(s_stream.good()){
          string subString;
          getline(s_stream, subString, ',');
          splitLine.push_back(subString);
        }
        // Create a new instance of an airport
        if (splitLine.size() == 14){
        Airport* currentAirport = new Airport(stoi(splitLine[0]), splitLine[4], stod(splitLine[6]), stod(splitLine[7]));
        airportVector.push_back(currentAirport);
      }

      }
    }

    return airportVector;
}



// Parses through the routes.dat file and links all the airports together
// in the incoming routes file
int parseRoutes(vector<Airport*> airportList, vector<int> airportIDs){
  int counter = 0;
  ifstream routes;
  routes.open("routes.dat");
  string line;
  string subString;

  if (routes)                                // Keep going until we run into a blank line
  {
    while (getline(routes, line))            // Get each line
    {
      // Split amongst the comma
      vector<string> splitLine;
      stringstream s_stream(line);
      while(s_stream.good() && splitLine.size() <= 5){
        getline(s_stream, subString, ',');
        splitLine.push_back(subString);
      }



      // 3rd entry is the source, 5th element is the destination
      // Check to make sure the airport exists
        if(splitLine[3].length() == 2 || splitLine[5].length() == 2){
          if((splitLine[3][1] == 'N') || (splitLine[5][1] == 'N')){
            if(splitLine[3] == splitLine[5])  {continue;}
            continue;
          }
        }

        int sourceID_parsed = stoi(splitLine[3]);
        int desitnationID_parsed = stoi(splitLine[5]);
        int sourceID = binarySearch1(airportIDs, sourceID_parsed);
        int destinationID = binarySearch1(airportIDs, desitnationID_parsed);
        if (sourceID == -1 || destinationID == -1)
          continue;

        Airport* source = airportList[sourceID];
        Airport* destination = airportList[destinationID];
        source->addOutgoing(destination);

        counter++;

    }
  }
    return counter;
}
