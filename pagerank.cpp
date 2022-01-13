#include "pagerank.h"

// Binary Search for Page Rank
int pageBFS(vector<int> airportIDs, int ourAirport){
  auto it = lower_bound(airportIDs.begin(), airportIDs.end(), ourAirport);
  if (it == airportIDs.end() || *it != ourAirport)
      return -1;
  else{
    return distance(airportIDs.begin(), it);
  }
}



// Performs the page rank algorithm on our graph of airports and outputs a vector
// containing all the airports ranked according to the algorithm

vector<double> PageRankNew(vector<Airport*> airportList, vector<int> airportIDs, int stepSize){
  // Decay factor
  double alpha = 0.85;

  // Store the number of airports for easy use
  int size = airportList.size();

  // Initialize each webpage a rank of 1 / size
  vector<double> ranks(size, double(1.0 / size));

  // Find the number of unique links for every airport
  vector<int> links(size, 0);

  // Itterate over every source airport
  for(int i = 0; i < size; i++)
  {

    int linkCount = 0;
    int sIndex = pageBFS(airportIDs, airportList[i]->getID());
    vector<bool> visited(size, false);

    // Itterate over every destination airport for a given source
    for(int  j = 0; j < airportList[i]->outgoingFlightCount() - 1; j++)
    {

      int dIndex = pageBFS(airportIDs, (airportList[i]->outgoing[j])->getID());

      // If we haven't visisted
      if(visited[dIndex] == false)
      {
        linkCount++;
        visited[dIndex] = true;
      }
      else
        linkCount++;

    }

    links[sIndex] = linkCount;

  }


  //int stepSize = 100;
  for(int step = 0; step < stepSize; step++)
  {
    // Display to show current progress of PageRank
    cout << "\33[1;32m\rPage Rank Progress \033[0m" << int(double(step)/double(stepSize) * 100) << "%" << flush;
    // Set every new rank as 0 to start
    vector<double> newRanks(size, 0.0);

    // Equally share the page rank for each airport
    for(int i = 0; i < size; i++)
    {

      // Get the airport index
      int sIndex = pageBFS(airportIDs, airportList[i]->getID());

      // Update the new rank
      if(links[sIndex] > 0)
      {

        // Itterate through every adjacent vertex and update the new rank
        for(int j = 0; j < airportList[sIndex]->outgoingFlightCount() - 1; j++)
        {
          int dIndex = pageBFS(airportIDs, (airportList[i]->outgoing[j])->getID());
          newRanks[dIndex] += (alpha * ranks[sIndex]) / links[sIndex];
        }
      }

      // No links, update every airport rank
      else
      {
        for(int k = 0; k < size; k++)
          newRanks[k] += ranks[sIndex] / double(size);
          ranks[sIndex] = 0.0;
      }


    }

    // Add an offset to keep the valid prob distribution
    for(int j = 0; j < size; j++)
      newRanks[j] += (1.0 - alpha) / double(size);


    //cout << *max_element(newRanks.begin(), newRanks.end()) << endl;
    //cout << airportList[distance(newRanks.begin(), max_element(newRanks.begin(), newRanks.end()))]->getName() << endl;
    ranks = newRanks;


  }
  cout << "\33[1;32m\rPage Rank Progress \033[0m" << int(100) << "%" << flush;



  return ranks;
}
