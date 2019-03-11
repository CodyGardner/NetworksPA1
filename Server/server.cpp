#include "servfuncs.h"

using namespace std;

int main()
{
	int newfd = 0, sockfd = socket(AF_INET, SOCK_STREAM, 0), re_stdout = dup(STDOUT_FILENO);
	struct sockaddr_in myAddr;
	struct sockaddr_in theirAddr;
	uint sinSize = 0;
	pid_t cpid;
	char* resp = new char[100];
	string cmd, ans;

//Ensure it formed correctly
	if (sockfd < 0)
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
		newfd = accept(sockfd, (struct sockaddr*)&theirAddr, &sinSize);
		//Fork process
		if ((cpid = fork()) == 0)
		{
			//Inside new process, direct STDOUT to new socket and begin interracting with client
			close(sockfd);//Close parent socket
			dup2(newfd, STDOUT_FILENO);//Direct STDOUT to new socket
			while(true)
			{
				recv(newfd, resp, MAXDATA, 0);
				cmd = string(resp); //Make resp into string
				//Process command and return to input
				switch(parsecommand(cmd))
				{
					case 'A'://ls
						system("ls");
						break;
					case 'B'://pwd
						system("pwd");
						break;
					case 'C'://cd
						//create substring of pathname and change directory
						chdir(cmd.substr(3).c_str());
						break;
					case 'D'://get
						sendFile(newfd, cmd.substr(4), theirAddr);
						break;
					case 'E'://bye
						//close socket, end child process
						dup2(STDOUT_FILENO, re_stdout); //Redirect stdout back to terminal
						close(newfd);
						exit(0);
					default:
						cout << "Error, command not found.  Try \"help\"";
				}
			}
		}
		else
			close(newfd);//Close new socket being handled in child process and return to accepting
	}

	cout << endl;

	return 0;
}
