#ifndef TAPEUTILS_H
#define TAPEUTILS_H

#include "tapearch.h"
#include "umps/types.h"
#include "umps/arch.h"
#include "terminal.h"
int alo=0;

static int seek_nfile(dtpreg_t *tape_reg, int n){

    int c=0;
    unsigned int status;
    while (c<n &&tape_reg->data1!=EOT){
    while ((status=tape_reg->status)==TAPE_BUSY || (status=tape_reg->status)==TAPE_NOTAPE)
        ;
        tape_reg->command=TAPE_SKIPBLK;
    while ((status=tape_reg->status)==TAPE_BUSY)
        ;
        tape_reg->command=TAPE_ACK;
    if (tape_reg->data1==EOF){
        c++;
    while ((status=tape_reg->status)==TAPE_BUSY || (status=tape_reg->status)==TAPE_NOTAPE)
        ;
        tape_reg->command=TAPE_SKIPBLK;
    while ((status=tape_reg->status)==TAPE_BUSY)
        ;
        tape_reg->command=TAPE_ACK;
        }
    }
    if (c<n) return 0;
    else return 1;
}

static int loadblock(dtpreg_t *tape_reg, unsigned int  ramaddr){

    unsigned int status;

    while ((status=tape_reg->status)==TAPE_BUSY || (status=tape_reg->status)==TAPE_NOTAPE)
        ;
    tape_reg->data0=ramaddr;
        term_putchar('a');
    tape_reg->command=TAPE_READBLK;
        term_putchar('b');
    while ((status=tape_reg->status)==TAPE_BUSY)
        alo=tape_reg->data0;
    if (status!=TAPE_READY)
         return -1;
        tape_reg->command=TAPE_ACK;
    return tape_reg->data1;
}

static int load_file(dtpreg_t *tape_reg, unsigned int  ramaddr){
    int n;
    do{
        alo++;
        n=loadblock(tape_reg, ramaddr);
        ramaddr+=4096;
            }while (n!=EOF && n!=EOT &&n>0);
    return ramaddr;
}
#endif
