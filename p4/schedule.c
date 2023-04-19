/** 
    @file schedule.c
    @author William J Krjacovic (wjkrajco)
    This is the primary file for the program as it contains the main function. This file
    is responsible for reading in the input from the user as commands and not the file. This file
    makes sure all the commands the user enters are valid, this file also holds the test and
    comparing functions that are called to in order to sort the catalog and schedule.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "catalog.h"

/** The Size for the string that will hold the second command*/
#define SIZE_FOR_SECOND_COMMAND_STRING 12

/** The common size string in command*/
#define SIZE_FOR_COMMON_COMMAND_STRING 7

/** The small size string in command*/
#define SIZE_FOR_SMALL_COMMAND_STRING 4

/**Value for 8:30*/
#define VALUE_FOR_SMALLEST_TIME 5

/**Value for 10:00*/
#define VALUE_FOR_SECOND_SMALLEST_TIME 4

/**Value for 11:30*/
#define VALUE_FOR_THIRD_SMALLEST_TIME 3

/**Value for 1:00*/
#define VALUE_FOR_FOURTH_SMALLEST_TIME 2

/**Value for 2:30*/
#define VALUE_FOR_FIFTH_SMALLEST_TIME 1

/**Value for 4:00*/
#define VALUE_FOR_LARGEST_TIME 0

/**Size of Department String*/
#define SIZE_OF_DEPARTMENT_STRING 3

/**Size of schedule array*/
#define SCHEDULE_SIZE 10

/**Number for three arguments*/
#define TWO_ARGUMENTS_READ 2

/**Number for three arguments*/
#define THREE_ARGUMENTS_READ 3

/**Number for four arguments*/
#define FOUR_ARGUMENTS_READ 4

/**The size of dept and number array*/
#define DEPT_AND_NUMBER_TOTAL

/** The size of dept and number with a space between*/
#define DEPT_AND_NUMBER_SPACE 7








/** 
    This function processes the arguments that were given into the program and makes sure
    there is at least a file for the program to read.

    @param argc the number of arguments that were given when running the program.
    @param argv An array of strings that were the arguments given at start
*/
static void processArgs(int argc, char*argv[])  
{
    if ((argc - 1) < 1)  {
        fprintf( stderr, "usage: schedule <course-file>*\n" );
        exit(1);
    }

}

/** 
    This function takes in two course void pointers and compares them by
    their department and number returning an int to show which should come first.

    @param va A void pointer that will be used as a course.
    @param vb A void pointer that will be used as a course.
    @return An int 1 to show va should be first, -1 for vb, and a 0 for va and vb being equal
*/
static int compareListCourses(const void *va, const void *vb)
{
    const Course *a = *(const Course**)va;
    const Course *b = *(const Course**)vb;

    int num = strcmp(a->dept, b->dept);

    if (num > 0)  {
        return 1;
    }
    else if (num < 0)  {
        return -1;
    }
    else  {
        int idNum = atoi(a->number) - atoi(b->number);
        if (idNum > 0) {
            return 1;
        }
        else {
            return -1;
        }
    }
    return 0;

}

/** 
    Only returns true to print the course every time

    @param course A pointer to a course that will be tested to see if it should be printed
    @param str1 String 1 that will be used to see if the course should be printed.
    @param str2 String 2 that will be used to see if the course should be printed.
    @return Return true if the course should be printed and false if not
*/
static bool testList(Course const *course, char const *str1, char const *str2)  
{
    return true;
}


/** 
    This function takes in two course void pointers and compares them by
    their names returning an int to show which should come first.

    @param va A void pointer that will be used as a course.
    @param vb A void pointer that will be used as a course.
    @return An int 1 to show va should be first, -1 for vb, and a 0 for va and vb being equal
*/
static int compareListNames(const void *va, const void *vb)  
{
    const Course *a = *(const Course**)va;
    const Course *b = *(const Course**)vb;
    int num = strcmp(a->name, b->name);
    if (num < 0) {
        return -1;
    }
    else if (num > 0) {
        return 1;
    }
    else {
        int idNum = atoi(a->number) - atoi(b->number);
        if (idNum > 0) {
            return 1;
        }
        else {
            return -1;
        }
    }
    return 0;
}


/** 
    This function takes in two course void pointers and compares them by
    their days and time returning an int to show which should come first.

    @param va A void pointer that will be used as a course.
    @param vb A void pointer that will be used as a course.
    @return An int 1 to show va should be first, -1 for vb, and a 0 for va and vb being equal
*/
static int compareListSchedule(const void *va, const void *vb)  
{
    const Course *a = *(const Course**)va;
    const Course *b = *(const Course**)vb;
    int aTime = 0;
    int bTime = 0;
    
    int num = strcmp(a->days, b->days);

    if (num > 0)  {
        return 1;
    }
    else if (num < 0)  {
        return -1;
    }
    else  {

        if (strcmp(a->time, "8:30") == 0)  {
            aTime = VALUE_FOR_SMALLEST_TIME;
        }
        else if (strcmp(a->time, "10:00") == 0) {
            aTime = VALUE_FOR_SECOND_SMALLEST_TIME;
        } 
        else if (strcmp(a->time, "11:30") == 0) {
            aTime = VALUE_FOR_THIRD_SMALLEST_TIME;
        }
        else if (strcmp(a->time, "1:00") == 0) {
            aTime = VALUE_FOR_FOURTH_SMALLEST_TIME;
        }
        else if (strcmp(a->time, "2:30") == 0) {
            aTime = VALUE_FOR_FIFTH_SMALLEST_TIME;
        }
        else {
            aTime = VALUE_FOR_LARGEST_TIME;
        }

        if (strcmp(b->time, "8:30") == 0)  {
            bTime = VALUE_FOR_SMALLEST_TIME;
        }
        else if (strcmp(b->time, "10:00") == 0) {
            bTime = VALUE_FOR_SECOND_SMALLEST_TIME;
        } 
        else if (strcmp(b->time, "11:30") == 0) {
            bTime = VALUE_FOR_THIRD_SMALLEST_TIME;
        }
        else if (strcmp(b->time, "1:00") == 0) {
            bTime = VALUE_FOR_FOURTH_SMALLEST_TIME;
        }
        else if (strcmp(b->time, "2:30") == 0) {
            bTime = VALUE_FOR_FIFTH_SMALLEST_TIME;
        }
        else if (strcmp(b->time, "4:00") == 0) {
            bTime = VALUE_FOR_LARGEST_TIME;
        }
        else {
            printf("PROBLEM");
        }

        if (aTime < bTime)  {
            return 1;
        }
        else if (aTime > bTime) {
            return -1;
        }
        else {
            return 0;
        }

    }
    return 0;
}

