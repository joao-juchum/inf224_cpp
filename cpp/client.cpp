/**
 * @file client.cpp
 * @brief C++ Client to communicate with a TCP server.
 *
 * Reads a request from the terminal, sends it to the server,
 * receives the response, and displays it on the terminal.
 * Note that the program blocks if the server does not respond.
 *
 * @author Eric Lecolinet - Telecom ParisTech - 2016/2020
 */

#include <iostream>
#include <string>
#include <algorithm>
#include "ccsocket.h"

static const std::string HOST = "127.0.0.1";
static const int PORT = 3331;

/**
 * @brief Main function.
 *
 * Establishes a connection to the server and enters a loop to send requests and receive responses.
 * Exits when the user inputs "quit".
 *
 * @return Exit status code.
 */
int main() {
  Socket sock;
  SocketBuffer sockbuf(sock);

  int status = sock.connect(HOST, PORT);

  if (status < 0) {
    switch (status) {
      case Socket::Failed:
        std::cerr << "Client: Couldn't reach host " << HOST << ":" << PORT << std::endl;
        return 1;
      case Socket::UnknownHost:
        std::cerr << "Client: Couldn't find host " << HOST << ":" << PORT << std::endl;
        return 1;
      default:
        std::cerr << "Client: Couldn't connect to host " << HOST << ":" << PORT << std::endl;
        return 1;
    }
  }

  std::cout << "Client connected to " << HOST << ":" << PORT << std::endl;

  while (std::cin) {
    std::cout << "Request: ";
    std::string request, response;

    std::getline(std::cin, request);
    if (request == "quit") return 0;

    // Sends the request to the server
    if (sockbuf.writeLine(request) < 0) {
        std::cerr << "Client: Couldn't send message" << std::endl;
        return 2;
    }

    // Reads the complete response until "<END>" is found
    response.clear();
    std::string line;
    while (true) {
        if (sockbuf.readLine(line) < 0) {
            std::cerr << "Client: Couldn't receive message" << std::endl;
            return 2;
        }
        response += line + '\n';  // Accumulates the line into the response
        if (response.find("<END>") != std::string::npos) {
            response.erase(response.find("<END>"));  // Removes the delimiter
            break;
        }
    }

    // Formats the response by replacing ';' with newline characters
    std::replace(response.begin(), response.end(), ';', '\n');
    std::cout << "Response:\n" << response << std::endl;
  }
}
