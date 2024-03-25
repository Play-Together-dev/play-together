#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client {
public:
    Client(const std::string& server_ip, int s_port, int s_portu);
    ~Client();
    void sendTCP(const std::string& message);
    void sendUDP(const std::string& message);
    void recvTCP(char resp[]);
    void recvUDP(char resp[]);
    void input();

private:
    int tcp_sockfd;
    int udp_sockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in server_addrU;
    struct sockaddr_in client_addr;
};

#endif // CLIENT_H
