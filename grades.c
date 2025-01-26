#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "linked-list.h"
#include "grades.h"


//=========Course ADT==========
typedef struct course* Course; 


struct course {
	int grade;
	char* course_name;
};


//2 funcs of courses - USER FUNCTIONS for courses list

int course_clone(void* course_in, void** course_out){

	//cast void* to course*
	Course original = (Course)course_in;

	//allocate memory to the clone, clone is a pointer to a new course
	Course clone = (Course)malloc(sizeof(struct course));

	if(!clone){
		return 1;
	}

	clone->grade = original->grade;

	clone->course_name = (char*)malloc(sizeof(original->course_name)+1);

	if(!clone->course_name){
		free(clone);
		return 1; 
	}

	strcpy(clone->course_name, original->course_name);

	//config course_out
	*course_out = (void*)clone;
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
//init new course.
Course course_init(const char* name, int grade_in){
	Course new_c = (Course)malloc(sizeof(struct course));

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
		return 1; //course not exist. 
	}
	fprintf(stdout, " %s %d", c->course_name, c->grade);
	return 0; //success
}

int get_course_grade(Course c) {
	if(!c){
		return -1; //course not exist. 
	}
	return c->grade;
}



char* get_course_name(Course c){

	//if(!c){
	//	return;
	//}

	return c->course_name;
}

//=========Course ADT END==========


//=========Student ADT==========
/* each student struct has name, unique ID, pointer to courses list,
pointer to iterator */
typedef struct student* Student; //defined in course.c to hide from user


struct student {
	int ID;
	char* name;
	struct list* courses_list; //course_list is a pointer to list
	//there is no iterator field because we can't struct it
	//on an empty list
};


int student_clone(void* student_in, void** student_out){

	Student original = (Student)student_in;
	//now original is a pointer to a student struct (student*)

	//allocate memory to clone
	Student clone = (Student)malloc(sizeof(struct student));

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
	clone->courses_list = original->courses_list;

	*student_out = (void*)clone;
	//now student_out it a pointer to a pointer to student

	return 0;
}


void student_destroy(void* s){
	Student student_in = (Student)s;
	//now student_in is a pointer to the input student struct

	//free allocation for name
	free(student_in->name);

	//delete the list of courses with linked-list destroy func
	list_destroy(student_in->courses_list);

	free(student_in); //check if needed
}


//setters & getters

Student student_init(const char* name_input, int id){

	Student new_student = (Student)malloc(sizeof(struct student));

	if(!new_student){
		return NULL;
	}

	new_student->ID = id;

	new_student->name = (char*)malloc(sizeof(name_input)+1);

	if(!new_student->name){
		free(new_student);
		return NULL;
	}

	strcpy(new_student->name, name_input);

	//list_init gets pointer to clone and destroy elements funcs.
	new_student->courses_list = list_init(course_clone , course_destroy);

	if(new_student->courses_list == NULL){
		return NULL;
	}

	return new_student;

}





