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

void sendFile(int &cSocket, const std::string file, struct sockaddr_in &clientAddr)
//Opens requested file and then sends file text through socket
{
  //Open file, send OK or OOPS depending on whether or not the file opens properly
  ifstream ifs(file, ifstream::binary);
  int ftpfd = 0;
  struct sockaddr_in addr;

  //If ok
  if(ifs)
  {
    send(cSocket, "OK", MAXDATA, 0);
    //Delay, then create new socket connected to client.
    sleep(1);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(FTPORT);
    addr.sin_addr = clientAddr.sin_addr;
    ftpfd = socket(AF_INET, SOCK_STREAM, 0);

    //If connection is successful, send file
    if(!connect(ftpfd, (struct sockaddr *)&addr, sizeof(addr)))
    {
        upload(ftpfd, file, ifs);
    }
    //Close socket to allow future connections
    close(ftpfd);
  }
  else
    send(cSocket, "OOPS", MAXDATA, 0);
}

void upload(const int fd, const string file, ifstream &ifs)
//Opens file, sends binary data over socket
{
  char *buffer = NULL;
  int len = 0;

  //Get and send file length
  ifs.seekg(0, ifs.end);
  len = ifs.tellg();
  send(fd, to_string(len).c_str(), MAXDATA, 0);

  //Rewind stream, read and send data
  ifs.seekg(0, ifs.beg);
  buffer = new char[len+1];
  ifs.read(buffer, len);
  buffer[len] = '\0'; //Append a null character to the end
  send(fd, buffer, len+1, 0);

  delete[] buffer;
  ifs.close();
}
