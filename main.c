#include <stdlib.h>
#include <stdio.h>

#define MAX_GCSTRING_SIZE 24
#define MAX_AMOUNTS 20

#define OP_ADD 1
#define OP_SUBTRACT -1
#define OP_MULTIPLY 3
#define OP_UKNWN 0
#define OP_CLEAR 2
#define OP_EXIT 99

#define U_GC 1
#define K_GC U_GC * 1000
#define M_GC K_GC * 1000
#define B_GC M_GC * 1000
#define T_GC B_GC * 1000

#define PARSE_ERROR 0
#define SUCCESS 1

#define TRUE 1
#define FALSE 0

int getCommand(char *buf);
int getOperator(char *amt);
long long parse(char *amt);
int multi(char *amt);

void printWelcome();
void printTotal(long long total);
long long pow1000(int multi);

int main() {
    char amount[MAX_GCSTRING_SIZE];
    long long total = 0;

    printWelcome();
    while (getCommand(amount)) {
        switch (getOperator(amount)) {
            case OP_ADD :
                total += parse(amount + 1);
                break;
            case OP_SUBTRACT:
                total -= parse(amount + 1);
                break;
            case OP_MULTIPLY:
                total *= multi(amount + 1);
                break;
            case OP_CLEAR:
                total = 0;
                printf("Total cleared.\n");
                break;
            case OP_EXIT:
                return EXIT_SUCCESS;
            default:
                fprintf(stderr, "Invalid operator.\n");
                break;
        }

        printTotal(total);
        printf("\n");
    }

    return 0;
}

int getCommand(char *buf)
{
    printf("> ");
    return (fgets(buf, MAX_GCSTRING_SIZE, stdin) != NULL);
}

int getOperator(char *amt) {
    switch (amt[0]) {
        case '+':
            return OP_ADD;
        case '-':
            return OP_SUBTRACT;
        case '*':
            return OP_MULTIPLY;
        case 'q':
            return OP_EXIT;
        case 'c':
            return OP_CLEAR;
        default:
            return OP_UKNWN;
    }
}

long long parse(char *amt) {
    if (amt[0] == ' ')
        amt++;

    long long total = 0;
    int done_f = FALSE;

    while (!done_f) {
        long long val = strtol(amt, &amt, 10);

        if (val >= 1000 || val < 0) {
            fprintf(stderr, "Invalid GC string format.\n");
            return PARSE_ERROR;
        }

        switch (amt[0]) {
            case 'T':
                total += val * T_GC;
                break;
            case 'B':
                total += val * B_GC;
                break;
            case 'M':
                total += val * M_GC;
                break;
            case 'K':
                total += val * K_GC;
                break;
            case 'G':
                if (amt[1] == 'C') {
                    total += val * U_GC;
                    done_f = TRUE;
                    break;
                }
            default:
                fprintf(stderr, "Invalid GC string format.\n");
                return PARSE_ERROR;
        }

        amt++;
    }

    return total;
}

int multi(char *amt) {
    if (amt[0] == ' ')
        amt++;

    int multi = strtol(amt, &amt, 10);
    if (multi == 0) {
        fprintf(stderr, "Invalid multiplier.\n");
        return 1;
    }
    return multi;
}

void printTotal(long long total) {
    char *terms[6] = {"", "K", "M", "B", "T", "Q"};
    int multi;

    if (total < 0) {
        printf("-");
        total = -total;
    } else if (total == 0) {
        printf("0GC\n");
        return;
    }

    for (multi = 5; multi >= 0; multi--) {
        long long p1000 = pow1000(multi);
        int trunc = (int) (total/p1000);
        if (trunc == 0)
            continue;

        printf("%d%s", trunc, terms[multi]);
        total -= trunc*p1000;
    }

    printf("GC\n");
    return;
}

long long pow1000(int multi) {
    long long val = 1;
    for (;multi > 0; multi--)
        val *= 1000;

    return val;
}

void printWelcome() {
    printf("\n");
    printf("-------MxBlue's GC Calculator-------\n");
    printf("\n");
    printf("Usage: <operator> <GC string>\n");
    printf("GC Strings should be in the xxxTxxxBxxxMxxxKxxxGC\n");
    printf("Example: ""10GC"", ""10B10KGC""\n");
    printf("\n");
    printf("Operators:\n");
    printf("   '+'  Add\n");
    printf("   '-'  Subtract\n");
    printf("   '*'  Multiply by number\n");
    printf("   'c'  Clear current total\n");
    printf("   'q'  Quit\n");
    printf("\n");

}