/** 
    Checks if the string follows the department format for courses.

    @param str The string being checked to see if it follows the department format
    @return True str is a proper string for a department
*/
static bool isDepartment(char *str)    
{
    if (strlen(str) != DEPT_LETTERS)    {
        return false;
    }
    for (int i = 0; i < DEPT_LETTERS; ++i)  {
        if (!isupper(str[i])) {
            return false;
        }
    }
    return true;
}

/** 
    Checks if the string follows the number format for courses.

    @param str The string being checked to see if it follows the number format
    @return True str is a proper string for a number
*/
static bool isNumber(char *str)    
{
    if (strlen(str) != COURSE_NUMBERS)    {
        return false;
    }
    for (int i = 0; i < COURSE_NUMBERS; ++i)  {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

/** 
    Checks if the course has the same department so if str1 and the department of the course are the same
    if they are the course should be printed.

    @param course A pointer to a course that will be tested to see if it should be printed
    @param str1 String 1 that will be used to see if the course should be printed.
    @param str2 String 2 that will be used to see if the course should be printed.
    @return Return true if the course should be printed and false if not
*/
static bool testListDepartment(Course const *course, char const *str1, char const *str2)  
{
    const Course *a = course;
    if (strcmp(a->dept, str1) == 0) {
        return true;
    }
    else {
        return false;
    }
}

/** 
    Checks if a department and number from str1 and str2 exist in the catalog and if they do exist in the catalog
    check if they are able to be added to the schedule.

    @param schedule The array of courses in the schedule to check for dupplicates or same time and day.
    @param catalog A pointer to a that may hold a course corresponding with str1 and str2.
    @param courses The number of courses in schedule.
    @param str1 String 1 that will be used to see if a course can be added.
    @param str2 String 2 that will be used to see if a course can be added.
    @return Return true if a course should be added to the schedule.
*/
static bool canGoInSchedule(Course* schedule[], Catalog *catalog, int courses, char *str1, char *str2)
{
    int catalogIndex = -1;
    bool isInCatalog = false;
    if (courses >= SCHEDULE_SIZE)  {
        return false;
    }
    for (int i = 0; i < catalog->count; i++)  {
        if ((strcmp(str1, catalog->list[i]->dept) == 0) &&  (strcmp(str2, catalog->list[i]->number) == 0)) {
            isInCatalog = true;
            catalogIndex = i;
        }
    }
    if (!isInCatalog)  {
        return false;
    }

    for (int i = 0; i < courses; i++)  {
        if (schedule[i] == catalog->list[catalogIndex])  {
            return false;
        }
        if ((strcmp(schedule[i]->days, catalog->list[catalogIndex]->days) == 0) && (strcmp(schedule[i]->time, catalog->list[catalogIndex]->time) == 0))  {
            return false;
        }
    }
    return true;
}

/** 
    Finds the index in the schedule where the given dept str1 and number str2 match to help to remove
    the course from the schedule.

    @param schedule The array of courses in the schedule to check for str1 and str2.
    @param courses The number of courses in schedule.
    @param str1 String 1 that will be used to see if a course can be dropped.
    @param str2 String 2 that will be used to see if a course can be dropped.
    @return Return the index of the course in schedule or -1 if nothing was found.
*/
static int indexInSchedule(Course* schedule[], int courses, char *str1, char *str2)
{
    for (int i = 0; i < courses; i++)  {
        if ((strcmp(schedule[i]->dept, str1) == 0) && (strcmp(schedule[i]->number, str2) == 0))  {
            return i;
        }
    }
    return -1;
}

/** 
    Prints out the courses that are in the schedule.

    @param schedule The array of courses in the schedule.
    @param courses The number of courses in schedule.
*/
static void listSchedule(Course* schedule[], int courses)  {
    printf("Course  Name                           Timeslot\n");
    for (int i = 0; i < courses; ++i)  {
        printf("%s %s %-30s %s %5s\n", schedule[i]->dept, schedule[i]->number, schedule[i]->name, schedule[i]->days, schedule[i]->time);
    }
    printf("%c", '\n');
}

/** 
    Prints out the courses that are in the schedule.

    @param schedule The array of courses in the schedule.
    @param courses The number of courses in schedule.
*/
static void sortSchedule( Course* schedule[], int courses, int (* compare) (void const *va, void const *vb ))  
{
    qsort(schedule, courses, sizeof(Course*), compare);

}

/** 
    Checks if the course has the same time and day so if str1 and the days of the course are the same
    and if str2 and the time of the course are the same then they should be printed.

    @param course A pointer to a course that will be tested to see if it should be printed.
    @param str1 String 1 that will be used to see if the course should be printed.
    @param str2 String 2 that will be used to see if the course should be printed.
    @return Return true if the course should be printed and false if not.
*/
static bool testTimeSlot(Course const *course, char const *str1, char const *str2)  
{
    const Course *a = course;
    if ((strcmp(a->days, str1) == 0) && (strcmp(a->time, str2) == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/** 
    Prints out the courses that are in the schedule in a calendar format.

    @param schedule The array of courses in the schedule.
    @param courses The number of courses in schedule.
*/
static void printCalendar(Course* schedule[], int courses)
{
    char str1[DEPT_AND_NUMBER_TOTAL] = "        ";
    str1[DEPT_AND_NUMBER_SPACE] = '\0';
    char str2[DEPT_AND_NUMBER_TOTAL] = "        ";
    str2[DEPT_AND_NUMBER_SPACE] = '\0';
    char str3[DEPT_AND_NUMBER_TOTAL] = "        ";
    str3[DEPT_AND_NUMBER_SPACE] = '\0';
    char str4[DEPT_AND_NUMBER_TOTAL] = "        ";
    str4[DEPT_AND_NUMBER_SPACE] = '\0';
    char str5[DEPT_AND_NUMBER_TOTAL] = "        ";
    str5[DEPT_AND_NUMBER_SPACE] = '\0';
    char str6[DEPT_AND_NUMBER_TOTAL] = "        ";
    str6[DEPT_AND_NUMBER_SPACE] = '\0';
    char str7[DEPT_AND_NUMBER_TOTAL] = "        ";
    str7[DEPT_AND_NUMBER_SPACE] = '\0';
    char str8[DEPT_AND_NUMBER_TOTAL] = "        ";
    str8[DEPT_AND_NUMBER_SPACE] = '\0';
    char str9[DEPT_AND_NUMBER_TOTAL] = "        ";
    str9[DEPT_AND_NUMBER_SPACE] = '\0';
    char str10[DEPT_AND_NUMBER_TOTAL] = "        ";
    str10[DEPT_AND_NUMBER_SPACE] = '\0';
    char str11[DEPT_AND_NUMBER_TOTAL] = "        ";
    str11[DEPT_AND_NUMBER_SPACE] = '\0';
    char str12[DEPT_AND_NUMBER_TOTAL] = "        ";
    str12[DEPT_AND_NUMBER_SPACE] = '\0';


    for (int i = 0; i < courses; i++)  {
        if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "8:30")) == 0)  {
            strcpy(str1, schedule[i]->dept);
            strcat(str1, " ");
            strcat(str1, schedule[i]->number);
        }
        if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "8:30")) == 0)  {
            strcpy(str2, schedule[i]->dept);
            strcat(str2, " ");
            strcat(str2, schedule[i]->number);
        }
       if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "10:00")) == 0)  {
            strcpy(str3, schedule[i]->dept);
            strcat(str3, " ");
            strcat(str3, schedule[i]->number);
        }
       if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "10:00")) == 0)  {
            strcpy(str4, schedule[i]->dept);
            strcat(str4, " ");
            strcat(str4, schedule[i]->number);
        }

        if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "11:30")) == 0)  {
            strcpy(str5, schedule[i]->dept);
            strcat(str5, " ");
            strcat(str5, schedule[i]->number);
        }
       if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "11:30")) == 0)  {
            strcpy(str6, schedule[i]->dept);
            strcat(str6, " ");
            strcat(str6, schedule[i]->number);
        }
        if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "1:00")) == 0)  {
            strcpy(str7, schedule[i]->dept);
            strcat(str7, " ");
            strcat(str7, schedule[i]->number);
        }
       if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "1:00")) == 0)  {
            strcpy(str8, schedule[i]->dept);
            strcat(str8, " ");
            strcat(str8, schedule[i]->number);
        }
        if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "2:30")) == 0)  {
            strcpy(str9, schedule[i]->dept);
            strcat(str9, " ");
            strcat(str9, schedule[i]->number);
        }
       if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "2:30")) == 0)  {
            strcpy(str10, schedule[i]->dept);
            strcat(str10, " ");
            strcat(str10, schedule[i]->number);
        }
        if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "4:00")) == 0)  {
            strcpy(str11, schedule[i]->dept);
            strcat(str11, " ");
            strcat(str11, schedule[i]->number);
        }
       if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "4:00")) == 0)  {
            strcpy(str12, schedule[i]->dept);
            strcat(str12, " ");
            strcat(str12, schedule[i]->number);
        }
    }

    printf("%s %s %s %s\n", "         Mon", "     Tue", "     Wed", "     Thu");
    printf("%s %s %s %s %s %s %s %s\n", " 8:30 ", str1, "", str2, "", str1, "", str2);
    printf("%s %s %s %s %s %s %s %s\n", "10:00 ", str3, "", str4, "", str3, "", str4);
    printf("%s %s %s %s %s %s %s %s\n", "11:30 ", str5, "", str6, "", str5, "", str6);
    printf("%s %s %s %s %s %s %s %s\n", " 1:00 ", str7, "", str8, "", str7, "", str8);
    printf("%s %s %s %s %s %s %s %s\n", " 2:30 ", str9, "", str10, "", str9, "", str10);
    printf("%s %s %s %s %s %s %s %s\n", " 4:00 ", str11, "", str12, "", str11, "", str12);
    printf("%c", '\n');

}


