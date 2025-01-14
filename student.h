#ifndef STUDENT_H
#define STUDENT_H

/* Defines the type "size_t", which is the standard for sizes in C */
#include <stddef.h>


typedef struct student; //defined in course.c to hide from user

//functions needed by linked-list
int student_clone(void* student_in, void** student_out);
void student_destroy(void* s);

//getters and setters

//create a new student struct. return pointer to the student
//struct
student* student_init(char* name_input, int id);


//checks ig grade is in range [0, 100] and if
//c_name is unique in the courses_list
int insert_course_to_list(student* s, char* c_name, int c_grade);


//returns 1 when failed
void print_student(student* s);

#endif
