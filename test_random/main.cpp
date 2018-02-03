/**
	@file   main.cpp
	@author Wade Spires
	@date   2006/10/20
	@brief  Program test_random.

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

int main( int argc, char** argv )
{
	CL_Options options( argc, argv );
	cout << "Random Number Generation Test" << endl;
	cout << "-----------------------------" << endl << endl;

	// different random number objects
	Uniform_Number u;
	Normal_Number  n;
	Normal_Number  n2( 2, 1.5 );
	
	const unsigned num_numbers = 10;

	cout << num_numbers << " uniformly distributed numbers [0,1):" << endl;
	for( unsigned i = 0; i != num_numbers; ++i )
	{
		cout << u.next() << endl;
	}
	cout << endl;

	cout << num_numbers << " uniformly distributed numbers in [10,15):" << endl;
	u.range(10,15);
	for( unsigned i = 0; i != num_numbers; ++i )
	{
		cout << u() << endl;
	}
	cout << endl;

	cout << num_numbers << " normally distributed numbers ~N(0,1):" << endl;
	for( unsigned i = 0; i != num_numbers; ++i )
	{
		cout << n() << endl;
	}
	cout << endl;

	cout << num_numbers << " normally distributed numbers ~N(2,1.5):" << endl;
	for( unsigned i = 0; i != num_numbers; ++i )
	{
		cout << n2() << endl;
	}
	cout << endl;

	// swap between different random number generators at random (this just tests
	// inheritance and is not really practical)
	u.range(0,1);
	Random_Number* r;
	cout << num_numbers << " randomly distributed random numbers:" << endl;
	for( unsigned i = 0; i != num_numbers; ++i )
	{
		// select a generator at random
		if( u() < .5 )
		{
			r = &u;

			// get next random number
			cout << r->next() << " (uniform)" << endl;
		}
		else
		{
			r = &n;
			cout << r->next() << " (normal)" << endl;
		}
	}
	cout << endl;

	return( EXIT_SUCCESS );
}
