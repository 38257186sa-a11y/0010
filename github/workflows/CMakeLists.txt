cmake_minimum_required(VERSION 3.10)
project(QuizHub)

set(CMAKE_CXX_STANDARD 17)

add_executable(quiz_website
    main.cpp
    quiz.cpp
    utils.cpp
    categories.cpp
)
