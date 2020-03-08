/*

TSP_Algorithm.cpp

Sheldon Roberts
Shayla Rao
Nick Vandomelen

*/
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct city {
  int identity;
  int x;
  int y;
};

//count the number of cities in a file
//int line_counter(string iFileName)
int line_counter()
{
  ifstream iFile;
  string line;
  iFile.open("tsp_example_1.txt");

  int lineCounter = 0;
  while (!iFile.eof())
  {
    getline(iFile, line);
    lineCounter++;
  }
  iFile.close();
  return lineCounter;
}

//finding a solution to the TSP
void tsp_alg (vector<city> &cityVector, int numCities)
{
  //input the tsp algorithm here
  for (int i = 0; i < numCities; i++)
  {
    cout << "cityVector[" << i << "].identity = " << cityVector[i].identity << endl;
  }
}

int main (int argc, char* argv[])
{

  //get name of file to open from command line

  string iFileName = argv[1];
  //string oFileName = argv[1] + ".tour";
  int numCities;
  int i;

  //numCities = line_counter(iFileName);  //set numCities equal to the number of cities in the input file
  numCities = line_counter();  //set numCities equal to the number of cities in the input file

  ifstream iFile;
  ofstream oFile;
  //open input and output file
  iFile.open(argv[1]);
  oFile.open("tsp_example_1.txt.tour");

  if(iFile.is_open()){
    while(getline(iFile, iFileName)){
      cout << "file opened" << endl;
    }
  }
  else{
    cout << "file not found" << endl;
  }


  //create a city vector and fill it from input file
  //city cityVector[numCities];
  vector<city> cityVector;
  for (i = 0; i < numCities; i++)
  {
    cityVector.push_back(city());
    iFile >> cityVector[i].identity;
    iFile >> cityVector[i].x;
    iFile >> cityVector[i].y;
  }

  //at this point, cityVector has all data from input file

  tsp_alg(cityVector, numCities);


  //always remember to close the files!
  iFile.close();
  oFile.close();
  return 0;
}
