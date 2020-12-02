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
#include "client.hpp"

using namespace std;

volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[32];

void str_overwrite_stdout()
{
    printf("%s", "> ");
    fflush(stdout);
}

void str_trim_lf(char* arr, int length)
{
    int i;
    for (i = 0; i < length; i++) {
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

/*
Handles the send message thread
*/
void* send_msg_handler(void* arg) {

    char message[LENGTH] = {};
	char buffer[LENGTH + 32 + 32] = {};

    while(true) {
        str_overwrite_stdout();
        fgets(message, LENGTH, stdin);
        str_trim_lf(message, LENGTH);

        if (strcmp(message, "exit") == 0) {
            send(sockfd, message, strlen(message), 0);
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
    return NULL;
}

/*
Handles the receive message thread
*/
void* recv_msg_handler(void* arg) {
    
	char message[LENGTH] = {};
    while (true) {
        int receive = recv(sockfd, message, LENGTH, 0);
        if (receive > 0) {
            if(strcmp(message, "Chat ended") == 0){
                break;
            }
            printf("%s", message);
            str_overwrite_stdout();
        }
        else if (receive == 0) {
            break;
        }
        else {
                // -1
        }
        memset(message, 0, sizeof(message));
    }
    flag = 1;
    return NULL;
}

void* chat_client(void* arg){

    const char *ip = "127.0.0.1";
	int port = (*(int*)arg) + 8500;

    cout << "Enter username:   " << flush;
    cin >> name;

    struct sockaddr_in server_addr;

	/* Socket settings */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        cout<<"\nsocket failure\n";
    }
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

    cout << "\nWelcome to live session\n";

    pthread_t send_msg_thread;
    if(pthread_create(&send_msg_thread, NULL, send_msg_handler, NULL) != 0){
		printf("ERROR: pthread\n");
        return NULL;
	}

	pthread_t recv_msg_thread;
    if(pthread_create(&recv_msg_thread, NULL, recv_msg_handler, NULL) != 0){
		printf("ERROR: pthread\n");
		return NULL;
	}

	while (true){
		if(flag){
            pthread_cancel(send_msg_thread);
            pthread_cancel(recv_msg_thread);
			break;
        }
	}

	close(sockfd);

	return NULL;
}