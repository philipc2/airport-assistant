#include "airport.h"
#include "parser.h"
#include "BFS.h"
#include "pagerank.h"
#include "Dijkstra.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include<unistd.h>
#include <cstddef>
#include <limits>
using namespace std;

void clearScreen(){
  int temp = -1;
  cout << "\033[0;37mEnter any integer to continue . . . \033[0m" << endl;
  cin >> temp;
  if (cin.fail()){
    cout << "\033[1;37m1) Please enter an Integer\033[0m";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  cout << "\033[2J\033[1;1H";
}
int binarySearch(vector<int> airportIDs, int ourAirport){
  auto it = lower_bound(airportIDs.begin(), airportIDs.end(), ourAirport);
  if (it == airportIDs.end() || *it != ourAirport)
      return -1;
  else{
    return distance(airportIDs.begin(), it);
  }
}


int main() {

  //unsigned int microsecond = 1000000;

  // Vector of airport pointers
  vector<Airport*> airportList = parseAirports();
  // Vector of airportID's used for binary search
  vector<int> airportIDs;

  for (unsigned long i = 0; i < airportList.size(); i++)
    airportIDs.push_back(airportList[i]->getID());

  // Parse through all the routes
  int routeCount = parseRoutes(airportList, airportIDs);


  // First thing displayed on screen
  int choice = -1;
  cout << "\033[2J\033[1;1H";
  cout << "\033[1;32mWelcome to our Airport Assistant Final Project for CS 225! \033[0m" << endl;
  cout << "\033[0;32mBy Philip, Matt, John, & Anushya \033[0m\n" << endl;

  // Ask the user to enter any key and then flush the screen
  clearScreen();

  // Display some information
  cout << "\033[1;32mIn order to properly use this program, you must know a few things.   \033[0m" << endl;
  cout << "\033[1;32mEvery airport is assigned an AirportID integer value, which you      \033[0m" << endl;
  cout << "\033[1;32mwill need to use our program. Here are a couple for your convenience \033[0m" << endl;
  cout << "\033[0;32mORD : 3830                                                          \033[0m" << endl;
  cout << "\033[0;32mLAX : 3484                                                          \033[0m" << endl;
  cout << "\033[0;32mATL : 3682                                                          \033[0m" << endl;

  clearScreen();

  // Main game loop
  while(choice != 0){
  cout << "\033[1;32mWhat would you like to do?\033[0m\n" << endl;
  cout << "\033[1;37m1) View Number of Airports\033[0m" << endl;
  cout << "\033[1;37m2) View Number of Routes\033[0m" << endl;
  cout << "\033[1;37m3) View Airport Info   \033[0m" << endl;
  cout << "\033[1;37m4) Airport Distance      (Haversine)  \033[0m" << endl;
  cout << "\033[1;37m5) Shortest Path         (Dijkstra's)  \033[0m" << endl;
  cout << "\033[1;37m6) Airport Ranking       (Pagerank)    \033[0m" << endl;
  cout << "\033[1;37m7) Visual Showcase       (BFS)          \033[0m" << endl;
  cout << "\033[1;37m0) Exit Program\033[0m\n" << endl;
  cout << "\033[1;32mPlease enter the integer value corresponding to your choice\033[0m" << endl;
  cin >> choice;
  if (cin.fail()){
    cout << "\033[1;37m1) Please enter an Integer\033[0m";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    choice = -2;
  }
  cout << "\033[2J\033[1;1H";

  switch (choice){
    case -2:
      continue;

    case 0:
      cout << "\033[1;31mThank you for using our program!\033[0m\n" << endl;
      continue;

    case 1:
      cout << "\033[1;32mTotal Number of Airports: \033[0m" << airportList.size() << endl;
      clearScreen();
      continue;

    case 2:
    cout << "\033[1;32mTotal Number of Routes: \033[0m" << routeCount << endl;
    clearScreen();
    continue;

    case 3:

      int selectedAirport;
      cout << "\033[1;32mPlease enter an AirportID integer value\033[0m" << endl;
      cin >> selectedAirport;

      if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearScreen();
        continue;
      }

      if (binary_search (airportIDs.begin(), airportIDs.end(), selectedAirport)){
        cout << "\033[0;32mAirport Name              : \033[0m" << airportList[binarySearch(airportIDs, selectedAirport)]->getName()                 << endl;
        cout << "\033[0;32mAirport ID                : \033[0m" << airportList[binarySearch(airportIDs, selectedAirport)]->getID()                   << endl;
        cout << "\033[0;32mNumber of Outgoing Routes : \033[0m" << airportList[binarySearch(airportIDs, selectedAirport)]->outgoingFlightCount()     << endl;
        cout << "\033[0;32mLatitude                  : \033[0m" << airportList[binarySearch(airportIDs, selectedAirport)]->getY()                    << endl;
        cout << "\033[0;32mLongitude                 : \033[0m" << airportList[binarySearch(airportIDs, selectedAirport)]->getX()                    << endl;                                                                             ;
      }
      else{
        cout << "\033[1;37mNot a valid AirportID number.\033[0m" << endl;
      }

        clearScreen();
        continue;


    case 4:

      int sourceAirport1;
      int destinationAirport1;
      int index1;
      int index2;
      double distance;
      cout << "\033[1;32mPlease enter your source AirportID\033[0m" << endl;
      cin >> sourceAirport1;

      if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearScreen();
        continue;
      }

      cout << "\033[1;32mPlease enter your destination AirportID\033[0m" << endl;
      cin >> destinationAirport1;

      if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearScreen();
        continue;
      }

      if(binary_search(airportIDs.begin(), airportIDs.end(), sourceAirport1) && binary_search(airportIDs.begin(), airportIDs.end(), destinationAirport1)){
        index1 = binarySearch(airportIDs, sourceAirport1);
        index2 = binarySearch(airportIDs, destinationAirport1);
        distance = airportList[index1]->getDistance(airportList[index2]);
        cout <<fixed<< "\033[0;32mDistance between airports     (meters): \033[0m" << distance << endl;
      }

      else{
        cout << "\033[1;37mOne or more of your AirportID's is invalid\033[0m" << endl;
      }

      clearScreen();
      continue;

    case 5:

      int sourceAirport;
      int destinationAirport;
      int sIndex;
      int dIndex;
      Airport* start;
      Airport* end;
      cout << "\033[1;32mPlease enter your source AirportID\033[0m" << endl;
      cin >> sourceAirport;
      if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearScreen();
        continue;
      }
      cout << "\033[1;32mPlease enter your destination AirportID\033[0m" << endl;
      cin >> destinationAirport;

      if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearScreen();
        continue;
      }

      if(binary_search(airportIDs.begin(), airportIDs.end(), sourceAirport) && binary_search(airportIDs.begin(), airportIDs.end(), destinationAirport)){
        // do here
        sIndex = binarySearch(airportIDs, sourceAirport);
        dIndex = binarySearch(airportIDs, destinationAirport);
        start = airportList[sIndex];
        end = airportList[dIndex];

        // vector <Airport*> getDistance(vector<Airport*> airportList, vector<int> airportIDs, Airport* start, Airport* end)
        // 1)   Set current node to source
        // 2)   Itterate over every edge
        // 3)   Calculate the distances using curNode->getDistance(it), where it is an Airport*
        // 4)   Set curNode to it, mark as visited, and then jump to 2


        // Test Code for Graphical Represenation

          vector<Airport*> DSSSP_output = DijkstraSSSP(airportList, airportIDs, start, end);

          cout << endl;
          cout << "\033[1;32mSource Airport:       \033[0m" << DSSSP_output[0]->getName() << endl;
          cout << "\033[1;32mDestination Airport:  \033[0m" << DSSSP_output[DSSSP_output.size() - 1]->getName() << endl;
          cout << '\n';
          cout << "\033[0;32mShortest Route \033[0m" << endl;

          for (unsigned long k = 0; k < DSSSP_output.size(); k++){
            cout << DSSSP_output[k]->getName();
            if (k == DSSSP_output.size() - 1){
              cout << '\n';
              break;
            }
            cout << "\033[1;32m -> \033[0m ";
          }

        }

        else{
          cout << "\033[1;37mOne or more of your AirportID's is invalid\033[0m" << endl;
        }

      //int sourceIndex = binarySearch(airportIDs, sourceAirport);
      //int destinationIndex = binarySearch(airportIDs, destinationAirport);

      //Airport* source = airportList[sourceIndex];
      //Airport* destination = airportList[destinationIndex];

      // dijkstras(source, destination);
      // Vector of Airport Pointers signifiying shortest path

      clearScreen();
      continue;

    case 6: {

      int stepSize;
      cout << "\033[1;32mPlease enter your desired number of iterations\033[0m" << endl;
      cin >> stepSize;

      if (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearScreen();
        continue;
      }


      vector<double> ranks = PageRankNew(airportList, airportIDs, stepSize);
      cout << " " << endl;

      cout << "\033[1;32mTop 10 Airports based on PageRank\033[0m" << endl;
      for(int k = 0; k < 10; k++){

        cout << airportList[std::distance(ranks.begin(), max_element(ranks.begin(), ranks.end()))]->getName() << endl;
        ranks[std::distance(ranks.begin(), max_element(ranks.begin(), ranks.end()))] = 0.0;
      }

      clearScreen();
      continue;
    }

    case 7: {

    int bfsSource;
    int bfsIndex;
    //vector<Airport*> returnPath;
    cout << "\033[1;32mPlease enter your source AirportID\033[0m" << endl;
    cin >> bfsSource;

    if (cin.fail()){
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      clearScreen();
      continue;
    }

    int bfsCount;
    cout << "\033[1;32mHow many steps would you like to print?\033[0m" << endl;
    cin >> bfsCount;

    if (cin.fail()){
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      clearScreen();
      continue;
    }



    if(binary_search(airportIDs.begin(), airportIDs.end(), bfsSource)){


       bfsIndex = binarySearch(airportIDs, bfsSource);
       BFS *testBFS;
       testBFS = new BFS(airportList, airportIDs, airportList[bfsIndex], 40);
       vector<Airport*> returnPath;
       returnPath = testBFS->algorithm();


       cout << "\033[1;32mEach airport is printed in the order visisted\033[0m" << endl;
       for(int w = 0; w < bfsCount; w++){
         cout << returnPath[w]->getName() << endl;
       }





    }

    clearScreen();
    continue;

}
    default:

      clearScreen();
      continue;
  }

}

  return 0;
}
