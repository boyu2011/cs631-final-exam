/*
    main.c
    
    Send a string to rev(), and get a new reversed string.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define TEXT "Do What You Like To Do. Enjoy What You Do."

int main( int argc, char ** argv )
{
    void * handle;
    char *(*rev)(const char *);
    char * error;
    char * rev_ptr = NULL;

    /* Open shared library */
    handle = dlopen ( "librev.so.1.0", RTLD_LAZY );
    if ( !handle )
    {
        fprintf ( stderr, "%s\n", dlerror() );
        exit (EXIT_FAILURE);
    }

    /* Clear any existing error */
    dlerror();

    /* Get rev() symbol address */
    *(void **) (&rev) = dlsym ( handle, "rev" );
    if ( ( error = dlerror() ) != NULL )
    {
        fprintf ( stderr, "%s\n", error );
        exit(EXIT_FAILURE);
    }

    printf ( "Before rev()\n" );
    printf ( TEXT );
    printf ( "\n" );

    /* Call rev() to get a reversed string */
    rev_ptr = rev ( TEXT );

    printf ( "After rev()\n" );
    if ( rev_ptr != NULL )
    {
        printf ( "%s", rev_ptr );
        printf ( "\n" );

		/* Release memory */
        free ( rev_ptr );
    }
    else
    {
        perror ( "reverse failed" );
    }

    dlclose ( handle );

    exit(EXIT_SUCCESS);
}
