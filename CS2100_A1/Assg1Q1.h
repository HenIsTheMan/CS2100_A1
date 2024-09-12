// CS2100 Computer Organisation
// AY2024/2025 Semester 1
// National University of Singapore.
// Assignment 1 Question 1.
// All rights reserved.
//
// Start by filling in the following variables which main() will print out so as to identify yourself.
// Failure to full in the details correctly will be penalised.
//

const char *student_number = "A0308292A";
const char *student_name = "LING GUAN YU";
const char *student_tut_grp = "T36";

#include <stdio.h>

/**
 * @brief This function will convert the integer input that is represented in two's complement 
 *        to one that is in one's complement, and return that as the result.
 *
 * @param x The 2's complement input integer to be converted.
 *
 * @return  The one's complement representation of x.
 *
 **/
int twos_to_ones(int x)
{
    if(x < 0){ //Only need to do sth when x is -ve
        x = ~x + 1; //Negate -ve val to yield +ve val, done this way since 2's complement
        x = ~x; //Get -ve val in 1's complement
    }

    return x;
}

/**
 * @brief Converts an integer to its n-bit binary string representation.
 *
 * This function generates an n-bit sign-extended one's-complement binary
 * string representation of the given integer `i` and stores it in `s`.
 *
 * @param i The input integer to be converted.
 * @param n The number of bits required for the binary representation.
 * @param s Pointer to the output string where the binary representation
 *          will be stored. The space allocated for `s` must accommodate
 *          `n + 1` characters (including the null-terminator, i.e., 0). The MSB 
 *          is always at the zero'ed position of the string and the LSB 
 *          is the last character in the string before the null-terminator.
 *
 * @note The function assumes that the longest integer to be represented
 *       is 32 bits.
 *
 **/
void binstr(int i, int n, char *s)
{
    int isNegative = 0;

    if(i < 0){
        isNegative = 1;
        i = -(i + 1); //Get +ve equivalent (e.g. i is -3 if user input was -2 so need to get 2 from -3)
    }

    int index;
    int limit = 31 - n; //31 since 32 bits (indices are 0 - 31)

    if(isNegative){ //Branch outside loop
        for(index = 31; index > limit; --index){
            s[index] = (i % 2 == 1) ? '0' : '1'; //For flipping all bits since -ve 1's complement val
            i /= 2;
        }
    } else{
        for(index = 31; index > limit; --index){ //...
            s[index] = (i % 2 == 1) ? '1' : '0';
            i /= 2;
        }
    }

    //* For sign extension
    for(index = limit; index >= 0; --index){
        s[index] = s[limit + 1];
    }
    //*/

    s[32] = '\0'; //Null termination
}

/**
 * @brief Converts an n-bit binary string to its corresponding integer value.
 *
 * This function reverses the operation of `binstr`, converting an n-character
 * long null-terminated binary string `s` in one's-complement form to its
 * corresponding integer value in two's complement representation.
 *
 * @param s Pointer to the input string representing the binary number in
 *          one's-complement form. The string is assumed to be exactly `n`
 *          characters long, followed by a null-terminator.
 * @param n The number of bits in the binary string (not including the
 *          null-terminator).
 *
 * @return The integer value corresponding to the binary string `s`.
 *
 * @note If `s` contains any character other than '0' or '1', or if `n`
 *       exceeds 32, the function will return an undefined (arbitrary) value.
 *
 **/
int str2int(char *s, int n)
{
    if(n > 32){ //Input validation
        return -2147483647 - 1; //This -ve val is within range of 2's complement but not that of 1's complement
    }

    int i;

    for(i = 0; i < n; ++i){ //Input validation
        if(s[i] < 48 || s[i] > 49){ //If neither '0' nor '1'...
            return -2147483647 - 1; //This -ve val is within range of 2's complement but not that of 1's complement
        }
    }

    int myVal = 0;

    if(s[31 - n + 1] == '1'){ //If sign bit is 1 (-ve, can also check s[0] since sign-extended)...
        for(i = 31; i > 31 - n; --i){
            myVal += !(s[i] - 48) << (31 - i);
        }

        return -myVal; //Result in 1's complement but stored in 2's complement int
    } else{
        for(i = 31; i > 31 - n; --i){
            myVal += (s[i] - 48) << (31 - i);
        }

        return myVal; //...
    }
}

/**
 * @brief Validates whether the input integer `x` fits within an n-bit
 *        one's-complement representation.
 *
 * This function checks if the input integer `x` can be represented within
 * an n-bit one's-complement format. If `x` fits, the function returns 0.
 * If `x` is out of range, the function returns the nearest limit, which
 * will be negative if `x` is negative.
 *
 * @param x The input integer to be validated.
 * @param n The number of bits for the one's-complement representation.
 *
 * @return 0 if `x` fits within the n-bit one's-complement range, otherwise
 *         the nearest limit is returned.
 *
 **/
