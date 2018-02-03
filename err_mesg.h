/**
	@file   err_mesg.h
	@author Wade Spires
	@date   2005/04/06
	@brief  C functions for handling error messages.

	Copyright 2006 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#ifndef __ERR_MESG_H
#define __ERR_MESG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern void err_quit( char*, ... );
extern void perr_quit( char*, ... );
extern void err_warn( char*, ... );

#ifdef __cplusplus
}
#endif

#endif // __ERR_MESG_H 
