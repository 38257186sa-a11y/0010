#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

// Structure to hold quiz questions
struct Question {
    string questionText;
    vector<string> options;
    char correctOption;
};

// Function to shuffle options for randomness
void shuffleOptions(Question &q) {
    vector<string> opts = q.options;
    random_shuffle(opts.begin(), opts.end());
    q.options = opts;
    for (size_t i = 0; i < opts.size(); ++i) {
        if (opts[i] == q.options[q.correctOption - 'A'])
            q.correctOption = 'A' + i;
    }
}

// Clear console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Display a question
void displayQuestion(const Question &q) {
    cout << "\n" << q.questionText << "\n";
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
                userAnswer = 'X'; // Mark as unanswered
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

        if (userAnswer == quiz[i].correctOption) {
            cout << "\033[32mCorrect!\033[0m\n"; // Green text
            score++;
        } else {
            cout << "\033[31mIncorrect.\033[0m Correct answer: " << quiz[i].correctOption << "\n"; // Red text
        }

        cout << "---------------------------------\n";
    }

    return score;
}

// Homepage display
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
    srand(time(0));

    // Math Quiz
    vector<Question> mathsQuiz = {
        {"What is 12 * 8?", {"80", "96", "108", "112"}, 'B'},
        {"Square root of 144?", {"10", "12", "14", "16"}, 'B'},
        {"15 + 27 = ?", {"40", "42", "44", "45"}, 'B'}
    };

    // GK Quiz
    vector<Question> gkQuiz = {
        {"Who is the Father of India?", {"Mahatma Gandhi","Jawaharlal Nehru","Subhash Bose","Bhagat Singh"}, 'A'},
        {"Capital of France?", {"Berlin","Paris","Madrid","Rome"}, 'B'},
        {"Red Planet is?", {"Venus","Mars","Jupiter","Saturn"}, 'B'}
    };

    int choice;
    int totalScore = 0;

    while (true) {
        clearScreen();
        showHomePage();
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            cout << "Starting Mathematics Quiz...\n";
            totalScore += runQuiz(mathsQuiz);
        } else if (choice == 2) {
            clearScreen();
            cout << "Starting General Knowledge Quiz...\n";
            totalScore += runQuiz(gkQuiz);
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
