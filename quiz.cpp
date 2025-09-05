#include "quiz.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

// Shuffle options for randomness
void shuffleOptions(Question &q) {
    vector<string> opts = q.options;
    random_shuffle(opts.begin(), opts.end());
    q.options = opts;
    for (size_t i = 0; i < opts.size(); ++i) {
        if (opts[i] == q.options[q.correctOption - 'A'])
            q.correctOption = 'A' + i;
    }
}

// Display a question
void displayQuestion(const Question &q) {
    cout << "\n" << q.questionText << endl;
    for (size_t i = 0; i < q.options.size(); ++i)
        cout << char('A' + i) << ". " << q.options[i] << endl;
}

// Run a quiz
int runQuiz(vector<Question> quiz) {
    int score = 0;
    shuffle(quiz.begin(), quiz.end(), default_random_engine(time(0)));

    for (size_t i = 0; i < quiz.size(); ++i) {
        displayQuestion(quiz[i]);

        char userAnswer;
        bool validInput = false;
        auto start = chrono::steady_clock::now();
        cout << "Your answer (A/B/C/D) within 20 seconds: ";

        while (!validInput) {
            auto now = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
            if (elapsed > 20) {
                cout << "\nTime's up! Moving to next question.\n";
                userAnswer = 'X';
                break;
            }

            if (cin.peek() != EOF) {
                cin >> userAnswer;
                userAnswer = toupper(userAnswer);
                if (userAnswer >= 'A' && userAnswer < 'A' + quiz[i].options.size())
                    validInput = true;
                else
                    cout << "Invalid input. Enter A/B/C/D: ";
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        if (userAnswer == quiz[i].correctOption)
            coloredText("Correct!", "green");
        else
            coloredText("Incorrect. Correct answer: " + string(1, quiz[i].correctOption), "red");

        cout << "---------------------------------\n";
    }

    return score;
}
