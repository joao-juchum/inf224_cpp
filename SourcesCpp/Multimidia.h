#ifndef MULTIMIDIA_H
#define MULTIMIDIA_H

#include <iostream>
#include <string>
#include <fstream>

class Multimidia{

    private:
        std::string name;
        std::string filePath;

    public:
        //Constructor without argument
        Multimidia();

        //Constructor with arguments
        Multimidia(const std::string& name, const std::string& filePath);

        //Destructor 
        virtual ~Multimidia();

        //Getters
        std::string getName() const;
        std::string getFilePath() const;

        //Setters
        void setName(const std::string& name);
        void setFilePath(const std::string& filePath);

        //Display
        void display(std::ostream& os) const{
            os << "Name: " << name << ", File Path: " << filePath << std::endl;
        };

        // Virtual method to play the multimedia object
        virtual void play() const = 0; // Pure virtual function

        //Virtual method for save and load
        virtual void save(std::ofstream& os) const = 0;
        virtual void load(std::ifstream& is) = 0;

        //Virtual method for get class name
        virtual std::string getClassName() const = 0;

};

#endif //MULTIMIDIA_H