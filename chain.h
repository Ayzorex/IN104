#ifndef __CHAIN_H__
#define __CHAIN_H__

struct Chain_link
{
    char* word;
    struct Chain_link* next;
};

struct Chain_head
{
    unsigned int size;
    struct Chain_link* chain_first;
    struct Chain_link* chain_last;
};


#endif
