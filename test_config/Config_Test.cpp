/**
	@file   Config_Test.cpp
	@author Wade Spires
	@date   2006/8/8
	@brief  Class Config_Test.
 */

#include "Config_Test.hpp"

using std::string;
using std::vector;

using namespace ws_tools;

/**
	Construct cascade from file name.
	@param[in] cascade_name File to read from
 */
Config_Test::Config_Test( const string& file_name )
: ssn(0), gpa(0)
{
	read( file_name );
}

/**
	Parse line
	// whitespace-delimited words found on a single line
 */
void
Config_Test::set_variables( const string& var, vector<string>& words,
		unsigned line_num )
{
	// create initial message in case of error
	const string error_line = format_string( "Line %u in '%s':",
			line_num, get_config_name().c_str() );
	const char* const error_str = error_line.c_str();

	/*
	fprintf( stderr, "%s", var.c_str() );
	for( unsigned i = 0; i != words.size(); ++i )
	{
		fprintf( stderr, " %s", words[i].c_str() );
	}
	fprintf( stderr, "\n" );
	 */

	if( var == "name" )
	{
		if( words.size() != 2 )
		{
			err_quit( "%s First and last name not given\n", error_str );
		}
		first_name = words[0];
		last_name  = words[1];
	}
	else if( var == "ssn" )
	{
		if( words.size() != 1 )
		{
			err_quit( "%s \n", error_str );
		}

		int s = atoi( words[0].c_str() );
		if( s <= 0 )
		{
			err_quit( "%s SSN must be >= 0\n", error_str );
		}
		ssn = s;
	}
	else if( var == "gpa" )
	{
		if( words.size() != 1 )
		{
			err_quit( "%s \n", error_str );
		}

		const double g  = string_to_double( words[0] );
		if( g < 0 || g > 4 )
		{
			err_quit( "%s GPA must be in the range [0,4.0)\n", error_str );
		}
		gpa = g;
	}
	else
	{
		err_quit( "%s unknown variable '%s'\n", error_str, var.c_str() );
	}
}

/**
	Verify that all required fields and no incompatible options were set.
 */
void
Config_Test::verify_parameters( )
{
	if( first_name == "" || last_name == "" )
	{
		err_quit( "First and last name not given\n" );
	}
}
