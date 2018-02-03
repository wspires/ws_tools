/**
	@file   main.cpp
	@author Wade Spires
	@date   2006/10/20
	@brief  Program test_name.

	Test path parsing functions.

	Copyright (c) 2006 Wade Spires. All rights reserved.
 */

// c++ headers
#include <iostream>
#include <string>
#include <vector>

// tools headers
#include "ws_tools.hpp"

using std::cerr;  using std::cout;  using std::endl;
using std::string;
using std::vector;

using namespace ws_tools;

/**
	@brief Structure for setting command-line options.

	The following is a list of mandatory program options:

	The following is a list of optional program options:
		'-h' Display usage information.
 */
struct CL_Options
{
	CL_Options( int argc, char** argv )
	: prog_name( argv[0] )
	{
		// set each option from command-line
		while( --argc != 0 )
		{
			++argv;
			if( argv == NULL )
			{
				print_usage();
			}
			string arg = *argv;

			// by convention, options start with a dash
			if( arg[0] == '-' )
			{
				if( arg.size() == 1 )
				{
					print_usage();
				}

				// handle each option type
				switch( arg[1] )
				{
					// set '-h' option
					case 'h':
						print_usage();
						break;

					default:
						print_usage();
						break;
				}
			}
		}
	}

	/**
		Print error message showing program usage.
	 */
	void print_usage( )
	{
		cerr << "usage: " << get_file_name( prog_name )
			<< " [ Options ]" << endl;
		exit( EXIT_FAILURE );
	}

	string prog_name;  //< Name of program
};

void print( const string& );

int main( int argc, char** argv )
{
	CL_Options options( argc, argv );

	// try some obvious cases
	print( "wade/doc/README.txt" );
	fprintf( stderr, "\n" );

	print( "/home/wade/doc/README.txt" );
	fprintf( stderr, "\n" );

	print( "README.txt" );
	fprintf( stderr, "\n" );

	print( "README" );
	fprintf( stderr, "\n" );

	print( "doc/" );
	fprintf( stderr, "\n" );

	print( "doc" );
	fprintf( stderr, "\n" );

	print( "~wade/file name with spaces.mp3" );
	fprintf( stderr, "\n" );

	// try some border cases
	print( "/" );
	fprintf( stderr, "\n" );

	print( ".xml" );
	fprintf( stderr, "\n" );

	print( "~/.bashrc" );
	fprintf( stderr, "\n" );

	print( "~/.firefox/plugins/libnull.so" );
	fprintf( stderr, "\n" );

	// try some pathological cases
	fprintf( stderr, "File name is empty.\n" );
	print( "" );
	fprintf( stderr, "\n" );

	fprintf( stderr, "File name is a space.\n" );
	print( " " );
	fprintf( stderr, "\n" );

	return( EXIT_SUCCESS );
}

/**
	Test each 'get_*' function.
 */
void
print( const string& path )
{
	fprintf( stderr, "Path: %s\n", path.c_str() );
	fprintf( stderr, "  get_dir:  %s\n", get_dir( path ).c_str() );
	fprintf( stderr, "  get_file: %s\n", get_file( path ).c_str() );
	fprintf( stderr, "  get_base: %s\n", get_base( path ).c_str() );
	fprintf( stderr, "  get_ext:  %s\n", get_ext_name( path ).c_str() );
}
