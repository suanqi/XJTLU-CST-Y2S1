// ===========================================================================
//  CSI101 Computer Systems - Assembly Programming
//  Lab 2: Logical and Arithmetic Shifts          MODEL SOLUTION
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
//  TASK 1 - take the shift count from CL instead of using a constant
//  Ask the user for a value and a shift count, then shift by that amount.
// ===========================================================================
void task1()
{
    int value = 0;
    int count = 0;
    int logical, arithmetic, leftShift;

    printf("\n--- Task 1: shift by a count held in CL ---\n\n");

    printf("Enter an integer (try a negative one): ");
    if (scanf_s("%d", &value) != 1) return;
    printf("Enter a shift count (0 to 31): ");
    if (scanf_s("%d", &count) != 1) return;

    if (count < 0 || count > 31) {
        printf("A 32-bit shift count outside 0..31 is not meaningful. Stopping.\n");
        return;
    }

    _asm {
        // A shift count that is not a constant MUST be in CL - no other
        // register will do.  CL is the low byte of ECX, and we cannot load a
        // byte register directly from a 32-bit variable, so load ECX first
        // and then use its low byte.
        mov     ecx, count          // ecx = the whole 32-bit count
                                    // cl is now the bottom byte of that value

        mov     eax, value
        shr     eax, cl             // logical  - zeros shifted in
        mov     logical, eax

        mov     eax, value
        sar     eax, cl             // arithmetic - sign preserved
        mov     arithmetic, eax

        mov     eax, value
        shl     eax, cl             // left shift - same instruction either way
        mov     leftShift, eax
    }

    printf("\n  value    = %d\n", value);
    printf("  shr by %-2d = %d\n", count, logical);
    printf("  sar by %-2d = %d\n", count, arithmetic);
    printf("  shl by %-2d = %d\n", count, leftShift);

    if (value < 0)
        printf("\nNegative input: notice SHR and SAR disagree, SAR is the correct divide.\n");
    else
        printf("\nNon-negative input: SHR and SAR agree, because the sign bit is 0.\n");
}

// ===========================================================================
//  TASK 2 - count how many bits are set to 1 in a 32-bit integer
//  Shift the value right one place at a time and test the carry flag.
// ===========================================================================
void task2()
{
    int value = 0;
    int ones  = 0;

    printf("\n--- Task 2: count the 1-bits ---\n\n");
    printf("Enter an integer: ");
    if (scanf_s("%d", &value) != 1) return;

    _asm {
        push    ebx                 // EBX must be preserved - save it first

        mov     eax, value
        xor     ebx, ebx            // ebx = 0, the running count of 1-bits
        mov     ecx, 32             // an int is 32 bits, so 32 iterations

    countLoop:
        shr     eax, 1              // the bit shifted out lands in the CARRY flag
        jnc     noBit               // CF = 0 -> that bit was a 0, skip
        inc     ebx                 // CF = 1 -> count it
                                    // INC does not disturb CF, but we have
                                    //   already used it, so that is fine
    noBit:
        loop    countLoop           // dec ecx, jump back while ecx != 0
                                    // LOOP changes no flags at all

        mov     ones, ebx           // write the count back to C++

        pop     ebx                 // restore on the way out
    }

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
