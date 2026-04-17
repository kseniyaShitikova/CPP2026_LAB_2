#include "Letter.h"
#include "QuadraticEquation.h"
#include <iostream>

Letter::Letter(const QuadraticEquation& eq, const std::string& answer, const std::string& name)
    : equation(eq), studentAnswer(answer), studentName(name) {
}

QuadraticEquation Letter::getEquation() const { return equation; }
std::string Letter::getStudentAnswer() const { return studentAnswer; }
std::string Letter::getStudentName() const { return studentName; }

std::vector<Letter> generateLetters(const std::vector<Student>& students,
    const std::vector<QuadraticEquation>& equations) {
    std::vector<Letter> letters;

    for (const auto& student : students) {
        for (const auto& eq : equations) {
            double x1, x2;
            int rootsCount = eq.solve(x1, x2);

            std::string answer = getStudentAnswer(eq, student.getType(), x1, x2, rootsCount);

            letters.push_back(Letter(eq, answer, student.getName()));
        }
    }

    std::cout << "Сгенерировано писем: " << letters.size() << std::endl;
    return letters;
}

void checkLetters(std::vector<Student>& students, const std::vector<Letter>& letters) {
    for (const auto& letter : letters) {
        double correctX1, correctX2;
        int rootsCount = letter.getEquation().solve(correctX1, correctX2);

        std::string correctAnswer = letter.getEquation().formatAnswer(correctX1, correctX2, rootsCount);

        for (auto& student : students) {
            if (student.getName() == letter.getStudentName()) {
                if (letter.getStudentAnswer() == correctAnswer) {
                    student.incrementSolvedCount();
                }
                break;
            }
        }
    }
}
