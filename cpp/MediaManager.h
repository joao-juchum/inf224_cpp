/**
 * @file MediaManager.h
 * @brief Declaration of the MediaManager class.
 */

#ifndef MEDIA_MANAGER_H
#define MEDIA_MANAGER_H

#include "Multimidia.h"
#include "Photo.h"
#include "Video.h"
#include "film.h"
#include "group.h"

#include <iostream>
#include <ostream>
#include <string>
#include <memory>
#include <map>

/**
 * @typedef MultimidiaPtr
 * @brief Shared pointer to multimedia objects.
 */
typedef std::shared_ptr<Multimidia> MultimidiaPtr; // Shared pointer to multimedia objects

/**
 * @typedef GroupPtr
 * @brief Shared pointer to groups of multimedia objects.
 */
typedef std::shared_ptr<Group> GroupPtr; // Shared pointer to groups of multimedia objects

/**
 * @class MediaManager
 * @brief Manages multimedia objects and groups.
 *
 * The MediaManager class provides functionalities to create, retrieve, display, play,
 * and remove multimedia objects and groups. It also allows saving and loading media data.
 */
class MediaManager {

private:
    std::map<std::string, MultimidiaPtr> mediaTable; ///< Map to store multimedia objects
    std::map<std::string, GroupPtr> groupTable;      ///< Map to store groups of multimedia objects

public:

    /**
     * @brief Creates a Photo object and adds it to the media table.
     * @param name Name of the photo.
     * @param filePath File path of the photo.
     * @param latitude Latitude coordinate.
     * @param longitude Longitude coordinate.
     * @return A shared pointer to the created Photo object.
     */
    std::shared_ptr<Photo> createPhoto(std::string name, std::string filePath, double latitude, double longitude){
        auto photo = std::make_shared<Photo>(name, filePath, latitude, longitude);
        mediaTable[name] = photo;
        return photo;
    }

    /**
     * @brief Creates a Video object and adds it to the media table.
     * @param name Name of the video.
     * @param filePath File path of the video.
     * @param duration Duration of the video in seconds.
     * @return A shared pointer to the created Video object.
     */
    std::shared_ptr<Video> createVideo(std::string name, std::string filePath, int duration){
        auto video = std::make_shared<Video>(name, filePath, duration);
        mediaTable[name] = video;
        return video;
    }

    /**
     * @brief Creates a Film object and adds it to the media table.
     * @param name Name of the film.
     * @param filePath File path of the film.
     * @param duration Duration of the film in seconds.
     * @param chapters Number of chapters in the film.
     * @param durations Array of durations for each chapter.
     * @return A shared pointer to the created Film object.
     */
    std::shared_ptr<Film> createFilm(std::string name, std::string filePath, int duration, int chapters, const int* durations){
        auto film = std::make_shared<Film>(name, filePath, duration, chapters, durations);
        mediaTable[name] = film;
        return film;
    }

    /**
     * @brief Creates a Group object and adds it to the group table.
     * @param name Name of the group.
     * @return A shared pointer to the created Group object.
     */
    std::shared_ptr<Group> createGroup(std::string name){
        auto group = std::make_shared<Group>(name);
        groupTable[name] = group;
        return group;
    }

    /**
     * @brief Gets the media table.
     * @return A constant reference to the map of multimedia objects.
     */
    const std::map<std::string, MultimidiaPtr>& getMediaTable() const {
        return mediaTable;
    }

    /**
     * @brief Gets the group table.
     * @return A constant reference to the map of groups.
     */
    const std::map<std::string, GroupPtr>& getGroupTable() const {
        return groupTable;
    }

    /**
     * @brief Retrieves a multimedia object by name.
     * @param name The name of the multimedia object.
     * @return A shared pointer to the multimedia object, or nullptr if not found.
     */
    MultimidiaPtr getMedia(const std::string& name) const {
        auto temp = mediaTable.find(name);
        if (temp != mediaTable.end()){
            return temp->second;
        } else {
            std::cout << "Media object " << name << " not found\n";
            return nullptr;
        }
    }

    /**
     * @brief Retrieves a group by name.
     * @param name The name of the group.
     * @return A shared pointer to the group, or nullptr if not found.
     */
    GroupPtr getGroup(const std::string& name) const {
        auto temp = groupTable.find(name);
        if (temp != groupTable.end()){
            return temp->second;
        } else {
            std::cout << "Group " << name << " not found\n";
            return nullptr;
        }
    }

    /**
     * @brief Displays information about a multimedia object.
     * @param name The name of the multimedia object.
     */
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

    /**
     * @brief Displays information about a group.
     * @param name The name of the group.
     */
    void displayGroup(const std::string& name) const {
        auto temp = groupTable.find(name);
        if (temp != groupTable.end()){
            temp->second->display(std::cout);
        } else {
            std::cout << "Group " << name << " not found\n";
        }
    }

    /**
     * @brief Plays a multimedia object.
     * @param name The name of the multimedia object.
     */
    void playMedia(const std::string& name) const {
        auto temp = mediaTable.find(name);
        if (temp != mediaTable.end()){
            temp->second->play();
        } else {
            std::cout << "Media object " << name << " not found\n";
        }
    }

    /**
     * @brief Removes a multimedia object from the media table.
     * @param name The name of the multimedia object to remove.
     */
    void removeMedia(const std::string& name){
        auto temp = mediaTable.find(name);
        if(temp != mediaTable.end()){
            mediaTable.erase(temp);
            std::cout << "Media object " << name << " removed\n";
        } else {
            std::cout << "Media object " << name << " not found\n";
        }
    }

    /**
     * @brief Removes a group from the group table.
     * @param name The name of the group to remove.
     */
    void removeGroup(const std::string& name){
        auto temp = groupTable.find(name);
        if(temp != groupTable.end()){
            groupTable.erase(temp);
            std::cout << "Group " << name << " removed\n";
        } else {
            std::cout << "Group " << name << " not found\n";
        }
    }

    /**
     * @brief Saves the media data to a file.
     * @param filename The name of the file to save to.
     */
    void save(const std::string& filename) const {
        std::ofstream ofs(filename);
        if (!ofs) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }
        for (const auto& mediaPair : mediaTable) {
            const auto& media = mediaPair.second;
            ofs << media->getClassName() << "\n";  // Saves the object's type
            ofs << mediaPair.first << "\n";        // Saves the object's name
            media->save(ofs);                      // Calls the save method of the specific object
        }
    }

    /**
     * @brief Loads media data from a file.
     * @param filename The name of the file to load from.
     */
    void load(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }

        std::string className;
        while (std::getline(ifs, className)) {
            std::string name, filePath;
            std::getline(ifs, name);  // Reads the object's name

            if (className == "Photo") {
                double latitude, longitude;
                std::getline(ifs, filePath);  // Reads the file path
                ifs >> latitude >> longitude;
                ifs.ignore();
                createPhoto(name, filePath, latitude, longitude);
            }
            else if (className == "Video") {
                int duration;
                std::getline(ifs, filePath);  // Reads the file path
                ifs >> duration;
                ifs.ignore();
                createVideo(name, filePath, duration);
            }
            else if (className == "Film") {
                int duration, chapters;
                std::getline(ifs, filePath);  // Reads the file path
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

#endif // MEDIA_MANAGER_H
