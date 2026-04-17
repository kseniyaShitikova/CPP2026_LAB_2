#include "QuadraticEquation.h"
#include "Student.h"
#include "Letter.h"
#include "Table.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <locale.h>

int main() {
    std::srand(std::time(0));
    setlocale(LC_CTYPE, "Russian");

    std::vector<QuadraticEquation> equations;
    std::ifstream file("equations.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл equations.txt" << std::endl;
        return 1;
    }

    double a, b, c;
    while (file >> a >> b >> c) {
        equations.push_back(QuadraticEquation(a, b, c));
    }
    file.close();
    std::cout << "Загружено уравнений: " << equations.size() << std::endl;

    if (equations.empty()) {
        std::cerr << "Нет уравнений для проверки. Программа завершена." << std::endl;
        return 1;
    }

    std::vector<Student> students = loadStudents("students.txt");
    if (students.empty()) {
        std::cerr << "Программа завершена." << std::endl;
        return 1;
    }

    std::cout << std::endl;

    std::vector<Letter> letters = generateLetters(students, equations);

    checkLetters(students, letters);

    publishTable(students);

    return 0;
}
