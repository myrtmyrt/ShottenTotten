cmake_minimum_required(VERSION 3.25)
project(LO21_Projet)

set(CMAKE_CXX_STANDARD 17)

add_executable(LO21_Projet main.cpp
        jeu.h
        jeu.cpp
        manche.cpp
        manche.h
        carte.h
        carte.cpp
        borne.h
        borne.cpp
        joueur.h
        joueur.cpp
        pioche.h
        pioche.cpp)
