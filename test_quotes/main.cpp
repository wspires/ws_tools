/**
	@file   main.cpp
	@author Wade Spires
	@date   2006/8/7
	@brief  Program test_quotes.
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
					// set '-a' option
					case 'a':
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
			<< " [ Options ]" << endl;
		exit( EXIT_FAILURE );
	}

	string prog_name;  //< Name of program
};

void print_words( const vector<string>& );

void test1( );
void test2( );
void test3( );
void test4( );
void test5( );
void test6( );
void test7( );

int main( int argc, char** argv )
{
	CL_Options options( argc, argv );

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();

	return( EXIT_SUCCESS );
}

void print_words( const vector<string>& words )
{
	for( unsigned i = 0; i != words.size(); ++i )
	{
		cout << words[i] << endl;
	}
}

/**
	No quotes.
 */
void test1( )
{
	vector<string> words( 3 );
	words[0] = "wade";
	words[1] = "and";
	words[2] = "miko";

	cout << "test1" << endl;
	print_words( words );
	cout << endl;
	words = merge_quoted_words( words );
	print_words( words );

	cout << endl;
	cout << endl;
}

/**
	Quotes in one word.
 */
void test2( )
{
	vector<string> words( 1 );
	words[0] = "'wade'";

	cout << "test2" << endl;
	print_words( words );
	cout << endl;
	words = merge_quoted_words( words );
	print_words( words );

	cout << endl;
	cout << endl;
}

/**
	Quotes across several words.
 */
void test3( )
{
	vector<string> words( 3 );
	words[0] = "'wade";
	words[1] = "and";
	words[2] = "miko'";

	cout << "test3" << endl;
	print_words( words );
	cout << endl;
	words = merge_quoted_words( words );
	print_words( words );

	cout << endl;
	cout << endl;
}

/**
	Words before and after the quotes.
 */
void test4( )
{
	vector<string> words( 4 );
	words[0] = "hey, 'wade";
	words[1] = "and";
	words[2] = "miko'.";
	words[3] = "done";

	cout << "test4" << endl;
	print_words( words );
	cout << endl;
	words = merge_quoted_words( words );
	print_words( words );

	cout << endl;
	cout << endl;
}

/**
	Multiple quotes in the same word.
 */
void test5( )
{
	vector<string> words( 1 );
	words[0] = "hey, 'wade and miko' and 'however' else.";

	cout << "test5" << endl;
	print_words( words );
	cout << endl;
	words = merge_quoted_words( words );
	print_words( words );

	cout << endl;
	cout << endl;
}

/**
	Many quotes everywhere.
 */
void test6( )
{
	vector<string> words( 5 );
	words[0] = "hey,'wade and miko'";
	words[1] = " and 'however";
	words[2] = " else it may be' within 'all this";
	words[3] = " we have to do' now'.'";
	words[4] = "'hmmm..'''";

	cout << "test6" << endl;
	print_words( words );
	cout << endl;
	words = merge_quoted_words( words );
	print_words( words );

	cout << endl;
	cout << endl;
}

/**
	Missing a matching quote.
 */
void test7( )
{
	vector<string> words( 2 );
	words[0] = "hey, 'wade ";
	words[1] = "miko else.";

	cout << "test7" << endl;
	print_words( words );
	cout << endl;
	words = merge_quoted_words( words );
	print_words( words );

	cout << endl;
	cout << endl;
}
