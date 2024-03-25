#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>

const int MAX_PLAYERS = 1;
const int TCP_PORT = 5001;
const int UDP_PORT = 5001;

class Server {
public:
    Server();
    ~Server();
    void start();
    void sendTCP(int desc, const std::string& message);
    void sendUDP(const std::string& message, int s);
    void recvTCP(char resp[]);
    void recvUDP(char resp[], int s);
private:
    int tcp_sockfd;
    int udp_sockfd;

    std::map<int, struct sockaddr_in> clients;
    struct sockaddr_in server_addr;
    struct sockaddr_in server_addrU;
    struct sockaddr_in client_addr;
    void handleClient(int client_socket);
/*
    void sendTCP(const std::string& message);
    void sendUDP(const std::string& message);
    void recvTCP(char resp[]);
    void recvUDP(char resp[]);*/
};

#endif // SERVER_H
