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

char parsecommand(const std::string input);//Evaluates user input to determine the appropriate response in main
void sendFile(int &socket, std::string &file);//Opens requested file and then sends file text through socket
