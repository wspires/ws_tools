/**
	@file   main.cpp
	@author Wade Spires
	@date   2006/8/7
	@brief  Program test_dir.
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

void print_files( const vector<string>& );

void create_dirs_and_files( );

void test1( );
void test2( );
void test3( );
void test4( );
void test5( );
void test6( );
void test7( );
void test8( );

bool jpg_filter( const string& );
bool pnm_filter( const string& );
bool img_filter( const string& );

int main( int argc, char** argv )
{
	CL_Options options( argc, argv );

	// create directories and files to use for testing
	create_dirs_and_files();

	// perform each test
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();

	return( EXIT_SUCCESS );
}

void print_files( const vector<string>& words )
{
	for( unsigned i = 0; i != words.size(); ++i )
	{
		cout << "   " << words[i] << endl;
	}
}

/**
	Create directories to use for testing the traversal routines.
	This also tests the functions of check_dir(), open_file(), and close_file().
 */
void create_dirs_and_files( )
{
	FILE* fp = 0;
	string dir_name;
	string file_name;
	string sub_dir_name;

	// create testing directory
	dir_name = "dir";
	check_dir( dir_name );

	// create each file in the directory
	file_name = dir_name + "a";
	fp = open_file( file_name, "w" );
	close_file( fp );

	file_name = dir_name + "b";
	fp = open_file( file_name, "w" );
	close_file( fp );

	file_name = dir_name + "c.jpg";
	fp = open_file( file_name, "w" );
	close_file( fp );

	file_name = dir_name + "d.jpg";
	fp = open_file( file_name, "w" );
	close_file( fp );

	file_name = dir_name + "d.pgm";
	fp = open_file( file_name, "w" );
	close_file( fp );

	// create empty sub-directory
	sub_dir_name = dir_name + "empty_dir";
	check_dir( sub_dir_name );

	// create non-empty sub-directory
	sub_dir_name = dir_name + "sub_dir";
	check_dir( sub_dir_name );

	// create each file in the sub-directory
	file_name = sub_dir_name + "e.pgm";
	fp = open_file( file_name, "w" );
	close_file( fp );

	file_name = sub_dir_name + "f.ppm";
	fp = open_file( file_name, "w" );
	close_file( fp );
}

/**
	Show all files in a directory. No recursion.
 */
void test1( )
{
	const string msg = "Show all files in a directory. No recursion.";
	fprintf( stderr, "Test 1 -- %s\n", msg.c_str() );

	const string dir_name = "dir";
	vector<string> files = dir_open( dir_name );
	print_files( files );

	fprintf( stderr, "End test 1\n\n" );
}

/**
	Show all files in a directory. Use recursion.
 */
void test2( )
{
	const string msg = "Show all files in a directory. Use recursion.";
	fprintf( stderr, "Test 2 -- %s\n", msg.c_str() );

	const string dir_name = "dir";
	vector<string> files = dir_traverse( dir_name );
	print_files( files );

	fprintf( stderr, "End test 2\n\n" );
}

/**
	Show all JPEG files in a directory. No recursion.
 */
void test3( )
{
	const string msg = "Show all JPEG files in a directory. No recursion.";
	fprintf( stderr, "Test 3 -- %s\n", msg.c_str() );

	const string dir_name = "dir";
	vector<string> files = dir_open( dir_name, jpg_filter );
	print_files( files );

	fprintf( stderr, "End test 3\n\n" );
}

/**
	Show all PNM files in a directory. Use recursion.
 */
void test4( )
{
	const string msg = "Show all PNM files in a directory. Use recursion.";
	fprintf( stderr, "Test 4 -- %s\n", msg.c_str() );

	const string dir_name = "dir";
	vector<string> files = dir_traverse( dir_name, pnm_filter );
	print_files( files );

	fprintf( stderr, "End test 4\n\n" );
}

/**
	Show all image files in a directory. Use recursion.
 */
void test5( )
{
	const string msg = "Show all image files in a directory. Use recursion.";
	fprintf( stderr, "Test 5 -- %s\n", msg.c_str() );

	const string dir_name = "dir";
	vector<string> files = dir_traverse( dir_name, img_filter );
	print_files( files );

	fprintf( stderr, "End test 5\n\n" );
}

/**
	Show all files after following a symbolic link.

	This tests symbolic links, which are not in MS Windows and not saved in
	CVS, so it has to create one first. Remember, this is for UNIX and Linux
	only.
 */
void test6( )
{
#ifndef _WIN32

#include <unistd.h>
#include <errno.h>

	const string msg = "Show all files after following a symbolic link.";
	fprintf( stderr, "Test 6 -- %s\n", msg.c_str() );

	// create the symbolic link first
	const string old_name = "sub_dir";
	const string dir_name = "dir/link";
	if( symlink( old_name.c_str(), dir_name.c_str() ) == 0 || errno == EEXIST )
	{
		vector<string> files = dir_traverse( dir_name );
		print_files( files );
	}
	else if( errno != EEXIST )
	{
		err_warn( "Unable to create symbolic link '%s'\n", dir_name.c_str() );
	}

	fprintf( stderr, "End test 6\n\n" );

#endif // _WIN32
}

/**
	Show all files in root directory. No recursion.
 */
void test7( )
{
	const string msg = "Show all files in root directory. No recursion.";
	fprintf( stderr, "Test 7 -- %s\n", msg.c_str() );

	// name of root directory
#ifdef _WIN32
	const string dir_name = "C:\\";
#else
	const string dir_name = "/";
#endif // _WIN32

	vector<string> files = dir_open( dir_name );
	print_files( files );

	fprintf( stderr, "End test 7\n\n" );
}

/**
	Show all files in home directory. No recursion.
 */
void test8( )
{
	const string msg = "Show all files in home directory. No recursion.";
	fprintf( stderr, "Test 8 -- %s\n", msg.c_str() );

	// name of home directory
#ifdef _WIN32
	const string dir_name = "C:\\";
#else
	const string dir_name = "~";
#endif // _WIN32

	vector<string> files = dir_open( dir_name );
	print_files( files );

	fprintf( stderr, "End test 8\n\n" );
}

/**
	JPEG file filter.
 */
bool jpg_filter( const string& file_name )
{
	string ext_name = get_ext_name( file_name );
	to_lower( ext_name );
	if( ext_name == "jpg" || ext_name == "jpeg" )
	{
		return( true );
	}
	return( false );
}

/**
	PNM file filter.
 */
bool pnm_filter( const string& file_name )
{
	string ext_name = get_ext_name( file_name );
	to_lower( ext_name );
	if( ext_name == "pgm" || ext_name == "ppm" || ext_name == "pbm" )
	{
		return( true );
	}
	return( false );
}

/**
	Image file filter.
 */
bool img_filter( const string& file_name )
{
	return( pnm_filter( file_name ) || jpg_filter( file_name ) );
}
