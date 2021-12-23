#ifndef _CC_STRINGS_H
#define _CC_STRINGS_H

// types, enums and prototypes here


extern double CCStringToDouble(const char *str, char **end, char decimalDelimiter);
extern int CCNextToken(char *content, char **point, char delimiter);
extern void CCStringReverse(char *str);
extern char * CCReadString(char *str, int elements);

#endif