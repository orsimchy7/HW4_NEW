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
		int tmp_id = s->ID;

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


/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

	if(!grades){
		return 1;
	}

	//search for the student struct with the input id
	struct it* = list_begin(grades->students_list);
	student* s;
	while(it==!NULL){
		//there are courses in list to print
		s = (student*)list_get(it);
		int tmp_id = s->ID;


		if(tmp_id == id){
			return insert_course_to_list(s, name, grade);
			//insert_course_to_list checks for unique course name
			//and for grade in range [0, 100]. it returns 0 om success
		}

		it = list_next(it);
	}

	//if we finished running over the while loop
	//without return from the if condition
	//it means that the wanted student doesnt exists
	return 1;
}


int grades_print_student(struct grades *grades, int id){
	if(!grades){
		return 1;
	}

		//search for the student struct with the input id
	struct it* = list_begin(grades->students_list);
	student* s;
	while(it==!NULL){
		//there are courses in list to print
		s = (student*)list_get(it);
		int tmp_id = s->ID;


		if(tmp_id == id){
			//we found the student with the input id
			print_student(student s);
			return 0;
		}

		it = list_next(it);
	}


	//if we finished running over the while loop
	//without return from the if condition
	//it means that the wanted student doesnt exists
	return 1;

}