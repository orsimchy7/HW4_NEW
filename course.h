#ifndef COURSE_H
#define COURSE_H

/* Defines the type "size_t", which is the standard for sizes in C */
#include <stddef.h>


typedef struct course* Course; //defined in course.c to hide from user

//functions needed by linked-list
int course_clone(void* course_in, void** course_out);
void course_destroy(void* c);

//getters and setters

//create a new course struct. return pointer to the course
Course course_init(char* name, int grade_in);

int get_course_grade(Course c);

char* get_course_name(Course c);


//======= NEED TO CONTINUE=======
//return 0 when success
int print_course_data(Course c);


#endif
