#ifndef SERVER_HPP
#define SERVER_HPP

typedef struct sockets
{
    int cli_sock;
    int serv_sock;
}   sockets;

void* handle_client(void* arg);

#endif /* SERVER_HPP */