# Nous voulons un cmake "r�cent" pour utiliser les derni�res fonctionnalit�s
cmake_minimum_required(VERSION 3.0)

# Notre projet est �tiquet� hello
project(AsteroideDefense)

# On inclut notre biblioth�que dans le processus de CMake
add_subdirectory(src)
add_subdirectory(include)

# Cr�e des variables avec les fichiers � compiler
set(SRCS
    main.cpp
    )
    
# Notre ex�cutable
add_executable(main ${SRCS})
target_compile_features(AsteroideDefense PUBLIC cxx_nullptr)

# Et pour que l'ex�cutable fonctionne, il faut lui indiquer la biblioth�que dont il d�pend
target_link_libraries(main AsteroideDefense)