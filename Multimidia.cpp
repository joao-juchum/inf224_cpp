#include "Multimidia.h"

//Constrcteur sans argument
Multimidia::Multimidia() : name("unknow"), filePath("unknow") {

};

//Constructeur avec argumenet
Multimidia::Multimidia(const std::string& name, const std::string& filePath) : name(name), filePath(filePath) {

};

//Destructeur 
Multimidia::~Multimidia() {
    
};

//Getters
std::string Multimidia::getName() const {
    return name;
};
std::string Multimidia::getFilePath() const {
    return filePath;
};

//Setters
void Multimidia::setName(const std::string& name){
    this->name = name;
};
void Multimidia::setFilePath(const std::string& filePath){
    this->filePath = filePath;
};

//Affichage
void Multimidia::displayObj(std::ostream& os) const {
    os << "name: " << name << "\n" << "filePath: " << filePath << std::endl;
};
