# Media Center Application - INF224

## Introduction

The Media Center Application is a client-server program that allows users to interact with multimedia content (photos and videos) stored on a server. The server is written in C++, and the client is a Java Swing GUI. Users can search for media, display media information, and play media files directly from the GUI.

## Requirements

### Software Dependencies

- **C++ Compiler**: GCC or any compatible C++11 compiler.
- **Java Development Kit (JDK)**: Version 8 or higher.
- **ImageJ**: An image processing program used to display photos.
- **mpv Media Player**: A media player used to play videos.
- **Make**: For building the project using the provided Makefile.

### Installing Dependencies on Linux

#### Install GCC and Make

```bash
sudo apt-get update
sudo apt-get install build-essential
```

#### Install Java Development Kit (JDK)

```bash
sudo apt-get install default-jdk
```

#### Install ImageJ

1. Download ImageJ from the [official website](https://imagej.nih.gov/ij/download.html).
2. Extract the downloaded archive.
3. Optionally, add ImageJ to your system PATH for easier access.

#### Install mpv Media Player

```bash
sudo apt-get install mpv
```

## Project Structure

```
ProjectRoot/
├── README.md
├── Makefile
├── doc/
│   ├── html/
│   └── latex/
├── images_inf224/
│   ├── banana.jpeg
│   ├── cat.jpeg
│   └── Miniom.jpeg
├── videos_inf224/
│   ├── Video_cat_1.mp4
│   ├── Video_cat_2.mp4
│   └── Video_cat_3.mp4
├── SourcesCpp/
│   ├── ccsocket.cpp
│   ├── ccsocket.h
│   ├── tcpserver.cpp
│   ├── tcpserver.h
│   ├── Multimidia.cpp
│   ├── Multimidia.h
│   ├── group.h
│   ├── Photo.h
│   ├── Video.h
│   ├── film.h
│   └── server.cpp
└── Swing/
    ├── Client.java
    └── MainWindow.java
```

- **SourcesCpp/**: Contains all the C++ source and header files for the server.
- **Swing/**: Contains the Java source files for the client GUI.
- **images_inf224/**: Contains image files used by the server.
- **videos_inf224/**: Contains video files used by the server.
- **doc/**: Documentation files (optional).

## Installation and Setup

1. **Clone the Repository**

   ```bash
   git clone https://your-repository-url.git
   ```

2. **Navigate to the Project Directory**

   ```bash
   cd ProjectRoot
   ```

3. **Build the Project**

   Use the provided Makefile to compile both the server and the client.

   ```bash
   make
   ```

   This command will:

   - Compile the C++ server source files.
   - Compile the Java client source files.

## Usage

### Running the Application

To start the server and launch the client GUI, run:

```bash
make run
```

This command will:

- Start the server in the background.
- Launch the Java Swing GUI for the client.
- Automatically shut down the server when you exit the GUI.

### Using the Client GUI

The GUI provides several functionalities accessible via buttons and menus:

- **Play Media**: Prompts you to enter the name of a media file to play. The server will play the media using ImageJ (for images) or mpv (for videos).
- **List Media**: Displays a list of all media files available on the server.
- **List Groups**: Displays a list of all media groups on the server.
- **Help**: Shows a help message with available commands.
- **Clear Text**: Clears the text area displaying server responses.
- **Exit**: Closes the client GUI.

#### Steps to Play a Media File

1. Click on **Play Media**.
2. Enter the name of the media file (e.g., `banana`).
3. The server will play the media file if it exists.

## Troubleshooting

- **Server Not Starting**

  - Ensure that all dependencies are installed.
  - Check if the server port (default is 3331) is not already in use.

- **Media Not Playing**

  - Verify that ImageJ and mpv are correctly installed and accessible from the command line.
  - Ensure that the media files are located in the correct directories relative to the server's execution path.

- **Compilation Errors**

  - Run `make clean` to remove old object files and binaries, then try `make` again.
  - Ensure that all source files are present and paths are correctly specified in the Makefile.

## Cleaning Up

To remove compiled files and clean the project directory, run:

```bash
make clean
```

This command will delete:

- All object files (`*.o`).
- The server executable.
- Java class files (`*.class`).

## Additional Notes

- **Extensibility**

  - The application can be extended by adding new media types or commands.
  - Modify the server code in `SourcesCpp/` and recompile using `make`.

- **Cross-Platform Compatibility**

  - The application is developed for Linux systems.
  - Modifications may be required for Windows or macOS environments, especially for paths and media player commands.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **ImageJ**: [https://imagej.nih.gov/ij/](https://imagej.nih.gov/ij/)
- **mpv Media Player**: [https://mpv.io/](https://mpv.io/)

---

**Enjoy using the Media Center Application! If you encounter any issues or have suggestions for improvements, feel free to contribute or contact the maintainers.**