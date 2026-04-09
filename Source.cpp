#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <locale.h>

using namespace std;

struct QuadraticEquation {
    double a, b, c;
};

struct Letter {
    QuadraticEquation equation;
    string studentAnswer;
    string studentName;
};

enum StudentType {
    GOOD,
    MIDDLE,
    BAD
};

struct Student {
    string name;
    StudentType type;
    int solvedCount;
};

int solveEquation(double a, double b, double c, double& x1, double& x2) {
    if (fabs(a) < 1e-9) {
        return -1;
    }

    double d = b * b - 4 * a * c;

    if (d < 0) {
        return 0;
    }

    if (fabs(d) < 1e-9) {
        x1 = -b / (2 * a);
        return 1;
    }

    x1 = (-b - sqrt(d)) / (2 * a);
    x2 = (-b + sqrt(d)) / (2 * a);
    return 2;
}

string formatAnswer(double x1, double x2, int rootsCount) {
    if (rootsCount == 0) {
        return "net korney";
    }
    else if (rootsCount == 1) {
        return "x = " + to_string(x1);
    }
    else {
        if (x1 > x2) {
            swap(x1, x2);
        }
        return "x1 = " + to_string(x1) + ", x2 = " + to_string(x2);
    }
}

string getStudentAnswer(const QuadraticEquation& eq, StudentType type,
    double correctX1, double correctX2, int rootsCount) {

    if (type == GOOD) {
        return formatAnswer(correctX1, correctX2, rootsCount);
    }
    else if (type == BAD) {
        return "x = 0";
    }
    else {
        if (rand() % 2 == 0) {
            return formatAnswer(correctX1, correctX2, rootsCount);
        }
        else {
            return "x = 1";
        }
    }
}

vector<QuadraticEquation> loadEquations(const string& filename) {
    vector<QuadraticEquation> equations;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return equations;
    }

    double a, b, c;
    while (file >> a >> b >> c) {
        equations.push_back({ a, b, c });
    }

    file.close();
    cout << "Загружено уравнений: " << equations.size() << endl;
    return equations;
}

vector<Student> loadStudents(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return students;
    }

    string name, typeStr;
    while (file >> name >> typeStr) {
        StudentType type;
        if (typeStr == "Good" || typeStr == "GOOD" || typeStr == "good") {
            type = GOOD;
        }
        else if (typeStr == "Middle" || typeStr == "MIDDLE" || typeStr == "middle") {
            type = MIDDLE;
        }
        else if (typeStr == "Bad" || typeStr == "BAD" || typeStr == "bad") {
            type = BAD;
        }
        else {
            cerr << "Неизвестный тип студента: " << typeStr << " для " << name << ". Использую Good" << endl;
            type = GOOD;
        }
        students.push_back({ name, type, 0 });
    }

    file.close();
    cout << "Загружено студентов: " << students.size() << endl;
    return students;
}

vector<Letter> generateLetters(const vector<Student>& students,
    const vector<QuadraticEquation>& equations) {
    vector<Letter> letters;

    for (const auto& student : students) {
        for (const auto& eq : equations) {
            double x1, x2;
            int rootsCount = solveEquation(eq.a, eq.b, eq.c, x1, x2);

            string answer = getStudentAnswer(eq, student.type, x1, x2, rootsCount);

            letters.push_back({ eq, answer, student.name });
        }
    }

    cout << "Сгенерировано писем: " << letters.size() << endl;
    return letters;
}

void checkLetters(vector<Student>& students, const vector<Letter>& letters) {
    for (const auto& letter : letters) {
        double correctX1, correctX2;
        int rootsCount = solveEquation(letter.equation.a, letter.equation.b,
            letter.equation.c, correctX1, correctX2);

        string correctAnswer = formatAnswer(correctX1, correctX2, rootsCount);

        for (auto& student : students) {
            if (student.name == letter.studentName) {
                if (letter.studentAnswer == correctAnswer) {
                    student.solvedCount++;
                }
                break;
            }
        }
    }
}

void publishTable(const vector<Student>& students) {
    cout << ">>>ТАБЛИЦА УСПЕВАЕМОСТИ<<<" << endl;
    cout << "   " << endl;
    cout << left << setw(20) << "Имя студента"
        << "Решено задач" << endl;
    cout << "----------------------------------------------" << endl;

    for (const auto& student : students) {
        cout << left << setw(20) << student.name
            << student.solvedCount << endl;
    }
    cout << "---------------------------------------------" << endl;
}

int main() {
    srand(time(0));
    setlocale(LC_CTYPE, "Russian");

    vector<QuadraticEquation> equations = loadEquations("equations.txt");
    if (equations.empty()) {
        cerr << "Нет уравнений для проверки. Программа завершена." << endl;
        return 1;
    }

    vector<Student> students = loadStudents("students.txt");
    if (students.empty()) {
        cerr << "Программа завершена." << endl;
        return 1;
    }

    cout << endl;

    vector<Letter> letters = generateLetters(students, equations);

    checkLetters(students, letters);

    publishTable(students);

    return 0;
}