# Media Manager

**Author:** João Pedro Juchum Chagas  
**Course:** Programming Paradigms (INF224)

---

## Introduction

The **Media Manager** project is a multimedia management application developed in C++ and Java as part of the Programming Paradigms course (INF224). The project simulates a set-top box that can manage and play various media types such as photos, videos, and films. It involves creating classes with inheritance, polymorphism, memory management, and client-server communication.

This README addresses the questions posed in the assignment, provides explanations of the implementation choices, and includes additional comments.

---

## Questions Addressed

### 1. What is this type of method called and how should it be declared?

In step 4, we were asked to implement a method that cannot have an implementation at the base class level because each derived type requires a different program to be played. Such a method is called a **pure virtual function** in C++. It should be declared in the base class using the `virtual` keyword and assigned `= 0` to indicate that it is pure virtual. For example:

```cpp
virtual void play() const = 0;
```

This makes the base class an **abstract class**, and it cannot be instantiated directly.

### 2. If you have done the above as requested, it will no longer be possible to instantiate objects of the base class. Why?

By declaring a pure virtual function in the base class, the class becomes abstract. In C++, abstract classes cannot be instantiated because they contain methods without implementations. This ensures that only derived classes that provide implementations for all pure virtual functions can be instantiated.

### 3. What is the characteristic property of object-oriented programming that allows us to do this?

The property is **polymorphism**, specifically **runtime polymorphism** achieved through virtual functions. Polymorphism allows us to treat objects of different derived classes uniformly through pointers or references to the base class, enabling us to write code that works with base class pointers or references without knowing the exact derived type.

### 4. What is specifically necessary to do in the case of C++?

In C++, to achieve runtime polymorphism, we need to:

- **Declare Methods as Virtual:** Use the `virtual` keyword in the base class for methods that will be overridden.
- **Use Base Class Pointers or References:** Interact with objects through pointers or references to the base class.
- **Implement Derived Methods:** Ensure derived classes override the virtual methods.
- **Virtual Destructor:** Declare the base class destructor as `virtual` to allow proper cleanup of derived objects.

### 5. What is the type of the elements in the array: should the array contain objects or pointers to these objects? Why? Compare with Java.

The array should contain **pointers to the base class** (`Multimedia*`), not objects themselves. This is because:

- **Object Slicing:** If we store derived objects directly in an array of base class objects, only the base part of the objects will be stored (object slicing), and we lose the derived class information.
- **Polymorphism:** Using pointers allows us to achieve polymorphic behavior, calling the correct overridden methods in derived classes.

In Java, all objects are accessed via references, and polymorphism is inherent, so this issue does not occur.

### 6. Among the previously written classes, which ones need to be modified to prevent memory leaks when objects are destroyed? Modify the code accordingly.

Classes that manage dynamic memory need to be modified, particularly the `Film` class, which may allocate dynamic arrays for chapter durations. To prevent memory leaks:

- **Implement Destructors:** Add destructors to deallocate any dynamically allocated memory.
- **Rule of Three/Five:** Implement the copy constructor, copy assignment operator, and destructor if the class manages resources.
- **Use Smart Pointers:** Replace raw pointers with smart pointers like `std::shared_ptr` or `std::unique_ptr`.

### 7. Copying objects can also cause problems when they have instance variables that are pointers. What is the problem and what are the solutions? Implement one.

**Problem:**

- **Shallow Copy Issues:** When copying objects with pointer members, the default copy constructor and assignment operator perform a shallow copy, copying the pointers' addresses. Both objects then point to the same memory, leading to potential double deletion or unintended modifications.

**Solutions:**

- **Deep Copy:** Implement a custom copy constructor and assignment operator that perform a deep copy, allocating new memory and copying the contents.
- **Disable Copying:** Delete the copy constructor and assignment operator if copying is not intended.
- **Use Smart Pointers:** Utilize smart pointers (e.g., `std::shared_ptr`) to manage memory automatically.

**Implementation:**

In the `Film` class, I implemented a deep copy in the copy constructor and assignment operator to ensure that the chapter durations array is properly copied.

### 8. We recall that the list of objects must in fact be a list of pointers to objects. Why? Compare with Java.

The group class should contain a list of pointers to objects because:

- **Polymorphism:** To store objects of different derived types and achieve polymorphic behavior.
- **Avoid Object Slicing:** Storing objects directly would slice derived class information.

