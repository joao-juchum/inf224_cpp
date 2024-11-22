/**
 * @file film.h
 * @brief Declaration of the Film class, representing a film with chapters.
 */

#ifndef FILM_H
#define FILM_H

#include "Video.h"
#include <iostream>
#include <cstring> // for std::memcpy

/**
 * @class Film
 * @brief Represents a film with multiple chapters.
 *
 * The Film class extends the Video class by adding chapters. Each chapter has its own duration.
 */
class Film : public Video {
private:
    std::string name;        ///< Name of the film.
    std::string filePath;    ///< File path to the film.
    int* chapterDurations;   ///< Array of chapter durations.
    int chapters;            ///< Number of chapters.

public:
    /**
     * @brief Constructs a new Film object with specified parameters.
     * @param name The name of the film.
     * @param filePath The file path to the film.
     * @param duration The total duration of the film.
     * @param chapters The number of chapters in the film.
     * @param durations An array containing the duration of each chapter.
     */
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

    /**
     * @brief Destructor for the Film class.
     *
     * Releases allocated memory for chapter durations.
     */
    ~Film() {
        delete[] chapterDurations;
        std::cout << "Film object " << getName() << " destroyed\n";
    }

    /**
     * @brief Copy constructor.
     * @param other The Film object to copy from.
     */
    Film(const Film& other) : Video(other), chapters(other.chapters) {
        if (chapters > 0) {
            chapterDurations = new int[chapters];
            std::memcpy(chapterDurations, other.chapterDurations, chapters * sizeof(int));
        } else {
            chapterDurations = nullptr;
        }
    }

    /**
     * @brief Copy assignment operator.
     * @param other The Film object to assign from.
     * @return Reference to the assigned Film object.
     */
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

    /**
     * @brief Gets the array of chapter durations.
     * @return Pointer to the array of chapter durations.
     */
    const int* getChapterDurations() const { return chapterDurations; }

    /**
     * @brief Gets the number of chapters in the film.
     * @return The number of chapters.
     */
    int getChapters() const { return chapters; }

    /**
     * @brief Sets the chapter durations.
     * @param chapters The number of chapters.
     * @param durations An array containing the duration of each chapter.
     */
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

    /**
     * @brief Displays the film's information, including chapter durations.
     * @param os The output stream to display to.
     */
    void display(std::ostream& os) const {
        Video::display(os);
        os << "Chapters: " << chapters << "\n";
        for (int i = 0; i < chapters; ++i) {
            os << "Chapter " << i + 1 << ": " << chapterDurations[i] << " minutes\n";
        }
    }

    /**
     * @brief Saves the film's data to an output file stream.
     * @param ofs The output file stream to save to.
     */
    void save(std::ofstream& ofs) const override {
        ofs << getClassName() << "\n" << name << "\n" << filePath << "\n" << chapterDurations << "\n" << chapters << "\n";
    }

    /**
     * @brief Loads the film's data from an input file stream.
     * @param ifs The input file stream to load from.
     */
    void load(std::ifstream& ifs) override {
        std::getline(ifs, name);
        std::getline(ifs, filePath);
        ifs >> *chapterDurations >> chapters;
        ifs.ignore();
    }

    /**
     * @brief Gets the class name of the object.
     * @return The string "film".
     */
    std::string getClassName() const override {
        return "film";
    }
};

#endif // FILM_H
