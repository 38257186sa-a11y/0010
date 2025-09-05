#include "utils.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Clear console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Print colored text
void coloredText(const string &text, const string &color) {
    if (color == "green")
        cout << "\033[32m" << text << "\033[0m" << endl;
    else if (color == "red")
        cout << "\033[31m" << text << "\033[0m" << endl;
    else
        cout << text << endl;
}
