/**
 * @file main.cpp
 * @brief Main program to test multimedia functionalities.
 *
 * This program demonstrates the use of multimedia classes such as Photo, Video, Film, Group,
 * and MediaManager. It includes functions to test individual classes and their interactions.
 *
 * Created on 30/06/2024
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Multimidia.h"
#include "Photo.h"
#include "Video.h"
#include "film.h"
#include "group.h"
#include "MediaManager.h"

using namespace std;

/** @brief Tests Photo and Video classes. */
void testPhotoVideo();

/** @brief Tests the Film class. */
void testFilm();

/** @brief Tests the Group class. */
void testGroup();

/** @brief Tests the MediaManager class with basic operations. */
void testMediaManager();

/** @brief Tests the MediaManager class with save and load functionalities. */
void testMediaManager2();

/**
 * @brief Main function.
 *
 * Executes one of the test functions to demonstrate the multimedia functionalities.
 * Uncomment the desired test function to run.
 *
 * @return Exit status code.
 */
int main()
{
    std::cout << "Hello brave new world" << std::endl;
    //testPhotoVideo();
    //testFilm();
    //testGroup();
    testMediaManager();
    //testMediaManager2();

    return 0;
}

void testPhotoVideo(){
    // Create some multimedia objects
    Photo p1("banana", "./images_inf224/banana.jpeg", 48.8584, 2.2945);
    Photo p2("cat", "./images_inf224/cat.jpeg", 40.6892, 74.0445);
    Photo p3("Miniom", "./images_inf224/Miniom.jpeg", 40.6892, 74.0445);
    Video v1("video1", "./videos_inf224/Video_cat_1.mp4", 120);
    Video v2("video2", "./videos_inf224/Video_cat_2.mp4", 60);
    Video v3("video3", "./videos_inf224/Video_cat_3.mp4", 90);

    // Demonstrating polymorphism
    std::vector<Multimidia*> mediaList;
    mediaList.push_back(&p1);
    mediaList.push_back(&p2);
    mediaList.push_back(&p3);
    mediaList.push_back(&v1);
    mediaList.push_back(&v2);
    mediaList.push_back(&v3);

    // Display the multimedia objects
    std::cout << "Displaying: \n";
    for (const auto& media : mediaList) {
        std::cout << "\t ---";
        media->display(std::cout);
        std::cout << "\n";
    }

    // Play the multimedia objects
    std::cout << "Playing: \n";
    for (const auto& media : mediaList) {
        media->play();
    }
}

void testFilm() {
    // Array of chapter durations
    int durations1[] = {10, 20, 30};
    int durations2[] = {15, 25, 35, 45};

    // Creating a Film object
    Film film1("Film1", "./videos_inf224/Video_cat_3.mp4", 90, 3, durations1);
    std::cout << "Film1 details:\n";
    film1.display(std::cout);

    // Modifying the array of durations
    film1.setChapterDurations(4, durations2);
    std::cout << "\nFilm1 details after modification:\n";
    film1.display(std::cout);

    // Testing the copy constructor
    Film film2 = film1;
    std::cout << "\nFilm2 (copy of Film1) details:\n";
    film2.display(std::cout);

    // Testing the assignment operator
    Film film3("Film3", "./videos_inf224/Video_cat_3.mp4", 120, 0, nullptr);
    film3 = film1;
    std::cout << "\nFilm3 (assigned from Film1) details:\n";
    film3.display(std::cout);
}

