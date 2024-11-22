// film.h
#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <iostream>
#include <cstring> // for std::memcpy

class Film : public Video {
private:
    std::string name;
    std::string filePath;
    int* chapterDurations; // Array of chapter durations
    int chapters; // Number of chapters

public:
    // Constructor with arguments
    Film(const std::string& name, const std::string& filePath, int duration, int chapters, const int* durations)
        : Video(name, filePath, duration), chapters(chapters) {
        if (chapters > 0) {
            chapterDurations = new int[chapters];
            std::memcpy(chapterDurations, durations, chapters * sizeof(int));
        } else {
            chapterDurations = nullptr;
        }
        std::cout << "Film object " << getName() << " created\n";
    }

    // Destructor
    ~Film() {
        delete[] chapterDurations;
        std::cout << "Film object " << getName() << " destroyed\n";
    }

    // Copy constructor
    Film(const Film& other) : Video(other), chapters(other.chapters) {
        if (chapters > 0) {
            chapterDurations = new int[chapters];
            std::memcpy(chapterDurations, other.chapterDurations, chapters * sizeof(int));
        } else {
            chapterDurations = nullptr;
        }
    }

    // Copy assignment operator
    Film& operator=(const Film& other) {
        if (this != &other) {
            Video::operator=(other);
            delete[] chapterDurations;

            chapters = other.chapters;
            if (chapters > 0) {
                chapterDurations = new int[chapters];
                std::memcpy(chapterDurations, other.chapterDurations, chapters * sizeof(int));
            } else {
                chapterDurations = nullptr;
            }
        }
        return *this;
    }

    // Getter for chapter durations
    const int* getChapterDurations() const { return chapterDurations; }

    // Getter for number of chapters
    int getChapters() const { return chapters; }

    // Setter for chapter durations
    void setChapterDurations(int chapters, const int* durations) {
        delete[] chapterDurations;
        this->chapters = chapters;
        if (chapters > 0) {
            chapterDurations = new int[chapters];
            std::memcpy(chapterDurations, durations, chapters * sizeof(int));
        } else {
            chapterDurations = nullptr;
        }
    }

    // Display method (override)
    void display(std::ostream& os) const {
        Video::display(os);
        os << "Chapters: " << chapters << "\n";
        for (int i = 0; i < chapters; ++i) {
            os << "Chapter " << i + 1 << ": " << chapterDurations[i] << " minutes\n";
        }
    }

    // Save and load methods
    void save(std::ofstream& ofs) const override {
        ofs << getClassName() << "\n" << name << "\n" << filePath << "\n" << chapterDurations << "\n" << chapters << "\n";
    }
    void load(std::ifstream& ifs) override {
        std::getline(ifs, name);
        std::getline(ifs, filePath);
        ifs >> *chapterDurations >> chapters;
        ifs.ignore();
    }

    //Get the class name
    std::string getClassName() const override {
        return "film";
    }
};

#endif // FILM_H