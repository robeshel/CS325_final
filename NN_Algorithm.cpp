/*
Shayla Rao
Nick Vandomelen
Sheldon Roberts

 Nearest Neighbor Algorithm for TSP
*/

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <cstddef>
#include <cstdlib>
using namespace std;

struct city {
  int identity;
  int x;
  int y;
};

int line_counter(char* iFileName)
{
  ifstream iFile1;
  string line;
  iFile1.open(iFileName);

  int lineCounter = 0;
  if(iFile1.is_open())
  {
    while (!iFile1.eof())
    {
      getline(iFile1, line);
      //cout << line << endl;   //print each line
      lineCounter++;
    }
  }
  else
  {
    iFile1.close();
    return -1;
  }

  iFile1.close();
  return (lineCounter - 1);   //-1 because of extra line
}

//finding the distance between two cities, using pythag, rounding to nearest int
int pythag (city city1, city city2)
{
  double distance = sqrt(pow((city1.x - city2.x), 2) + pow((city1.y - city2.y), 2));    //pythag theorem
  int distanceInt = round(distance);        //make sure to round to an int
  return distanceInt;
}

int pythag_vector (vector<city> &cityVector, int curr_city, int test_city)
{
  double distance = sqrt(pow((cityVector[curr_city].x - cityVector[test_city].x), 2) + pow((cityVector[curr_city].y - cityVector[test_city].y), 2));    //pythag theorem
  int distanceInt = round(distance);        //make sure to round to an int
  return distanceInt;
}

//finding a solution to the TSP
void tsp_alg (vector<city> &cityVector,  int numCities, char* iFileName)      //THE ACTUAL ALGORITHM
{
  int iFileNameSize = strlen(iFileName);              //strlen(char[n]) = 1
  char* oFileName = new char[iFileNameSize + 5];      //+5 for 5 characters from .tour
  int i, j, k, min_distance, current_distance;
  strcpy(oFileName, iFileName);
  ofstream oFile;
  srand(time(NULL));

  char tour[] = {'.','t','o','u','r'};
  for (k = 0; k < 5; k++)     //concatentate each character of ".tour"
  {
    oFileName[k + iFileNameSize] = tour[k];
  }
  //at this point, oFileName should be correct
  oFile.open(oFileName);

  //INPUT THE NEAREST NEIGHBOR ALGORITHM HERE
  //cityVector[] has all identities, x coordinates, and y coordinates
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  int visit_arr[numCities];
  int counter = 0;
  int tour_arr[numCities];
  //Fill the visit array to be all unvisited nodes
  //0 = unvisited || 1 = visited
  for (i = 0; i < numCities; i++ ){
    visit_arr[i] = 0;
  }
   // Select a random node to start at.
  int current_node = rand() % numCities;
  int start_node = current_node;
  //Test statement to check that random is being seeded correctly
  //cout << "current_node : " << current_node << endl;

  int current_city = cityVector[current_node].identity;
  //cout << "current city: ID, X, Y : " << cityVector[current_node].identity << ", " << cityVector[current_node].x << ", " << cityVector[current_node].y << endl;

  //Set the first node to be visited so that it cant have the length fucntion run on it
  visit_arr[current_node] = 1;
  //set min distance to largest int possible to get the loop started
  min_distance = 2147483647;
  cout << "counter = " << counter << endl;
  cout << "numCities = " << numCities << endl;
  while(counter < numCities){
    for (i = 0; i < numCities; i++){
      //If the node has not been visited, compute pythag and compare to min distance
      if(visit_arr[i] == 0){
        current_distance = pythag_vector(cityVector, current_city, i);
        //cout << "cityVector[i].x : " << cityVector[i].x  << endl;
        //Check to see if min distance is still the lesser
        if(min_distance < current_distance){
          //If it is, keep the index value and increase the index by one to check the next node
          //continue;
          cout << "min_distance : " << min_distance << endl;
          cout << "current_distance: " << current_distance << endl;
        }
        else{
          //If the min is no longer to lesser of the two, set min to current_distance
          min_distance = current_distance;
          //keep track of the minimum distance node index value for later
          current_node = i;
          cout << "Else statement, min_distance : " << min_distance << endl;
        }
      }
      //If the current node has already been visited then just increment the counter by one and move on
      else{
        //Keep track of how many nodes have been visited, if the counter == numCities, move on and call the program complete
        counter++;
      }
    }
    //After exiting the for loop we should have found the min distance between all the nodes unvisited
    //Set the visit arr of the current node to 1  to set it as visited
    visit_arr[current_node] = 1;
    tour_arr[current_node] = cityVector[current_node].identity;
    // cout << "current node : " << current_node << endl;
    // cout << "Starting node" << start_node << endl;
    // cout << "counter: "  << counter << endl;
    // cout << "Min distance: " << min_distance << endl;

  }
  cout << "Num Cities: " << numCities << endl;
  cout << "current node : " << current_node << endl;
  cout << "Starting node" << start_node << endl;
  cout << "counter: "  << counter << endl;
  cout << "Min distance: " << min_distance << endl;
  cout << "tour contents: " <<  endl;
  for(int i=0; i < numCities; i++){
    cout << tour_arr[i] << ", ";
  }
  //while(counter != 0 )



  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  //print the output to oFile
  for (i = 0; i < numCities; i++)
  {
    //oFile << "START" << '\t' << "tab?" << endl;
    oFile << cityVector[i].identity << ' ';
    oFile << cityVector[i].x << ' ';
    oFile << cityVector[i].y << endl;
  }
  oFile << endl;        //adding an extra line for n+1 lines total

  delete[] oFileName;   //free dynamic memory
  oFile.close();
}

int main (int argc, char* argv[])
{
  //make sure to test file names with various lengths

  //get name of file to open from command line
  //names must be character pointers
  char* iFileName = argv[1];
  int numCities;
  int i;

  numCities = line_counter(iFileName);  //set numCities equal to the number of cities in the input file
  if (numCities == -1)  //if file doesn't exist, exit normally
  {
    cout << "could not open file! Exiting.." << endl;
    return 0;
  }

  //declare and open input/output file
  ifstream iFile;
  iFile.open(argv[1]);

  //create a city vector
  vector<city> cityVector;
  for (i = 0; i < numCities; i++)		//fill the city vector from input file
  {
    cityVector.push_back(city());
    iFile >> cityVector[i].identity;
    iFile >> cityVector[i].x;
    iFile >> cityVector[i].y;
    cout << "cityVector[i].identity: " << cityVector[i].identity << '\t';
    cout << "cityVector[i].x" << cityVector[i].x << '\t';
    cout << "cityVector[i].y" << cityVector[i].y << endl;
    // cityVector[i].identity = i;
    // cityVector[i].x = i;
    // cityVector[i].y = i;
  }
  //at this point, cityVector has all data from input file

  //running the actual TSP algorithm
  tsp_alg(cityVector,numCities, iFileName);
  //always remember to close the files!
  iFile.close();

  return 0;
}
