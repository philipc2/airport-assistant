# Airport Assistant - CS 225 Final Project

## Contributors
* Philip Chmielowiec - philipc2
* Matheu Fletcher - matheuf2
* John Smith - johnhs3
* Anushya Iyer - anushya2

## Overview

We created an interactive console application to showcase different graph algorithms on a subset of the OpenFlights dataset. All the user has to do is run the program, and everything is accessible through a console-based graphical interface. All major data and results will be viewable after the user determines what they want to do.

## AirportID Disclaimer

Our program relies on the AirportID integer value associated with every airport. For example, "ORD" corresponds to 3830. In order to properly use this program, you may want to have the airports.dat file open so you can quickly look up an airportID number. However, we provide you with a few to get started.

## Compilation Instructions

We have two options to run our program. The first one is the standard console command to compile our program:

> module load llvm/6.0.1

> clang++ -Wall -std=c++11 main.cpp airport.cpp parser.cpp BFS.cpp pagerank.cpp Dijkstra.cpp -o main

> ./main

Our other option is to use the make file. This is often the go-to method, and we recommend you use it for its ease of use:

> module load llvm/6.0.1

> make

> ./finalproj

## Test Instructions

Likewise, we have prepared a collection of tests that can be run to verify the correctness of our program and its algorithms. Test cases are located in the file `testcases.cpp`, and you can compile our tests by running:

> make test

> ./test

These tests are designed to test all the major components of our program, including the BFS traversal, Dijkstra's Algorithm, Page-Rank Algorithm, and Haversine Formula Distance Calculator. They are separated by part. For example, typing "`./test [part=1]`" would run all tests associated with the BFS traversal.
A list of some of the included tests is provided below. For a full list of tests and their descriptions, look above each section/part in `testcases.cpp`:

**BFS**:
* Make sure BFS is traversing correctly
* Handles edge cases in traversal. e.g., what if the user enters a number of steps that is greater than the number of airports in the connected component of which the source airport is a member?

**Dijkstra's**:
* Finds the shortest path from Champaign-Urbana's very own Willard Municipal Airport to O'Hare. (Hint: it's a direct flight).
* When a round-trip exists, tests if the flight path from destination to source is the reverse of source to destination.
* Tests a multi-layover flight path around the world.
* Tests if the program handles an input of two airports for which there does not exist a path between them (i.e. in different components of the graph)
* Checks that program handles the trivial path from an airport to itself.

**Haversine Formula**:
* Tests that the distance between two airports is correct, as verified online.
* Tests that the distance from airport A to airport B is the same as the distance from B to A.
* Tests distance between two airports at approximately the same latitude.
* Tests distance between two airports at approximately the same longitude.
* Checks that the distance from an airport to itself is zero.

**Page-Rank**:
* Checks if program results match accepted records for most popular airports (top 10).





# matheuf2-anushya2-philipc2-johnhs3
