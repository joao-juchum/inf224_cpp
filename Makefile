# Makefile for compiling and running the Media Center application

# Compiler for C++
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++11

# Java compiler
JAVAC = javac

# Java execution command
JAVA = java

# Directories
CPP_DIR = cpp
JAVA_DIR = swing

# C++ source files
CPP_SOURCES = $(CPP_DIR)/ccsocket.cpp \
              $(CPP_DIR)/tcpserver.cpp \
              $(CPP_DIR)/Multimidia.cpp \
              $(CPP_DIR)/server.cpp \
			  $(CPP_DIR)/ccsocket.h \
              $(CPP_DIR)/tcpserver.h \
              $(CPP_DIR)/Multimidia.h \
              $(CPP_DIR)/MediaManager.h \
              $(CPP_DIR)/group.h \
              $(CPP_DIR)/Photo.h \
              $(CPP_DIR)/Video.h \
              $(CPP_DIR)/film.h

# C++ object files
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)

# C++ executable
SERVER_EXE = $(CPP_DIR)/server

# Java source files
JAVA_SOURCES = $(JAVA_DIR)/MainWindow.java \
               $(JAVA_DIR)/Client.java

# Java class files
JAVA_CLASSES = $(JAVA_SOURCES:.java=.class)

# Default target
.PHONY: all
all: $(SERVER_EXE) $(JAVA_CLASSES)

# Rule to build the server executable
$(SERVER_EXE): $(CPP_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXE) $(CPP_OBJECTS)

# Rule to compile C++ source files into object files
$(CPP_DIR)/%.o: $(CPP_DIR)/%.cpp $(CPP_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile Java source files
$(JAVA_DIR)/%.class: $(JAVA_DIR)/%.java
	$(JAVAC) -d $(JAVA_DIR) $<

# Run the server and client
.PHONY: run
run: all
	@echo "Starting server..."
	@cd $(CPP_DIR) && ./server &
	@sleep 1
	@echo "Starting client..."
	cd $(JAVA_DIR) && $(JAVA) MainWindow
	@echo "Shutting down server..."
	@pkill -f "./server"

# Clean up generated files
.PHONY: clean
clean:
	rm -f $(CPP_DIR)/*.o $(SERVER_EXE)
	rm -f $(JAVA_DIR)/*.class
