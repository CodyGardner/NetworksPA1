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
      if (input == "pwd")
        return 'B';
      if (input == "bye")
        return 'E';
      break;

    default:
      if (input.substr(0,2) == "cd")
        return 'C';
      if (input.substr(0,3) == "get")
        return 'D';
      break;
  }
}

void sendFile(int &socket, std::string &file)
//Opens requested file and then sends file text through socket
{

}
