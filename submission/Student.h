#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>




enum EntryType {Legitimate, Empty, Deleted};


struct Student
{
    int key;
    std::string name;
    double gpa;
    enum EntryType status;
};

#endif
