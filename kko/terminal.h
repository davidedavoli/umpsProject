#ifndef TERMINAL_H
#define TERMINAL_H

int term_putchar(char c);
int term_puts();
int term_putline();
int term_getchar(void);
int term_puts_till_space(char *str, int posSpace);
#endif
