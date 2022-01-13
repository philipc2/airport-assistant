
#include "BFS.h"


BFS::BFS(){

}
BFS::BFS(vector<Airport*> AirportList, vector<int> AirportIDs, Airport* start, int count)
{
  //set the current airport to the starting point
  curAirport = start;
  startAirport = start; 
  //set up the vector of visited airports
  for(unsigned long i = 0; i < AirportList.size(); i++){
    visited.push_back(false);
  }

  //set up iteration count and airportIDs
  it_count = count;

  //create a local AirportID vector
  for(unsigned long i = 0; i < AirportIDs.size();i++){
    AirportID.push_back(AirportIDs[i]);
  }

  //set up the final vector size
  //for(int i = 0; i < count; i++){
  //  final_airports.push_back(NULL);
  //}

}

int BFS::BinaryBFS(vector<int> AirportIDs, int ourAirport)
{
  auto it = lower_bound(AirportIDs.begin(), AirportIDs.end(), ourAirport);
  if (it == AirportIDs.end() || *it != ourAirport)
    return -1;
  else{
    return distance(AirportIDs.begin(), it);
  }
}
vector<Airport*> BFS::algorithm()
{
  //enqueue current Airport
  q.push(curAirport);

  //mark as visited
  visited[BinaryBFS(AirportID, curAirport->getID())] = true;
  /**
   * Checks to see if outgoing Airports (adjacencies) are NULL
   * Allows us to see if they have been visited
   * from there we can push them into the queue (if not visited and adjacent)
   * mark as visited
   **/

  while(!q.empty()){
    
    /*
     * Beginning part of BFS 
     * adds 1st airport to queue 
     * makes it visited 
     */
      curAirport = q.front();
      q.pop();
      
      final_airports.push_back(curAirport);
      visited[BinaryBFS(AirportID,curAirport->getID())] = true; 
   
   unsigned i = 0;
   int count = 0;
    //Edge case for BFS- what happens if the outgoing vector of start airport is 0 
    if((startAirport->outgoing).size() == 0){
      std::cout << "No valid outgoing flight paths." << std::endl; 
      return final_airports; 
    }
    /*
     * bulk of BFS 
     * pushes airport to queue, marks as visited, and stops if count is as necessary 
     */
    while(i < (curAirport->outgoing).size()){
      if((curAirport->outgoing[i] != NULL ) && ((visited[BinaryBFS(AirportID, (curAirport->outgoing[i])->getID())]) == false)){
        q.push(curAirport->outgoing[i]);
        visited[BinaryBFS(AirportID, (curAirport->outgoing[i])->getID())] = true;
        //if the count is less than the final count, we add it to the final list of airports
        if(count == it_count - 1){
          return final_airports;
        }
        final_airports.push_back(curAirport->outgoing[i]);
      }
      //iterate through count and i
      count++;
      i++;
    }
  }
  return final_airports;
}
