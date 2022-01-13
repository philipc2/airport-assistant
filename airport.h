#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

  class Airport {

    public:

      // Default constructor
      Airport();

      // Main constructor
      Airport(int AirportID_input, string AirportName_input, double latitude_input, double longitude_input);

      // Returns the integer ID of the airport
      int getID();

      // Returns the string name of the airport
      string getName();

      // Adds an incoming flight
      void addOutgoing(Airport* source);

      // Returns the # of incoming flights
      int outgoingFlightCount();

      // Sets the coordinates of the airport
      double getX();

      double getY();

      double getDistance(Airport* destination);



      vector<Airport*> outgoing;        // Vector of outgoing flights
    private:
      double latitude;
      double longitude;
      int airportID;                    // Unique AirportID value
      string airportName;               // Unique Airport Name


  };
