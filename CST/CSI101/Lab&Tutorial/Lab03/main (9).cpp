// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 3: ECX as an Automatic Loop Counter          MODEL SOLUTION
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
//  TASK 1 - add up only the EVEN values in the array, and count them
//  A number is even when its lowest bit is 0, which TEST can check.
// ===========================================================================
void task1()
{
    int evenSum   = 0;
    int evenCount = 0;

    printf("\n--- Task 1: sum only the even values ---\n\n");

    _asm {
        push    esi                 // preserve the registers we borrow
        push    ebx

        lea     esi, data           // esi = address of data[0]
        xor     eax, eax            // eax = running sum of even values
        xor     ebx, ebx            // ebx = how many even values we found
        mov     ecx, SIZE           // loop counter

    nextItem:
        mov     edx, [esi]          // edx = the current element

        test    edx, 1              // AND with 1, keep only the flags
        jnz     skipOdd             // ZF = 0 means the low bit was 1 -> odd

        add     eax, edx            // even, so add it in
        inc     ebx                 // and count it

    skipOdd:
        add     esi, 4              // move to the next int
        loop    nextItem            // LOOP changes no flags, so it is safe here

        mov     evenSum, eax
        mov     evenCount, ebx

        pop     ebx                 // restore in the REVERSE order
        pop     esi
    }

    printf("  Array           = { 4, 8, 15, 16, 23 }\n");
    printf("  Even values     = %d\n", evenCount);      // 3
    printf("  Sum of evens    = %d\n", evenSum);        // 28
}

// ===========================================================================
//  TASK 2 - find the largest AND the smallest value in one pass
//  Two running comparisons inside a single LOOP.
// ===========================================================================
void task2()
{
    int largest  = 0;
    int smallest = 0;

    printf("\n--- Task 2: largest and smallest in one pass ---\n\n");

    _asm {
        push    esi
        push    ebx

        lea     esi, data
        mov     eax, [esi]          // assume element 0 is the largest ...
        mov     ebx, eax            // ... and also the smallest

        mov     ecx, SIZE
        dec     ecx                 // element 0 is already accounted for,
                                    //   so only SIZE-1 comparisons remain
        add     esi, 4              // start the scan at element 1

    scanLoop:
        mov     edx, [esi]          // edx = the candidate

        cmp     edx, eax
        jle     checkSmallest       // SIGNED jump - the data may be negative
        mov     eax, edx            // new largest

    checkSmallest:
        cmp     edx, ebx
        jge     nextOne
        mov     ebx, edx            // new smallest

    nextOne:
        add     esi, 4
        loop    scanLoop

        mov     largest, eax
        mov     smallest, ebx

        pop     ebx
        pop     esi
    }

    printf("  Array           = { 4, 8, 15, 16, 23 }\n");
    printf("  Largest         = %d\n", largest);        // 23
    printf("  Smallest        = %d\n", smallest);       // 4
    printf("\nNote the DEC ECX before the loop: if SIZE were 1, ECX would reach\n");
    printf("zero here and LOOP would wrap round to 4,294,967,295 iterations.\n");
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
