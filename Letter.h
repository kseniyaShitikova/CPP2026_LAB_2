#pragma once
#ifndef LETTER_H
#define LETTER_H

#include "QuadraticEquation.h"
#include "Student.h"
#include <string>
#include <vector>

class Letter {
private:
    QuadraticEquation equation;
    std::string studentAnswer;
    std::string studentName;

public:
    Letter(const QuadraticEquation& eq, const std::string& answer, const std::string& name);
    QuadraticEquation getEquation() const;
    std::string getStudentAnswer() const;
    std::string getStudentName() const;
};

std::vector<Letter> generateLetters(const std::vector<Student>& students,
    const std::vector<QuadraticEquation>& equations);
void checkLetters(std::vector<Student>& students, const std::vector<Letter>& letters);

#endif
