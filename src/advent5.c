/*
 ============================================================================
 Name        : advent5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

static char sequence[100*1024];
static char orig[100*1024];

int reduce(void);
int removeElem(char c);

int main(void)
{
    FILE * input;

    input = fopen("input.txt", "r");
    if (input)
    {
        fgets(orig, sizeof(orig), input);
        printf("len %i\n", strlen(sequence));

//        strcpy(sequence, "dabAcCaCBAcCcaDA");

        uint32_t shortestlen = -1;
        char shortest;

        for (char c = 'a'; c <= 'z'; c++)
        {
            uint32_t reductions = 0;
            uint32_t reduced = 0;
            strcpy(sequence, orig);
            removeElem(c);
            do
            {
                reduced = reduce();
                reductions += reduced;
            } while (reduced);

//            printf("result: %s\n", sequence);
            if (strlen(sequence) < shortestlen)
            {
                shortest = c;
                shortestlen = strlen(sequence);
            }

            printf("len %i\n", strlen(sequence));
        }

        printf("shortest reduction is %c with %i\n", shortest, shortestlen);

        return 0;
    }
    return 1;
}

int removeElem(char c)
{
    int reduced = 0;
    uint32_t index = 0;
    uint32_t len = strlen(sequence);

    while (sequence[index] != 0)
    {
        // same element
        if (tolower(sequence[index]) == c)
        {
            // flag return
            reduced++;
            // shift in rest of string
            memcpy(&sequence[index], &sequence[index+1], len - index);
            len--;
            // hack to undo the increment
            index--;
        }
        index++;
    }

    return reduced;
}

int reduce(void)
{
    int reduced = 0;
    uint32_t index = 1;
    uint32_t len = strlen(sequence);

    while (sequence[index] != 0)
    {
        // same element
        if (tolower(sequence[index-1]) == tolower(sequence[index]))
        {
            // opposite polarity
            if (sequence[index-1] != sequence[index])
            {
                // flag return
                reduced++;
                // shift in rest of string
                memcpy(&sequence[index-1], &sequence[index+1], len - index);
                len-=2;
                // hack to undo the increment
                index--;
                return (reduced);
            }
        }
        index++;
    }

    return reduced;
}
