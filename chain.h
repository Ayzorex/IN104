#ifndef __CHAIN_H__
#define __CHAIN_H__

struct Chain_link
{
    char* word;
    struct Chain_link* next;
};

#endif
