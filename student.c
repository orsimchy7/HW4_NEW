
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked-list"
#include "course"


/* each student struct has name, unique ID, pointer to courses list,
pointer to iterator */
typedef struct student {
	int ID;
	char* name;
	struct list* courses_list; //course_list is a pointer to list
	struct iterator* iterator; //check if needed here
}


int student_clone(void* student_in, void** student_out){

	student* original = (student*)student_in;

	//allocate memory to clone

	student* clone = (student*)malloc(sizeof(student));

	if(!clone){
		return 1;
	}

	clone->ID = original->ID;

	clone->name = (char*)malloc(sizeof(original->name)+1);

	if(!clone->name){
		free(clone);
		return 1;
	}

	strcpy(clone->name, original->name);

	//the clone will have the same course_list pointer 
	clone->courses_list = original->courses_list

	clone->iterator = original->iterator;

	return 0;

}


void student_destroy(void* s){
	student* student_in = (student*)s;
	//now student_in is a pointer to the input student struct

	//free allocation for name
	free(student_in->name);

	//delete the list of courses with linked-list destroy func

	free(student_in->courses_list);

	free(student_in); //check if needed
}


//setters & getters

int student_init(char* name_input, int id){



}





//insert course to student courses list

/**
 * @brief Pushes a new node at the end of the list
 * @param list A pointer to list
 * @param element A pointer to the element.
 * @returns 0 on success
 * @note "list" holds a copy of "element" (clone)
 */
//int list_push_back(struct list *list, void *element);

//
int insert_course_to_list(student* s, char* c_name, int c_grade){

	//we create a course
	course* new_c = course_init(c_name, c_grade);
	if(!new_c){
		return 1;
	}

	if(list_push_back(s->courses_list, new_c)==1){
		course_destroy(new_c);
		return 1;
	}

	return 0;
	

}



//create a new course struct. return 1 if failed.
int course_init(char* name, int grade_in);