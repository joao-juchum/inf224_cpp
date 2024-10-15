//
// main.cpp
// Created on 30/06/2024
//

#include <iostream>
#include <string>
#include <vector>
#include "Multimidia.h"
#include "Photo.h"
#include "Video.h"
using namespace std;

int main()
{
    std::cout << "Hello brave new world" << std::endl;
    
    // Create some multimedia objects
    Photo p1("banana", "./images_inf224/banana.jpeg", 48.8584, 2.2945);
    Photo p2("cat", "./images_inf224/cat.jpeg", 40.6892, 74.0445);
    Photo p3("Miniom", "./images_inf224/Miniom.jpeg", 40.6892, 74.0445);
    Video v1("video1", "./videos_inf224/Video_cat_1.mp4", 120);
    Video v2("video2", "./videos_inf224/Video_cat_2.mp4", 60);
    Video v3("video3", "./videos_inf224/Video_cat_3.mp4", 90);
    

    // Doing polymorphism
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

    return 0;
}