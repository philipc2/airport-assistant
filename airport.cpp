#include "airport.h"


Airport::Airport(){
  airportID = -1;
  airportName = "Undefined Airport";
  latitude = 0;
  longitude = 0;

}

Airport::Airport(int AirportID_input, string AirportName_input, double latitude_input, double longitude_input){
  airportID = AirportID_input;
  airportName = AirportName_input;
  latitude = latitude_input;
  longitude = longitude_input;

}

int Airport::getID(){
  return airportID;
}

string Airport::getName(){
  return airportName;
}

void Airport::addOutgoing(Airport* destination){
  outgoing.push_back(destination);
}


int Airport::outgoingFlightCount(){
  return outgoing.size();
}


double Airport::getY(){
  return latitude;
}

double Airport::getX(){
  return longitude;
}

double Airport::getDistance(Airport* destination){
  double pi = 3.1415926535897;
  double lat1 = latitude * pi / 180.0;
  double lat2 = destination->getY() * pi / 180.0;
  double long1 = longitude * pi / 180.0;
  double long2 = destination->getX() * pi / 180.0;

  double hav1 = pow(sin((lat2 - lat1)/2.0), 2);
  double hav2 = pow(sin((long2 - long1)/2.0), 2);

  double a = hav1 + cos(lat1)*cos(lat2)*hav2;
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  double d = (6378.1 * 1000) * c;

  return d;
}
