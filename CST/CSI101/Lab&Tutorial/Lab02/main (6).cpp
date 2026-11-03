// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 2: Logical and Arithmetic Shifts          STUDENT STARTER
//
//  Part A below is complete - build it, run it, and read it first.
//  Task 1 and Task 2 are yours to write. Follow the TODO comments.
//
//  Build settings: Win32 Console Application, Visual Studio 2022,
//                  Solution Platform must be x86 (NOT x64).
// ===========================================================================

#include <cstdio>

// ===========================================================================
//  PART A - the main program from the lecture (section 11.2)
//  Show that SHR and SAR give different answers for a negative value.
// ===========================================================================
void partA()
{
    int value = -32;
    int logical, arithmetic, leftShift;

    printf("--- Part A: SHR, SAR and SHL on %d ---\n\n", value);

    _asm {
        mov     eax, value
        shr     eax, 2              // LOGICAL right shift: zeros come in at the top
        mov     logical, eax

        mov     eax, value
        sar     eax, 2              // ARITHMETIC right shift: the sign bit is copied
        mov     arithmetic, eax

        mov     eax, value
        shl     eax, 1              // left shift by 1 = multiply by 2
        mov     leftShift, eax
    }

    printf("  shr eax, 2  ->  %d\n", logical);       // 1073741816 - sign bit lost
    printf("  sar eax, 2  ->  %d\n", arithmetic);    // -8         - correct
    printf("  shl eax, 1  ->  %d\n", leftShift);     // -64
    printf("\nOnly SAR gives the arithmetically correct -32 / 4 = -8.\n");
    printf("Use SAR for signed values and SHR for unsigned values.\n");
}

// ===========================================================================
//  TASK 1 - see the lab handout for the full specification
// ===========================================================================
void task1()
{
    int value = 0;
    int count = 0;
    int logical = 0, arithmetic = 0, leftShift = 0;

    printf("\n--- Task 1: shift by a count held in CL ---\n\n");

    printf("Enter an integer (try a negative one): ");
    if (scanf_s("%d", &value) != 1) return;
    printf("Enter a shift count (0 to 31): ");
    if (scanf_s("%d", &count) != 1) return;

    if (count < 0 || count > 31) {
        printf("A 32-bit shift count outside 0..31 is not meaningful. Stopping.\n");
        return;
    }

    // TODO 1a. A shift count that is not a constant must be in CL, and CL
    //          cannot be loaded straight from a 32-bit variable.  Load the
    //          whole count into ECX first:   mov ecx, count
    //
    // TODO 1b. Produce three results, reloading 'value' before each one:
    //              shr eax, cl   -> logical
    //              sar eax, cl   -> arithmetic
    //              shl eax, cl   -> leftShift

    printf("\n  value    = %d\n", value);
    printf("  shr by %-2d = %d\n", count, logical);
    printf("  sar by %-2d = %d\n", count, arithmetic);
    printf("  shl by %-2d = %d\n", count, leftShift);
}

// ===========================================================================
//  TASK 2 - see the lab handout for the full specification
// ===========================================================================
void task2()
{
    int value = 0;
    int ones  = 0;

    printf("\n--- Task 2: count the 1-bits ---\n\n");
    printf("Enter an integer: ");
    if (scanf_s("%d", &value) != 1) return;

    // TODO 2a. Save EBX before you use it, and restore it before the block
    //          ends.  It is one of the registers you must preserve.
    //
    // TODO 2b. Set up:  eax = value,  ebx = 0 (the count),  ecx = 32.
    //
    // TODO 2c. Loop 32 times.  Each time round, SHR EAX, 1 pushes the bottom
    //          bit out into the CARRY flag.  Use JNC to skip the count when
    //          that bit was 0, and INC EBX when it was 1.  Finish the loop
    //          body with the LOOP instruction - it changes no flags, so it
    //          will not disturb your carry test.
    //
    // TODO 2d. Copy EBX into 'ones'.

    printf("\n%d has %d bit(s) set to 1 out of 32.\n", value, ones);
    printf("(Check: -1 has 32, 0 has 0, 255 has 8, -32 has 27.)\n");
}

// ===========================================================================
int main()
{
    int choice = 0;

    do {
        printf("\n=========================================\n");
        printf(" CSI101 Lab 2 - Logical and Arithmetic Shifts\n");
        printf("=========================================\n");
        printf(" 1. Part A - SHR, SAR and SHL on -32\n");
        printf(" 2. Task 1 - shift by a count in CL\n");
        printf(" 3. Task 2 - count the 1-bits\n");
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
