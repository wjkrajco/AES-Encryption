/** 
    @file catalog.c
    @author William J Krjacovic (wjkrajco)
    This catalog function has the job of making and free the catalog space. The file
    also reads in the courses give a file name and creates new courses and stores them in the Catalog
    through pointers. The file also has the job of printing out the courses, and sorting the catalog based
    on input from the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "input.h"
#include "catalog.h"



Catalog *makeCatalog()  
{
    Catalog *catalog = malloc(sizeof(Catalog));
    catalog->count = 0;
    catalog->capacity = 5;
    catalog->list = malloc(catalog->capacity * sizeof(Course *));
    return catalog;
}

void freeCatalog(Catalog *catalog)  
{
    for (int i = 0; i < catalog->count; i++)  {
        free(catalog->list[i]);
    }
    free(catalog->list);
    free(catalog);
}



void readCourses(char const *filename, Catalog *catalog)  
{
    FILE *fp = fopen(filename, "r");
    if (!fp)  {
        fprintf( stderr, "Can't open file: %s\n", filename );
        exit(1);
    }
    char *str = NULL;
    int courseCounter = 0;
    bool whiteSpace = false;
    bool dept = false;
    bool num = false;
    bool days = false;
    bool time = false;
    bool name = false;
    while((str = readLine(fp)) != NULL)  {


        if (catalog->count == catalog->capacity) {
            catalog->list = realloc(catalog->list, (catalog->capacity * 2) * sizeof(Course *));
            catalog->capacity = catalog->capacity * 2;

        }

        courseCounter++;
        if (dept)  {
            dept = false;
            num = false;
            days = false;
            time = false;
            name = false;
            whiteSpace = false;

        }
        Course *course = malloc(sizeof(Course));
        memset(course, 0, sizeof(Course));

        for (int i = 0; str[i] != '\0'; i++)  {

            if (!isspace(str[i]) && (whiteSpace || !dept))  {
                if (!dept && strlen(str) > i + 4)  {
                    char deptStr[4];
                    deptStr[3] = '\0';
                    for (int j  = 0; j < 3; j++)  {
                        if (isupper(str[i + j]))  {
                            deptStr[j] = str[i + j];
                        }
                        else {
                            fprintf( stderr, "Invalid course file: %s\n", filename );
                            exit(1);
                        }
                    }
                    strncpy(course->dept, deptStr, sizeof(course->dept) - 1);
                    // strncpy(newCourse->dept, deptStr, sizeof(newCourse->dept) - 1);
                    whiteSpace = false;
                    dept = true;
                    i += 2;
                }
                else if (!num && (strlen(str) > i + 4) && whiteSpace)  {
                    char numStr[4];
                    numStr[3] = '\0';
                    for (int j  = 0; j < 3; j++)  {
                        if (isdigit(str[i + j]))  {
                            numStr[j] = str[i + j];
                        }
                        else {
                            fprintf( stderr, "Invalid course file: %s\n", filename );
                            exit(1);
                        }
                    }
                    strncpy(course->number, numStr, sizeof(course->number) - 1);
                    // strcpy(courses[courseCounter - 1].number, numStr);
                    whiteSpace = false;
                    num = true;
                    i += 2;

                }
                else if (!days && (strlen(str) > i + 3) && whiteSpace)  {
                    char daysStr[3];
                    daysStr[2] = '\0';
                    if ((str[i] == 'M' && str[i + 1] == 'W') || (str[i] == 'T' && str[i + 1] == 'H'))  {
                        daysStr[0] = str[i];
                        daysStr[1] = str[i + 1];
                    } else { 
                        fprintf( stderr, "Invalid course file: %s\n", filename );
                        exit(1);
                    }
                    strncpy(course->days, daysStr, sizeof(course->days) - 1);
                    // strcpy(courses[courseCounter - 1].days, daysStr);
                    whiteSpace = false;
                    days = true;
                    i += 1;
                } else if (!time && (strlen(str) > i + 6) && whiteSpace)  {
                    char timeStr[6];
                    timeStr[5] = '\0';
                    if ((str[i] == '1' && str[i + 1] == '0' && str[i + 2] == ':' && str[i + 3] == '0'  && str[i + 4] == '0') ||
                          (str[i] == '1' && str[i + 1] == '1' && str[i + 2] == ':' && str[i + 3] == '3'  && str[i + 4] == '0'))  {
                        timeStr[0] = str[i];
                        timeStr[1] = str[i + 1];
                        timeStr[2] = str[i + 2]; 
                        timeStr[3] = str[i + 3];       
                        timeStr[4] = str[i + 4];
                        i += 4;               

                    } else if ((str[i] == '4' && str[i + 1] == ':' && str[i + 2] == '0' && str[i + 3] == '0') ||
                          (str[i] == '8' && str[i + 1] == ':' && str[i + 2] == '3' && str[i + 3] == '0') || 
                            (str[i] == '1' && str[i + 1] == ':' && str[i + 2] == '0' && str[i + 3] == '0') || 
                              (str[i] == '2' && str[i + 1] == ':' && str[i + 2] == '3' && str[i + 3] == '0')) {
                        timeStr[0] = str[i];
                        timeStr[1] = str[i + 1];
                        timeStr[2] = str[i + 2]; 
                        timeStr[3] = str[i + 3];
                        timeStr[4] = '\0';
                        i += 3;

                    } else { 
                        fprintf( stderr, "Invalid course file: %s\n", filename );
                        exit(1);
                    }
                    strncpy(course->time, timeStr, sizeof(course->time) - 1);
                    // strcpy(courses[courseCounter - 1].time, timeStr);
                    whiteSpace = false;
                    time = true;
                }
                else if (!name && whiteSpace)  {
                    char nameStr[31];
                    nameStr[30] = '\0';
                    int counter = 0;
                    for (int j = 0; (str[j + i] != '\0') && ((j) < 30); ++j)  {
                        nameStr[j] = str[j + i];
                        counter++;
                    }
                    if(counter == 30)  {
                        if (str[30 + i] != '\0')  {
                          fprintf( stderr, "Invalid course file: %s\n", filename );
                          exit(1);  
                        }
                    }
                    else {
                        for (int k = counter; k < 30; ++k)  {
                            nameStr[k] = '\0';
                        }
                        strncpy(course->name, nameStr, sizeof(course->name) - 1);
                        // strcpy(courses[courseCounter - 1].name, nameStr);
                        whiteSpace = false;
                        name = true;
                        i += counter - 1;
                    }
                    


                }
                else {
                    fprintf( stderr, "Invalid course file: %s\n", filename );
                    exit(1);
                }
            }
            else {
                whiteSpace = true;
            }
        }


        for (int i = 0; i < catalog->count; i++)  {
            if ((strcmp(catalog->list[i]->dept, course->dept) == 0) && (strcmp(catalog->list[i]->number, course->number) == 0))  {
                fprintf( stderr, "Invalid course file: %s\n", filename );
                exit(1);
            }
        }



        catalog->list[catalog->count] = course;
        catalog->count++;
        free(str);
    }
    fclose(fp);
    
}

void sortCourses( Catalog *catalog, int (* compare) (void const *va, void const *vb ))  
{
    qsort(catalog->list, catalog->count, sizeof(Course*), compare);

}


void listCourses( Catalog *catalog, bool (*test)( Course const *course, char const *str1, char const *str2 ), char const *str1, char const *str2 )
{
    printf("Course  Name                           Timeslot\n");
    for (int i = 0; i < catalog->count; ++i)  {
        if (test(catalog->list[i], str1, str2))  {
            printf("%s %s %-30s %s %5s\n", catalog->list[i]->dept, catalog->list[i]->number, catalog->list[i]->name, catalog->list[i]->days, catalog->list[i]->time);
        }
    }
    printf("%c", '\n');
}
