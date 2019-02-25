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

//Functions
void help();//Prints the help options
char parsecommand(const std::string input);//Evaluates user input to determine the appropriate response in main
void chitchat(int &socket);//Used to recieve and print the terminal output from server after ls and pwd
