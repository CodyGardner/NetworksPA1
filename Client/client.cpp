#include "cfuncs.h"

#define PORT 5280
#define MAXDATA 250 //Most data that can be sent at once

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
//	int newfd = socket(AF_INET, SOCK_STREAM, 0);
//	int bytes = 0;
	struct hostent *he = gethostbyname(argv[1]);
	struct sockaddr_in addr;
	char* buff = NULL;
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
		//return 1;
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
				cout << "Selected ls or pwd";
				//send(sockfd, input.c_str(), MAXDATA, 0);
				//prepare to recieve response
				break;
			case 'F'://cd
				cout << "Selected cd";
				//send command
				//send(sockfd, input.c_str(), MAXDATA, 0);
				break;
			case 'G'://get
				cout << "Selected get";
				//send command, branch into subprogram to download file
				//send(sockfd, input.c_str(), MAXDATA, 0);
				break;
			case 'H'://bye
				cout << "Goodbye";
				//send(sockfd, input.c_str(), MAXDATA, 0);
				//TODO
				//wait for server to close socket
				//return
				break;
			default:
				cout << "Error, command not found.  Try \"help\"";
		}
/*
		recv(sockfd, buff, 20, 0);
		cout << buff << endl;
		send(sockfd, buff, 20, 0);
*/
	}


//	system("pwd");
//	chdir("..");
//	system("pwd");

	cout << endl << endl;

	return 0;
}
