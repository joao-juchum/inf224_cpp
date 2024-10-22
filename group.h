// group.h
#ifndef GROUP_H
#define GROUP_H

#include <list>
#include <string>
#include <iostream>
#include "Multimidia.h"

class Group : public std::list<Multimidia*> {
private:
    std::string name;

public:
    // Constructor
    Group(const std::string& name) : name(name) {}

    // Accessor for the group name
    std::string getName() const { return name; }

    // Display method
    void display(std::ostream& os) const {
        os << "Group: " << name << "\n";
        for (const auto& item : *this) {
            item->display(os);
            os << "\n";
        }
    }
};

#endif // GROUP_H