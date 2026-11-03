// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 4: A Function That Uses the Stack          MODEL SOLUTION
//
//  Build settings: Win32 Console Application, Visual Studio 2022,
//                  Solution Platform must be x86 (NOT x64).
// ===========================================================================

#include <cstdio>

// ===========================================================================
//  PART A - the main program from the lecture (section 11.4)
//
//  absDiff(a, b) returns |a - b|.
//
//  Stack layout once the compiler has built the frame:
//      [ebp+12]  b            second argument
//      [ebp+8]   a            first argument
//      [ebp+4]   return address
//      [ebp]     saved EBP
//      [ebp-4]   result       local variable
//  You never have to write those offsets: name a, b and result and the
//  compiler substitutes the right offset for you.
// ===========================================================================
int absDiff(int a, int b)
{
    int result;

    _asm {
        push    ebx                 // EBX is callee-saved: preserve it first

        mov     eax, a              // eax = a          (from [ebp+8])
        mov     ebx, b              // ebx = b          (from [ebp+12])
        sub     eax, ebx            // eax = a - b, and the flags now describe it

        jns     done                // SF = 0 -> already positive or zero
        neg     eax                 // otherwise flip the sign

    done:
        mov     result, eax         // store into the local          ([ebp-4])

        pop     ebx                 // restored on EVERY path out of the block
    }

    return result;                  // clear, readable, and portable
}

void partA()
{
    int fromCpp;
    int fromAsm;

    printf("--- Part A: absDiff using stack parameters ---\n\n");

    // Called the ordinary way - C++ pushes the arguments for us.
    fromCpp = absDiff(10, 3);

    // Called by hand, so you can see exactly what a call costs.
    _asm {
        push    3                   // LAST argument is pushed FIRST
        push    10                  // so 10 ends up nearest the top of the
                                    //   stack, where the callee looks for
                                    //   its first parameter at [ebp+8]
        call    absDiff
        add     esp, 8              // __cdecl: the CALLER removes the
                                    //   arguments - 2 x 4 bytes
        mov     fromAsm, eax        // the result comes back in EAX
    }

    printf("  |10 - 3| called from C++       = %d\n", fromCpp);
    printf("  |10 - 3| called from assembly  = %d\n", fromAsm);
    printf("  |3 - 10| (arguments swapped)   = %d\n", absDiff(3, 10));
    printf("\nBoth routes run exactly the same instructions.\n");
}

// ===========================================================================
//  TASK 1 - a function with THREE stack parameters
//  maxOf3(a, b, c) returns the largest of the three.
//
//      [ebp+16]  c
//      [ebp+12]  b
//      [ebp+8]   a
// ===========================================================================
int maxOf3(int a, int b, int c)
{
    int result;

    _asm {
        mov     eax, a              // running maximum starts as a
        cmp     eax, b
        jge     checkC              // a >= b, so keep a
        mov     eax, b              // b wins so far

    checkC:
        cmp     eax, c
        jge     haveMax             // current best still wins
        mov     eax, c              // c wins

    haveMax:
        mov     result, eax
    }

    return result;
}

void task1()
{
    int answer;
    int a = 10, b = 3, c = 25;

    printf("\n--- Task 1: a three-parameter function ---\n\n");

    _asm {
        push    c                   // third argument pushed first
        push    b
        push    a                   // first argument pushed last
        call    maxOf3
        add     esp, 12             // THREE arguments now: 3 x 4 = 12 bytes
        mov     answer, eax
    }

    printf("  maxOf3(%d, %d, %d) = %d\n", a, b, c, answer);
    printf("  maxOf3(-5, -20, -1) = %d\n", maxOf3(-5, -20, -1));
    printf("\nThree arguments means ADD ESP, 12. Get that number wrong and the\n");
    printf("stack drifts a little further out of balance on every call.\n");
}

// ===========================================================================
//  TASK 2 - return TWO results through pointer arguments
//  minMax(a, b, &lo, &hi) writes the smaller value into *lo and the larger
//  into *hi.  EAX can only bring one value back, so anything beyond the
//  first result has to travel through memory.
//
//      [ebp+20]  hi     an ADDRESS
//      [ebp+16]  lo     an ADDRESS
//      [ebp+12]  b
//      [ebp+8]   a
// ===========================================================================
void minMax(int a, int b, int* lo, int* hi)
{
    _asm {
        push    ebx

        mov     eax, a
        mov     edx, b
        cmp     eax, edx
        jle     inOrder             // a <= b, so eax is already the smaller
        xchg    eax, edx            // one instruction swaps the two registers

    inOrder:                        // eax = smaller, edx = larger

        mov     ebx, lo             // ebx = the VALUE of the pointer,
                                    //   which is the address to write to
        mov     [ebx], eax          // *lo = smaller
                                    // the brackets mean "go to that address"

        mov     ebx, hi
        mov     [ebx], edx          // *hi = larger

        pop     ebx
    }
}

void task2()
{
    int lo = 0, hi = 0;

    printf("\n--- Task 2: returning results through pointers ---\n\n");

    minMax(10, 3, &lo, &hi);
    printf("  minMax(10, 3)   -> lo = %d, hi = %d\n", lo, hi);

    minMax(-7, 42, &lo, &hi);
    printf("  minMax(-7, 42)  -> lo = %d, hi = %d\n", lo, hi);

    minMax(5, 5, &lo, &hi);
    printf("  minMax(5, 5)    -> lo = %d, hi = %d\n", lo, hi);

    printf("\nMOV EBX, lo loads the pointer. MOV [EBX], EAX writes through it.\n");
    printf("Forgetting the brackets would overwrite the pointer, not the target.\n");
}

// ===========================================================================
int main()
{
    int choice = 0;

    do {
        printf("\n===========================================\n");
        printf(" CSI101 Lab 4 - A Function That Uses the Stack\n");
        printf("===========================================\n");
        printf(" 1. Part A - absDiff(a, b)\n");
        printf(" 2. Task 1 - maxOf3(a, b, c)\n");
        printf(" 3. Task 2 - minMax through pointers\n");
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