/** 
    This is the main function and does most of the work of the program by takingin input from the user
    and using that input to read files, add courses, drop courses, and list out courses in different sorted
    orderings.

    @param argc the number of arguments that were given when running the program.
    @param argv An array of strings that were the arguments given at start.
    @return 0 for a succesful exit and not 0 for a failed one.
*/
int main(int argc, char *argv[]) 
{

    Catalog *catalog = makeCatalog();
    Course* schedule[SCHEDULE_SIZE];
    for (int i = 0; i < SCHEDULE_SIZE; i++) {
        schedule[i] = NULL;
    }
    int courseCounter = 0;
    processArgs(argc, argv);

    for (int i = 1; i < argc; i++)  {
        readCourses(argv[i], catalog);
    }

    char *line;
    while (1) {
        printf("cmd> ");
        if ((line = readLine(stdin)) == NULL) {
            freeCatalog(catalog);
            exit(0);
        }
        

        char first[SIZE_FOR_COMMON_COMMAND_STRING];
        memset(first, '\0',sizeof(first));
        char second[SIZE_FOR_SECOND_COMMAND_STRING];
        memset(second, '\0',sizeof(second));
        char third[SIZE_FOR_SMALL_COMMAND_STRING];
        memset(third, '\0',sizeof(third));
        char fourth[SIZE_FOR_COMMON_COMMAND_STRING];
        memset(fourth, '\0',sizeof(fourth));
        char fifth[SIZE_FOR_COMMON_COMMAND_STRING];
        memset(fifth, '\0',sizeof(fifth));

        if (line == NULL) {
            freeCatalog(catalog);
            exit(1);
        }
        printf("%s\n", line);
        if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == 0)  {
            printf("%s\n\n", "Invalid command");
            free(line);
            continue;
        }
        else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == 1)  {
            if (strcmp(first, "quit") == 0)  {
                free(line);
                freeCatalog(catalog);
                exit(0);
            }
            else if (strcmp(first, "calendar") == 0)  {
                free(line);
                printCalendar(schedule, courseCounter);
                continue;

            }
            else {
                printf("%s\n\n", "Invalid command");
                free(line);
                continue;
            }
        }
        else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == TWO_ARGUMENTS_READ)  {
            if (strcmp(first, "list") == 0)  {
                if (strcmp(second, "courses") == 0)  {
                    free(line);
                    sortCourses(catalog, compareListCourses);
                    listCourses(catalog, testList, NULL, NULL);
                    continue;
                }
                else if (strcmp(second, "names") == 0)  {
                    free(line);
                    sortCourses(catalog, compareListNames);
                    listCourses(catalog, testList, NULL, NULL);
                    continue;
                }
                else if (strcmp(second, "schedule") == 0)  {
                    free(line);
                    sortSchedule(schedule, courseCounter, compareListSchedule);
                    listSchedule(schedule, courseCounter);
                    continue;
                }
                else {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue;
                }
            }
            else {
                printf("%s\n\n", "Invalid command");
                free(line);
                continue;
            }
        }
        else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == THREE_ARGUMENTS_READ) {
            if (strlen(third) != COURSE_NUMBERS)  {
                printf("%s\n\n", "Invalid command");
                free(line);
                continue; 
            }
            third[COURSE_NUMBERS] = '\0';
            if (strcmp(first, "add") == 0)  {
                if (strlen(second) != DEPT_LETTERS) {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue; 
                }
                second[DEPT_LETTERS] = '\0';
                if (isDepartment(second) && isNumber(third) && canGoInSchedule(schedule, catalog, courseCounter, second, third))  {
                    printf("%c", '\n');
                    free(line);
                    for (int i = 0; i < catalog->count; i++)  {
                        if ((strcmp(second, catalog->list[i]->dept) == 0) &&  (strcmp(third, catalog->list[i]->number) == 0)) {
                            schedule[courseCounter] = catalog->list[i];
                            courseCounter++;
                            break;
                        }
                    }
                }
                else {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue;  
                }
            }
            else if (strcmp(first, "drop") == 0)  {
                if (strlen(second) != DEPT_LETTERS) {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue;  
                }
                second[DEPT_LETTERS] = '\0';

                if (isDepartment(second) && isNumber(third) && (indexInSchedule(schedule, courseCounter, second, third) >= 0)) {
                    printf("%c", '\n');
                    free(line);
                    int index = indexInSchedule(schedule, courseCounter, second, third);
                    schedule[index] = schedule[courseCounter - 1];
                    schedule[courseCounter - 1] = NULL;
                    courseCounter--;
                }
                else {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue;  
                }

            }
            else if (strcmp(first, "list") == 0)  {
                if (strcmp(second, "department") == 0)  {
                    if (isDepartment(third))  {
                       free(line);
                       sortCourses(catalog, compareListCourses);
                       listCourses(catalog, testListDepartment, third, NULL);  
                       continue;
                    }
                    else {
                        printf("%s\n\n", "Invalid command");
                        free(line);
                        continue; 
                    }
                }
                else {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue; 
                }
                
            }
            else {
                printf("%s\n\n", "Invalid command");
                free(line);
                continue;   
            }
        } else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == FOUR_ARGUMENTS_READ)  {
            if ((strcmp(first, "list") == 0) && (strcmp(second, "timeslot") == 0) && ((strcmp(third, "MW") == 0) || (strcmp(third, "TH") == 0)) &&
                ((strcmp(fourth, "8:30") == 0) || (strcmp(fourth, "10:00") == 0) || (strcmp(fourth, "11:30") == 0) || (strcmp(fourth, "1:00") == 0) ||
                    (strcmp(fourth, "2:30") == 0) || (strcmp(fourth, "4:00") == 0)))  {
                free(line);
                sortCourses(catalog, compareListCourses);
                listCourses(catalog, testTimeSlot, third, fourth);
                continue;
            }
            else {
                printf("%s\n\n", "Invalid command");
                free(line);
                continue; 
            }
        }
        else {
            printf("%s\n\n", "Invalid command");
            free(line);
            continue; 
        }
    }

    freeCatalog(catalog);
    return EXIT_SUCCESS;
}

