/** 
    @file operation.h 
    @author William J Krjacovic (wjkrajco)
    This is the header file for operation which contains the block comments
    for the arithmetic functions plus, minus, times, divide and exponential located in operation.c
*/

/** This is the exit status given if an overflow occurs. */
#define OVERFLOW_EXIT 100

/** The exit status returned from dividing by zero. */
#define DIVIDE_BY_ZERO_EXIT 101

/** 
    This function adds the parameters a and b. If there is an overflow
    of the addition then the function exits with the status of 100.

    @param a The first long being added.
    @param b The second long being added.
    @return The sum of longs returned as a long if there is no overflow.
    If there is an overflow then exit with status of 100.
*/
long plus ( long a, long b );

/** 
    This function minuses the parameters a and b. If there is an overflow
    then the function exits with the status of 100. The function utlizes the
    plus function to get its result;

    @param a The first long being subtracted.
    @param b The second long being subtracted.
    @return The subtraction of the longs returned as a long if there is no overflow.
    If there is an overflow then exit with status of 100.
*/
long minus ( long a, long b );

/** 
    This function times the parameters a and b. If there is an overflow
    of the multiplication then the function exits with the status of 100. 
    To find overflow the function uses LONG_MAX and LONG_MIN.

    @param a The first long being multiplied.
    @param b The second long being multiplied.
    @return The multiplication of the longs returned as a long if there is no overflow.
    If there is an overflow then exit with status of 100.
*/
long times ( long a, long b );

/** 
    This function find the exponential answer of a the base, and b
    the exponent being calculated.

    @param a The base long.
    @param b The exponential long.
    @return The value of a raised to b if there is no overflow and 
    exit with status of 100 if there is an overflow
*/
long exponential ( long a, long b );

/** 
    This function divides the parameters a and b. If there is an overflow
    of the divide then the function exits with the status of 100. The
    function utlizes the times function to find the result

    @param a The dividend.
    @param b The divisor.
    @return The division of the longs returned as a long if there is no overflow.
    If there is an overflow then exit with status of 100, if ther is a divide by zero situation
    then return exit with status of 101.
*/
long divide ( long a, long b );
