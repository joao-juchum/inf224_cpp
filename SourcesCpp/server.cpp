#include <string>
#include <iostream>
#include <sstream>
#include "MediaManager.h"
#include "tcpserver.h"


const int PORT = 3331;


int main(int argc, char* argv[])
{
  MediaManager manager;

  // Creating some multimedia objects and add them to the manager
  auto photo1 = manager.createPhoto("banana", "../images_inf224/banana.jpeg", 48.8584, 2.2945);
  auto photo2 = manager.createPhoto("cat", "../images_inf224/cat.jpeg", 40.6892, 74.0445);
  auto photo3 = manager.createPhoto("Miniom", "../images_inf224/Miniom.jpeg", 40.6892, 74.0445);
  auto video1 = manager.createVideo("video1", "../videos_inf224/Video_cat_1.mp4", 120);
  auto video2 = manager.createVideo("video2", "../videos_inf224/Video_cat_2.mp4", 60);
  auto film = manager.createFilm("film1", "../videos_inf224/Video_cat_3.mp4", 150, 3, new int[3]{10, 20, 30});

  // Creating a group and adding the multimedia objects to it
  auto mediaGroup = manager.createGroup("Media Group");
  mediaGroup->push_back(photo1);
  mediaGroup->push_back(photo2);
  mediaGroup->push_back(photo3);
  mediaGroup->push_back(video1);
  mediaGroup->push_back(video2);
  mediaGroup->push_back(film);

  // Create a server
  auto* server =
  new TCPServer( [&](std::string const& request, std::string& response)->bool {
    
    // If the request is empty, return a welcome message
    if (request.empty()) {
        response = "Use 'help' to see available commands. <END>";
        return true;
    }

    std::stringstream ss(request);  // make a stream from the request string
    std::string command, name; // command and name extracted from the request
    ss >> command >> name; // extract command and name from the request

    // Search for a media object
    if (command == "search") {
      std::ostringstream os; 
      auto media = manager.getMedia(name); // get the media object
      if(media) {
        media->display(os);
        response = os.str() + "<END>";
      } else {
        response = "Media object " + name + " not found <END>";
      }
    } 
    
    // Play a media object
    else if (command == "play"){
      auto media = manager.getMedia(name); // get the media object
      if(media) {
        media->play();
        response = "Playing: " + name + "<END>";
      } else {
        response = "Media object " + name + " not found <END>";
      }
    }

    // List all media objects
    else if (command == "listMedia") {
      std::ostringstream os;
      for (auto& m: manager.getMediaTable()) {
        m.second->display(os);
      }
      response = os.str() + "<END>";
    }

    // List all groups
    else if (command == "listGroups") {
      std::ostringstream os;
      for (auto& g: manager.getGroupTable()) {
        g.second->display(os);
      }
      response = os.str() + "<END>";
    }

    // List all 
    else if (command == "list") {
      std::ostringstream os;
      for (auto& m: manager.getMediaTable()) {
        m.second->display(os);
      }
      for (auto& g: manager.getGroupTable()) {
        g.second->display(os);
      }
      response = os.str() + "<END>";
    }
    
    // List all
    else if (command == "help") {
    std::ostringstream os;
    os << "\nAvailable commands:\n";
    os << "\t- search <name> - Search for a media object by name and display its attributes.\n";
    os << "\t- play <name> - Play a media object by name.\n";
    os << "\t- listMedia - List all media objects.\n";
    os << "\t- listGroups - List all media groups.\n";
    os << "\t- list - List all media objects and groups.\n";
    os << "\t- help - Show this help message.\n";
    response = os.str() + "<END>";
  }

    else {
      response = "Unknown command: " + command + "<END>";
    }

    // return false would close the connecytion with the client
    return true;
  });


  // lance la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // error
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}