In Java, collections store references to objects, and polymorphism is inherent, so we don't face object slicing issues.

### 9. The previous methods ensure the consistency of the database because when we create an object we add it to the appropriate table. However, this will not be the case if we create an object directly with `new` (it will not belong to any table). How can we prevent this, so that only the class used to manipulate the objects can create new ones?

To prevent objects from being created directly with `new`, we can:

- **Make Constructors Private or Protected:** Restrict access to the constructors so that only the manager class can create instances.
- **Use Factory Pattern:** Provide creation methods in the manager class and avoid exposing the constructors publicly.
- **Friend Classes:** Declare the manager class as a friend of the media classes.

In our implementation, we used the Factory pattern by providing creation methods in the `MediaManager` class and not exposing constructors publicly.

### 10. Now it's your turn! Handle the main cases of errors as you see fit, using the first or second strategy, or a combination of both depending on the severity of the errors. But make sure your code is consistent with your choices and justify them in the report and/or documentation generated by Doxygen.

**Error Handling Strategy:**

I chose to use a combination of error codes and exception handling:

- **Error Codes:** For less severe errors, such as attempting to play a non-existent media, methods return boolean values indicating success or failure.
- **Exceptions:** For critical errors, such as memory allocation failures or invalid operations, I used exceptions (e.g., throwing `std::runtime_error`).

**Justification:**

Using exceptions for critical errors ensures that they cannot be ignored and must be handled appropriately, improving program robustness. For less critical errors, returning error codes simplifies the flow without the overhead of exceptions. This approach balances safety and performance.

---

## Additional Comments

- **Documentation:**

  The code is thoroughly documented using **Doxygen** for C++ and **JavaDoc** for Java, enabling automatic generation of comprehensive documentation. This enhances code readability and maintainability.

- **Memory Management:**

  **Smart pointers** (`std::shared_ptr`) are utilized to manage dynamic memory automatically, preventing memory leaks and dangling pointers. This simplifies memory management and reduces the risk of errors associated with manual memory handling.

- **Client-Server Communication:**

  Implemented a **TCP server** in C++ and a **Java client** that communicate over sockets. The server processes requests to search, display, and play media objects. The client acts as a remote control, sending commands and displaying responses.

- **Design Patterns:**

  Applied the **Factory Pattern** in the `MediaManager` class to control object creation and maintain consistency. This centralizes object management and ensures that all media objects are registered within the manager.

- **Testing:**

  Extensive testing was performed to ensure that media objects are correctly created, managed, and played. The client-server interaction was thoroughly tested to verify proper communication and handling of requests.

- **Exception Safety:**

  Careful consideration was given to exception safety, particularly in resource management and object copying. By adhering to the Rule of Three/Five and using smart pointers, the code is more robust against exceptions.

---

## Instructions to Run the Project

### For compilation unified

- In the main directory run the following comand in terminal:
  ```bash
  make run
  ```

### For compilation separade

#### C++ Server

- **Compilation:**

  Run the following command in the terminal in `./cpp`:

  ```bash
  make run
  ```

  Ensure that all required source files are included in the `Makefile`.

- **Execution:**

  Start the server by running:

  ```bash
  ./server
  ```

  The server will listen on the default port (e.g., `3331`) and await client connections.

#### Java Client

- **Compilation:**

  Use the provided `Makefile` by running in `./Swing`:

  ```bash
  make run
  ```

- **Execution:**

  Run the client application with:

  ```bash
  java MainWindow
  ```

  The client will connect to the server and provide a graphical user interface for interaction.

---

## Notes

- **Port Configuration:**

  Ensure that the server and client are configured to use the same port and host settings. By default, the server listens on `localhost` and port `3331`.

- **Dependencies:**

  - The C++ server requires the `pthread` library for threading.
  - The Java client requires standard Java libraries; no external dependencies are needed.
  - The softwares `Imagej` and `Mpv` was necessary for the program.

- **Platform Compatibility:**

  - The server and client have been tested on Linux and Windows environments.
  - Ensure that the media files are accessible to the server, and the paths are correctly specified.

---

**This project demonstrates the application of object-oriented programming principles, memory management, and network communication. It provides a foundation for a multimedia management system that can be expanded with additional features.**

**Author:** João Pedro Juchum Chagas

---