// YOU ARE NOT TO SUBMIT THIS FILE.
// It is strictly for testing your code.
//

#include <stdio.h>
#include <stdlib.h> // Provides the exit() function to abort.

extern const char *student_number;
extern const char *student_name;
extern const char *student_tut_grp;

extern int twos_to_ones(int x);

extern void binstr(int i, int n, char *s);

extern int str2int(char *s, int n);

extern int validate_1s_complement(int x, int n);

extern int check_carryout(char *carry_str);

extern int check_overflow(char *op1, char *op2, char *sum);

extern int perform_addition(int n, char *x, char *y, char *z, char *c);

int main(int argc, char *argv[])
{
    int x, y, z, n, check;
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
    scanf("%d", &n);

    // Check if n is valid.
    if ((n < 2) || (n>33)) {
       printf("Invalid number of bits. Unable to proceed. Exiting...\n");
       exit(-1);
    }

    printf("\nInput your first number (as signed decimal): ");
    scanf("%d", &x);

    // Check that x will fit into n bits. Note that y here is still in two's complement.
    check = validate_1s_complement(x, n); 

    if (check) {
       printf("\nSorry, but %d exceeds the range of a %d-bit one's complement representation. The limit is %d. Exiting...\n",
              x, n, check);
       exit(-1);
    }

    // The input x is in two's complement. Need to convert it to the one's complement equivalent.
    x1s = twos_to_ones(x);

    printf("\nInput your second number (as signed decimal): ");
    scanf("%d", &y);

    // Check that y will fit into n bits. Note that y here is still in two's complement.
    check = validate_1s_complement(y, n); 

    if (check) {
       printf("\nSorry, but %d exceeds the range of a %d-bit one's complement representation. The limit is %d. Exiting...\n",
              y, n, check);
       exit(-1);
    }

    // The input y is in two's complement. Need to convert it to the one's complement equivalent.
    y1s = twos_to_ones(y);

    printf("\nThe one's complement addition process is as follows:\n\n");

    binstr(x1s, n, x_str);

    binstr(y1s, n, y_str);

    perform_addition(n, x_str, y_str, z1_str, c1_str);

    // Print what we had achieved so far.
    printf("X:   %s (%d)\n", x_str, x);
    printf("Y:   %s (%d) +\n", y_str, y);

    for (int k=0; k<n; k++)
        printf("-");
    printf("----------------\n");

    printf("C1: %s\n", c1_str);
    printf("Z1:  %s (%d)", z1_str, str2int(z1_str, n));

    if (check_carryout(c1_str)) { // Carry out!

       printf("\n");

       binstr(1, n, one_str);

       perform_addition(n, z1_str, one_str, z2_str, c2_str);

       printf("     %s +       <-- due to carry out\n", one_str);

       for (int k=0; k<n; k++)
           printf("-");
       printf("----------------\n");

       printf("C2: %s\n", c2_str);
       printf("Z2:  %s", z2_str); 
 
       // Check for overflow
       if (check_overflow(x_str, y_str, z2_str)) {
          printf("\nRESULT OVERFLOWED!!!\n");
          exit(-1);
       }

       // Everything correct. Print out the decimal value of the result.
       printf(" (%d) [FINAL ANSWER in one's complement]\n", str2int(z2_str, n));
    } else { // No carry out

       // Check for overflow
       if (check_overflow(x_str, y_str, z1_str)) {
          printf("\nRESULT OVERFLOWED!!!\n");
          exit(-1);
       }

       printf(" [FINAL ANSWER in one's complement]\n");
    }

    printf("\n");
}
