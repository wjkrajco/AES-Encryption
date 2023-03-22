
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "catalog.h"




static void processArgs(int argc, char*argv[])  
{
    if ((argc - 1) < 1)  {
        fprintf( stderr, "usage: schedule <course-file>*\n" );
        exit(1);
    }

}

// int main(int argc, char *argv[]) 
// {
//     makeCatalog();
//     processArgs(argc, argv);

//     for (int i = 1; i < argc; i++)  {
//         FILE *fp = fopen(argv[i], "r");
//         if (!fp)  {
//             fprintf( stderr, "Can't open file: %s\n", argv[i] );
//             exit(1);
//         }
//         char *line;
//         while ((line = readLine(fp)) != NULL)  {
//             printf ("%s\n", line);
//             free(line);
//         }
//         fclose(fp);
//     }
//     freeCatalog(catalog);
//     return EXIT_SUCCESS;
// }

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

static bool testList(Course const *course, char const *str1, char const *str2)  
{
    return true;
}



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
            aTime = 5;
        }
        else if (strcmp(a->time, "10:00") == 0) {
            aTime = 4;
        } 
        else if (strcmp(a->time, "11:30") == 0) {
            aTime = 3;
        }
        else if (strcmp(a->time, "1:00") == 0) {
            aTime = 2;
        }
        else if (strcmp(a->time, "2:30") == 0) {
            aTime = 1;
        }
        else {
            aTime = 0;
        }

        if (strcmp(b->time, "8:30") == 0)  {
            bTime = 5;
        }
        else if (strcmp(b->time, "10:00") == 0) {
            bTime = 4;
        } 
        else if (strcmp(b->time, "11:30") == 0) {
            bTime = 3;
        }
        else if (strcmp(b->time, "1:00") == 0) {
            bTime = 2;
        }
        else if (strcmp(b->time, "2:30") == 0) {
            bTime = 1;
        }
        else if (strcmp(b->time, "4:00") == 0) {
            bTime = 0;
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

        // int idNum = atoi(a->number) - atoi(b->number);
        // if (idNum > 0) {
        //     return 1;
        // }
        // else {
        //     return -1;
        // }
    }
    return 0;
}

static bool isDepartment(char *str)    
{
    if (strlen(str) != 3)    {
        return false;
    }
    for (int i = 0; i < 3; ++i)  {
        if (!isupper(str[i])) {
            return false;
        }
    }
    return true;
}

static bool isNumber(char *str)    
{
    if (strlen(str) != 3)    {
        return false;
    }
    for (int i = 0; i < 3; ++i)  {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

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

static bool canGoInSchedule(Course* schedule[], Catalog *catalog, int courses, char *str1, char *str2)  {
    int catalogIndex = -1;
    bool isInCatalog = false;
    if (courses >= 10)  {
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

static int indexInSchedule(Course* schedule[], int courses, char *str1, char *str2)  {
    for (int i = 0; i < courses; i++)  {
        if ((strcmp(schedule[i]->dept, str1) == 0) && (strcmp(schedule[i]->number, str2) == 0))  {
            return i;
        }
    }
    return -1;
}

void listSchedule(Course* schedule[], int courses)  {
    printf("Course  Name                           Timeslot\n");
    for (int i = 0; i < courses; ++i)  {
        printf("%s %s %-30s %s %5s\n", schedule[i]->dept, schedule[i]->number, schedule[i]->name, schedule[i]->days, schedule[i]->time);
    }
    printf("%c", '\n');
}

void sortSchedule( Course* schedule[], int courses, int (* compare) (void const *va, void const *vb ))  
{
    qsort(schedule, courses, sizeof(Course*), compare);

}

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



int main(int argc, char *argv[]) 
{

    Catalog *catalog = makeCatalog();
    Course* schedule[10];
    for (int i = 0; i < 10; i++) {
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
        

        char first[7];
        memset(first, '\0',sizeof(first));
        char second[12];
        memset(second, '\0',sizeof(second));
        char third[4];
        memset(third, '\0',sizeof(third));
        char fourth[7];
        memset(fourth, '\0',sizeof(fourth));
        char fifth[7];
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
            else {
                printf("%s\n\n", "Invalid command");
                free(line);
                continue;
            }
        }
        else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == 2)  {
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
        else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == 3) {
            if (strlen(third) != 3)  {
                printf("%s\n\n", "Invalid command");
                free(line);
                continue; 
            }
            third[3] = '\0';
            if (strcmp(first, "add") == 0)  {
                if (strlen(second) != 3) {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue; 
                }
                second[3] = '\0';
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
                if (strlen(second) != 3) {
                    printf("%s\n\n", "Invalid command");
                    free(line);
                    continue;  
                }
                second[3] = '\0';

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
        } else if (sscanf(line, "%s %s %s %s %s", first, second, third, fourth, fifth) == 4)  {
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
