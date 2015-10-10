#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

int hash_31(char *s) {
    unsigned value = 0;
    for (; (*s) !='\0'; s++)
        value = (value << 5) - (value + (*s));
    return value % MAX_HASH_SIZE;
}


/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    /* TODO: implement */
   #if 0
   while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
    #else
    int hash;
    entry *e;
    hash = hash_31(lastname);
    e = hash_table[hash];
    while (e != NULL) {
        if (strcasecmp(lastname, e->lastName) == 0) {
            return e;
        }
        e = e->pNext;
    }
    return NULL;
    #endif
}

entry *append(char lastName[], entry *e)
{
    int hash;
    entry *p;
    p = (entry *) malloc(sizeof(entry));
    p->pNext = NULL;
    strcpy(p->lastName, lastName);
    hash = hash_31(lastName);
    if (hash_table[hash] == NULL) {
        hash_table[hash] = p; 
    }
    else {
        p->pNext = hash_table[hash];
        hash_table[hash] = p;
    }
    return p;
}
