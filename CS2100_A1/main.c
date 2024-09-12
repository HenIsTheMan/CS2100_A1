#include <stdio.h>

/*
Smallest input for 2 bits: -1
Largest input for 2 bits: 1
Smallest input for 32 bits: -2147483647
Largest input for 32 bits: 2147483647

extern const char *student_number;
extern const char *student_name;
extern const char *student_tut_grp;

extern int twos_to_ones(int x); //Correct (checked by ensuring output -ve int [stored in 2's complement C int] is 1 less than input -ve int)

extern void binstr(int i, int n, char *s); //Correct (checked by comparing bin representations of +ve val and its -ve counterpart)

extern int str2int(char *s, int n); //Correct (checked)

extern int validate_1s_complement(int x, int n); //Correct (checked by testing smallest and largest input for 2 and 32 bits)

extern int check_carryout(char *carry_str); //Correct (checked)

//Adding same vals in C yields a result 1 less than printed result (expected due to overflow diff in 2's complement and 1's complement)
extern int check_overflow(char *op1, char *op2, char *sum); //Correct (checked)

extern int perform_addition(int n, char *x, char *y, char *z, char *c); //Correct (checked)
//*/

#include "Assg1Q1.h"

int main(){
    int x, y, n, check;
    int x1s, y1s;
    char x_str[33], y_str[33], z1_str[33], z2_str[33], one_str[33]; 
    char c1_str[34], c2_str[34]; // Holds the carries. It is 33 bits because the MSB is the carry out.

    printf("CS2100 Assignment 1 Question 1\n");
    printf("------------------------------\n");
    printf("One's complement addition submission by:\n\n");
    printf("Student name: %s\n", student_name);
    printf("Student number: %s\n", student_number);
    printf("Tutorial group: %s\n", student_tut_grp);
    printf("======================================\n");
    printf("How many bits do you want to do this in (must be [2, 32])? ");
    scanf_s("%d", &n);

    // Check if n is valid.
    if ((n < 2) || (n>33)) {
       printf("Invalid number of bits. Unable to proceed. Exiting...\n");
       return -1;
    }

    printf("\nInput your first number (as signed decimal): ");
    scanf_s("%d", &x);

    // Check that x will fit into n bits. Note that y here is still in two's complement.
    check = validate_1s_complement(x, n); 

    if (check) {
       printf("\nSorry, but %d exceeds the range of a %d-bit one's complement representation. The limit is %d. Exiting...\n",
              x, n, check);
       return -1;
    }

    // The input x is in two's complement. Need to convert it to the one's complement equivalent.
    x1s = twos_to_ones(x);

    printf("\nInput your second number (as signed decimal): ");
    scanf_s("%d", &y);

    // Check that y will fit into n bits. Note that y here is still in two's complement.
    check = validate_1s_complement(y, n); 

    if (check) {
       printf("\nSorry, but %d exceeds the range of a %d-bit one's complement representation. The limit is %d. Exiting...\n",
              y, n, check);
       return -1;
    }

    // The input y is in two's complement. Need to convert it to the one's complement equivalent.
    y1s = twos_to_ones(y);

    printf("\nThe one's complement addition process is as follows:\n\n");

    binstr(x1s, n, x_str);
    binstr(y1s, n, y_str);

    printf("1st number:   %s (%d)\n", x_str, x);
    printf("2nd number:   %s (%d) +\n", y_str, y);

    for (int k=0; k<n; k++)
        printf("-");
    printf("----------------\n");

    perform_addition(n, x_str, y_str, z1_str, c1_str);

    printf("Carry1:      %s\n", c1_str);
    printf("Result1:      %s (%d)", z1_str, str2int(z1_str, n));

    if (check_carryout(c1_str)) { // Carry out!

       printf("\n");

       binstr(1, n, one_str);

       perform_addition(n, z1_str, one_str, z2_str, c2_str);

       printf("              %s +       <-- due to carry out\n", one_str);

       for (int k=0; k<n; k++)
           printf("-");
       printf("----------------\n");

       printf("Carry2:      %s\n", c2_str);
       printf("Result2:      %s", z2_str); 
 
       // Check for overflow
       if (check_overflow(x_str, y_str, z2_str)) {
          printf("\nRESULT OVERFLOWED!!!\n");
          return -1;
       }

       // Everything correct. Print out the decimal value of the result.
       printf(" (%d) [FINAL ANSWER in one's complement]\n", str2int(z2_str, n));
    } else { // No carry out

       // Check for overflow
       if (check_overflow(x_str, y_str, z1_str)) {
          printf("\nRESULT OVERFLOWED!!!\n");
          return -1;
       }

       printf(" [FINAL ANSWER in one's complement]\n");
    }

    printf("\n");
}
