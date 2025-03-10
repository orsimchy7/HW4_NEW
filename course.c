
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* courses user-function declarations */
//int course_clone(void *course_in, void **course_out);
//void destroy_course(void* course);


struct course {
	int grade;
	char* course_name;
}


//2 funcs of courses - USER FUNCTIONS for courses list

int course_clone(void* course_in, void** course_out){

	//cast void* to course*
	Course original = (Course)course_in;

	//allocate memory to the clone, clone is a pointer to a new course
	Course clone = (Course)malloc(sizeof(course));

	if(!clone){
		return 1;
	}

	clone->grade = original->grade;

	clone->course_name = (char*)malloc(sizeof(original->course_name)+1);

	if(!clone->course_name){
		free(clone);
		return 1; 
	}

	strcpy(clone->course_name, orignal->course_name);

	//config course_out
	*course_out = clone;
	/*now course_out is a pointer to a pointer of a course.
	because clone is a pointer to course struct */

	return 0;
}


void course_destroy(void* c){
	if(!c){
		return;
	}

	//casting - course_in i a corse* (pointer to the input course)
	Course course_in = (Course)c;

	free(course_in->course_name);

	free(course_in);

}


//functions of course to get and set values:
	//1. setters
//init new course. return 1 if fail
Course course_init(char* name, int grade_in){
	Course new_c = (Course)malloc(sizeof(course));

	if(!new_c){
		return NULL;
	}

	new_c->grade = grade_in;

	new_c->course_name = (char*)malloc(sizeof(name)+1);

	if(!new_c->course_name){
		free(new_c);
		return NULL;
	}

	strcpy(new_c->course_name, name);

	return new_c;

}
	//2. getters
//return 0 when success
int print_course_data(Course c){
	if(!c){
		return; //course not exist. return what?
	}
	printf(" %s %d", course->course_name, course->grade);
	return 0; //success
}

int get_course_grade(Course c) {
	if(!c){
		return; //course not exist. return what?
	}
	return course->grade;
}



char* get_course_name(Course c){

	if(!c){
		return;
	}

	return c->course_name;
}
