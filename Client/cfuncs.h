#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <fstream>

#define PORT 5280
#define MAXDATA 1023 //Most data that can be sent at once

//Functions
void help();//Prints the help options
char parsecommand(const std::string input);//Evaluates user input to determine the appropriate response in main
void chitchat(const int socket);//Used to recieve and print the terminal output from server after ls and pwd
void getFile(const int socket, const std::string filename);//Opens socket, waits for connection from server, downloads file
int FTPSocket();//Builds new socket, accepts connection from server and returns file descriptor
void download(const int fd, const std::string fname, const int fsize);//Opens new buffer, downloads file
