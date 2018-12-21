#ifndef TAPEUTILS_H
#define TAPEUTILS_H

#include "tapearch.h"
#include "umps/types.h"
#include "umps/arch.h"

static int loadblock(dtpreg_t *tape_reg, unsigned long int  ramaddr){

    unsigned int status;

    while ((status=tape_reg->status)==TAPE_BUSY || (status=tape_reg->status)==TAPE_NOTAPE)
        ;
    tape_reg->data0=ramaddr;
    tape_reg->command=TAPE_READBLK;
    while ((status=tape_reg->status)==TAPE_BUSY)
        ;
    if (status!=TAPE_READY)
         return -1;
    tape_reg->command=TAPE_ACK;
    return tape_reg->data1;
}

static int load_file(dtpreg_t *tape_reg, unsigned long int  ramaddr){
    int n;
    while ((n=loadblock(tape_reg, ramaddr))!=EOF && n>0){
        ramaddr+=4096;
        loadblock(tape_reg, ramaddr);
            }
    return ramaddr;
}
#endif
