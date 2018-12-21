#ifndef TAPEARCH_H
#define TAPEARCH_H

/*Tape status constants*/

#define TAPE_READY 1
#define TAPE_BUSY 3
#define TAPE_NOTAPE 0

/*Tape commands constant*/

#define TAPE_RESET 0
#define TAPE_ACK 1
#define TAPE_SKIPBLK 2
#define TAPE_READBLK 3
#define TAPE_BACKBLK 4

/* Tape special characters*/

#define EOT 0
#define EOF 1
#define EOB 2
#define TS  3


#endif
