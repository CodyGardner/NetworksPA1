#include "servfuncs.h"

#define MYPORT 5280
#define BACKLOG 10
#define MAXDATA 250

using namespace std;

int main()
{
	int newfd = 0, sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in myAddr;
	struct sockaddr_in theirAddr;
	uint sinSize = 0;
	pid_t cpid;
	char* hello = "Whassaaaap???!!";
	char* resp = new char[20];
	string cmd, ans;

//Create socket fd
	newfd = socket(AF_INET, SOCK_STREAM, 0);

//Ensure it formed correctly
	if (newfd < 0)
	{
		cout << "ERROR ESTABLISHING SOCKET\n\n";
		return 1;
	}

	cout << "SERVER SOCKET CREATED\n\n";

//Build myAddr object
	myAddr.sin_family = AF_INET;
	myAddr.sin_addr.s_addr = INADDR_ANY;
	myAddr.sin_port = htons(MYPORT);

//Bind socket
	if ((bind(sockfd, (struct sockaddr*)&myAddr, sizeof(myAddr)) < 0))
	{
		cout << "ERROR BINDING SOCKET\n\n";
		return 1;
	}

	sinSize = sizeof(struct sockaddr_in);

//Start listening on socket
	listen(sockfd, BACKLOG);

	while(true)
	{
		//Accept new connections
		newfd = accept(sockfd, (struct sockaddr*)&myAddr, &sinSize);
		//Fork process
		if ((cpid = fork()) == 0)
		{
			while(true)
			{
				recv(newfd, resp, MAXDATA, 0);
				cmd = string(resp); //Make resp into string

				//Process command and return to input
				switch(parsecommand(cmd))
				{
					case 'B'://ls
						system("ls");
						break;
					case 'C'://pwd
						system("pwd");
						break;
					case 'D'://cd
						//create substring of pathname and change directory
						chdir(cmd.substr(3).c_str());
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
			}
		}
	}

	cout << endl;

	return 0;
}
