#include <stdio.h>

#include "db.h"

void question_or_create_universe(char * universe)
{
    int status = unqlite_open(&db, universe, UNQLITE_OPEN_CREATE);
    if( status != UNQLITE_OK)
    {
        // something bad happened. probably out of memory
        printf("Failed to create the universe. Failed to even question it.");
        
	}
}