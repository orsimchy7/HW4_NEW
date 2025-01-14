
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
	//there is no iterator field because we can't struct it
	//on an empty list
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


	return 0;

}


void student_destroy(void* s){
	student* student_in = (student*)s;
	//now student_in is a pointer to the input student struct

	//free allocation for name
	free(student_in->name);

	//delete the list of courses with linked-list destroy func
	list_destroy(student_in->courses_list);

	free(student_in); //check if needed
}


//setters & getters

student* student_init(char* name_input, int id){

	student* new_student = (student*)malloc(sizeof(student));

	if(!new_student){
		return;
	}

	new_student->ID = id;

	new_student->name = (char*)malloc(sizeof(name_input)+1);

	if(!new_student->name){
		free(new_student);
		return;
	}

	strcpy(new_student->name, name_input);

	//list_init gets pointer to clone and destroy elements funcs.
	new_student->courses_list = list_init(course_clone , course_destroy);

	if(new_student->courses_list == NULL){
		return;
	}

}





//insert course to student courses list
int insert_course_to_list(student* s, char* c_name, int c_grade){

	/* CHECK INPUT
		- grade in range [0, 100]
		-course name should be uniqe in the list
	
	*/
	if(c_grade<0 || c_grade>100){
		return 1; //not a valid grade;
	}

	struct it* = list_begin(s->courses_list);

	while(it==!NULL){
		//there are courses in list to print
		course* c = (course*)list_get(it);
		char* tmp_name = get_course_name(c);

		if(strcmp(tmp_name, c_name)==0){
			return 1;
			//strcmp== 0 when strings equal
			//then the course is not unique- fail
		}

		it = list_next(it);
	}

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


// * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]

void print_student(student* s){

	student* student_input = (student*)s;
	printf("%s %d ", student_in->name, student_in->ID);

	struct it* = list_begin(student_in->courses_list);

	while(it==!NULL){
		//there are courses in list to print
		course* c = (course*)list_get(it);

		print_course_data(c);

		it = list_next(it);
	}


}


