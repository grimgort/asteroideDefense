# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté libhello
project(AsteroideDefense)

# Crée des variables avec les fichiers à compiler
set(SRCS
    *.cpp
    )
    
set(HEADERS
    *.h
    )

add_library(AsteroideDefense ${SRCS} ${HEADERS})
target_compile_features(AsteroideDefense PUBLIC cxx_nullptr)