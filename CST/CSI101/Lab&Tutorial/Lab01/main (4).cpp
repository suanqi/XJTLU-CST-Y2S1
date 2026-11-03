// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 1: Comparing Numbers          STUDENT STARTER
//
//  Part A below is complete - build it, run it, and read it first.
//  Task 1 and Task 2 are yours to write. Follow the TODO comments.
//
//  Build settings: Win32 Console Application, Visual Studio 2022,
//                  Solution Platform must be x86 (NOT x64).
// ===========================================================================

#include <cstdio>

// ---------------------------------------------------------------------------
//  All data is declared in C++.  Inline assembly cannot define data of its
//  own - no DB, DW or DD - so every string and every variable lives here and
//  the _asm blocks simply refer to them by name.
// ---------------------------------------------------------------------------
char msgFirst[]     = "Enter the first number: ";
char msgSecond[]    = "Enter the second number: ";
char msgThird[]     = "Enter the third number: ";
char msgEqual[]     = "\nThe numbers are equal.\n";
char msgFirstBig[]  = "\nThe first is larger.\n";
char msgSecondBig[] = "\nThe second is larger.\n";
char format[]       = "%d";

int first, second, third;

// ===========================================================================
//  PART A - the main program from the lecture (section 11.1)
//  Read two integers, compare them, and report the result.
// ===========================================================================
void partA()
{
    printf("--- Part A: compare two numbers ---\n\n");

    _asm {
        // ---- prompt for and read the first number ----------------------
        lea     eax, msgFirst       // eax = address of the prompt string
        push    eax                 // one argument for printf
        call    printf
        add     esp, 4              // 1 argument x 4 bytes = 4

        lea     eax, first          // scanf_s must WRITE into first,
        push    eax                 //   so it needs the address, not the value
        lea     eax, format         // "%d"
        push    eax                 // format string is pushed last
        call    scanf_s
        add     esp, 8              // 2 arguments x 4 bytes = 8

        // ---- prompt for and read the second number ---------------------
        lea     eax, msgSecond
        push    eax
        call    printf
        add     esp, 4

        lea     eax, second
        push    eax
        lea     eax, format
        push    eax
        call    scanf_s
        add     esp, 8

        // ---- compare, then converge on one exit -------------------------
        mov     eax, first
        cmp     eax, second         // subtracts second from first, keeps flags
        je      equal               // ZF = 1  -> the two are equal
        jg      firstBigger         // SIGNED greater-than; JA would be wrong here

        lea     eax, msgSecondBig   // fell through: second must be larger
        jmp     show

    firstBigger:
        lea     eax, msgFirstBig
        jmp     show

    equal:
        lea     eax, msgEqual

    show:                           // one printf, reached by all three paths
        push    eax
        call    printf
        add     esp, 4
    }
}

// ===========================================================================
//  TASK 1 - see the lab handout for the full specification
// ===========================================================================
void task1()
{
    int largest = 0;

    printf("\n--- Task 1: largest of three numbers ---\n\n");

    // TODO 1a. Prompt for and read a THIRD number into the global 'third'.
    //          Copy the printf / scanf_s pattern from partA - remember that
    //          printf takes one argument (add esp, 4) and scanf_s takes two
    //          (add esp, 8).
    //
    // TODO 1b. Find the largest of first, second and third using the
    //          running-maximum pattern:
    //              mov eax, first      // assume the first one wins
    //              cmp eax, second
    //              jge <skip>          // signed jump - the data may be negative
    //              mov eax, second
    //          then repeat the cmp / jge / mov shape for 'third'.
    //
    // TODO 1c. Finish with  mov largest, eax  so C++ can print the answer.

    printf("\nThe largest of the three is %d.\n", largest);
}

// ===========================================================================
//  TASK 2 - see the lab handout for the full specification
// ===========================================================================
void task2()
{
    int equalFlag = 0;              // 0 = not yet equal, 1 = equal
    int attempts  = 0;              // how many pairs the user has typed

    printf("\n--- Task 2: repeat until the two numbers match ---\n");
    printf("Keep entering pairs of numbers until both are the same.\n\n");

    while (equalFlag == 0)
    {
        _asm {
            // TODO 2a. Add 1 to 'attempts' with a single INC instruction.
            //
            // TODO 2b. Read two numbers into 'first' and 'second', exactly as
            //          partA does.
            //
            // TODO 2c. Compare them and set 'equalFlag' to 1 when they match
            //          and 0 when they do not.  Build it around JNE, and put
            //          the store AFTER the label - a label must always be
            //          followed by an instruction:
            //              xor edx, edx
            //              ...
            //              jne storeFlag
            //              mov edx, 1
            //          storeFlag:
            //              mov equalFlag, edx
            nop
        }

        if (equalFlag == 0)
            printf("\nNot equal yet - try again.\n\n");
        else
            break;                  // remove this once TODO 2c is written
    }

    printf("\nMatched after %d attempt(s).\n", attempts);
}

// ===========================================================================
int main()
{
    int choice = 0;

    do {
        printf("\n=====================================\n");
        printf(" CSI101 Lab 1 - Comparing Numbers\n");
        printf("=====================================\n");
        printf(" 1. Part A - compare two numbers\n");
        printf(" 2. Task 1 - largest of three\n");
        printf(" 3. Task 2 - repeat until equal\n");
        printf(" 0. Exit\n");
        printf("Choose: ");

        if (scanf_s("%d", &choice) != 1)
            return 0;                       // non-numeric input: give up tidily

        switch (choice) {
        case 1: partA(); break;
        case 2: task1(); break;
        case 3: task2(); break;
        }
    } while (choice != 0);

    return 0;
}
