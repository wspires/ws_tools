/**
	@file   log_mesg.c
	@author Wade Spires
	@date   2005/04/06
	@brief  C function for handling log messages.

	Copyright 2006 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#include "log_mesg.h"

/// Whether to write message to the log (1) or not (0)
unsigned verbose = 0;

/**
   Prints a log message and continues running program.

   The message can have conversion specifications (i.e., %d, %s, etc.) since
   log_msg() takes a variable number of arguments.

	@param[in] message Log message to print
 */
void log_msg( char* message, ... )
{
   va_list v_args;

	if( verbose > 0 )
	{
		va_start( v_args, message );
		vfprintf( stdout, message, v_args );
		va_end( v_args );
	}
}
