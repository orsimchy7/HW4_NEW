
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* courses user-function declarations */
int course_clone(void *course_in, void **course_out);
void destroy_course(void* course);


typedef struct course {
	int grade;
	char* course_name;
}


//2 funcs of courses - USER FUNCTIONS for courses list

int course_clone(void* course_in, void** course_out){

	//cast void* to course*
	course* original = (course*)course_in;

	//allocate memory to the clone, clone is a pointer to a new course
	course* clone = (course*)malloc(sizeof(course));

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
	course* course_in = (course*)c;

	free(course_in->course_name);

	free(course_in);

}


//functions of course to get and set values:

//init new course. return 1 if fail
course* course_init(char* name, int grade_in){
	course* new_c = (course*)malloc(sizeof(course));

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


