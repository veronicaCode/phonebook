#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define MAX_HASH_SIZE 100

/* original version */
typedef struct __PHONE_BOOK_DETAIL {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} detail;

typedef struct __PHONE_BOOK_NEW {
    char lastName[MAX_LAST_NAME_SIZE];
    detail * personDetail;
    struct __PHONE_BOOK_NEW * pNext;
}entry;

entry *hash_table[MAX_HASH_SIZE];

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