//insert course to student courses list
int insert_course_to_list(Student s, const char* c_name, int c_grade){

	/* CHECK INPUT
		- grade in range [0, 100]
		-course name should be uniqe in the list
	
	*/
	if(c_grade<0 || c_grade>100){
		return 1; //not a valid grade;
	}

	struct iterator* it = list_begin(s->courses_list);

	while(it){
		//there are courses in list
		Course c = (Course)list_get(it);
		char* tmp_name = get_course_name(c);

		if(strcmp(tmp_name, c_name)==0){
			return 1;
			//strcmp== 0 when strings equal
			//then the course is not unique- fail
		}

		it = list_next(it);
	}

	//we create a course
	Course new_c = course_init(c_name, c_grade);
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

void print_student(Student s){

	fprintf(stdout, "%s %d:", s->name, s->ID);

	struct iterator* it = list_begin(s->courses_list);

	while(it){
		//there are courses in list to print
		Course c = (Course)list_get(it);

		print_course_data(c);

		it = list_next(it);
	}

}

//=====Student ADT END==========


typedef struct grades {
  struct list* students_list;
};

struct grades* grades_init(){

	struct grades* g = (struct grades*)malloc(sizeof(struct grades));  // Allocate memory for g
    if (!g) {
        return NULL;  
    }

	g->students_list = list_init(student_clone , student_destroy);
	//check if this is the right way to transfer pointers to funcs
	if(g->students_list == NULL){
		return NULL;
	}

	return g;
}

void grades_destroy(struct grades *grades) {

  	list_destroy(grades->students_list);
}

int grades_add_student(struct grades* grades, const char *name, int id) {
  if (!grades){
  	return 1;
  } 
  
  //check if id is new in the list
  struct iterator* it = list_begin(grades->students_list);

	while(it){
		//there are courses in list to print
		Student s = (Student)list_get(it);
		int tmp_id = s->ID;

		if(tmp_id == id){
			return 1;
			//id is not uniqe- fail
		}

		it = list_next(it);
	}
	//

  	Student newStudent = student_init(name, id);
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
	struct iterator* it = list_begin(grades->students_list);
	Student s;
	while(it){
		//there are courses in list to print
		s = (Student)list_get(it);
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

//returns -1 on error (and when fails? check)
float grades_calc_avg(struct grades *grades, int id, char **out){
	if (!grades) {
		return -1;
	}
	float avg = 0;
	int found = 0;
	struct iterator* itSTUDENT = list_begin(grades->students_list);
	while(itSTUDENT){
		//keep searching
		Student s = (Student)list_get(itSTUDENT);
		int potentialID = s->ID;
		if (potentialID == id){
			found = 1;
			break;
		}
		itSTUDENT = list_next(itSTUDENT);
	}
	if (found) {
		//setting string out by derefrence & allocating memory
		Student s = (Student)list_get(itSTUDENT);
		*out = (char*)malloc(sizeof(s->name)+1);
		if (!(*out)) {
			return -1; //error. *out = NULL
		}
		strcpy(*out, s->name);
		
		//averging
		size_t courseNum = list_size(s->courses_list); //check it
		struct iterator* itCOURSE = list_begin(s->courses_list);
		while(itCOURSE){
			//keep averging courses
			Course c = (Course)list_get(itCOURSE);
			int course_grd = c->grade;
			avg = avg + course_grd/courseNum;
			itCOURSE = list_next(itCOURSE);
		}
		return avg;
	}
	else { //no student with desired id
		*out = NULL;
		return -1;
	}
}


int grades_print_student(struct grades *grades, int id){
	if(!grades){
		return 1;
	}

	//search for the student struct with the input id
	struct iterator* it = list_begin(grades->students_list);
	Student s;
	while(it){
		//there are courses in list to print
		s = (Student)list_get(it);
		int tmp_id = s->ID;


		if(tmp_id == id){
			//we found the student with the input id
			print_student(s);
			return 0;
		}

		it = list_next(it);
	}


	//if we finished running over the while loop
	//without return from the if condition
	//it means that the wanted student doesnt exists
	return 1;

}

int grades_print_all(struct grades *grades) {
	if (!grades) return 1;
	struct iterator* itSTUDENT = list_begin(grades->students_list);
	while(itSTUDENT){
		//keep printing students data
		Student student = (Student)list_get(itSTUDENT);
		print_student(student);
		struct iterator* itCOURSE = list_begin(student->courses_list);
		while(itCOURSE){
			//keep printing courses
			Course course = (Course)list_get(itCOURSE);
			print_course_data(course);
			itCOURSE = list_next(itCOURSE);
			if (itCOURSE){
				fprintf(stdout, ",");
			}
		}
		fprintf(stdout, "\n");
		itSTUDENT = list_next(itSTUDENT);
	}
	return 0;
}
