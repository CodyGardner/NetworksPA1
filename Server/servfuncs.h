#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <fstream>
#include <cstdio>

#define MYPORT 5280
#define BACKLOG 10
#define MAXDATA 1023
#define FTPORT 9001 //FTP traditionally uses port 20 for the data transfer

char parsecommand(const std::string input);//Evaluates user input to determine the appropriate response in main
void sendFile(int &socket, const std::string file, struct sockaddr_in &clientAddr);//Opens requested file and then sends file text through socket
void upload(const int fd, const std::string file, std::ifstream &ifs);//Opens file, sends binary data over socket
