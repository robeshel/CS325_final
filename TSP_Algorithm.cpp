/*

TSP_Algorithm.cpp

Sheldon Roberts
Shayla Rao
Nick Vandomelen

*/

//LAST WORK DONE LINE 46

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct city {
  int identity;
  int x;
  int y;
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

//finding a solution to the TSP
void tsp_alg (vector<city> &cityVector, int numCities, char* iFileName)      //ADD THE ACTUAL ALGORITHM
{
  int iFileNameSize = strlen(iFileName);              //strlen(char[n]) = 1
  char* oFileName = new char[iFileNameSize + 5];      //+5 for 5 characters from .tour
  strcpy(oFileName, iFileName);
  ofstream oFile;

  char tour[] = {'.','t','o','u','r'};
  for (int k = 0; k < 5; k++)     //concatentate each character of ".tour"
  {
    oFileName[k + iFileNameSize] = tour[k];
  }
  //at this point, oFileName should be correct
  //cout << "oFileName = " << oFileName << endl;
  oFile.open(oFileName);

  //INPUT THE BRANCH AND BOUND ALGORITHM HERE
  //cityVector[] has all identities, x coordinates, and y coordinates
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////



  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  //print the output to oFile
  for (int i = 0; i < numCities; i++)
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

  //create a city vector and fill it from input file
  //city cityVector[numCities];
  vector<city> cityVector;
  for (i = 0; i < numCities; i++)
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

  //cout << "going into tsp_alg()" << endl;
  tsp_alg(cityVector, numCities, iFileName);

  //always remember to close the files!
  iFile.close();
  return 0;
}
