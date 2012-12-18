/*
	rev.c
    
	Implement a shared, dynamic library that provides the following function:

    char *rev(const char *s);

    The rev() function allocates sufficient memory for a copy of the
    string s, copies and reverses the given input string and returns a pointer
    to it.  The pointer may subsequently be used as an argument to the
    function free(3).  If insufficient memory is available, NULL is
    returned and errno is set to ENOMEM.
*/

#include <stdio.h>

char * rev( const char * );

char * rev ( const char * s )
{
//	printf ( "entering rev()" );
	return NULL;
}
