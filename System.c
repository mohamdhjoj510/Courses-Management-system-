#include <stdio.h>
#include <stdlib.h>

#define QUIT 0
#define INSERT_STUDENT 1
#define DELETE_STUDENT 2
#define LUCKY_STUDENT 3
#define CHANGE_RATIO 4
#define PRINT_LIST 5
#define MAX_GRADE 100
#define MIN_GRADE 0
#define PASSING_GRADE 60
#define MAX_RATIO 1
#define MIN_RATIO 0
#define MAX_ID 99999
#define MIN_ID 10000

/*PROGRAM INSERT MESSAGES*/
#define INSERT_ID "insert student ID\n"
#define INSERT_HW "insert hw grade\n"
#define INSERT_EXAM "insert exam grade\n"
#define REMOVE_STUDENT "Enter student to expunge from records:\n"
#define NEW_PROPORTION "New homework grade proportion\n"

/*PROGRAM ERROR MESSAGES*/
#define INVALID_ID "Invalid student id try_again: value between 10,000 and 99,999\ninsert student ID\n"
#define INVALID_HW "Invalid hw grade: value between 0 and 100\ninsert hw grade\n"
#define INVALID_EXAM "Invalid exam grade: value between 0 and 100\ninsert exam grade\n"
#define INVALID_PROPRTION "Proportion must be a value between 0 and 1.\n"
#define INVALID_SELECTION "Invalid Selection\n"

double ratio = 0.3; /*THIS VARIABLE IS THE FIRST HOMEWORK RATIO*/

/*THIS STRUCT REPRESENT STUDENT DETAILS IN THE MUSIC CLASS*/
typedef struct music_student
{
    int student_ID;
    double hw_average;
    int exam_grade;
    int final_grade;
    struct music_student* next;
} Music_student;

/*FUNCTION DEFINITIONS*/
void catalog();
void end();
int take_selection();
int my_round(double final_grade);
int final_ratio(Music_student* st, double ratio);
void insertIntoList(Music_student** head);
void print_list(Music_student* head);
void removeFromList(Music_student** head);
void lucky_student(Music_student* head);
void new_ratio();
void updateGrades(Music_student** head, double ratio);

/**MAIN FUNCTIN**/
int main()
{
    Music_student* head = NULL;
    int selection;

    catalog();/*FUNCTION CALL*/

    while (1)
    {
        selection=take_selection();
        if(selection==QUIT)
        {
            end();
            return 0;
        }
        if(selection==INSERT_STUDENT)
        {
            insertIntoList(&head);
            continue;/*ENTER SELECTION AGAIN*/
        }
        if(selection==DELETE_STUDENT)
        {
            removeFromList(&head);
            continue;
        }
        if(selection==LUCKY_STUDENT)
        {
            lucky_student(head);
            continue;
        }
        if(selection==CHANGE_RATIO)
        {
            new_ratio();
            updateGrades(&head, ratio);
            continue;
        }
        if(selection==PRINT_LIST)
        {
            print_list(head);
            continue;
        }
        printf(INVALID_SELECTION);/*UNKNOW SELECTION*/
        continue;
    }
    return 0;
}

/**
*catalog FUNCTION
*THIS FUNCTION USED TO PRINT THE SELECTION OPTIONS FOR THE USER
*/
void catalog()
{
    printf("Course Management Menu\n");
    printf("Please choose among the following:\n");
    printf("***\n");
    printf("0: Quit.\n");
    printf("1: Insert student at first place on the list.\n");
    printf("2: Delete by ID.\n");
    printf("3: Find lucky student.\n");
    printf("4: Change homework exam ratio.\n");
    printf("5: Print List.\n");
}

/**
*end FUNCTION
THIS FUNCTION IS USED TO PRINT THE END PROGRAM MESSAGE .
*/
void end()
{
    printf("bye bye!");
    return;
}

/**
*take_selection FUNCTION
THIS FUNCTION IS USED TO TAKE A SELECTION FROM THE USER AND RETURN IT TO MAIN
*/
int take_selection()
{
    int selection;
    scanf("%d", &selection);
    return selection;
}

/**
my_round FUNCTION
THIS FUNCTION IS TAKES THE FINAL GRADE FOR EACH STUDENT AND ROUND IT (MAKING IT WITHOUT AN INTEGER)
*@ final_grade
*@ return values : round .
*/

int my_round(double final_grade)
{
    int round = final_grade;
    if (final_grade - round >= 0.5)/*CHECKING IF THE FINAL GRADE IS CONTAINS A FRACTION GREATER THAN HALF*/
    {
        return round + 1; /*RETURN FINAL GRADE ROUNDED UP*/
    }
    else
    {
        return round; /*RETURN FINAL GRADE ROUNDED DOWN*/
    }
}

/**
final_grade FUNCTION
THIS FUNCTION IS USED TO CALCULATE THE FINAL GRADE(NOT ROUNDED) FOR EACH STUDENT BASED ON THE HOMEWORK&EXAM RATIO AND CALLING MY ROUND FUNCTION TO ROUND IT.
*@ Music_student* st : MUSIC STUDENT DETAILS .
*@ grade : HOMEWORK GRADE RATIO .
*@ return values :  my_round FUNCTION CALL .
*/
int final_grade(Music_student* st, double grade)
{
    return my_round((st->hw_average * grade) + (st->exam_grade * (1 - grade))); /*CALCULATING FINAL GRADE*/
}

