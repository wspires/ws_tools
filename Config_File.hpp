/**
	@file   Config_File.hpp
	@author Wade Spires
	@date   2006/7/17
	@brief  Class Config_File.

	Copyright 2007 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#ifndef _CONFIG_FILE_HPP
#define _CONFIG_FILE_HPP

#define NDEBUG  // comment this line out to enable assert() debugging calls
#include <cassert>

// c++ headers
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

// c headers
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

// tools headers
#include "util.hpp"
#include "err_mesg.h"

namespace ws_tools
{

/**
	@brief Config_File
 */
class Config_File
{
	
public:

	/**
		Default constructor.
	 */
	Config_File( )
	{ }

	/**
		Construct configuration file object using the given file name.
		@param[in] file_name File to read from
	 */
	Config_File( const std::string& );

	/**
		Destructor does nothing since no member variables are dynamically
		allocated.
	 */
   virtual ~Config_File( )
	{ }

	/**
		Read configuration from file name.

		Derived classes should not override this method but should call it from
		inside the constructor.

		@param[in] file_name File to read from
	 */
	void read( const std::string& );

	std::string config_name;  //< Name of config file

	/**
		Return name of configuration file.
		@retval config_name Name of configuration file
	 */
	inline std::string get_config_name( ) const
	{
		return( config_name );
	}

protected:

	/**
		Set variables.

		Derived classes should override this method. Called by read().

		@param[in] var Variable
		@param[in,out] words whitespace-delimited words found on a single line
		@param[in] line_num Current line number
	 */
	virtual void set_variables( const std::string&, std::vector<std::string>&,
			unsigned );

	/**
		Verify that all required fields and no incompatible options were set.

		Derived classes should override this method. Called by read().
	 */
	virtual void verify_parameters( );

};

} // namespace ws_tools

#endif // _CONFIG_FILE_HPP
