/**
 * @file group.h
 * @brief Declaration of the Group class.
 */

#ifndef GROUP_H
#define GROUP_H

#include "Multimidia.h"
#include <list>
#include <string>
#include <iostream>
#include <memory>

/**
 * @class Group
 * @brief Represents a group of multimedia objects.
 *
 * The Group class inherits from `std::list` of shared pointers to `Multimidia` objects.
 * It allows grouping multiple multimedia objects and provides methods to interact with them.
 */
class Group : public std::list<std::shared_ptr<Multimidia>> {
private:
    std::string name; ///< Name of the group.

public:
    /**
     * @brief Constructor that initializes the group with a name.
     * @param name The name of the group.
     */
    Group(const std::string& name) : name(name) {}

    /**
     * @brief Gets the name of the group.
     * @return The name of the group.
     */
    std::string getName() const { return name; }

    /**
     * @brief Displays the group's information and its multimedia items.
     * @param os The output stream to display to.
     */
    void display(std::ostream& os) const {
        os << "Group: " << name << "\n";
        for (const auto& item : *this) {
            item->display(os);
            os << "\n";
        }
    }
};

#endif // GROUP_H
