#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class QuadraticEquation;

enum StudentType {
    GOOD,
    MIDDLE,
    BAD
};

class Student {
private:
    std::string name;
    StudentType type;
    int solvedCount;

public:
    Student(const std::string& name_, StudentType type_);
    std::string getName() const;
    StudentType getType() const;
    int getSolvedCount() const;
    void incrementSolvedCount();

};

std::vector<Student> loadStudents(const std::string& filename);
std::string getStudentAnswer(const QuadraticEquation& eq, StudentType type,
    double correctX1, double correctX2, int rootsCount);

#endif
