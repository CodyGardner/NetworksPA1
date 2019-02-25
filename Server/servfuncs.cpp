#include "servfuncs.h"

using namespace std;

char parsecommand(const string input)
//Evaluates user input to determine the appropriate response in main
{
  //TODO: Generate return values based on commands

  switch (input.size())
  //Switch based on instruction length to simplify total comparisons
  {
    case 2:
      if (input == "ls")
        return 'A';
      break;

    case 3:
      if (input == "lls")
        return 'B';
      if (input == "pwd")
        return 'E';
      if (input == "bye")
        return 'H';
      break;

    case 4:
      if (input == "help")
        return 'A';
      if (input == "lpwd")
        return 'C';
      break;

    default:
      if (input.substr(0,2) == "cd")
        return 'F';
      if (input.substr(0,3) == "lcd")
        return 'D';
      if (input.substr(0,3) == "get")
        return 'G';
      break;
  }
