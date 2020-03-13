/*

TSP_Algorithm.cpp

Sheldon Roberts
Shayla Rao
Nick Vandomelen

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
using namespace std;

struct city {
  int identity;
  int x;
  int y;
  //vector<city> connections;
  //vector<int> distances;    //costs?
};

struct node {
  struct node* left;
  struct node* right;
  vector<city> cities;
  int identity;
  int totalCities;
};

//count the number of cities in a file
//int line_counter(string iFileName)
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

//just printing the tree
void rootPrint (node root)
{
  cout << "root.totalCities = " << root.totalCities << endl;
  cout << "root.left.cities[0].identity = " << root.left->cities[0].identity << endl;
  
  rootPrint(*root.left);		//std::bad_alloc(), core dumped
  rootPrint(*root.right);
}

//recursive filling of all nodes
void nodeFill (node &currNode, int numCities)
{ 
  int i;
  int numCitiesLeft  = numCities / 2;				//will round down
  int numCitiesRight = numCities - numCitiesLeft;		//remaining nodes on the right
  
  //create branches no matter what, we always look at the branches
  node right;
  node left;
  
  //if (numCities == 1), then we are at a leaf
  //so set left/right to Null, and exit recursion
  //base case
  if (numCities == 1)
  { 
    left.left   = NULL;
    left.right  = NULL;
    right.left  = NULL;
    right.right = NULL;
    
    return;
  }
  //otherwise function normally
  
  left.totalCities = 0;
  for (i = 0; i < numCitiesLeft; i++)
  {
    left.cities.push_back(city());		//fill currNode.left's city vector
    left.cities[i] = currNode.cities[i];
    left.totalCities++;
  }
  //cout << "left.totalCities = " << left.totalCities << endl;
  right.totalCities = 0;
  for (i = 0; i < numCitiesRight; i++)	//index through
  {
    right.cities.push_back(city());		//fill currNode.right's city vector
    right.cities[i] = currNode.cities[i + numCitiesLeft];	//indexing for the right half of the array
    right.totalCities++;
  }
  //cout << "right.totalCities = " << right.totalCities << endl;
  
  currNode.left = &left;
  currNode.right = &right;
  
  nodeFill (left, numCitiesLeft);
  nodeFill (right, numCitiesRight);
}

//finding a solution to the TSP
void tsp_alg (vector<city> &cityVector, node root, int numCities, char* iFileName)      //THE ACTUAL ALGORITHM
{
  int iFileNameSize = strlen(iFileName);              //strlen(char[n]) = 1
  char* oFileName = new char[iFileNameSize + 5];      //+5 for 5 characters from .tour
  int i, j, k;
  strcpy(oFileName, iFileName);
  ofstream oFile;

  char tour[] = {'.','t','o','u','r'};
  for (k = 0; k < 5; k++)     //concatentate each character of ".tour"
  {
    oFileName[k + iFileNameSize] = tour[k];
  }
  //at this point, oFileName should be correct
  oFile.open(oFileName);

  //INPUT THE BRANCH AND BOUND ALGORITHM HERE
  //cityVector[] has all identities, x coordinates, and y coordinates
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  //1. put all of the tours hotels in the root node (first node)
  //newTree = createTree(cityVector, numCities, 0, 0);
    
  
  
  //2a. calculate cost of all hotels
  //Hotel_cost_root = 0.5 * sum of two adjacent edges" distances
  

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
    //cout << "cityVector[i].identity: " << cityVector[i].identity << '\t';
    //cout << "cityVector[i].x" << cityVector[i].x << '\t';
    //cout << "cityVector[i].y" << cityVector[i].y << endl;
    // cityVector[i].identity = i;
    // cityVector[i].x = i;
    // cityVector[i].y = i;
  }
  //at this point, cityVector has all data from input file
    
  node root; //creating and filling a root node
  root.totalCities = 0;
  for (i = 0; i < numCities; i++)
  {
    root.cities.push_back(city());
    root.cities[i] = cityVector[i];		//MIGHT BE FUCKING UP
    root.totalCities++;
  }
  //cout << "root.totalCities = " << root.totalCities << endl;
  //int numNodes = (numCities * 2) - 1;
  nodeFill(root, numCities);
  
  rootPrint(root);
  
  //running the actual TSP algorithm
  tsp_alg(cityVector, root, numCities, iFileName);
  
  //always remember to close the files!
  iFile.close();
   
  return 0;
}