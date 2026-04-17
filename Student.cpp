#include "Student.h"
#include "QuadraticEquation.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdlib>

Student::Student(const std::string& name_, StudentType type_)
    : name(name_), type(type_), solvedCount(0) {
}

std::string Student::getName() const { return name; }
StudentType Student::getType() const { return type; }
int Student::getSolvedCount() const { return solvedCount; }
void Student::incrementSolvedCount() { solvedCount++; }

std::vector<Student> loadStudents(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return students;
    }

    std::string name, typeStr;
    while (file >> name >> typeStr) {
        StudentType type;

        std::string lowerType = typeStr;
        for (char& c : lowerType) {
            c = std::tolower(c);
        }

        if (lowerType == "good") {
            type = GOOD;
        }
        else if (lowerType == "middle") {
            type = MIDDLE;
        }
        else if (lowerType == "bad") {
            type = BAD;
        }
        else {
            std::cerr << "Неизвестный тип студента: " << typeStr << " для " << name << ". Использую Good" << std::endl;
            type = GOOD;
        }
        students.push_back(Student(name, type));
    }

    file.close();
    std::cout << "Загружено студентов: " << students.size() << std::endl;
    return students;
}

std::string getStudentAnswer(const QuadraticEquation& eq, StudentType type,
    double correctX1, double correctX2, int rootsCount) {

    if (type == GOOD) {
        return eq.formatAnswer(correctX1, correctX2, rootsCount);
    }
    else if (type == BAD) {
        return "x = 0";
    }
    else {
        if (std::rand() % 2 == 0) {
            return eq.formatAnswer(correctX1, correctX2, rootsCount);
        }
        else {
            return "x = 1";
        }
    }
}
