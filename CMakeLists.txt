cmake_minimum_required(VERSION 3.24)
project(projet)

set(CMAKE_CXX_STANDARD 17)

add_executable(projet main.cpp jeu.cpp carte.h jeu.h carte.cpp pioche.cpp pioche.h borne.cpp "Rendu 2 : 14 mai/manche.cpp" "Rendu 2 : 14 mai/manche.h" manche.cpp manche.h joueur.cpp)
