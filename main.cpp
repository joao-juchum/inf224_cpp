//
// main.cpp
// Created on 30/06/2024
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Multimidia.h"
#include "Photo.h"
#include "Video.h"
#include "film.h"
#include "group.h"

using namespace std;

void testPhotoVideo();
void testFilm();
void testGroup();

int main()
{
    std::cout << "Hello brave new world" << std::endl;
    //testPhotoVideo();
    //testFilm();
    testGroup();

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

}

void testFilm() {
    // Array de durações dos capítulos
    int durations1[] = {10, 20, 30};
    int durations2[] = {15, 25, 35, 45};

    // Criação de um objeto Film
    Film film1("Film1", "/path/to/film1", 90, 3, durations1);
    std::cout << "Film1 details:\n";
    film1.display(std::cout);

    // Modificação do array de durações
    film1.setChapterDurations(4, durations2);
    std::cout << "\nFilm1 details after modification:\n";
    film1.display(std::cout);

    // Teste do construtor de cópia
    Film film2 = film1;
    std::cout << "\nFilm2 (copy of Film1) details:\n";
    film2.display(std::cout);

    // Teste do operador de atribuição
    Film film3("Film3", "/path/to/film3", 120, 0, nullptr);
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
    
    // Photo* p1 = new Photo("banana", "./images_inf224/banana.jpeg", 48.8584, 2.2945);
    // Photo* p2 = new Photo("cat", "./images_inf224/cat.jpeg", 40.6892, 74.0445);
    // Video* v1 = new Video("video1", "./videos_inf224/Video_cat_1.mp4", 120);
    // int durations[] = {10, 20, 30};
    // Film* f1 = new Film("Film1", "/path/to/film1", 90, 3, durations);

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