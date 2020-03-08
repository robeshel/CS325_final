/*

TSP_Algorithm.cpp

Sheldon Roberts
Shayla Rao
Nick Vandomelen

*/

#include <stdio>
#include <iostream>
#include <fstream>
using namespace std;

struct city {
  int identity;
  int x;
  int y;
};

int main ()
{
  
  //get name of file to open
  string iFileName = "tsp_example_1.txt";
  string oFileName = iFileName + ".tour";
  int numCities;
  string line;
  int lineCounter = 0;
  
  ifstream iFile;
  ofstream oFile;
  iFile.open(iFileName);
  oFile.open(oFileName);
  
  lineCounter = 0;
  while (!iFile.eof())
  {
    getline(iFile, line);
    lineCounter++;
  }
  iFile.close(iFile)
  iFile.open(iFileName);
  
  city cityArray[numCities];
  
  
  
  iFile.close(iFile);
  oFile.close(oFile);
  return 0;
}