/*
	main.c
	To call rev()
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
	void * handle;
	char *(*rev)(const char *);
	char * error;
	
	handle = dlopen ( "rev.so", RTLD_LAZY );
	if ( !handle )
	{
		fprintf ( stderr, "%s\n", dlerror() );
		exit (EXIT_FAILURE);
	}

	/* Clear any existing error */
	dlerror();

	*(void **) (&rev) = dlsysm ( handle, "rev" );
	if ( ( error = dlerror() ) != NULL )
	{
		fprintf ( stderr, "%s\n", error );
		exit(EXIT_FAILURE);
	}

	rev ( "hi" );

	dlclose ( handle );

	exit(EXIT_SUCCESS);
}
