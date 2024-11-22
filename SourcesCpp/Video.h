// video.h
#ifndef VIDEO_H
#define VIDEO_H

#include "Multimidia.h"

class Video : public Multimidia {
private:
    std::string name;
    std::string filePath; 
    int duration; // Duration of the video in seconds

public:
    // Constructor with arguments
    Video(const std::string& name, const std::string& filePath, int duration)
        : Multimidia(name, filePath), duration(duration) {
        std::cout << "Video object " << getName() << " created\n";
        }

    // Getter (accessor)
    int getDuration() const { return duration; }

    // Setter (mutator)
    void setDuration(int duration) { this->duration = duration; }

    // Display method (override)
    void display(std::ostream& os) const {
        Multimidia::display(os);
        os << "Duration: " << duration << " seconds" << std::endl;
    }

    // Play method (specific to Video)
    void play() const override {
        std::string command = "mpv " + Multimidia::getFilePath() + " &";
        system(command.data());
    }

    // Save and load methods
    void save(std::ofstream& ofs) const override {
        ofs << getClassName() << "\n" << name << "\n" << filePath << "\n" << duration << "\n";
    }
    void load(std::ifstream& ifs) override {
        std::getline(ifs, name);
        std::getline(ifs, filePath);
        ifs >> duration;
        ifs.ignore();
    }

    //Get the class name
    std::string getClassName() const override {
        return "Video";
    }

    // Destructor
    ~Video() {
        std::cout << "Video object " << getName() << " destroyed\n";
    }
};
#endif
