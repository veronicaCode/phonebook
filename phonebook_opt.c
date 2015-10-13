#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

#ifdef _HASH_
int hash_31(char *s)
{
    unsigned value = 0;
    for (; (*s) !='\0'; s++)
        value = (value << 5) - (value + (*s));
    return value % MAX_HASH_SIZE;
}
#endif

#ifdef _BST_
entry * left_rotate(entry *e, entry*x)
{
    entry * y = x->rightNode;
    x->rightNode = y->leftNode;
    if (y->leftNode != NULL)
        y->leftNode->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        e = y;
    else {
        if (x == x->parent->leftNode)
            x->parent->leftNode = y;
        else
            x->parent->rightNode = y;
    }
    y->leftNode = x;
    x->parent = y;
    return e;
}

entry * right_rotate(entry *e, entry *x)
{
    entry *y = x->leftNode;
    x->leftNode = y->rightNode;
    if (y->rightNode != NULL)
        y->rightNode->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        e = y;
    else {
        if (x == x->parent->leftNode)
            y->parent->leftNode = y;
        else
            y->parent->rightNode = y;
    }
    y->rightNode = x;
    x->parent = y;
    return e;
}

entry *  INSERT_FIX(entry *e, entry *z)
{
    while ( (z != e) && (z->parent->color == RED) ) {
        if( z->parent == z->parent->parent->leftNode) {
            entry *y = z->parent->parent->rightNode;
            if ((y != NULL) && (y->color == RED)) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else { // y is a black node
                if (z == z->parent->rightNode) {
                    z = z->parent;
                    e = left_rotate(e, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                e = right_rotate(e, z->parent->parent);
            }
        } else {
            entry * y = z->parent->parent->leftNode;
            if ( (y != NULL) && (y->color == RED)) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->leftNode) {
                    z = z->parent;
                    e = right_rotate( e, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                e = left_rotate(e, z->parent->parent);
            }
        }
    }
    e->color = BLACK;
    return e;
}
#endif

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
#if 0
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
#endif
#ifdef _HASH_
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
#ifdef _BST_
    entry *e;
    e = pHead;
    int cmp;
    while (e != NULL) {
        cmp = strcasecmp(lastname, e->lastName);
        if (cmp == 0) {
            return e;
        } else if(cmp < 0)
            e = e->leftNode;
        else
            e = e->rightNode;
    }
    return NULL;
#endif
}

entry *append(char lastName[], entry *e)
{
#ifdef _HASH_
    int hash;
    entry *p;
    p = (entry *) malloc(sizeof(entry));
    p->pNext = NULL;
    strcpy(p->lastName, lastName);
    hash = hash_31(lastName);
    hash_num_count[hash]++;
    if (hash_table[hash] == NULL) {
        hash_table[hash] = p;
    } else {
        p->pNext = hash_table[hash];
        hash_table[hash] = p;
    }
    return p;
#endif

#ifdef _BST_
    entry *y = NULL;
    entry *x = e;
    entry *z = (entry *) malloc(sizeof(entry));
    strcpy(z->lastName, lastName);
    while (x != NULL) {
        y = x;
        if (strcasecmp(lastName, x->lastName) < 0)
            x = x->leftNode;
        else
            x = x->rightNode;
    }
    z->parent = y;
    if (y == NULL) {
        e = z;
    } else {
        if (strcmp(lastName, y->lastName) < 0)
            y->leftNode = z;
        else
            y->rightNode = z;
    }
    z->color = RED;
    z->leftNode = NULL;
    z->rightNode = NULL;
    e = INSERT_FIX(e, z);
    return e;
#endif
}
