/**
	@file   err_mesg.c
	@author Wade Spires
	@date   2005/04/06
	@brief  C functions for handling error messages.

	Copyright 2006 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#include "err_mesg.h"

/**
   Prints an error message and exits program.

   Error message can have conversion specifications (i.e., %d, %s, etc.) since
   err_quit() takes a variable number of arguments.

	@param message -- error message to print
 */
void err_quit( char* message, ... )
{
   va_list v_args;

   va_start( v_args, message );
	fprintf( stderr, "Error: " );
   vfprintf( stderr, message, v_args );
   va_end( v_args );

   exit( EXIT_FAILURE );
}

/**
   Calls perror() to print error message and exits program.

   Error message can have conversion specifications (i.e., %d, %s, etc.) since
   perr_quit() takes a variable number of arguments.

	@param message -- error message to print
 */
void perr_quit( char* message, ... )
{
   va_list v_args;
   char tmp_msg[ BUFSIZ ];

   va_start( v_args, message );
   vsnprintf( tmp_msg, BUFSIZ, message, v_args );
   va_end( v_args );

   perror( tmp_msg );
   exit( EXIT_FAILURE );
}

/**
   Prints a warning message and continues running program.

   Error message can have conversion specifications (i.e., %d, %s, etc.) since
   err_warn() takes a variable number of arguments.

	@param message -- error message to print
 */
void err_warn( char* message, ... )
{
   va_list v_args;

   va_start( v_args, message );
	fprintf( stderr, "Warning: " );
   vfprintf( stderr, message, v_args );
   va_end( v_args );
}
