#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>

struct Question {
    std::string questionText;
    std::vector<std::string> options;
    char correctOption;
};

// Function declarations
void displayQuestion(const Question &q);
int runQuiz(std::vector<Question> quiz);

#endif
