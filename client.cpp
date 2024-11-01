//
// Client C++ pour communiquer avec un serveur TCP
// eric lecolinet - telecom paristech - 2016/2020
//

#include <iostream>
#include <string>
#include <algorithm>
#include "ccsocket.h"

static const std::string HOST = "127.0.0.1";
static const int PORT = 3331;

///
/// Lit une requete depuis le Terminal, envoie cette requete au serveur,
/// recupere sa reponse et l'affiche sur le Terminal.
/// Noter que le programme bloque si le serveur ne repond pas.
///

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
        std::cerr << "Client: Couldn't connect host " << HOST << ":" << PORT << std::endl;
        return 1;
    }
  }

  std::cout << "Client connected to " << HOST << ":" << PORT << std::endl;

  while (std::cin) {
    std::cout << "Request: ";
    std::string request, response;

    std::getline(std::cin, request);
    if (request == "quit") return 0;

    // Envia a requisição ao servidor
    if (sockbuf.writeLine(request) < 0) {
        std::cerr << "Client: Couldn't send message" << std::endl;
        return 2;
    }

    // Lê a resposta completa até encontrar "<END>"
    response.clear();
    std::string line;
    while (true) {
        if (sockbuf.readLine(line) < 0) {
            std::cerr << "Client: Couldn't receive message" << std::endl;
            return 2;
        }
        response += line + '\n';  // Acumula a linha na resposta
        if (response.find("<END>") != std::string::npos) {
            response.erase(response.find("<END>"));  // Remove o delimitador
            break;
        }
    }

    std::replace(response.begin(), response.end(), ';', '\n');  // Formatação da resposta
    std::cout << "Response:\n" << response << std::endl;
}
}
