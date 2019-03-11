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
			if (input == "exit")
				return 'H';
      break;

    default:
      if (input.substr(0,3) == "cd ")
        return 'F';
      if (input.substr(0,4) == "lcd ")
        return 'D';
      if (input.substr(0,4) == "get ")
        return 'G';
      break;
  }
    //If invalid command
    return '0';
}

void chitchat(const int socket)
//Used to recieve and print the terminal output from server after ls and pwd
{
  char msg[MAXDATA];
  //TODO: while loop to receive and print information recieved from the socket
  recv(socket, msg, MAXDATA, 0);
  cout << msg;
}

void getFile(const int sSocket, const std::string filename)
//Downloads requested file
{
  char *buffer = new char[MAXDATA];
  int ftpfd = 0;

  //Recv OK or OOPS
  recv(sSocket, buffer, MAXDATA, 0);
  //If OK
  if(!strcmp(buffer, "OK"))
  {
    //Open FTP socket
    if((ftpfd = FTPSocket()) < 0)
    {
      cout << "ERROR CREATING SOCKET FOR FTP\n";
      return;
    }

		//Get filesize and download
		recv(ftpfd, buffer, MAXDATA, 0);
		download(ftpfd, filename, atoi(buffer));

		//Close FTP socket
		close(ftpfd);
  }
	else
		cout << "SERVER ERROR - CANNOT OPEN FILE\n";
}

void download(const int fd, const string fname, const int fsize)
//Opens new buffer, downloads file
{
	//Open buffer and file
	char* buffer = new char[fsize+1];
	ofstream ofs(fname, ios::binary);
	//Get file info and close file
	recv(fd, buffer, fsize+2, 0);
	ofs.write(buffer, fsize);
	ofs.close();
	delete[] buffer;
}

int FTPSocket()
//Builds new socket, accepts connection from server and returns file descriptor
{
  int newsock = socket(AF_INET, SOCK_STREAM, 0);
  uint sinSize = 0;
  struct sockaddr_in addr;
  //Build address object

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(FTPORT);
  //Bind socket
  if((bind(newsock, (struct sockaddr*)&addr, sizeof(addr)) < 0))
    return -1;

  sinSize = sizeof(struct sockaddr_in);
  listen(newsock, 1);
  //Accept and return new connection
  return accept(newsock, (struct sockaddr*)&addr, &sinSize);
}
