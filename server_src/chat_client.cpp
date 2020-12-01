#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include "server.hpp"

#define LENGTH 2048
#define CHAT_PORT 9000

using namespace std;

volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[32];

void* send_msg_handler(void* arg) {
    User* chat_user = (User*)arg;

    char message[LENGTH] = {};
	char buffer[LENGTH + 32] = {};

    while(true) {
        string header;
        string data;
        recv_data(chat_user->cli_sock, header, data);

        strcpy(message, data.c_str());

        if (strcmp(message, "exit") == 0) {
            break;
        } 
        else {
            sprintf(buffer, "%s: %s\n", name, message);
            send(sockfd, buffer, strlen(buffer), 0);
        }

        bzero(message, LENGTH);
        bzero(buffer, LENGTH + 32);
    }
    flag = 1;
}

void* recv_msg_handler(void* arg) {
    User* chat_user = (User*)arg;

	char message[LENGTH] = {};
    while (true) {
        int receive = recv(sockfd, message, LENGTH, 0);
        if (receive > 0) {
            send_data(chat_user->cli_sock, true, message);
        } 
        else if (receive == 0) {
            break;
        } 
        else {
                // -1
        }
        memset(message, 0, sizeof(message));
    }
}

void* chat_client(void* arg){

    User* chat_user = (User*)arg;

    char *ip = "127.0.0.1";
	int port = CHAT_PORT;

    strcpy(name, chat_user->name.c_str());

    struct sockaddr_in server_addr;

	/* Socket settings */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    // Connect to Server
    int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err == -1) {
		printf("ERROR: connect\n");
		return NULL;
	}

    // Send name
	send(sockfd, name, 32, 0);

    send_data(chat_user->cli_sock, true, "\nWelcome to live session\n");

    pthread_t send_msg_thread;
    if(pthread_create(&send_msg_thread, NULL, send_msg_handler, chat_user) != 0){
		printf("ERROR: pthread\n");
        return NULL;
	}

	pthread_t recv_msg_thread;
    if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, chat_user) != 0){
		printf("ERROR: pthread\n");
		return NULL;
	}

	while (true){
		if(flag){
			break;
        }
	}

	close(sockfd);

	return NULL;
}