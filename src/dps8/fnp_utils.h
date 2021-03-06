/*
 Copyright 2014-2016 by Harry Reed
 Copyright 2014-2016 by Charles Anthony

 All rights reserved.

 This software is made available under the terms of the
 ICU License -- ICU 1.8.1 and later.
 See the LICENSE file at the top-level directory of this distribution and
 at https://sourceforge.net/p/dps8m/code/ci/master/tree/LICENSE
 */

//
//  fnp_utils.h
//  fnp
//
//  Created by Harry Reed on 12/9/14.
//  Copyright (c) 2014 Harry Reed. All rights reserved.
//

#ifndef __fnp__fnp_utils__
#define __fnp__fnp_utils__

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

char *stripquotes(char *s);

char *strclip(char *s);
char *strpad(char *s, int len);
char *strpreclip(char *s);
char *strchop(char *s);

char *trim(char *s);
char *ltrim(char *s);
char *rtrim(char *s);

char *strexp(char *, char *);
char *strexpP(char *, char *);

char *Strtok(char *, char *);

char *Strdup(char *s, int size);
char *strrev(char *s);
int strcpyWhile(char *dst, char *src, int (*f)(int));
char *strlower(char *q);
bool startsWith(const char *str, const char *pre);

//#define strsep  "Replaced w/ Strsep()"

char *Strsep(char **stringp, const char *delim);

char *Now(void);

#endif /* defined(__fnp__fnp_utils__) */
