/**
 * @file tcpserver.h
 * @brief Declaration of the TCPServer class for a TCP/IP INET Server.
 *
 * Supports TCP/IP AF_INET IPv4 connections with multiple clients.
 * One thread is used per client to handle communication.
 *
 * (c) Eric Lecolinet - Telecom ParisTech - 2016.
 * http://www.telecom-paristech.fr/~elc
 */

#ifndef __tcpserver__
#define __tcpserver__

#include <memory>
#include <string>
#include <functional>
#include "ccsocket.h"

class TCPConnection;
class TCPLock;

/**
 * @class TCPServer
 * @brief TCP/IP IPv4 server class.
 *
 * The TCPServer class supports TCP/IP AF_INET IPv4 connections with multiple clients.
 * Each client connection is handled in its own thread.
 */
class TCPServer {
public:

  /**
   * @brief Type definition for the callback function.
   *
   * The callback is a function that processes client requests.
   * It takes the client's request as a `const std::string&` and returns the response as a `std::string&`.
   * The function should return `true` to keep the connection open or `false` to close it.
   */
  using Callback = std::function< bool(std::string const& request, std::string& response) >;

  /**
   * @brief Initializes the server with a callback function.
   *
   * The callback function will be called each time the server receives a request from a client.
   * - `request` contains the data sent by the client.
   * - `response` will be sent to the client as a response.
   *
   * The connection with the client is closed if the callback returns `false`.
   *
   * @param callback The function to process client requests.
   */
  TCPServer(Callback const& callback);

  /**
   * @brief Destructor for the TCPServer class.
   */
  virtual ~TCPServer();

  /**
   * @brief Starts the server.
   *
   * Binds an internal `ServerSocket` to `port` and then starts an infinite loop that processes connection
   * requests from clients.
   *
   * @param port The port number to bind the server to.
   * @return `0` on normal termination, or a negative value if the `ServerSocket` could not be bound
   *         (value is then one of `Socket::Errors`).
   */
  virtual int run(int port);

private:
  friend class TCPLock;
  friend class SocketCnx;

  TCPServer(TCPServer const&) = delete;
  TCPServer& operator=(TCPServer const&) = delete;

  /**
   * @brief Logs an error message.
   * @param msg The error message to display.
   */
  void error(std::string const& msg);

  ServerSocket servsock_; ///< Internal server socket used to accept client connections.
  Callback callback_{};   ///< Callback function to process client requests.
};

#endif // __tcpserver__
