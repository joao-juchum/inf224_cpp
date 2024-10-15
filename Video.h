// video.h
#ifndef VIDEO_H
#define VIDEO_H

#include "Multimidia.h"

class Video : public Multimidia {
private:
    int duration; // Duration of the video in seconds

public:
    // Constructor with arguments
    Video(const std::string& name, const std::string& filePath, int duration)
        : Multimidia(name, filePath), duration(duration) {}

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
        std::string command = "mpv " + getFilePath() + " &";
        system(command.data());
    }
};
#endif
