/**
 * @file photo.h
 * @brief Declaration of the Photo class.
 */

#ifndef PHOTO_H
#define PHOTO_H

#include "Multimidia.h"
#include <string>
#include <fstream>

/**
 * @class Photo
 * @brief Represents a photo with geolocation data.
 *
 * The Photo class extends the Multimidia class by adding latitude and longitude information.
 * It provides methods to access and modify these geolocation attributes, as well as methods
 * to display and play the photo.
 */
class Photo : public Multimidia {
private:
    std::string name;       ///< Name of the photo.
    std::string filePath;   ///< File path of the photo.
    double latitude;        ///< Latitude coordinate of the photo.
    double longitude;       ///< Longitude coordinate of the photo.

public:
    /**
     * @brief Constructor with arguments.
     *
     * Initializes a Photo object with the given name, file path, latitude, and longitude.
     *
     * @param name The name of the photo.
     * @param filePath The file path to the photo.
     * @param lat The latitude coordinate.
     * @param lon The longitude coordinate.
     */
    Photo(const std::string& name, const std::string& filePath, double lat, double lon)
        : Multimidia(name, filePath), latitude(lat), longitude(lon) {}

    /**
     * @brief Gets the latitude of the photo.
     * @return The latitude coordinate.
     */
    double getLatitude() const { return latitude; }

    /**
     * @brief Gets the longitude of the photo.
     * @return The longitude coordinate.
     */
    double getLongitude() const { return longitude; }

    /**
     * @brief Sets the latitude of the photo.
     * @param lat The new latitude coordinate.
     */
    void setLatitude(double lat) { latitude = lat; }

    /**
     * @brief Sets the longitude of the photo.
     * @param lon The new longitude coordinate.
     */
    void setLongitude(double lon) { longitude = lon; }

    /**
     * @brief Displays the photo's information.
     *
     * Overrides the base class display method to include latitude and longitude.
     *
     * @param os The output stream to display to.
     */
    void display(std::ostream& os) const {
        Multimidia::display(os);
        os << "Latitude: " << latitude << ", Longitude: " << longitude << std::endl;
    }

    /**
     * @brief Plays the photo.
     *
     * Implements the play method specific to Photo, using an external image viewer.
     */
    void play() const override {
        std::string command = "imagej " + Multimidia::getFilePath() + " &";
        system(command.data());
    }

    /**
     * @brief Saves the photo's data to an output file stream.
     * @param ofs The output file stream to save to.
     */
    void save(std::ofstream& ofs) const override {
        ofs << getClassName() << "\n" << name << "\n" << filePath << "\n" << latitude << "\n" << longitude << "\n";
    }

    /**
     * @brief Loads the photo's data from an input file stream.
     * @param ifs The input file stream to load from.
     */
    void load(std::ifstream& ifs) override {
        std::getline(ifs, name);
        std::getline(ifs, filePath);
        ifs >> latitude >> longitude;
        ifs.ignore();
    }

    /**
     * @brief Gets the class name of the object.
     * @return The string "Photo".
     */
    std::string getClassName() const override {
        return "Photo";
    }

    /**
     * @brief Destructor for the Photo class.
     *
     * Outputs a message indicating that the Photo object is destroyed.
     */
    ~Photo(){
        std::cout << "Photo object " << getName() << " destroyed\n";  
    }
};

#endif // PHOTO_H
