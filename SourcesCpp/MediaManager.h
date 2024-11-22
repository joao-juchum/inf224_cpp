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

        // Get mulmidia table
        const std::map<std::string, MultimidiaPtr>& getMediaTable() const {
            return mediaTable;
        }

        // Get group table
        const std::map<std::string, GroupPtr>& getGroupTable() const {
            return groupTable;
        }

        //Get multimedia objects
        MultimidiaPtr getMedia(const std::string& name) const {
            auto temp = mediaTable.find(name);
            if (temp != mediaTable.end()){
                return temp->second;
            } else {
                std::cout << "Media object " << name << " not found\n";
                return nullptr;
            }
        }

        //Get groups
        GroupPtr getGroup(const std::string& name) const {
            auto temp = groupTable.find(name);
            if (temp != groupTable.end()){
                return temp->second;
            } else {
                std::cout << "Group " << name << " not found\n";
                return nullptr;
            }
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

        // Método save
        void save(const std::string& filename) const {
            std::ofstream ofs(filename);
            if (!ofs) {
                std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << "\n";
                return;
            }
            for (const auto& mediaPair : mediaTable) {
                const auto& media = mediaPair.second;
                ofs << media->getClassName() << "\n";  // Salva o tipo do objeto
                ofs << mediaPair.first << "\n";        // Salva o nome do objeto
                media->save(ofs);                      // Chama o método save do objeto específico
            }
        }

        // Método load
        void load(const std::string& filename) {
            std::ifstream ifs(filename);
            if (!ifs) {
                std::cerr << "Erro ao abrir o arquivo para leitura: " << filename << "\n";
                return;
            }

            std::string className;
            while (std::getline(ifs, className)) {
                std::string name, filePath;
                std::getline(ifs, name);  // Lê o nome do objeto

                if (className == "Photo") {
                    double latitude, longitude;
                    std::getline(ifs, filePath);  // Lê o caminho do arquivo
                    ifs >> latitude >> longitude;
                    ifs.ignore();
                    createPhoto(name, filePath, latitude, longitude);
                } 
                else if (className == "Video") {
                    int duration;
                    std::getline(ifs, filePath);  // Lê o caminho do arquivo
                    ifs >> duration;
                    ifs.ignore();
                    createVideo(name, filePath, duration);
                } 
                else if (className == "Film") {
                    int duration, chapters;
                    std::getline(ifs, filePath);  // Lê o caminho do arquivo
                    ifs >> duration >> chapters;
                    int* chapterDurations = new int[chapters];
                    for (int i = 0; i < chapters; ++i) {
                        ifs >> chapterDurations[i];
                    }
                    ifs.ignore();
                    createFilm(name, filePath, duration, chapters, chapterDurations);
                    delete[] chapterDurations;
                }
            }
        }
};


#endif //MEDIA_MANAGER_H