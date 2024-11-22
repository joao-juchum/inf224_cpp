/**
 * @file video.h
 * @brief Declaration of the Video class.
 */

#ifndef VIDEO_H
#define VIDEO_H

#include "Multimidia.h"

/**
 * @class Video
 * @brief Represents a video with a duration.
 *
 * The Video class extends the Multimidia class by adding a duration attribute.
 * It provides methods to access and modify the duration, as well as methods
 * to display and play the video.
 */
class Video : public Multimidia {
private:
    std::string name;        ///< Name of the video.
    std::string filePath;    ///< File path of the video.
    int duration;            ///< Duration of the video in seconds.

public:
    /**
     * @brief Constructor with arguments.
     *
     * Initializes a Video object with the given name, file path, and duration.
     *
     * @param name The name of the video.
     * @param filePath The file path to the video.
     * @param duration The duration of the video in seconds.
     */
    Video(const std::string& name, const std::string& filePath, int duration)
        : Multimidia(name, filePath), duration(duration) {
        std::cout << "Video object " << getName() << " created\n";
    }

    /**
     * @brief Gets the duration of the video.
     * @return The duration in seconds.
     */
    int getDuration() const { return duration; }

    /**
     * @brief Sets the duration of the video.
     * @param duration The new duration in seconds.
     */
    void setDuration(int duration) { this->duration = duration; }

    /**
     * @brief Displays the video's information.
     *
     * Overrides the base class display method to include the duration.
     *
     * @param os The output stream to display to.
     */
    void display(std::ostream& os) const {
        Multimidia::display(os);
        os << "Duration: " << duration << " seconds" << std::endl;
    }

    /**
     * @brief Plays the video.
     *
     * Implements the play method specific to Video, using an external video player.
     */
    void play() const override {
        std::string command = "mpv " + Multimidia::getFilePath() + " &";
        system(command.data());
    }

    /**
     * @brief Saves the video's data to an output file stream.
     * @param ofs The output file stream to save to.
     */
    void save(std::ofstream& ofs) const override {
        ofs << getClassName() << "\n" << name << "\n" << filePath << "\n" << duration << "\n";
    }

    /**
     * @brief Loads the video's data from an input file stream.
     * @param ifs The input file stream to load from.
     */
    void load(std::ifstream& ifs) override {
        std::getline(ifs, name);
        std::getline(ifs, filePath);
        ifs >> duration;
        ifs.ignore();
    }

    /**
     * @brief Gets the class name of the object.
     * @return The string "Video".
     */
    std::string getClassName() const override {
        return "Video";
    }

    /**
     * @brief Destructor for the Video class.
     *
     * Outputs a message indicating that the Video object is destroyed.
     */
    ~Video() {
        std::cout << "Video object " << getName() << " destroyed\n";
    }
};

#endif // VIDEO_H
