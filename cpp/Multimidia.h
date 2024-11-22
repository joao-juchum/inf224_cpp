/**
 * @file Multimidia.h
 * @brief Declaration of the Multimidia class.
 */

#ifndef MULTIMIDIA_H
#define MULTIMIDIA_H

#include <iostream>
#include <string>
#include <fstream>

/**
 * @class Multimidia
 * @brief Abstract base class representing a multimedia object.
 *
 * The Multimidia class serves as an abstract base class for different types of multimedia objects,
 * such as photos, videos, and films. It provides common attributes and methods that can be overridden
 * by derived classes.
 */
class Multimidia{

    private:
        std::string name;     ///< Name of the multimedia object.
        std::string filePath; ///< File path of the multimedia object.

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes the multimedia object with default values.
         */
        Multimidia();

        /**
         * @brief Constructor with parameters.
         *
         * @param name The name of the multimedia object.
         * @param filePath The file path of the multimedia object.
         */
        Multimidia(const std::string& name, const std::string& filePath);

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~Multimidia();

        /**
         * @brief Gets the name of the multimedia object.
         * @return The name as a string.
         */
        std::string getName() const;

        /**
         * @brief Gets the file path of the multimedia object.
         * @return The file path as a string.
         */
        std::string getFilePath() const;

        /**
         * @brief Sets the name of the multimedia object.
         * @param name The new name to set.
         */
        void setName(const std::string& name);

        /**
         * @brief Sets the file path of the multimedia object.
         * @param filePath The new file path to set.
         */
        void setFilePath(const std::string& filePath);

        /**
         * @brief Displays the multimedia object's information.
         * @param os The output stream to display to.
         */
        void display(std::ostream& os) const{
            os << "Name: " << name << ", File Path: " << filePath << std::endl;
        };

        /**
         * @brief Pure virtual method to play the multimedia object.
         *
         * Must be overridden by derived classes to implement specific play functionality.
         */
        virtual void play() const = 0; // Pure virtual function

        /**
         * @brief Pure virtual method to save the multimedia object.
         *
         * Must be overridden by derived classes to implement specific save functionality.
         * @param os The output file stream to save to.
         */
        virtual void save(std::ofstream& os) const = 0;

        /**
         * @brief Pure virtual method to load the multimedia object.
         *
         * Must be overridden by derived classes to implement specific load functionality.
         * @param is The input file stream to load from.
         */
        virtual void load(std::ifstream& is) = 0;

        /**
         * @brief Pure virtual method to get the class name.
         *
         * Must be overridden by derived classes to return the class name as a string.
         * @return The class name as a string.
         */
        virtual std::string getClassName() const = 0;

};

#endif // MULTIMIDIA_H
