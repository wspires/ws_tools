/**
	@file   log_mesg.h
	@author Wade Spires
	@date   2006/02/28
	@brief  C functions for handling error messages.

	Copyright 2006 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#ifndef __LOG_MESG_H
#define __LOG_MESG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/// Whether to write message to the log (1) or not (0)
extern unsigned verbose;

extern void log_msg( char*, ... );

#ifdef __cplusplus
}
#endif

#endif // __LOG_MESG_H 
