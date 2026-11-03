// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 4: A Function That Uses the Stack          STUDENT STARTER
//
//  Part A below is complete - build it, run it, and read it first.
//  Task 1 and Task 2 are yours to write. Follow the TODO comments.
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
//  TASK 1 - see the lab handout for the full specification
// ===========================================================================
int maxOf3(int a, int b, int c)
{
    int result = 0;

    // TODO 1a. Use the running-maximum pattern from Lab 1:
    //              mov eax, a
    //              cmp eax, b
    //              jge <skip>
    //              mov eax, b
    //          then compare the winner against c the same way.
    //
    // TODO 1b. Finish with  mov result, eax.
    //
    // You do not need to save any registers here: EAX, ECX and EDX are all
    // free to use.

    return result;
}

void task1()
{
    int answer = 0;
    int a = 10, b = 3, c = 25;

    printf("\n--- Task 1: a three-parameter function ---\n\n");

    // TODO 1c. Call maxOf3 by hand from an _asm block.  Push the arguments
    //          right to left (c, then b, then a), CALL maxOf3, then clean up
    //          with ADD ESP, 12 - three arguments at four bytes each.  The
    //          result arrives in EAX.

    printf("  maxOf3(%d, %d, %d) = %d\n", a, b, c, answer);
    printf("  maxOf3(-5, -20, -1) = %d\n", maxOf3(-5, -20, -1));
}

// ===========================================================================
//  TASK 2 - see the lab handout for the full specification
// ===========================================================================
void minMax(int a, int b, int* lo, int* hi)
{
    // TODO 2a. Save EBX at the start and restore it at the end.
    //
    // TODO 2b. Load a into EAX and b into EDX, compare them, and arrange for
    //          EAX to hold the smaller and EDX the larger.  XCHG EAX, EDX
    //          swaps two registers in a single instruction.
    //
    // TODO 2c. 'lo' and 'hi' are ADDRESSES.  Load one into EBX with MOV (not
    //          LEA - the pointer's value is already the address you want),
    //          then write through it:
    //              mov ebx, lo
    //              mov [ebx], eax
    //          Repeat for hi.  Forget the brackets and you overwrite the
    //          pointer instead of the thing it points at.
    (void)a; (void)b; (void)lo; (void)hi;   // delete this line when you start
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
