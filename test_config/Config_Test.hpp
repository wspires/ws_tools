/**
	@file   Config_Test.hpp
	@author Wade Spires
	@date   2006/8/8
	@brief  Class Config_Test.
 */

#ifndef _CONFIG_TEST_HPP
#define _CONFIG_TEST_HPP

#define NDEBUG  // comment this line out to enable assert() debugging calls
#include <cassert>

// c++ headers
#include <algorithm>
#include <string>
#include <vector>

// c headers
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

// tools headers
#include "Config_File.hpp"
#include "util.hpp"
#include "err_mesg.h"

/**
	@brief Config_Test
 */
class Config_Test : public ws_tools::Config_File
{
	
public:

	/**
		Default constructor.
	 */
   Config_Test( )
	{ }

	/**
		Default constructor.
	 */
	Config_Test( const std::string& );

	/**
		Destructor does nothing since no member variables are dynamically
		allocated.
	 */
   virtual ~Config_Test( )
	{ }

	// variables to read
	std::string  first_name;
	std::string  last_name;
	int          ssn;
	double       gpa;

protected:
	virtual void set_variables( const std::string&, std::vector<std::string>&,
			unsigned );
	virtual void verify_parameters( );
};

#endif // _CONFIG_TEST_HPP