// /** 
//     @file schedule.c
//     @author William J Krjacovic (wjkrajco)
//     This is the primary file for the program as it contains the main function. This file
//     is responsible for reading in the input from the user as commands and not the file. This file
//     makes sure all the commands the user enters are valid, this file also holds the test and
//     comparing functions that are called to in order to sort the catalog and schedule.
// */

// #include <stdlib.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <string.h>
// #include <ctype.h>
// #include "input.h"
// #include "catalog.h"

// /** The Size for the string that will hold the second command*/
// #define SIZE_FOR_SECOND_COMMAND_STRING 12

// /** The common size string in command*/
// #define SIZE_FOR_COMMON_COMMAND_STRING 7

// /** The small size string in command*/
// #define SIZE_FOR_SMALL_COMMAND_STRING 4

// /**Value for 8:30*/
// #define VALUE_FOR_SMALLEST_TIME 5

// /**Value for 10:00*/
// #define VALUE_FOR_SECOND_SMALLEST_TIME 4

// /**Value for 11:30*/
// #define VALUE_FOR_THIRD_SMALLEST_TIME 3

// /**Value for 1:00*/
// #define VALUE_FOR_FOURTH_SMALLEST_TIME 2

// /**Value for 2:30*/
// #define VALUE_FOR_FIFTH_SMALLEST_TIME 1

