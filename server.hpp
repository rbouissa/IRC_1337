#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <cstring>//for memset
#include<sstream>
#include"client.hpp"


class Server{

    private:
    std::vector<Client> clients;
    
    
    int fd_Server;
    //static bool signal;
    std::vector<struct pollfd>fds;
    public:
    int port;
    int count;
    std::string pass;
        Server(){
            fd_Server = -1;
            count = 0;
        }
    int be_ready_for_connection();
    void AcceptNewConnetinClient();
    void ReceiveNewData(int fd);
    void ClearClients(int fd);
    void sendToClient(int fd, const std::string& message);
    void parseClientInput(int fd, const std::string& data);
};
#endif