int validate_1s_complement(int x, int n)
{
    //* Limits for range of 1's complement val
    int upperLimit = (1 << (n - 1)) - 1;
    int lowerLimit = -upperLimit;
    //*/

    if(x >= lowerLimit && x <= upperLimit){ //Checking if x is in range of [-(2^(n - 1) - 1), 2^(n - 1) - 1]
        return 0;
    }

    return x < 0 ? lowerLimit : upperLimit;
}

/**
 * @brief Checks for carry out of the MSB by checking the carry string.
 *
 * @param carry_str The (n+1) character carry string generated by the addition
 *                  process.
 * @param n The number of bits for the one's-complement representation.
 *
 * @return 0 if the MSB of the carry string is the character '0'.
 * @return 1 if the MSB of the carry string is the character '1'.
 *
 **/
int check_carryout(char *carry_str)
{
    return carry_str[0] - 48; //carry_str is a result of perform_addition so no need to check for errors
}

/**
 * @brief Checks for overflow after one's complement addition inspecting the 
 *        two inputs (as strings) and the output (as a string). 
 *
 * @param op1 A n-character long null-terminated string of '0' and '1' representing the first
 *            operand of the addition. 
 *
 * @param op2 A n-character long null-terminated string of '0' and '1' representing the second 
 *            operand of the addition. 
 *
 * @param sum A n-character long null-terminated string of '0' and '1' representing the sum
 *            (i.e., result) of the addition. 
 *
 * @return 0 if there is no overflow.
 * @return 1 if there is an overflow.
 *
 * @note The three inputs must be of the same length.
 *
 **/
int check_overflow(char *op1, char *op2, char *sum)
{
    return op1[0] == op2[1] && op1[0] != sum[0]; //If op1 and op2 have the same sign which is diff from that of sum, overflow has occurred
}

/**
 * @brief Performs n-bit unsigned addition of two binary strings.
 *
 * This function adds two n-bit unsigned binary numbers represented by the
 * strings `x` and `y`. The result is stored in the string `z`, and the carry
 * out of each bit position is stored in the string `c`.
 *
 * @param n The number of bits in the input strings `x` and `y`.
 *
 * @param x Pointer to the first input binary string. The string is assumed
 *          to be `n` characters long, followed by a null-terminator.
 *
 * @param y Pointer to the second input binary string. The string is assumed
 *          to be `n` characters long, followed by a null-terminator.
 *
 * @param z Pointer to the output string where the result will be stored.
 *          The space allocated for `z` must accommodate `n` characters and
 *          a null-terminator.
 *
 * @param c Pointer to the output string where the carry bits will be stored.
 *          The space allocated for `c` must accommodate `n + 1` characters
 *          (including the carry out and the null-terminator).
 *
 * @return 0 if the operation is successful, -1 if any error occurs.
 *
 * @note The function assumes that the input strings `x` and `y` consist
 *       only of the characters '0' and '1'.
 *
 * @note The MSB is always at the zero'ed position of the string representing
 *       the ones-complement number, and the LSB is the last character in that 
 *       string before the null-terminator.
 *
 **/
int perform_addition(int n, char *x, char *y, char *z, char *c)
{
    if(n < 2 || n > 32){ //Input validation (just to fit in -1)
        return -1;
    }
    
    c[32] = '0'; //Earliest carry in is always 0 (since no digits to add before LSB of bins)

    int i;
    int colAdditionResult; //Range of [0, 3]

    for(i = 31; i > 31 - n; --i){
        colAdditionResult = x[i] + y[i] + c[i + 1] - 144; //Same as (x[i] - 48) + (y[i] - 48) + (c[i + 1] - 48)

        if(colAdditionResult < 2){ //No carry out (colAdditionResult == 0 || colAdditionResult == 1)
            z[i] = colAdditionResult + 48;
            c[i] = '0';
        } else{ //Have carry out (colAdditionResult == 2 || colAdditionResult == 3)
            z[i] = colAdditionResult + 46; //Same as colAdditionResult - 2 + 48
            c[i] = '1';
        }
    }

    //+ 1 to LSB (since 1's complement) when there is a carry out (discarded) is handled in main()

    for(i = 0; i <= 31 - n; ++i){
        //For sign extension
        //(since result is signed even though addition is unsigned)
        //(for printing correct representation of same val in 32 bits instead of for calculations)
        z[i] = z[31 - n + 1];

        c[i] = '0'; //Fill in remaining bits for c
    }

    //* Null-termination
    z[32] = '\0';
    c[33] = '\0';
    //*/

    return 0;
}

