/*
    Created By: Cody Gardner
    Environment: Linux Mint 19.1
    This document is the main source code for an FTP client, an active project for my Graduate Networks class.
    This project is still in progress, but currently supports the following commands: cd (client and server), ls (client and server), pwd (client and server), bye, exit, and help
    Currently under development: get
*/

#include "cfuncs.h"

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *he = gethostbyname(argv[1]);
	struct sockaddr_in addr;
	char* buff = new char[MAXDATA];
	string input;

	if (sockfd < 0)
	{
		cout << "ERROR CREATING SOCKET\n";
		return 1;
	}

	//Build addr
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(addr.sin_zero), '\0', 8);

	cout << "SEARCHING FOR SERVER...\n";
	if ((connect(sockfd, (struct sockaddr *)&addr, sizeof(addr))) == 0)
		cout << "CONNECTED! WELCOME TO FTP-SHARE!\n\n";
	else
	{
		cout << "FAILED TO CONNECT\n";
		return 1;
	}

	while(true)
	{
		//Print prompt, get input
		//The extra garbage in the prompt sets text color to bold green and back again
		cout << "\n\033[1;32mFTP-SHARE>>\033[0m ";
		getline(cin, input);

		//Process command and return to input
		switch(parsecommand(input))
		{
			case 'A'://help
				help();
				break;
			case 'B'://lls
				system("ls");
				break;
			case 'C'://lpwd
				system("pwd");
				break;
			case 'D'://lcd
				//create substring of pathname and change directory
				chdir(input.substr(4).c_str());
				break;
			case 'E'://ls and pwd
				//Send command, recieve response
        send(sockfd, input.c_str(), MAXDATA, 0);
				chitchat(sockfd);
				break;
			case 'F'://cd
				//send command
				send(sockfd, input.c_str(), MAXDATA, 0);
				break;
			case 'G'://get
				//send command, branch into subprogram to download file
				send(sockfd, input.c_str(), MAXDATA, 0);
				getFile(sockfd, input.substr(4));
				break;
			case 'H'://bye and exit
				send(sockfd, input.c_str(), MAXDATA, 0); //Send command
				close(sockfd);
				return 0;
			default:
				cout << "Error, command not found.  Try \"help\"";
		}
	}

	cout << endl << endl;

	return 0;
}
