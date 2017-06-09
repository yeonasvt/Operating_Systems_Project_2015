#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <csignal>
#include <signal.h>
using namespace std;


int main(int argc, char **argv)
{
   
  //read in pid from file
  pid_t p1;

  ifstream myfile;
  myfile.open("PidFile.txt");
  if (!myfile.eof())
  {
    myfile >> p1;
    std::cout<< p1 <<std::endl;
  } else {
   cout << "Unable to open file"; 
  }
  myfile.close();

  //send signal to kill target process  
  kill(p1, SIGKILL);


}
