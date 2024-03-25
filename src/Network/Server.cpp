#include <iostream>
#include <thread>
#include "Server.h"

Server::Server() {
    tcp_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sockfd < 0) {
        perror("Error creating TCP socket");
        exit(EXIT_FAILURE);
    }

    udp_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sockfd < 0) {
        perror("Error creating UDP socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(TCP_PORT);

    server_addrU.sin_family = AF_INET;
    server_addrU.sin_addr.s_addr = INADDR_ANY;
    server_addrU.sin_port = htons(UDP_PORT);

    if (bind(tcp_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding TCP socket");
        exit(EXIT_FAILURE);
    }

    if (bind(udp_sockfd, (struct sockaddr*)&server_addrU, sizeof(server_addrU)) < 0) {
        perror("Error binding UDP socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started." << std::endl;
}

Server::~Server() {
    close(tcp_sockfd);
    close(udp_sockfd);
}

void Server::start() {
    listen(tcp_sockfd, MAX_PLAYERS);

    while (true) {
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(tcp_sockfd, (struct sockaddr*)&client_addr, &client_len);

        if (client_socket < 0) {
            perror("Error accepting connection");
            continue;
        }

        std::cout << "New connection accepted." << std::endl;

        std::thread client_thread(&Server::handleClient, this, client_socket);
        client_thread.detach(); // Detach the thread to allow it to run independently
    }
}

void Server::sendTCP(int desc, const std::string& message){
    ssize_t resS = send(desc, message.c_str(), message.length(), 0);

    if (resS == -1) {
        std::cerr << "Error while sending TCP" << std::endl;
    }
    if (resS == 0) {
        std::cerr << "sendTCP: Connection closed by peer" << std::endl;
    }
}

void Server::recvTCP(char resp[]){
    ssize_t resR = recv(tcp_sockfd, resp, sizeof(resp), 0);
    if (resR == -1) {
        std::cerr << "Error while receiving TCP" << std::endl;
    }
    if (resR == 0) {
        std::cerr << "recvTCP: Connection closed by peer" << std::endl;
    }
}

void Server::recvUDP(char resp[], int s){
    struct sockaddr_in adC;
    socklen_t cLen = sizeof(adC);
    ssize_t resR = recvfrom(udp_sockfd, resp, sizeof(resp), 0, (struct sockaddr*)&adC, &cLen);
    if (resR == -1) {
        std::cerr << "Error while receiveing UDP" << std::endl;
    }
    if (resR == 0) {
        std::cerr << "recvUDP: Connection closed by peer" << std::endl;
    }
    else{
        std::cout << "Receiving UDP done!" << std::endl;
        clients[s] = adC;
    }
}

void Server::sendUDP(const std::string& message, int s){
    ssize_t resS = sendto(udp_sockfd, message.c_str(), message.length(), 0, (struct sockaddr*)&clients[s], sizeof(clients[s]));
    if (resS == -1) {
        std::cerr << "Error while sending UDP" << std::endl;
    }
    if (resS == 0) {
        std::cerr << "sendUDP: Connection closed by peer" << std::endl;
    }
    else{
        std::cout << "Sending UDP done" << std::endl;
    }
}

void Server::handleClient(int client_socket) {
    char buffer[1024];
    int bytes_received;

    while (true) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received < 0) {
            perror("Error receiving message from client");
            break;
        } else if (bytes_received == 0) {
            std::cout << "Client disconnected." << std::endl;

            auto it = clients.find(client_socket);
            if (it != clients.end()) {
                clients.erase(it);
            }

            std::cout << "Number of clients in the map: " << clients.size() << std::endl;

            std::cout << "Current client sockets: ";
            for (const auto &pair: clients) {
                std::cout << pair.first << " ";
            }
            std::cout << std::endl;
            break;
        }

        std::cout << "Received from client TCP: " << buffer << std::endl;

        char port[5] = "3000";
        sendTCP(client_socket, port);

        char udp_buffer[1024];
        recvUDP(udp_buffer, client_socket);
        std::cout << "Received UDP from Client : " << udp_buffer << std::endl;

        sendUDP("Finish!", client_socket);
    }
}
int main() {
    Server server;
    server.start();

    return 0;
    }