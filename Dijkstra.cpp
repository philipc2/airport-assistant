/* IMPLEMENTATION OF DIJKSTRA'S ALGORITHM -- FOR OUR AIRPLANE FLIGHT TRACKER PROJECT
    Notes: -Dependencies: BFS.

*/
#include "Dijkstra.h"
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using namespace std;

//helper method for performing binary search on airport IDs vector. returns the index of the airport matching the parameter.
int DJbinarySearch(vector<int> AirportIDs, int ourAirport)
{
  auto it = lower_bound(AirportIDs.begin(), AirportIDs.end(), ourAirport);
  if (it == AirportIDs.end() || *it != ourAirport)
    return -1;
  else{
    return distance(AirportIDs.begin(), it);
  }
}

vector<Airport *> DijkstraSSSP(vector<Airport*> AirportList, vector<int> AirportIDs, Airport* source, Airport* destination){

    //vector of airport distances. Initially with value INF for all of them.
    vector<double> d(AirportList.size(),INF);

    // map of previous airports. takes the form p[current] = prev.
    map<Airport*,Airport*> p;
    //our priority queue. sorted by first element, the distance d[v]
    typedef pair<double, Airport*> queuePair;
    priority_queue<queuePair, vector<queuePair>, greater<queuePair>> Q;

    // initialize visited to all false, p to all nullptr, set d[source] = 0, set visited[source] = true, push to Queue.
    vector<bool> visited(AirportList.size(),false);
    for(auto i : AirportList){
        p.insert(make_pair(i,nullptr));
    }
    d[DJbinarySearch(AirportIDs,source->getID())] = 0;
    Q.push(make_pair(d[DJbinarySearch(AirportIDs,source->getID())],source));
    visited[DJbinarySearch(AirportIDs,source->getID())] = true;
    
    // To check if two airports are NOT connected at all, we will have a counter variable that will increment each time
    // the main loop is run. Since the number of times the loop runs is bounded above by the number of airports, 
    // we can check if our counter exceeds this, then break out and return.
    unsigned counter = 0;
    //while the top of the queue is not destination
    while(!(Q.top().second == destination)){
        ++counter;
        //check if airports are in two distinct components of the graph.
        if(counter > AirportList.size()){
            return vector<Airport*>();
        }        

        //u = Q.removeMin(). then pop it
        Airport* u = Q.top().second;
        Q.pop();

        //for each neighbor of u that is not in visited (i.e. if it's still on the queue):
        vector<Airport*> neighbors;
        for(auto n : u->outgoing){
            if(visited[DJbinarySearch(AirportIDs,n->getID())] == false){
                neighbors.push_back(n);
            }
        }

        //now we've built neighbors. It's time to go over them and do the crucial part of the algo.
        // v is a possible route.
        for( auto v : neighbors ){
            double potentialDist = d[DJbinarySearch(AirportIDs,u->getID())] + u->getDistance(v);
            if(potentialDist < d[DJbinarySearch(AirportIDs,v->getID())]){
                d[DJbinarySearch(AirportIDs,v->getID())] = potentialDist;
                Q.push(make_pair(d[DJbinarySearch(AirportIDs,v->getID())],v));
                p[v] = u;
            }
        }
        visited[DJbinarySearch(AirportIDs,u->getID())] = true;
    }
    //cout << "Reached line 107" << endl;

    //now, prev should hold a "chain" of vectors starting at destination and going backwards to start.
    //we want to take this, extract it, and reverse the chain, putting each entry in a vector, then returning that vector.
    vector<Airport*> output;
    Airport * current = destination;
    output.push_back(current);
    std::vector<Airport*>::iterator it = output.begin();
    while(current != source){
        //this should never be executed.
        if(p[current] == nullptr){
            cout << "Uh-oh!! the previous node of current node is nullptr!" << endl;
            return output;
        }
        output.insert(it,p[current]);
        current = p[current];
        it = output.begin();
        
    }
    
    return output;
}
