// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 1: Comparing Numbers          MODEL SOLUTION
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
//  TASK 1 - extend the comparison to THREE numbers
//  Read a third integer and report the largest of the three.
// ===========================================================================
void task1()
{
    int largest;

    printf("\n--- Task 1: largest of three numbers ---\n\n");

    _asm {
        // ---- read all three values ------------------------------------
        lea     eax, msgFirst
        push    eax
        call    printf
        add     esp, 4
        lea     eax, first
        push    eax
        lea     eax, format
        push    eax
        call    scanf_s
        add     esp, 8

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

        lea     eax, msgThird
        push    eax
        call    printf
        add     esp, 4
        lea     eax, third
        push    eax
        lea     eax, format
        push    eax
        call    scanf_s
        add     esp, 8

        // ---- running-maximum pattern ------------------------------------
        // Keep the largest value seen so far in eax and compare each new
        // candidate against it.  Two comparisons handle three values.
        mov     eax, first          // assume the first is the largest
        cmp     eax, second
        jge     checkThird          // eax still holds the larger of the two
        mov     eax, second         // second beats it, so eax = second

    checkThird:
        cmp     eax, third
        jge     haveLargest         // current largest still wins
        mov     eax, third          // third beats it

    haveLargest:
        mov     largest, eax        // write the answer back to C++
    }

    printf("\nThe largest of the three is %d.\n", largest);
}

// ===========================================================================
//  TASK 2 - keep asking until the two numbers entered are equal
//  Count how many attempts it takes and report the total.
// ===========================================================================
void task2()
{
    int equalFlag = 0;              // 0 = not yet equal, 1 = equal
    int attempts  = 0;              // how many pairs the user has typed

    printf("\n--- Task 2: repeat until the two numbers match ---\n");
    printf("Keep entering pairs of numbers until both are the same.\n\n");

    // The repetition is driven by C++.  Each time round, one _asm block does
    // the reading, the counting and the comparison.  Letting C++ own the loop
    // keeps the assembly short enough to read in one go.
    while (equalFlag == 0)
    {
        _asm {
            inc     attempts            // one more attempt, counted in assembly

            lea     eax, msgFirst
            push    eax
            call    printf
            add     esp, 4
            lea     eax, first
            push    eax
            lea     eax, format
            push    eax
            call    scanf_s
            add     esp, 8

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

            xor     edx, edx            // edx = 0, meaning "not equal"
            mov     eax, first
            cmp     eax, second
            jne     storeFlag           // ZF = 0 -> different, leave edx at 0
            mov     edx, 1              // matched

        storeFlag:                      // a label must be followed by an
            mov     equalFlag, edx      //   instruction, so the store lives here
        }

        if (equalFlag == 0)
            printf("\nNot equal yet - try again.\n\n");
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