// /**Value for 4:00*/
// #define VALUE_FOR_LARGEST_TIME 0

// /**Size of Department String*/
// #define SIZE_OF_DEPARTMENT_STRING 3

// /**Size of schedule array*/
// #define SCHEDULE_SIZE 10

// /**Number for three arguments*/
// #define TWO_ARGUMENTS_READ 2

// /**Number for three arguments*/
// #define THREE_ARGUMENTS_READ 3

// /**Number for four arguments*/
// #define FOUR_ARGUMENTS_READ 4

// /**The size of dept and number array*/
// #define DEPT_AND_NUMBER_TOTAL

// /** The size of dept and number with a space between*/
// #define DEPT_AND_NUMBER_SPACE 7








// /** 
//     This function processes the arguments that were given into the program and makes sure
//     there is at least a file for the program to read.

//     @param argc the number of arguments that were given when running the program.
//     @param argv An array of strings that were the arguments given at start
// */
// static void processArgs(int argc, char*argv[])  
// {
//     if ((argc - 1) < 1)  {
//         fprintf( stderr, "usage: schedule <course-file>*\n" );
//         exit(1);
//     }

// }

// /** 
//     This function takes in two course void pointers and compares them by
//     their department and number returning an int to show which should come first.

//     @param va A void pointer that will be used as a course.
//     @param vb A void pointer that will be used as a course.
//     @return An int 1 to show va should be first, -1 for vb, and a 0 for va and vb being equal
// */
// static int compareListCourses(const void *va, const void *vb)
// {
//     const Course *a = *(const Course**)va;
//     const Course *b = *(const Course**)vb;

//     int num = strcmp(a->dept, b->dept);

//     if (num > 0)  {
//         return 1;
//     }
//     else if (num < 0)  {
//         return -1;
//     }
//     else  {
//         int idNum = atoi(a->number) - atoi(b->number);
//         if (idNum > 0) {
//             return 1;
//         }
//         else {
//             return -1;
//         }
//     }
//     return 0;

// }

// /** 
//     Only returns true to print the course every time

//     @param course A pointer to a course that will be tested to see if it should be printed
//     @param str1 String 1 that will be used to see if the course should be printed.
//     @param str2 String 2 that will be used to see if the course should be printed.
//     @return Return true if the course should be printed and false if not
// */
// static bool testList(Course const *course, char const *str1, char const *str2)  
// {
//     return true;
// }


// /** 
//     This function takes in two course void pointers and compares them by
//     their names returning an int to show which should come first.

//     @param va A void pointer that will be used as a course.
//     @param vb A void pointer that will be used as a course.
//     @return An int 1 to show va should be first, -1 for vb, and a 0 for va and vb being equal
// */
// static int compareListNames(const void *va, const void *vb)  
// {
//     const Course *a = *(const Course**)va;
//     const Course *b = *(const Course**)vb;
//     int num = strcmp(a->name, b->name);
//     if (num < 0) {
//         return -1;
//     }
//     else if (num > 0) {
//         return 1;
//     }
//     else {
//         int idNum = atoi(a->number) - atoi(b->number);
//         if (idNum > 0) {
//             return 1;
//         }
//         else {
//             return -1;
//         }
//     }
//     return 0;
// }


// /** 
//     This function takes in two course void pointers and compares them by
//     their days and time returning an int to show which should come first.

//     @param va A void pointer that will be used as a course.
//     @param vb A void pointer that will be used as a course.
//     @return An int 1 to show va should be first, -1 for vb, and a 0 for va and vb being equal
// */
// static int compareListSchedule(const void *va, const void *vb)  
// {
//     const Course *a = *(const Course**)va;
//     const Course *b = *(const Course**)vb;
//     int aTime = 0;
//     int bTime = 0;
    
//     int num = strcmp(a->days, b->days);

//     if (num > 0)  {
//         return 1;
//     }
//     else if (num < 0)  {
//         return -1;
//     }
//     else  {

//         if (strcmp(a->time, "8:30") == 0)  {
//             aTime = VALUE_FOR_SMALLEST_TIME;
//         }
//         else if (strcmp(a->time, "10:00") == 0) {
//             aTime = VALUE_FOR_SECOND_SMALLEST_TIME;
//         } 
//         else if (strcmp(a->time, "11:30") == 0) {
//             aTime = VALUE_FOR_THIRD_SMALLEST_TIME;
//         }
//         else if (strcmp(a->time, "1:00") == 0) {
//             aTime = VALUE_FOR_FOURTH_SMALLEST_TIME;
//         }
//         else if (strcmp(a->time, "2:30") == 0) {
//             aTime = VALUE_FOR_FIFTH_SMALLEST_TIME;
//         }
//         else {
//             aTime = VALUE_FOR_LARGEST_TIME;
//         }

