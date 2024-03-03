#ifndef PLAY_TOGETHER_UDPSERVER_H
#define PLAY_TOGETHER_UDPSERVER_H

#include <map>
#include <mutex>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <ranges>
#include <algorithm>
#include <cstring>

#include "../Utils/UDPError.h"

/**
 * @brief The UDPServer class provides functionality to create and manage a UDP server.
 */
class UDPServer {
public:
    /**
     * @brief Constructs a UDPServer object.
     */
    UDPServer();

    /**
     * @brief Destroys the UDPServer object and shuts down the server.
     */
    ~UDPServer();

    /**
     * @brief Returns the server socket file descriptor.
     * @return The server socket file descriptor.
     */
    [[nodiscard]] int getSocketFileDescriptor() const;

    /**
     * @brief Initializes the UDP server with the given port.
     * @param port The port number to listen on.
     * @return True if initialization is successful, false otherwise.
     */
    bool initialize(short port);

    /**
     * @brief Starts the UDP server to handle incoming messages.
     */
    void start();

    /**
     * @brief Sends a message to the specified client.
     * @param clientAddress The client address structure.
     * @param message The message to send.
     * @return True if the message is sent successfully, false otherwise.
     */
    bool send(const sockaddr_in& clientAddress, const std::string &message) const;

    /**
     * @brief Broadcasts a message to all connected clients.
     * @param message The message to broadcast.
     * @return True if the message is sent successfully to all clients, false otherwise.
     */
    bool broadcast(const std::string &message) const;

    /**
     * @brief Receives a message from a client.
     * @param clientAddress The client address structure.
     * @return The received message.
     */
    [[nodiscard]] std::string receive(sockaddr_in& clientAddress, int timeout) const;

    /**
     * @brief Shuts down the server.
     */
    void stop();

private:
    int socketFileDescriptor = -1; /**< The server socket file descriptor. */
    bool stopRequested = false; /**< Flag to indicate if the server should stop. */

    /**
     * @brief Waits for incoming messages.
     */
    void handleMessage();
};

#endif //PLAY_TOGETHER_UDPSERVER_H
