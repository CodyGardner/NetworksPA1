#include "cfuncs.h"

using namespace std;

void help()//Prints the help options
{
  cout << "Important: All commands are lower case ONLY (file and path names not included)\n";
  cout << "help.....Prints the list of acceptable instructions\n";
  cout << "ls.......Lists the directories and files available from the connected server process\n";
  cout << "lls......Lists the directories and files available in the current working directory on this device\n";
  cout << "pwd......Prints the current working directory of the connected server process\n";
  cout << "lpwd.....Prints the current working directory on this device\n";
  cout << "cd.......Change the current working directory of the connected server process to the specified target\n";
  cout << "lcd......Change the current working directory on this device\n";
  cout << "get......Retrieve the specified target file\n";
  cout << "bye......Disconnect from the server and close the client\n\n";
}

char parsecommand(const string input)
//Evaluates user input to determine the appropriate response in main
{
  switch (input.size())
  //Switch based on instruction length to simplify total comparisons
  {
    case 2:
      if (input == "ls")
        return 'E';
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

    //if invalid command
    return '0';
}

void chitchat(int &socket)
//Used to recieve and print the terminal output from server after ls and pwd
{
  char msg[1023];
  //TODO: while loop to receive and print information recieved from the socket
  recv(socket, msg, 1023, 0);
  cout << msg;
}
