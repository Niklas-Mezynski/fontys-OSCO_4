#include "stdio.h"
#include "structs.h"
#include <string.h>

int printStudentToConsole(student *student);
student readStudentFromConsole();
int copyStudent(student src, student *target);

int main()
{
    course c1;
    student s1;
    strcpy(c1.courseName, "Software Engineering");
    c1.courseId = 5;
    c1.grade = 9.5;

    strcpy(s1.firstName, "Max");
    strcpy(s1.lastName, "Mustermann");
    s1.studentNumber = 1337;
    s1.course1 = c1;

    course c3;
    student s3;
    strcpy(c3.courseName, "Informatik");
    c3.courseId = 42;
    c3.grade = 5.5;

    strcpy(s3.firstName, "Hans");
    strcpy(s3.lastName, "Peter");
    s3.studentNumber = 100;
    s3.course1 = c3;

    printStudentToConsole(&s1);
    printStudentToConsole(&s3);

    printf("Copy first student to second one\n First one\n");
    copyStudent(s1, &s3);
    printStudentToConsole(&s1);
    printf("Second one\n");
    printStudentToConsole(&s3);

    student s2 = readStudentFromConsole();
    printStudentToConsole(&s2);
    return 0;
}

int printStudentToConsole(student *student)
{
    printf("Student number: %ld\n", student->studentNumber);
    printf("First name: %s\n", student->firstName);
    printf("Last name: %s\n", student->lastName);
    printf("Student's course id: %ld\n", student->course1.courseId);
    printf("Course name: %s\n", student->course1.courseName);
    printf("Course grade: %f\n", student->course1.grade);
    printf("\n");
    return 1;
}

student readStudentFromConsole()
{
    char firstName[20], lastName[20], courseName[20];
    long studentId, courseId;
    float grade;
    course c;
    student s;
    printf("Creating a new student...\n");
    printf("Enter the first name:\n");
    scanf("%s", firstName);
    printf("Enter the last name:\n");
    scanf("%s", lastName);
    printf("Enter an ID for the student:\n");
    scanf("%ld", &studentId);
    printf("Enter the course name for the student:\n");
    scanf("%s", courseName);
    printf("Enter the ID for that course:\n");
    scanf("%ld", &courseId);
    printf("Enter the grade for that course:\n");
    scanf("%f", &grade);

    c.courseId = courseId;
    strcpy(c.courseName, courseName);
    c.grade = grade;
    strcpy(s.firstName, firstName);
    strcpy(s.lastName, lastName);
    s.studentNumber = studentId;
    s.course1 = c;

    return s;
}

int copyStudent(student src, student *target)
{
    *target = src;
    return 1;
}