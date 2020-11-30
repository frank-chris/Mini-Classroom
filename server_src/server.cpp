/*
    server program
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "server.hpp"

#define PORT 8080

using namespace std;

void* new_client_thread(void* arg){
    sockets* socks = (sockets*)arg;
    User* usr = (User*)malloc(sizeof(User));

	usr->cli_sock = socks->cli_sock;
	usr->active = true;

	cout<<"\nThread spawned\n";
	
    handle_client(usr);
}

int main(int argc, char const *argv[])
{
    initFS();

	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);	

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 8) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	cout<<"\nListening on "<<PORT<<"\n";

    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
		cout<<"\nClient: "<<new_socket<<" connected\n";
        pthread_t new_thread;
        sockets* socks = (sockets *)(malloc(sizeof(sockets)));
        socks->cli_sock = new_socket;
        socks->serv_sock = server_fd;

        pthread_create(&new_thread, NULL, &new_client_thread, socks);
    }
	
	return 0; 
}