//         if (strcmp(b->time, "8:30") == 0)  {
//             bTime = VALUE_FOR_SMALLEST_TIME;
//         }
//         else if (strcmp(b->time, "10:00") == 0) {
//             bTime = VALUE_FOR_SECOND_SMALLEST_TIME;
//         } 
//         else if (strcmp(b->time, "11:30") == 0) {
//             bTime = VALUE_FOR_THIRD_SMALLEST_TIME;
//         }
//         else if (strcmp(b->time, "1:00") == 0) {
//             bTime = VALUE_FOR_FOURTH_SMALLEST_TIME;
//         }
//         else if (strcmp(b->time, "2:30") == 0) {
//             bTime = VALUE_FOR_FIFTH_SMALLEST_TIME;
//         }
//         else if (strcmp(b->time, "4:00") == 0) {
//             bTime = VALUE_FOR_LARGEST_TIME;
//         }
//         else {
//             printf("PROBLEM");
//         }

//         if (aTime < bTime)  {
//             return 1;
//         }
//         else if (aTime > bTime) {
//             return -1;
//         }
//         else {
//             return 0;
//         }

//     }
//     return 0;
// }

// /** 
//     Checks if the string follows the department format for courses.

//     @param str The string being checked to see if it follows the department format
//     @return True str is a proper string for a department
// */
// static bool isDepartment(char *str)    
// {
//     if (strlen(str) != DEPT_LETTERS)    {
//         return false;
//     }
//     for (int i = 0; i < DEPT_LETTERS; ++i)  {
//         if (!isupper(str[i])) {
//             return false;
//         }
//     }
//     return true;
// }

// /** 
//     Checks if the string follows the number format for courses.

//     @param str The string being checked to see if it follows the number format
//     @return True str is a proper string for a number
// */
// static bool isNumber(char *str)    
// {
//     if (strlen(str) != COURSE_NUMBERS)    {
//         return false;
//     }
//     for (int i = 0; i < COURSE_NUMBERS; ++i)  {
//         if (!isdigit(str[i])) {
//             return false;
//         }
//     }
//     return true;
// }

// /** 
//     Checks if the course has the same department so if str1 and the department of the course are the same
//     if they are the course should be printed.

//     @param course A pointer to a course that will be tested to see if it should be printed
//     @param str1 String 1 that will be used to see if the course should be printed.
//     @param str2 String 2 that will be used to see if the course should be printed.
//     @return Return true if the course should be printed and false if not
// */
// static bool testListDepartment(Course const *course, char const *str1, char const *str2)  
// {
//     const Course *a = course;
//     if (strcmp(a->dept, str1) == 0) {
//         return true;
//     }
//     else {
//         return false;
//     }
// }

// /** 
//     Checks if a department and number from str1 and str2 exist in the catalog and if they do exist in the catalog
//     check if they are able to be added to the schedule.

//     @param schedule The array of courses in the schedule to check for dupplicates or same time and day.
//     @param catalog A pointer to a that may hold a course corresponding with str1 and str2.
//     @param courses The number of courses in schedule.
//     @param str1 String 1 that will be used to see if a course can be added.
//     @param str2 String 2 that will be used to see if a course can be added.
//     @return Return true if a course should be added to the schedule.
// */
// static bool canGoInSchedule(Course* schedule[], Catalog *catalog, int courses, char *str1, char *str2)
// {
//     int catalogIndex = -1;
//     bool isInCatalog = false;
//     if (courses >= SCHEDULE_SIZE)  {
//         return false;
//     }
//     for (int i = 0; i < catalog->count; i++)  {
//         if ((strcmp(str1, catalog->list[i]->dept) == 0) &&  (strcmp(str2, catalog->list[i]->number) == 0)) {
//             isInCatalog = true;
//             catalogIndex = i;
//         }
//     }
//     if (!isInCatalog)  {
//         return false;
//     }

//     for (int i = 0; i < courses; i++)  {
//         if (schedule[i] == catalog->list[catalogIndex])  {
//             return false;
//         }
//         if ((strcmp(schedule[i]->days, catalog->list[catalogIndex]->days) == 0) && (strcmp(schedule[i]->time, catalog->list[catalogIndex]->time) == 0))  {
//             return false;
//         }
//     }
//     return true;
// }

// /** 
//     Finds the index in the schedule where the given dept str1 and number str2 match to help to remove
//     the course from the schedule.

//     @param schedule The array of courses in the schedule to check for str1 and str2.
//     @param courses The number of courses in schedule.
//     @param str1 String 1 that will be used to see if a course can be dropped.
//     @param str2 String 2 that will be used to see if a course can be dropped.
//     @return Return the index of the course in schedule or -1 if nothing was found.
// */
// static int indexInSchedule(Course* schedule[], int courses, char *str1, char *str2)
// {
//     for (int i = 0; i < courses; i++)  {
//         if ((strcmp(schedule[i]->dept, str1) == 0) && (strcmp(schedule[i]->number, str2) == 0))  {
//             return i;
//         }
//     }
//     return -1;
// }

// /** 
//     Prints out the courses that are in the schedule.

//     @param schedule The array of courses in the schedule.
//     @param courses The number of courses in schedule.
// */
// static void listSchedule(Course* schedule[], int courses)  {
//     printf("Course  Name                           Timeslot\n");
//     for (int i = 0; i < courses; ++i)  {
//         printf("%s %s %-30s %s %5s\n", schedule[i]->dept, schedule[i]->number, schedule[i]->name, schedule[i]->days, schedule[i]->time);
//     }
//     printf("%c", '\n');
// }

// /** 
//     Prints out the courses that are in the schedule.

//     @param schedule The array of courses in the schedule.
//     @param courses The number of courses in schedule.
// */
// static void sortSchedule( Course* schedule[], int courses, int (* compare) (void const *va, void const *vb ))  
// {
//     qsort(schedule, courses, sizeof(Course*), compare);

// }

// /** 
//     Checks if the course has the same time and day so if str1 and the days of the course are the same
//     and if str2 and the time of the course are the same then they should be printed.