void testGroup() {
    // Create some multimedia objects
    std::shared_ptr<Photo> p1 = std::make_shared<Photo>("banana", "./images_inf224/banana.jpeg", 48.8584, 2.2945);
    std::shared_ptr<Photo> p2 = std::make_shared<Photo>("cat", "./images_inf224/cat.jpeg", 40.6892, 74.0445);
    std::shared_ptr<Video> v1 = std::make_shared<Video>("video1", "./videos_inf224/Video_cat_1.mp4", 120);
    int durations[] = {10, 20, 30};
    std::shared_ptr<Film> f1 = std::make_shared<Film>("Film1", "./videos_inf224/Video_cat_2.mp4", 90, 3, durations);

    // Create groups
    Group photoGroup("Photo Group");
    Group videoGroup("Video Group");
    Group mixedGroup("Mixed Group");

    // Add objects to groups
    photoGroup.push_back(p1);
    photoGroup.push_back(p2);

    videoGroup.push_back(v1);

    mixedGroup.push_back(p1);
    mixedGroup.push_back(v1);
    mixedGroup.push_back(f1);

    // Display groups
    std::cout << "\nPhoto Group details:\n";
    photoGroup.display(std::cout);

    std::cout << "\nVideo Group details:\n";
    videoGroup.display(std::cout);

    std::cout << "\nMixed Group details:\n";
    mixedGroup.display(std::cout);
}

void testMediaManager() {
    MediaManager manager;

    // Creating some multimedia objects and adding them to the manager
    auto photo = manager.createPhoto("banana", "../images_inf224/banana.jpeg", 48.8584, 2.2945);
    auto video = manager.createVideo("video1", "../videos_inf224/Video_cat_1.mp4", 120);
    auto film = manager.createFilm("film1", "../videos_inf224/Video_cat_2.mp4", 150, 3, new int[3]{10, 20, 30});

    // Creating a group and adding the multimedia objects to it
    auto mediaGroup = manager.createGroup("Media Group");
    mediaGroup->push_back(photo);
    mediaGroup->push_back(video);
    mediaGroup->push_back(film);

    // Displaying individual multimedia objects
    std::cout << "\n--- Displaying individual media ---\n";
    manager.displayMedia("banana");
    manager.displayMedia("video1");
    manager.displayMedia("film1");

    // Displaying the group
    std::cout << "\n--- Displaying group ---\n";
    manager.displayGroup("Media Group");

    // Playing multimedia objects
    std::cout << "\n--- Playing media ---\n";
    manager.playMedia("video1");
    manager.playMedia("film1");

    // Testing removal of media
    std::cout << "\n--- Removing media ---\n";
    manager.removeMedia("banana");
    manager.displayMedia("banana");  // Should show that the media object was removed

    // Testing removal of group
    std::cout << "\n--- Removing group ---\n";
    manager.removeGroup("Media Group");
    manager.displayGroup("Media Group");  // Should show that the group was removed
}

void testMediaManager2() {
    MediaManager manager;

    // Create and add some multimedia objects to the manager
    auto photo = manager.createPhoto("banana", "./images_inf224/banana.jpeg", 48.8584, 2.2945);
    auto video = manager.createVideo("video1", "./videos_inf224/Video_cat_1.mp4", 120);
    auto film = manager.createFilm("film1", "./videos_inf224/Video_cat_2.mp4", 150, 3, new int[3]{10, 20, 30});

    // Create a group and add the multimedia objects to it
    auto mediaGroup = manager.createGroup("Media Group");
    mediaGroup->push_back(photo);
    mediaGroup->push_back(video);
    mediaGroup->push_back(film);

    // Save the objects to a file
    std::string filename = "media_data.txt";
    manager.save(filename);
    std::cout << "\nObjects saved in " << filename << std::endl;

    // Uncomment the following lines to test loading from the file

    // // Clear the MediaManager and reload the objects from the file to test deserialization
    // manager = MediaManager(); // This recreates the manager, clearing the tables

    // // Load the objects from the file
    // manager.load(filename);
    // std::cout << "\nObjects loaded from " << filename << std::endl;

    // // Display the loaded objects
    // for (const auto& mediaPair : manager.getMediaTable()) {
    //     mediaPair.second->display(std::cout);
    // }

    // for (const auto& groupPair : manager.getGroupTable()) {
    //     groupPair.second->display(std::cout);
    // }
}
