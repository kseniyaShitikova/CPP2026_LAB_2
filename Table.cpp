#include "Table.h"
#include <iostream>
#include <iomanip>

void publishTable(const std::vector<Student>& students) {
    std::cout << ">>>ТАБЛИЦА УСПЕВАЕМОСТИ<<<" << std::endl;
    std::cout << "   " << std::endl;
    std::cout << std::left << std::setw(20) << "Имя студента"
        << "Решено задач" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    for (const auto& student : students) {
        std::cout << std::left << std::setw(20) << student.getName()
            << student.getSolvedCount() << std::endl;
    }
    std::cout << "---------------------------------------------" << std::endl;
}