//     @param course A pointer to a course that will be tested to see if it should be printed.
//     @param str1 String 1 that will be used to see if the course should be printed.
//     @param str2 String 2 that will be used to see if the course should be printed.
//     @return Return true if the course should be printed and false if not.
// */
// static bool testTimeSlot(Course const *course, char const *str1, char const *str2)  
// {
//     const Course *a = course;
//     if ((strcmp(a->days, str1) == 0) && (strcmp(a->time, str2) == 0)) {
//         return true;
//     }
//     else {
//         return false;
//     }
// }

// /** 
//     Prints out the courses that are in the schedule in a calendar format.

//     @param schedule The array of courses in the schedule.
//     @param courses The number of courses in schedule.
// */
// static void printCalendar(Course* schedule[], int courses)
// {
//     char str1[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str1[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str2[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str2[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str3[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str3[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str4[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str4[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str5[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str5[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str6[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str6[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str7[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str7[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str8[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str8[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str9[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str9[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str10[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str10[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str11[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str11[DEPT_AND_NUMBER_SPACE] = '\0';
//     char str12[DEPT_AND_NUMBER_TOTAL] = "        ";
//     str12[DEPT_AND_NUMBER_SPACE] = '\0';


//     for (int i = 0; i < courses; i++)  {
//         if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "8:30")) == 0)  {
//             strcpy(str1, schedule[i]->dept);
//             strcat(str1, " ");
//             strcat(str1, schedule[i]->number);
//         }
//         if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "8:30")) == 0)  {
//             strcpy(str2, schedule[i]->dept);
//             strcat(str2, " ");
//             strcat(str2, schedule[i]->number);
//         }
//        if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "10:00")) == 0)  {
//             strcpy(str3, schedule[i]->dept);
//             strcat(str3, " ");
//             strcat(str3, schedule[i]->number);
//         }
//        if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "10:00")) == 0)  {
//             strcpy(str4, schedule[i]->dept);
//             strcat(str4, " ");
//             strcat(str4, schedule[i]->number);
//         }

//         if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "11:30")) == 0)  {
//             strcpy(str5, schedule[i]->dept);
//             strcat(str5, " ");
//             strcat(str5, schedule[i]->number);
//         }
//        if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "11:30")) == 0)  {
//             strcpy(str6, schedule[i]->dept);
//             strcat(str6, " ");
//             strcat(str6, schedule[i]->number);
//         }
//         if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "1:00")) == 0)  {
//             strcpy(str7, schedule[i]->dept);
//             strcat(str7, " ");
//             strcat(str7, schedule[i]->number);
//         }
//        if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "1:00")) == 0)  {
//             strcpy(str8, schedule[i]->dept);
//             strcat(str8, " ");
//             strcat(str8, schedule[i]->number);
//         }
//         if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "2:30")) == 0)  {
//             strcpy(str9, schedule[i]->dept);
//             strcat(str9, " ");
//             strcat(str9, schedule[i]->number);
//         }
//        if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "2:30")) == 0)  {
//             strcpy(str10, schedule[i]->dept);
//             strcat(str10, " ");
//             strcat(str10, schedule[i]->number);
//         }
//         if ((strcmp(schedule[i]->days, "MW") == 0) && (strcmp(schedule[i]->time, "4:00")) == 0)  {
//             strcpy(str11, schedule[i]->dept);
//             strcat(str11, " ");
//             strcat(str11, schedule[i]->number);
//         }
//        if ((strcmp(schedule[i]->days, "TH") == 0) && (strcmp(schedule[i]->time, "4:00")) == 0)  {
//             strcpy(str12, schedule[i]->dept);
//             strcat(str12, " ");
//             strcat(str12, schedule[i]->number);
//         }
//     }

//     printf("%s %s %s %s\n", "         Mon", "     Tue", "     Wed", "     Thu");
//     printf("%s %s %s %s %s %s %s %s\n", " 8:30 ", str1, "", str2, "", str1, "", str2);
//     printf("%s %s %s %s %s %s %s %s\n", "10:00 ", str3, "", str4, "", str3, "", str4);
//     printf("%s %s %s %s %s %s %s %s\n", "11:30 ", str5, "", str6, "", str5, "", str6);
//     printf("%s %s %s %s %s %s %s %s\n", " 1:00 ", str7, "", str8, "", str7, "", str8);
//     printf("%s %s %s %s %s %s %s %s\n", " 2:30 ", str9, "", str10, "", str9, "", str10);
//     printf("%s %s %s %s %s %s %s %s\n", " 4:00 ", str11, "", str12, "", str11, "", str12);
//     printf("%c", '\n');

// }


// /** 
//     This is the main function and does most of the work of the program by takingin input from the user
//     and using that input to read files, add courses, drop courses, and list out courses in different sorted
//     orderings.

//     @param argc the number of arguments that were given when running the program.
//     @param argv An array of strings that were the arguments given at start.
//     @return 0 for a succesful exit and not 0 for a failed one.
// */
// int main(int argc, char *argv[]) 
// {

//     Catalog *catalog = makeCatalog();
//     Course* schedule[SCHEDULE_SIZE];
//     for (int i = 0; i < SCHEDULE_SIZE; i++) {
//         schedule[i] = NULL;
//     }
//     int courseCounter = 0;
//     processArgs(argc, argv);

//     for (int i = 1; i < argc; i++)  {
//         readCourses(argv[i], catalog);
//     }

//     char *line;
//     while (1) {
//         printf("cmd> ");
//         if ((line = readLine(stdin)) == NULL) {
//             freeCatalog(catalog);
//             exit(0);
//         }
        

//         char first[SIZE_FOR_COMMON_COMMAND_STRING];
//         memset(first, '\0',sizeof(first));
//         char second[SIZE_FOR_SECOND_COMMAND_STRING];
//         memset(second, '\0',sizeof(second));
//         char third[SIZE_FOR_SMALL_COMMAND_STRING];
//         memset(third, '\0',sizeof(third));
//         char fourth[SIZE_FOR_COMMON_COMMAND_STRING];
//         memset(fourth, '\0',sizeof(fourth));
//         char fifth[SIZE_FOR_COMMON_COMMAND_STRING];
//         memset(fifth, '\0',sizeof(fifth));

