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
#include"server.hpp"
#include <cstdlib>


void Server::sendToClient(int fd, const std::string& message) {
    send(fd, message.c_str(), message.size(), 0);
}



void Server::parseClientInput(int fd, const std::string& data) {
    std::istringstream stream(data);  // Create an input string stream from the data string
    std::string line;
    while (std::getline(stream, line)) {  // Read each line from the stream
        std::istringstream linestream(line);  // Create an input string stream from the line
        std::string command;
        linestream >> command;  // Read the command from the line
    if(command=="quit")
    {
        std::cout  <<RED<< "Client <" << fd << "> Disconnected" << std::endl;
		close(fd);
    }
        for (size_t i = 0; i < clients.size(); ++i) {
             Client& client = clients[i];
            if (client.getFd() == fd) {
                if (command == "CAP")
                {
                    std::string passe = colorCode("Please enter your password:\r\n",3);
                    send(fd, passe.c_str(), passe.size(), 0);
                }
                if (!client.hasPasswordReceived() && command == "PASS" && count ==0) {
                    std::string passe;
                    linestream >> passe;  // Read the password
                    if(passe!=pass)
                    {
                        std::string pass_err=colorCode(ERR_PASSWDMISMATCH(),5);
                        std::string passe = colorCode("Please enter your password \r\n",3);
                        send(fd,pass_err.c_str(),pass_err.size(),0);
                        send(fd, passe.c_str(), passe.size(), 0);
                        continue;
                    }
                        client.setPassword(passe);
                    std::cout<<"my password"<<passe<<std::endl;
                    count =1;

                    // Prompt for nickname after receiving password
                    std::string nicknamePrompt = colorCode("Please enter your nickname:\r\n",3);
                    send(fd, nicknamePrompt.c_str(), nicknamePrompt.size(), 0);
                } else if (client.hasPasswordReceived() && !client.hasNicknameReceived() && command == "NICK"&&count ==1) {
                    std::string nick;
                    linestream >> nick;  // Read the nickname
                    if(!prsNickname(nick,fd))
                        continue;
                    client.setNickname(nick);
                    std::cout<<"my nick : "<<nick<<std::endl;

                    // Prompt for username after receiving nickname
                    std::string usernamePrompt = colorCode("Please enter your username:\r\n",3);
                    send(fd, usernamePrompt.c_str(), usernamePrompt.size(), 0);
                    count=2;
                } else if (client.hasPasswordReceived() && client.hasNicknameReceived() && !client.hasUsernameReceived() && command == "USER"&&count ==2) {
                    std::string user, mode, unused, realname;
             
                    client.setUsername(user);
                    std::cout<<"my User : "<<user<<std::endl;

                    // Client setup is complete, you can now proceed with further handling
                    std::string welcomeMessage =colorCode(":myserver 001 " + client.getNickname()  + " :Welcome to the IRC server\r\n",6);
                    std::string yourHostMsg = colorCode(":myserver 002 " + client.getNickname() + " :Your host is myserver\r\n",6);
                    std::string createdMsg = colorCode(":myserver 003 " + client.getNickname()+ " :This server was created just now\r\n",6);
                     std::string myInfoMsg = colorCode(":myserver 004 " + client.getNickname()+ " myserver v1.0 i\r\n",6);
  
                    send(fd, welcomeMessage.c_str(), welcomeMessage.size(), 0);
                    send(fd, yourHostMsg.c_str(), yourHostMsg.size(), 0);
                    send(fd, createdMsg.c_str(), createdMsg.size(), 0);
                    send(fd, myInfoMsg.c_str(), myInfoMsg.size(), 0);
                }
                }
                break;
            }
        }}