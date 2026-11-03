// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 3: ECX as an Automatic Loop Counter          STUDENT STARTER
//
//  Part A below is complete - build it, run it, and read it first.
//  Task 1 and Task 2 are yours to write. Follow the TODO comments.
//
//  Build settings: Win32 Console Application, Visual Studio 2022,
//                  Solution Platform must be x86 (NOT x64).
// ===========================================================================

#include <cstdio>

// A preprocessor macro, not a const int.  #define SIZE 5 becomes the plain
// number 5 by the time the assembler sees it, which is what "mov ecx, SIZE"
// needs.  A const int is a variable, and would be read from memory instead.
#define SIZE 5

int data[SIZE] = { 4, 8, 15, 16, 23 };

// ===========================================================================
//  PART A - the main program from the lecture (section 11.3)
//  Two uses of LOOP: a counted sum, and a walk along an array.
// ===========================================================================
void partA()
{
    int total = 0;
    int arrayTotal = 0;

    printf("--- Part A: LOOP as an automatic counter ---\n\n");

    // ---- sum the integers from 1 to 10 --------------------------------
    _asm {
        xor     eax, eax            // total = 0 (faster than mov eax, 0)
        mov     ecx, 10             // LOOP always counts down in ECX

    sumLoop:
        add     eax, ecx            // add the current counter value
        loop    sumLoop             // dec ecx, then jump back while ecx != 0

        mov     total, eax          // 10+9+8+...+1 = 55
    }

    // ---- sum the five elements of the array ----------------------------
    _asm {
        push    esi                 // ESI must be preserved across the block

        lea     esi, data           // esi = address of data[0]
        xor     eax, eax            // running total
        mov     ecx, SIZE           // five elements, so five iterations

    nextItem:
        add     eax, [esi]          // add the int that esi points at
        add     esi, 4              // step on by one int (4 bytes)
        loop    nextItem

        mov     arrayTotal, eax     // 4+8+15+16+23 = 66

        pop     esi                 // restore it before leaving
    }

    printf("  Sum of 1..10           = %d\n", total);
    printf("  Sum of the array       = %d\n", arrayTotal);
    printf("\nLOOP does two jobs at once: it decrements ECX and it jumps.\n");
}

// ===========================================================================
//  TASK 1 - see the lab handout for the full specification
// ===========================================================================
void task1()
{
    int evenSum   = 0;
    int evenCount = 0;

    printf("\n--- Task 1: sum only the even values ---\n\n");

    // TODO 1a. Save ESI and EBX at the start of the block and restore them at
    //          the end, in the reverse order.
    //
    // TODO 1b. Set up:  esi = address of data (LEA),  eax = 0 (sum),
    //          ebx = 0 (count),  ecx = SIZE.
    //
    // TODO 1c. Inside the loop, copy the current element into EDX, then use
    //              test edx, 1
    //              jnz  <skip>
    //          to skip odd values.  A number is even when its lowest bit is 0.
    //
    // TODO 1d. For even values, add EDX to EAX and INC EBX.  Then step ESI on
    //          by 4 bytes and finish with LOOP.
    //
    // TODO 1e. Store EAX into evenSum and EBX into evenCount.

    printf("  Array           = { 4, 8, 15, 16, 23 }\n");
    printf("  Even values     = %d\n", evenCount);
    printf("  Sum of evens    = %d\n", evenSum);
}

// ===========================================================================
//  TASK 2 - see the lab handout for the full specification
// ===========================================================================
void task2()
{
    int largest  = 0;
    int smallest = 0;

    printf("\n--- Task 2: largest and smallest in one pass ---\n\n");

    // TODO 2a. Save ESI and EBX, and restore them at the end.
    //
    // TODO 2b. Load the address of data into ESI, then take element 0 as the
    //          starting guess for BOTH answers:  eax = [esi],  ebx = eax.
    //
    // TODO 2c. Element 0 is already accounted for, so set ecx = SIZE and then
    //          DEC ECX, and step ESI on by 4 before the loop begins.
    //
    // TODO 2d. In the loop, put the candidate in EDX and make two signed
    //          comparisons: replace EAX when EDX is larger, replace EBX when
    //          EDX is smaller.  Use JLE and JGE to skip over the updates.
    //
    // TODO 2e. Store EAX into largest and EBX into smallest.

    printf("  Array           = { 4, 8, 15, 16, 23 }\n");
    printf("  Largest         = %d\n", largest);
    printf("  Smallest        = %d\n", smallest);
}

// ===========================================================================
int main()
{
    int choice = 0;

    do {
        printf("\n=============================================\n");
        printf(" CSI101 Lab 3 - ECX as an Automatic Loop Counter\n");
        printf("=============================================\n");
        printf(" 1. Part A - sum 1..10 and sum an array\n");
        printf(" 2. Task 1 - sum only the even values\n");
        printf(" 3. Task 2 - largest and smallest in one pass\n");
        printf(" 0. Exit\n");
        printf("Choose: ");

        if (scanf_s("%d", &choice) != 1)
            return 0;

        switch (choice) {
        case 1: partA(); break;
        case 2: task1(); break;
        case 3: task2(); break;
        }
    } while (choice != 0);

    return 0;
}
