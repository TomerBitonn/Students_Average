/* This program calculates students averages scores and overall
   average of all students. It divides them into two groups with
   a score greater/equal to the average and less than the average. */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct student_init_data
{
	int id;
	int* grades;
	int tests;
}StudentInitData;

typedef struct student_processed_data
{
	int id;
	double student_average;
}StudentProcessData;

typedef struct statistics
{
	StudentProcessData* above_average;
	StudentProcessData* below_average;
	int above_size;
	int below_size;
	double total_average;
}Statistics;

int* Input_Data(int num_of_tests);
double Student_Average(int* grades, int num_of_tests);
double Total_Average(double* averages, int num_of_tests);
void Classification(StudentInitData* students, int num_of_students, Statistics* stats);
void Print_Tab(Statistics item);
void Free_Memory(Statistics* new_students_arr, StudentInitData* students, int num_of_students);

int main()
{
	int num_of_students;
	Statistics new_students_arr;

	printf("Enter the number of students: ");
	scanf("%d", &num_of_students);

	StudentInitData* students;
	students = (StudentInitData*)malloc(num_of_students * sizeof(StudentInitData));
	if (!students) return NULL;

	for (int i = 0; i < num_of_students; i++)
	{
		printf("\nEnter student ID: ");
		scanf("%d", &students[i].id);
		printf("Enter the number of tests: ");
		scanf("%d", &students[i].tests);
		students[i].grades = Input_Data(students[i].tests);
	}

	Classification(students, num_of_students, &new_students_arr);

	Print_Tab(new_students_arr);

	Free_Memory(&new_students_arr, students, num_of_students);

	return 0;
}

int* Input_Data(int num_of_tests)
{
	int grade;
	int* grades = (int*)malloc(num_of_tests * sizeof(int));
	if (!grades) return NULL;

	for (int i = 0; i < num_of_tests; i++)
	{
		printf("Enter your grade: ");
		scanf("%d", &grade);
		grades[i] = grade;
	}
	return grades;
}

double Student_Average(int* grades, int num_of_tests)
{
	int i;
	double sum = 0;
	for (i = 0; i < num_of_tests; i++)
		sum += grades[i];
	return sum / num_of_tests;
}

double Total_Average(double* averages, int num_of_tests)
{
	int i;
	double sum = 0;
	for (i = 0; i < num_of_tests; i++)
		sum += averages[i];
	return sum / num_of_tests;
}

void Classification(StudentInitData* students, int num_of_students, Statistics* stats)
{
	int i, above_size = 0, below_size = 0;
	StudentProcessData* arr_above, * arr_below;

	double* averages = (double*)malloc(num_of_students * sizeof(double)); // dynamic memory averages array
	if (!averages) return NULL;

	for (i = 0; i < num_of_students; i++)
		averages[i] = Student_Average(students[i].grades, students[i].tests);

	stats->total_average = Total_Average(averages, num_of_students); // total average for all of the students

	arr_above = (StudentProcessData*)malloc(num_of_students * sizeof(StudentProcessData));
	arr_below = (StudentProcessData*)malloc(num_of_students * sizeof(StudentProcessData));
	if (!arr_above || !arr_below) return NULL;

	for (i = 0; i < num_of_students; i++)
	{
		if (averages[i] < stats->total_average)
		{
			arr_below[below_size].student_average = averages[i];
			arr_below[below_size++].id = students[i].id;
		}
		else if (averages[i] >= stats->total_average)
		{
			arr_above[above_size].student_average = averages[i];
			arr_above[above_size++].id = students[i].id;
		}
	}

	stats->above_average = (StudentProcessData*)realloc(arr_above, above_size * sizeof(StudentProcessData));
	stats->below_average = (StudentProcessData*)realloc(arr_below, below_size * sizeof(StudentProcessData));
	if (!stats->above_average || !stats->below_average) return NULL;

	stats->above_size = above_size;
	stats->below_size = below_size;
	free(averages);
}

void Print_Tab(Statistics item)
{
	int i;
	printf("\nAbove average grades: %d\n", item.above_size);
	for (i = 0; i < item.above_size; i++)
		printf("\nID = %d\nAverage = %.02f\n", item.above_average[i].id, item.above_average[i].student_average);
	printf("\n");

	printf("\nBelow average grades: %d\n", item.below_size);
	for (i = 0; i < item.below_size; i++)
		printf("\nID = %d\nAverage = %.02f\n", item.below_average[i].id, item.below_average[i].student_average);
	printf("\n");

	printf("The total average is: %.02f\n", item.total_average);
}

void Free_Memory(Statistics* new_students_arr, StudentInitData* students, int num_of_students)
{
	for (int i = 0; i < num_of_students; i++)
		free(students[i].grades);

	free(students);
	students = NULL;

	free(new_students_arr->above_average);
	new_students_arr->above_average = NULL;

	free(new_students_arr->below_average);
	new_students_arr->below_average = NULL;
}
