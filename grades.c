#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list"
#include "grades.h"
//later - remove them and implement everything here
#include "course.h"
#include "student.h"

typedef struct grades {
  struct list* students_list,
  student_clone //functions needed?
}

//to implement:
  //1. init
  //2. destroy

int grades_add_student(struct grades *grades, const char *name, int id) {
  if (!grades) return; //what to return exactly? (same problem as in cource.c ...)
  //look for id in grades & if exist return failure;
  struct student newStudent = student_init(name, id);
  return val = list_push_back(grades->students_list, newStudent);
}
