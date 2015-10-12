#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#define MAX_LAST_NAME_SIZE 16
#define _BST_

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

#ifndef _BST_
typedef struct __PHONE_BOOK_NEW {
    char lastName[MAX_LAST_NAME_SIZE];
    detail * personDetail;
    struct __PHONE_BOOK_NEW * pNext;
}entry;
#endif

#ifdef _HASH_
#define MAX_HASH_SIZE 100
entry *hash_table[MAX_HASH_SIZE];
int hash_num_count[MAX_HASH_SIZE];
#endif

#ifdef _BST_
typedef struct __PHONE_BOOK_BST {
    char lastName[MAX_LAST_NAME_SIZE];
    detail * personDetail;
    enum {RED, BLACK} color;
    struct __PHONE_BOOK_BST * leftNode;
    struct __PHONE_BOOK_BST * rightNode;
    struct __PHONE_BOOK_BST * parent;
    struct __PHONE_BOOK_BST * pNext;
}entry;
entry * root;
#endif
entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
