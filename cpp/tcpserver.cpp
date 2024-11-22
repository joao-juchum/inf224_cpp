/**
 * @file tcpserver.cpp
 * @brief Implementation of the TCPServer and SocketCnx classes for a TCP/IP INET Server.
 *
 * (c) Eric Lecolinet - Telecom ParisTech - 2016.
 * http://www.telecom-paristech.fr/~elc
 */

#include <csignal>
#include <iostream>
#include <thread>
#include "tcpserver.h"
using namespace std;

/**
 * @class SocketCnx
 * @brief Manages the connection with a given client using a separate thread.
 *
 * Each instance of SocketCnx handles communication with a client in its own thread.
 */
class SocketCnx {
public:
  /**
   * @brief Constructor for SocketCnx.
   * @param server Reference to the TCPServer instance.
   * @param socket Pointer to the connected Socket.
   */
  SocketCnx(TCPServer& server, Socket* socket);

  /**
   * @brief Destructor for SocketCnx.
   */
  ~SocketCnx();

  /**
   * @brief Processes incoming requests from the client.
   *
   * This function runs in an infinite loop, reading requests and sending responses.
   */
  void processRequests();

  TCPServer& server_;       ///< Reference to the TCPServer.
  Socket* sock_;            ///< Pointer to the client's Socket.
  SocketBuffer* sockbuf_;   ///< SocketBuffer for buffered communication.
  std::thread thread_;      ///< Thread handling the client's connection.
};

SocketCnx::SocketCnx(TCPServer& server, Socket* socket) :
server_(server),
sock_(socket),
sockbuf_(new SocketBuffer(sock_)),
thread_( std::thread([this]{processRequests();}) ) {
  thread_.detach();
}

SocketCnx::~SocketCnx() {
  sock_->close();
  delete sockbuf_;
  delete sock_;
}

/**
 * @brief Infinite loop that processes incoming requests on a client connection.
 *
 * Reads requests from the client, processes them using the server's callback,
 * and sends back responses. Handles errors and client disconnections.
 */
void SocketCnx::processRequests() {
  while (true) {
    std::string request, response;

    // Read the incoming request sent by the client
    // SocketBuffer::readLine() reads up to the first delimiter (which is removed)
    auto received = sockbuf_->readLine(request);

    if (received < 0) {
      server_.error("Read error");
      break;
    }

    if (received == 0) {
      server_.error("Connection closed by client");
      break;
    }

    // Processes the request
    if (!server_.callback_) {
      response = "OK";
    }
    // Closes the connection with this client if the callback returns false
    else if (!server_.callback_(request, response)) {
      server_.error("Closing connection with client");
      break;
    }

    // A response is always sent to the client (otherwise it might block)
    // writeLine() sends the response followed by a \n delimiter
    auto sent = sockbuf_->writeLine(response);

    if (sent < 0) {
      server_.error("Write error");
      break;
    }

    if (sent == 0) {
      server_.error("Connection closed by client");
      break;
    }
  }

  // Free resources and terminate thread
  delete this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
 * @brief Constructor for TCPServer.
 * @param callback The function to process client requests.
 */
TCPServer::TCPServer(Callback const& callback) :
callback_(callback) {
  // signal(SIGPIPE, SIG_IGN);  // Ignore SIGPIPE signals
}

TCPServer::~TCPServer() {}

/**
 * @brief Runs the TCP server on the specified port.
 * @param port The port number to bind the server to.
 * @return 0 on success, negative value on error.
 *
 * Starts the server loop, accepting client connections and creating a SocketCnx
 * for each client to handle communication.
 */
int TCPServer::run(int port) {
  int status = servsock_.bind(port);  // Bind the ServerSocket to this port

  if (status < 0) {
    error("Can't bind on port: " + to_string(port));
    return status;   // Returns negative value, see Socket::bind()
  }

  while (true) {
    if (auto* socket = servsock_.accept()) {
      // Launches the message reading for this socket in a thread
      new SocketCnx(*this, socket);
    }
    else error("Input connection failed");
  }
  return 0;  // Means OK
}

/**
 * @brief Logs an error message to standard error.
 * @param msg The error message to display.
 */
void TCPServer::error(const string& msg) {
  std::cerr << "TCPServer: " << msg << std::endl;
}