/**
insertIntoList FUNCTION
*THIS FUNCTION IS USED TO TAKE EACH STUDENT DETAILS (ID/HW_GRADE/EXAM_GRADE) WHEN CHOOSING SELECTION "1".
*@ Music_student** head : FIRST STUDENT IN THE LIST.
*@ return values : - .
*/
void insertIntoList(Music_student** head)
{
    Music_student* newNode = (Music_student*) malloc (sizeof (Music_student));
    int id;
    double hw_grade;
    int exam_grade;

    printf(INSERT_ID);
    scanf("%d", &id);/*TAKING ID*/
    while (id < MIN_ID || id > MAX_ID)
    {
        printf(INVALID_ID);
        scanf("%d", &id);
    }
    newNode->student_ID = id;

    printf(INSERT_HW);
    scanf("%lf", &hw_grade);/*TAKING HOMEWORK GRADE*/

    while (hw_grade < MIN_GRADE || hw_grade > MAX_GRADE)
    {
        printf(INVALID_HW);
        scanf("%lf", &hw_grade);
    }
    newNode->hw_average = hw_grade;

    printf(INSERT_EXAM);
    scanf("%d", &exam_grade);/*TAKING EXAM GRADE*/

    while (exam_grade < MIN_GRADE || exam_grade > MAX_GRADE)
    {
        printf(INVALID_EXAM);
        scanf("%d", &exam_grade);
    }
    newNode->exam_grade = exam_grade;
    newNode->final_grade = final_grade(newNode, ratio);
    newNode->next = *head;
    *head = newNode;
}

/**
*print_list FUNCTION
*THIS FUNCTION IS PRINT THE LIST AFTER CHOOSING OPTION "5".
*@ Music_student** head : FIRST STUDENT IN THE LIST.
*@ return values : - .
*/
void print_list(Music_student* head)
{
    Music_student* cur = head;
    while (cur!=NULL)/*PRINTING LIST TO THE END*/
    {
        printf("Student Id: %d\n", cur->student_ID);
        printf("Final Grade: %d\n", cur->final_grade);
        cur = cur->next;
    }
}

/**
*removeFromList FUNCTION
*THIS FUNCTION IS USED TO REMOVE A STUDENT FROM THE LIST BY THE CHOOSIN ID .
*@ Music_student** head : FIRST STUDENT IN THE LIST.
*@ return values : - .
*/
void removeFromList(Music_student** head)
{
    int id;
    Music_student* cur = *head;
    Music_student* prev = NULL;
    printf(REMOVE_STUDENT);
    scanf("%d", &id);
    while (cur!=NULL)/*REMOVING STUDENT FROOM LIST*/
    {
        if (cur->student_ID == id)
        {
            if (prev == NULL)
            {
                *head = (*head)->next;
            }
            else
            {
                prev->next = cur->next;
            }
            free(cur);/*FREEING MEMORY*/
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    return;
}

/**
*lucky_student FUNCTION
*THIS FUNCTION IS USED FIND THE LUCKY STUDENT IN THE LIST THAT PASSED THE COURSE WITH THE LOWEST FINAL GRADE AVERAGE.
*@ Music_student** head : FIRST STUDENT IN THE LIST.
*@ return values : - .
*/
void lucky_student(Music_student* head)
{
    Music_student* cur = head;
    Music_student* min = NULL;
    if (head==NULL)/*CASE OF EMPTY LIST*/
    {
        printf("No student passed the music class.\n");
        return;
    }
    while(cur!=NULL)/*FINDING THE STUDENT WHO PASSED THE COURSE WITH THE LOWEST GRADE*/
    {
        if (min == NULL && cur->final_grade >= PASSING_GRADE)
        {
            min = cur;
        }
        if(cur->final_grade >= PASSING_GRADE && cur->final_grade < min->final_grade)
        {
            min = cur;
        }
        cur = cur->next;
    }
    if(min!=NULL)/*IF THERE IS A STUDENT WHO PASSED THE COURSE*/
    {
        printf("Student with id %d is the luckiest.\n", min->student_ID);
        printf("The grade of lucky student was %d.\n", min->final_grade);
    }
    else
    {
        printf("No student passed the music class.\n");
    }
}

/**
* new_ratio FUNCTION
*THIS FUNCTION IS USED TO TAKE THE NEW HOMEWORK RATIO WHEN CHOOSING THE OPTION "4" .
*@ return values : - .
*/
void new_ratio()
{
    printf(NEW_PROPORTION);
    scanf("%lf", &ratio);/*TAKING NEW RATIO*/
    while(ratio <= MIN_RATIO || ratio >= MAX_RATIO)
    {
        printf(INVALID_PROPRTION);
        scanf("%lf", &ratio);
    }
    return;
}

/**
* updateGrades FUNCTION
*THIS FUNCTION IS USED UPDATE THE NEW FINAL GRADE FOR EACH STUDENT AFTER CHANGING THE HOMEWORK RATIO (CHOOSEN THE OPTION "4").
*@ Music_student** head : FIRST STUDENT IN THE LIST.
*@ grade : THE NEW HOMEWORK RATIO .
*@ return values : - .
*/
void updateGrades(Music_student** head, double grade)
{
    Music_student* cur = *head;
    while(cur!=NULL)
    {
        cur->final_grade = final_grade(cur, grade);/*FUNCTION CALL TO UPDATE GRADES*/
        printf("overall_grade: %d\n", cur->final_grade);
        cur = cur->next;
    }
    return;
}

