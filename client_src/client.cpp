/*
    client program
*/
#include "client.hpp"

//Default port to connect to
int PORT = 8080;

int main(int argc, char const *argv[])
{
	if (argc != 3 && argc!=4)
	{
		cerr<<"Invalid number of arguments"<<endl;
		exit (-1);
	}
	if (argc==4){
		string fl = argv[3];
		freopen(fl.c_str(), "r", stdin);
	}
	int sock = 0, valread;
	string serv_ip = argv[1];
	PORT = atoi(argv[2]);
	struct sockaddr_in serv_addr;

	char buffer[1024] = {0};
	//Creating socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, serv_ip.c_str(), &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/Address not supported \n");
		return -1;
	}

	//Connect with the server
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	user usr;

	usr.sock = sock;

	if (argc==3)
	{
		usr.rd_from_file = 0;
	}
	else 
	{
		usr.rd_from_file = 1;
	}

	//Handles the requests and response for the client
	handle_user(usr);

	return 0;
}
