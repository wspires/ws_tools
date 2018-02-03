/**
	@file   Config_File.cpp
	@author Wade Spires
	@date   2006/7/17
	@brief  Class Config_File.

	Copyright 2007 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#include "Config_File.hpp"

using std::string;
using std::vector;
using std::ifstream;

using namespace ws_tools;

/**
	Construct configuration file object using the given file name.
	@param[in] file_name File to read from
 */
Config_File::Config_File( const string& file_name )
{
	read( file_name );
}

/**
	Read configuration from file name.

	Derived classes should not override this method but should call it from
	inside the constructor.

	@param[in] file_name File to read from
 */
void
Config_File::read( const string& file_name )
{
	config_name = sub_home(file_name);
	ifstream config_file( config_name.c_str() );
	if( !config_file )
	{
		err_quit( "Unable to open file '%s'\n", file_name.c_str() );
	}

	unsigned       line_count = 0;
	string         line;   // single line from file
	vector<string> words;  // whitespace-delimited words found on a single line

	// read and store each line of the configuration file
	while( getline( config_file, line ) )
	{
		++line_count;

		// strip comments from each line, split lines into words,
		// and skip empty lines
		remove_comments( line, "#" );
		words = split_string( line );
		if( words.empty() )
		{
			continue;
		}

		// use the first word, in lower case, as the variable to assign;
		// combine quoted words into single strings, e.g., '~/some dir'
		const string var = words[0];
		words.erase( words.begin(), words.begin() + 1 );
		words = merge_quoted_words( words );

		set_variables( var, words, line_count );
	}
	verify_parameters();
}

/**
	Set variables.

	Derived classes should override this method. Called by read().

	@param[in] var Variable
	@param[in,out] words whitespace-delimited words found on a single line
	@param[in] line_num Current line number
 */
void
Config_File::set_variables( const string& var, vector<string>& words,
		unsigned line_num )
{
	// create initial message in case of error
	// const string error_line = format_string( "Line %u in '%s':",
			// line_num, config_name.c_str() );
	// const char* const error_str = error_line.c_str();

	// print each line as a default
	fprintf( stderr, "%s", var.c_str() );
	for( unsigned i = 0; i != words.size(); ++i )
	{
		fprintf( stderr, " %s", words[i].c_str() );
	}
	fprintf( stderr, "\n" );
}

/**
	Verify that all required fields and no incompatible options were set.

	Derived classes should override this method. Called by read().
 */
void
Config_File::verify_parameters( )
{
}
