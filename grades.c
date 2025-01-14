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
}

//to implement:
  //1. init
  //2. destroy

struct grades* grades_init(){

	struct grades g;

	g->students_list = list_init(student_clone , student_destroy);
	//check if this is the right way to transfer pointers to funcs

	if(g->students_list == NULL){
		return NULL;
	}

	return g;
}




int grades_add_student(grades* grades, const char *name, int id) {
  if (!grades){
  	return 1;
  } 
  
  //check if id is new in the list
  struct it* = list_begin(grades->students_list);

	while(it==!NULL){
		//there are courses in list to print
		student* s = (student*)list_get(it);
		tmp_id = s->ID;

		if(tmp_id == id){
			return 1;
			//id is not uniqe- fail
		}

		it = list_next(it);
	}
	//

  	student* newStudent = student_init(name, id);
  	int val = list_push_back(grades->students_list, newStudent);
  	free(newStudent);

  	return val;
}
