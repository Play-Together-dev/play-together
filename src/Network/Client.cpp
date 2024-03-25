//
// Created by Anaïs Mackow on 01/03/2024.
//

#include "Client.h"

#include <iostream>
#include <string>
#include <arpa/inet.h>

#include <iostream>
#include <string>
#include "Client.h"

Client::Client(const std::string& server_ip, int s_port, int s_portu) {

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
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
    server_addr.sin_port = htons(s_port);

    server_addrU.sin_family = AF_INET;
    server_addrU.sin_addr.s_addr = inet_addr(server_ip.c_str());
    server_addrU.sin_port = htons(s_portu);


    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY; // Bind to any local interface
    client_addr.sin_port = htons(0); // Let the OS choose a free port

    if (bind(udp_sockfd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        perror("Error binding UDP socket");
        exit(EXIT_FAILURE);
    }

    if (connect(tcp_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
}


Client::~Client() {
    close(tcp_sockfd);
    close(udp_sockfd);
}

void Client::sendTCP(const std::string& message){
    ssize_t resS = send(tcp_sockfd, message.c_str(), message.length(), 0);

    if (resS == -1) {
        std::cerr << "Error while sending TCP" << std::endl;
    }
    if (resS == 0) {
        std::cerr << "sendTCP: Connection closed by peer" << std::endl;
    }

}

void Client::recvTCP(char resp[]){
    ssize_t resR = recv(tcp_sockfd, resp, sizeof(resp), 0);
    if (resR == -1) {
        std::cerr << "Error while receiving TCP" << std::endl;
    }
    if (resR == 0) {
        std::cerr << "recvTCP: Connection closed by peer" << std::endl;
    }

}

void Client::recvUDP(char resp[]){
    socklen_t sLen;
    ssize_t resR = recvfrom(udp_sockfd, resp, 1024, 0, (struct sockaddr*)&server_addrU, &sLen);
    if (resR == -1) {
        std::cerr << "Error while receiveing UDP" << std::endl;
    }
    if (resR == 0) {
        std::cerr << "recvUDP: Connection closed by peer" << std::endl;
    }
    else{
        std::cout << "Receiving done" << std::endl;
    }
}

void Client::sendUDP(const std::string& message){
    ssize_t resS = sendto(udp_sockfd, message.c_str(), message.length(), 0, (struct sockaddr*)&server_addrU, sizeof(server_addr));
    if (resS == -1) {
        std::cerr << "Error while sending UDP" << std::endl;
    }
    if (resS == 0) {
        std::cerr << "sendUDP: Connection closed by peer" << std::endl;
    }
    else{
        std::cout << "Sending done" << std::endl;
    }
}

void Client::input(){
    char *mess;
    fgets(mess, 10, stdin);
}

int main(int argc, char *argv[]) {

    std::string server_ip;
    int s_port, s_portu;
    std::cout << "Enter server IP address : ";
    std::cin >> server_ip;
    std::cout << "Enter server TCP port : ";
    std::cin >> s_port;
    std::cout << "Enter server UDP port : ";
    std::cin >> s_portu;
    Client client(server_ip, s_port, s_portu);

    std::string message;


        /*std::cout << "Enter message to send (press Enter to send, type 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }*/

    client.sendTCP("GOODBYE");

    char buf[5];
    buf[5] = '\0';

    client.recvTCP(buf);
    std::cout << "Received from Server TCP : " << buf << std::endl;
/*
    std::cout << "Enter UDP message to send: ";
    std::getline(std::cin, message);*/

    client.sendUDP("Is it finish yet");

    char bufU[100];
    client.recvUDP(bufU);
    std::cout << "Received from Server UDP : " << bufU << std::endl;

    std::string userInput;
    std::cout << "Enter something: ";
    std::cin.ignore(); // Ignorer le saut de ligne restant dans le buffer
    std::getline(std::cin, userInput);
    std::cout << "You entered: " << userInput << std::endl;


    return 0;
}