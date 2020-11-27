#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

typedef struct sockets
{
    int cli_sock;
    int serv_sock;
}   sockets;

void* handle_client(void* arg);

#endif /* DEFINITIONS_HPP */