#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* first target for return value overwrite */
void
demo(void)
{
    printf("I should not be here\n");
    exit(0);
}

/* second target for return value overwrite */
const char *flag = "d4s_flag{sm4sh_th4t_st4ck}";


/* self_hack - function that overwrites its own return value
 *  @target : address to jump to after return
 */
void
self_hack(void (*target)(void))
{
    register uint64_t rbp asm("rbp");

    ((uint64_t *) rbp)[1] = (uint64_t) target;
}

/* usage - prints a help message for this program
 */
int32_t
usage(void)
{
    printf("Usage: ./05-overflow {demo,flag}\n");
    return -1;
}

/* main - prgram entry point
 *  @argc : number of command line arguments
 *  @argv : array of argument strings (first is always the program name)
 *
 *  @return : 0 if everything went well
 */
int32_t
main(int32_t argc, char *argv[])
{
    void *target;

    /* sanity check */
    if (argc != 2)
        return usage();

    /* decide target based on CLI argument */
    if (!strcmp(argv[1], "demo"))
        target = demo;
    else if (!strcmp(argv[1], "flag"))
        target = (void *) flag;
    else
        return usage();

    /* invoke self_hack function */
    printf("Calling self_hack() from main()\n");
    self_hack(target);
    printf("Returned from self_hack() to main()\n");

    return 0;
}

