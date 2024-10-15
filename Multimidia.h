#ifndef MULTIMIDIA_H
#define MULTIMIDIA_H

#include <iostream>
#include <string>

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
        ~Multimidia();

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

};

#endif //MULTIMIDIA_H