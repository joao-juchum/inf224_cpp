/**
 * @file Multimidia.cpp
 * @brief Implementation of the Multimidia class methods.
 */

#include "Multimidia.h"

/**
 * @brief Default constructor.
 *
 * Initializes the multimedia object with default values.
 */
Multimidia::Multimidia() : name("unknown"), filePath("unknown") {
}

/**
 * @brief Constructor with parameters.
 *
 * @param name The name of the multimedia object.
 * @param filePath The file path of the multimedia object.
 */
Multimidia::Multimidia(const std::string& name, const std::string& filePath) : name(name), filePath(filePath) {
}

/**
 * @brief Destructor.
 */
Multimidia::~Multimidia() {
}

/**
 * @brief Gets the name of the multimedia object.
 * @return The name as a string.
 */
std::string Multimidia::getName() const {
    return name;
}

/**
 * @brief Gets the file path of the multimedia object.
 * @return The file path as a string.
 */
std::string Multimidia::getFilePath() const {
    return filePath;
}

/**
 * @brief Sets the name of the multimedia object.
 * @param name The new name to set.
 */
void Multimidia::setName(const std::string& name){
    this->name = name;
}

/**
 * @brief Sets the file path of the multimedia object.
 * @param filePath The new file path to set.
 */
void Multimidia::setFilePath(const std::string& filePath){
    this->filePath = filePath;
}
