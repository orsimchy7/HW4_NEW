#ifndef STUDENT_H
#define STUDENT_H

/* Defines the type "size_t", which is the standard for sizes in C */
#include <stddef.h>


typedef struct student; //defined in course.c to hide from user

//functions needed by linked-list
int student_clone(void* student_in, void** student_out);
void student_destroy(void* s);

//getters and setters

//create a new student struct. return 1 if failed.
int student_init(char* name_input, int id);




//======= NEED TO CONTINUE=======
//print

#endif
