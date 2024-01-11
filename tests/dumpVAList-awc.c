#include "tests.h"

int dumpCount = 0;

void dumpVAList(va_list l){
    fputs("--------- dump vaList call ", stderr);printNumber(dumpCount++);fputs(" ---------\n", stderr);
    fputs("va_list: ", stderr); printAddress(l);fputc('\n', stderr);
    fputs("gp_offset: ", stderr); printNumber(l[0].gp_offset);fputc('\n', stderr);
    fputs("fp_offset: ", stderr); printNumber(l[0].fp_offset);fputc('\n', stderr);
    fputs("overflow_arg_area: ", stderr); printAddress(l[0].overflow_arg_area);fputc('\n', stderr);
    fputs("reg_save_area: ", stderr); printAddress(l[0].reg_save_area);fputc('\n', stderr);
    fputs("remaining: ", stderr); printNumber(l[0].remaining);fputc('\n', stderr); // Only valid with AWC!
    fflush(stderr);
}