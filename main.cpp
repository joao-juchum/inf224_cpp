//
// main.cpp
// Created on 30/06/2024
//

#include <iostream>
#include <string>
#include "Multimidia.h"
using namespace std;

int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;
    

    // Test de la classe
    Multimidia* Video = new Multimidia("Video", "home/Telecom/inf224/Videos");
    Multimidia* Foto = new Multimidia("Foto", "home/Telecom/inf224/Fotos");

    std::string nameMidia1 = Video->getName();
    std::string nameMidia2 = Foto->getName();

    std::string PathMidia1 = Video->getFilePath();
    std::string PathMidia2 = Foto->getFilePath();

    std::cout << "Media 01: " << nameMidia1 << " \n \tFile path: " << PathMidia1 << "\n";
    std::cout << "Media 02: " << nameMidia2 << " \n \tFile path: " << PathMidia2 << "\n";

    return 0;
}