//         if (line == NULL) {
//             freeCatalog(catalog);
//             exit(1);
//         }
//         printf("%s\n", line);
//         if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == 0)  {
//             printf("%s\n\n", "Invalid command");
//             free(line);
//             continue;
//         }
//         else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == 1)  {
//             if (strcmp(first, "quit") == 0)  {
//                 free(line);
//                 freeCatalog(catalog);
//                 exit(0);
//             }
//             else if (strcmp(first, "calendar") == 0)  {
//                 free(line);
//                 printCalendar(schedule, courseCounter);
//                 continue;

//             }
//             else {
//                 printf("%s\n\n", "Invalid command");
//                 free(line);
//                 continue;
//             }
//         }
//         else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == TWO_ARGUMENTS_READ)  {
//             if (strcmp(first, "list") == 0)  {
//                 if (strcmp(second, "courses") == 0)  {
//                     free(line);
//                     sortCourses(catalog, compareListCourses);
//                     listCourses(catalog, testList, NULL, NULL);
//                     continue;
//                 }
//                 else if (strcmp(second, "names") == 0)  {
//                     free(line);
//                     sortCourses(catalog, compareListNames);
//                     listCourses(catalog, testList, NULL, NULL);
//                     continue;
//                 }
//                 else if (strcmp(second, "schedule") == 0)  {
//                     free(line);
//                     sortSchedule(schedule, courseCounter, compareListSchedule);
//                     listSchedule(schedule, courseCounter);
//                     continue;
//                 }
//                 else {
//                     printf("%s\n\n", "Invalid command");
//                     free(line);
//                     continue;
//                 }
//             }
//             else {
//                 printf("%s\n\n", "Invalid command");
//                 free(line);
//                 continue;
//             }
//         }
//         else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == THREE_ARGUMENTS_READ) {
//             if (strlen(third) != COURSE_NUMBERS)  {
//                 printf("%s\n\n", "Invalid command");
//                 free(line);
//                 continue; 
//             }
//             third[COURSE_NUMBERS] = '\0';
//             if (strcmp(first, "add") == 0)  {
//                 if (strlen(second) != DEPT_LETTERS) {
//                     printf("%s\n\n", "Invalid command");
//                     free(line);
//                     continue; 
//                 }
//                 second[DEPT_LETTERS] = '\0';
//                 if (isDepartment(second) && isNumber(third) && canGoInSchedule(schedule, catalog, courseCounter, second, third))  {
//                     printf("%c", '\n');
//                     free(line);
//                     for (int i = 0; i < catalog->count; i++)  {
//                         if ((strcmp(second, catalog->list[i]->dept) == 0) &&  (strcmp(third, catalog->list[i]->number) == 0)) {
//                             schedule[courseCounter] = catalog->list[i];
//                             courseCounter++;
//                             break;
//                         }
//                     }
//                 }
//                 else {
//                     printf("%s\n\n", "Invalid command");
//                     free(line);
//                     continue;  
//                 }
//             }
//             else if (strcmp(first, "drop") == 0)  {
//                 if (strlen(second) != DEPT_LETTERS) {
//                     printf("%s\n\n", "Invalid command");
//                     free(line);
//                     continue;  
//                 }
//                 second[DEPT_LETTERS] = '\0';

//                 if (isDepartment(second) && isNumber(third) && (indexInSchedule(schedule, courseCounter, second, third) >= 0)) {
//                     printf("%c", '\n');
//                     free(line);
//                     int index = indexInSchedule(schedule, courseCounter, second, third);
//                     schedule[index] = schedule[courseCounter - 1];
//                     schedule[courseCounter - 1] = NULL;
//                     courseCounter--;
//                 }
//                 else {
//                     printf("%s\n\n", "Invalid command");
//                     free(line);
//                     continue;  
//                 }

//             }
//             else if (strcmp(first, "list") == 0)  {
//                 if (strcmp(second, "department") == 0)  {
//                     if (isDepartment(third))  {
//                        free(line);
//                        sortCourses(catalog, compareListCourses);
//                        listCourses(catalog, testListDepartment, third, NULL);  
//                        continue;
//                     }
//                     else {
//                         printf("%s\n\n", "Invalid command");
//                         free(line);
//                         continue; 
//                     }
//                 }
//                 else {
//                     printf("%s\n\n", "Invalid command");
//                     free(line);
//                     continue; 
//                 }
                
//             }
//             else {
//                 printf("%s\n\n", "Invalid command");
//                 free(line);
//                 continue;   
//             }
//         } else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == FOUR_ARGUMENTS_READ)  {
//             if ((strcmp(first, "list") == 0) && (strcmp(second, "timeslot") == 0) && ((strcmp(third, "MW") == 0) || (strcmp(third, "TH") == 0)) &&
//                 ((strcmp(fourth, "8:30") == 0) || (strcmp(fourth, "10:00") == 0) || (strcmp(fourth, "11:30") == 0) || (strcmp(fourth, "1:00") == 0) ||
//                     (strcmp(fourth, "2:30") == 0) || (strcmp(fourth, "4:00") == 0)))  {
//                 free(line);
//                 sortCourses(catalog, compareListCourses);
//                 listCourses(catalog, testTimeSlot, third, fourth);
//                 continue;
//             }
//             else {
//                 printf("%s\n\n", "Invalid command");
//                 free(line);
//                 continue; 
//             }
//         }
//         else {
//             printf("%s\n\n", "Invalid command");
//             free(line);
//             continue; 
//         }
//     }

//     freeCatalog(catalog);
//     return EXIT_SUCCESS;
// }
