#include "quiz.h"
#include <vector>
using namespace std;

vector<Question> loadMathQuiz() {
    return {
        {"What is 12 * 8?", {"80", "96", "108", "112"}, 'B'},
        {"Square root of 144?", {"10", "12", "14", "16"}, 'B'},
        {"15 + 27 = ?", {"40", "42", "44", "45"}, 'B'}
    };
}

vector<Question> loadGKQuiz() {
    return {
        {"Who is the Father of India?", {"Mahatma Gandhi","Jawaharlal Nehru","Subhash Bose","Bhagat Singh"}, 'A'},
        {"Capital of France?", {"Berlin","Paris","Madrid","Rome"}, 'B'},
        {"Red Planet is?", {"Venus","Mars","Jupiter","Saturn"}, 'B'}
    };
}
