#include <iostream>
#include "quiz.h"
#include "utils.h"
#include <vector>

using namespace std;

void showHomePage() {
    cout << "=============================\n";
    cout << "      Welcome to Quiz Hub    \n";
    cout << "=============================\n";
    cout << "1. Mathematics\n";
    cout << "2. General Knowledge\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    int totalScore = 0;

    while (true) {
        clearScreen();
        showHomePage();
        cin >> choice;

        vector<Question> quiz;
        if (choice == 1) {
            quiz = loadMathQuiz();
            totalScore += runQuiz(quiz);
        } else if (choice == 2) {
            quiz = loadGKQuiz();
            totalScore += runQuiz(quiz);
        } else if (choice == 3) {
            cout << "Thank you for playing! Your total score: " << totalScore << endl;
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }

        cout << "\nPress Enter to return to homepage...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}
