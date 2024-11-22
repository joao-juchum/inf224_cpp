// photo.h
#ifndef PHOTO_H
#define PHOTO_H

#include "Multimidia.h"
#include <string>
#include <fstream>

class Photo : public Multimidia {
private:
    std::string name; // Name of the photo
    std::string filePath; // File path of the photo
    double latitude;  // Latitude of the photo
    double longitude; // Longitude of the photo

public:
    // Constructor with arguments
    Photo(const std::string& name, const std::string& filePath, double lat, double lon)
        : Multimidia(name, filePath), latitude(lat), longitude(lon) {}

    // Getters (accessors)
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    // Setters (mutators)
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }

    // Display method (override)
    void display(std::ostream& os) const {
        Multimidia::display(os);
        os << "Latitude: " << latitude << ", Longitude: " << longitude << std::endl;
    }

    // Play method (specific to Photo)
    void play() const override {
        std::string command = "imagej " + Multimidia::getFilePath() + " &";
        system(command.data());
    }

    // Save and load methods
    void save(std::ofstream& ofs) const override {
        ofs << getClassName() << "\n" << name << "\n" << filePath << "\n" << latitude << "\n" << longitude << "\n";
    }
    void load(std::ifstream& ifs) override {
        std::getline(ifs, name);
        std::getline(ifs, filePath);
        ifs >> latitude >> longitude;
        ifs.ignore();
    }

    //Get the class name
    std::string getClassName() const override {
        return "Photo";
    }

    // Destructor
    ~Photo(){
        std::cout << "Photo object " << getName() << " destroyed/n";  
    }
};

#endif
