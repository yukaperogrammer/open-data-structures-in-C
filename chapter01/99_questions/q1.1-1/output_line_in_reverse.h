#ifndef OUTPUT_LINE_IN_REVERSE_H
#define OUTPUT_LINE_IN_REVERSE_H

#define DEFAULT_LINE_SIZE 256 
#define DEFAULT_ROW_SIZE 32 
#define TRUE 1
#define FALSE 0

void do_output(FILE *);
void output_reverse(char **, int);
void *xmalloc(void *, int);

#endif

