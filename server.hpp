#ifndef SERVER_HPP
#define SERVER_HPP
#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color
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
#include <cstdlib>
#include"headrs_irc.hpp"


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
    bool prsNickname(std::string nickname,int fd);
    bool validateNickname(std::string nickname);
    std::string colorCode(const std::string& message, int color);
};

#endif