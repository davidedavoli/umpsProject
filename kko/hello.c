#include "umps/libumps.h"
#include "umps/arch.h"
#include "umps/types.h"
#include "strutils.h"
#include "tapeutils.h"
#include "terminal.h"

#define ST_READY           1
#define ST_BUSY            3
#define ST_TRANSMITTED     5

#define CMD_ACK            1
#define CMD_TRANSMIT       2

#define CHAR_OFFSET        8
#define TERM_STATUS_MASK   0xFF

#define RAM_BEGIN          0x20000000
#define BLOCK_SIZE         4096

#define STD_TERM_W 72
#define STD_TERM_H 24

typedef unsigned int u32;

static dtpreg_t *tape0_reg= (dtpreg_t *) DEV_REG_ADDR(IL_TAPE, 0);

static int load_ram_block(char *addr);
static int load_window();
static int display_window(int posSpace);
static void init_window();
static char bbuffer[BLOCK_SIZE];
static void term_readline();
static int ld_block();
static struct tmp{
char tmp_c[128];
int tmp_len;
}tmp_t;
static struct window{
    int bufpos;
    /*char win[STD_TERM_H*STD_TERM_W];*/
	} finestra;

int lavallo;

void main(void)
{
    char a[128];
    do lavallo=ld_block(); while (lavallo!=EOF && lavallo!=EOT);
    /* Go to sleep and power off the machine if anything wakes us up */
    WAIT();
    *((u32 *) MCTL_POWER) = 0x0FF;
    while (1) ;
}

static int ld_block(void){
    init_window();
    int a=loadblock(tape0_reg, RAM_BEGIN);
    term_puts(tmp_t.tmp_c);
    int posSpace;
    char buf[128];
    int b=0;
    posSpace = load_ram_block(RAM_BEGIN);
    display_window(posSpace);
    term_readline(buf,128);
    return a;
}

static void init_window (void){
     finestra.bufpos=0;
     }

static int load_ram_block(char* addr){
    int i=0;
    tmp_t.tmp_len=0;
    int pos=-1;
    for (i=0; i<BLOCK_SIZE; i++, addr++)
         bbuffer[i]=*addr;
    for (i=BLOCK_SIZE-1; i>=0 && pos==-1; i--)
    {
    	if (bbuffer[i] == ' ') pos=i;
    }
    for (i=pos; i<BLOCK_SIZE; i++,tmp_t.tmp_len++)
    	tmp_t.tmp_c[tmp_t.tmp_len] = bbuffer[i];
    return pos;
}
int bp=0;
static int load_window(void){
    /*char c;
    int i;
        for (i=0; i<STD_TERM_H*STD_TERM_W-1; i++){
                c=bbuffer[finestra.bufpos];
                bp=finestra.bufpos++;
                finestra.win[i]=c;
                finestra.win[i+1]='\0';
                if (c==EOF)
                    return 1;
                else if (c==EOB)
                    return -1;
            }
    return 0;*/
    
}

static int display_window(int posSpace){
        term_puts_till_space(bbuffer,posSpace);
        return finestra.bufpos;
}

static void term_readline(char *buf, unsigned int count)
{
    int c;

    while (--count && (c = term_getchar()) != '\n')
        *buf++ = c;

    *buf = '\0';
}

