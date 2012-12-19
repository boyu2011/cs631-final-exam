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
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char * rev( const char * );
    
char * rev ( const char * s )
{   
    int src_len = 0;
    char * target_ptr = NULL;
    int i, j;
    char c;
    
    if ( s == NULL )
        return NULL;
    
    src_len = strlen(s);
    
    /* Allocate memory space for the reversed string */
    target_ptr = malloc ( src_len );
    if ( NULL == target_ptr )
    {
        errno = ENOMEM;
        return NULL;
    }
    
    /* Copy string */
    strcpy ( target_ptr, s );
    
    /* Reverse string */
    for ( i=0, j=src_len-1; i<j; i++, j-- )
    {
        c = target_ptr[i];
        target_ptr[i] = target_ptr[j];
        target_ptr[j] = c;
    }
        
    /* Return the reversed string */
    return target_ptr;
}   
