#ifndef MEDIA_MANAGER_H
#define MEDIA_MANAGER_H

#include"Multimidia.h"
#include"Photo.h"
#include"Video.h"
#include"film.h"
#include"group.h"

#include<iostream>
#include <ostream>
#include<string>
#include<memory>
#include<map>

typedef std::shared_ptr<Multimidia> MultimidiaPtr; // Shared pointer to multimedia objects
typedef std::shared_ptr<Group> GroupPtr; // Shared pointer to groups of multimedia objects

class MediaManager{
    
    private:
        std::map<std::string, MultimidiaPtr> mediaTable; // Map to store multimedia objects
        std::map<std::string, GroupPtr> groupTable; // Map to store groups of multimedia objects

    public:

        //Create photos
        std::shared_ptr<Photo> createPhoto(std::string name, std::string filePath, double latitude, double longitude){
            auto photo = std::make_shared<Photo>(name, filePath, latitude, longitude);
            mediaTable[name] = photo;
            return photo;
        }
        //Create videos
        std::shared_ptr<Video> createVideo(std::string name, std::string filePath, int duration){
            auto video = std::make_shared<Video>(name, filePath, duration);
            mediaTable[name] = video;
            return video;
        }
        //Create Films
        std::shared_ptr<Film> createFilm(std::string name, std::string filePath, int duration, int chapters, const int* durations){
            auto film = std::make_shared<Film>(name, filePath, duration, chapters, durations);
            mediaTable[name] = film;
            return film;
        }
        //Create groups
        std::shared_ptr<Group> createGroup(std::string name){
            auto group = std::make_shared<Group>(name);
            groupTable[name] = group;
            return group;
        }

        //Display multimedia objects
        void displayMedia(const std::string& name) const {
            auto temp = mediaTable.find(name);
            if (temp != mediaTable.end()){
                 for (auto& groupPair : groupTable) {
                auto& group = groupPair.second;
                group->remove(temp->second);
            }
                temp->second->display(std::cout);
            } else {
                std::cout << "Media object " << name << " not found\n";
            }
        }

        //Display groups
        void displayGroup(const std::string& name) const {
            auto temp = groupTable.find(name);
            if (temp != groupTable.end()){
                temp->second->display(std::cout);
            } else {
                std::cout << "Group " << name << " not found\n";
            }
        }

        //Player multimedia objects
        void playMedia(const std::string& name) const {
            auto temp = mediaTable.find(name);
            if (temp != mediaTable.end()){
                temp->second->play();
            } else {
                std::cout << "Media object " << name << " not found\n";
            }
        }

        //Media remover
        void removeMedia(const std::string& name){
            auto temp = mediaTable.find(name);
            if(temp != mediaTable.end()){
                mediaTable.erase(temp);
                std::cout << "Media object " << name << " removed\n";
            } else {
                std::cout << "Media object " << name << " not found\n";
            }
        }

        //Group remover
        void removeGroup(const std::string& name){
            auto temp = groupTable.find(name);
            if(temp != groupTable.end()){
                groupTable.erase(temp);
                std::cout << "Group " << name << " removed\n";
            } else {
                std::cout << "Group " << name << " not found\n";
            }
        }
};


#endif //MEDIA_MANAGER_H