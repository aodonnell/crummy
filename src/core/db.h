#ifndef _DB_H
#define _DB_H

#include <unqlite.h>

unqlite * db;

void question_or_create_universe(char * universe);

#endif