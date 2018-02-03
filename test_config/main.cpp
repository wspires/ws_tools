/**
	@file   main.cpp
	@author Wade Spires
	@date   2006/8/8
	@brief  Program test_config.
 */

// c++ headers
#include <iostream>
#include <string>
#include <vector>

// tools headers
#include "util.hpp"
#include "err_mesg.h"

// local headers
#include "Config_Test.hpp"

using std::cerr;  using std::cout;  using std::endl;
using std::string;
using std::vector;

using namespace ws_tools;

/**
	@brief Structure for setting command-line options.
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
					// set '-c' option
					case 'c':
						++argv;
						if( --argc == 0 )
						{
							print_usage();
						}
						config_file = *argv;

						break;

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
			<< " -c config_file [ -h ]" << endl;
		exit( EXIT_FAILURE );
	}

	string prog_name;    //< Name of program
	string config_file;  //< Name of config file
};

int main( int argc, char** argv )
{
	CL_Options options( argc, argv );

	// read and process config file
	Config_Test config( options.config_file );

	// display fields
	fprintf( stderr, "%s %s -- %u %.2lf\n",
			config.first_name.c_str(), config.last_name.c_str(),
			config.ssn, config.gpa );

	return( EXIT_SUCCESS );
}
