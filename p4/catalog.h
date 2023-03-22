/** 
    @file catalog.h
    @author William J Krjacovic (wjkrajco)
    This is the header file for Catalog which holds the bock comments for the functions
    makeCatalog, freeCatalog, readCourses, sortCourses and listCourses.
*/

/**The max number of letters in the department for the course*/
#define DEPT_LETTERS 3

/**The max number of numbers in the number for the course*/
#define COURSE_NUMBERS 3

/**The max number of letters in the days for the course*/
#define COURSE_DAYS 2

/**The max number of characters in the time for the course*/
#define COURSE_TIME 5

/**The max number of letters name for the course*/
#define MAX_NAME 30

struct CourseStruct {
    char dept[DEPT_LETTERS + 1];
    char number[COURSE_NUMBERS + 1];
    char days[COURSE_DAYS + 1];
    char time[COURSE_TIME + 1];
    char name[MAX_NAME + 1];
};
typedef struct CourseStruct Course;

struct CatalogStruct {
    Course **list;
    int count;
    int capacity;
};
typedef struct CatalogStruct Catalog;


/** 
    This function dynamically allocates storage for Catalog, initalizes its fields and returns
    a pointer the created Catalog.

    @return The pointer to the newly created Catalog.
*/
Catalog *makeCatalog();

/** 
    Takes a pointer to catalog and frees the space for all the courses in the catalog
    and the catalog itself.

    @param catalog The catalog that will have itself and all it's courses' storage freed.
*/
void freeCatalog( Catalog *catalog );

/** 
    This function uses filename to read all of the courses, it will then make an instance of the course
    struct for each of the read courses and stores a pointer to the course in the catalog parameter.

    @param fileName The file that is going to be read for courses
    @param catalog The catalog pointer that is going to store all the read courses
*/
void readCourses( char const *fileName, Catalog *catalog );

/** 
    This function sorts the courses in a given catalog and a pointer to a comparison function that will be 
    used in the qsort() function

    @param catalog The catalog pointer that is going to be used to sort the courses
    @param compare A pointer to a comparison function that will be used in qsort()
*/
void sortCourses( Catalog *catalog, int ( *compare ) ( void const *va, void const *vb ) );

/** 
    This function prints all or some of the courses in the catalog. The function will take str1 and str2 to decide
    which courses to print, it will also use the bool test pointer as a way to show what to print, checking if the course
    matches true then printing and if false then not printing.

    @param catalog The catalog pointer that is going to be used to print the courses
    @param test A test boolean to see if a course should or should not be printed
    @param str1 The first string that is going to be used to see if a course should or shouldn't be printed
    @param str2 The second string that is going to be used to see if a course should or shouldn't be printed
*/
void listCourses( Catalog *catalog, bool (*test)( Course const *course, char const *str1, char const *str2 ), char const *str1, char const *str2 );