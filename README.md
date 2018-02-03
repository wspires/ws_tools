# ws_tools
Library for handling simple, common tasks, such as formatting error messages, directory traversal, file/directory name parsing, number conversion, etc.

Availability of a UNIX or GNU/Linux system is assumed.
To compile the library and test programs, type 'make'.
To compile the library only, type 'make lib'.
Either way, 'libws_tools.a' is created in the current directory.

To use the library in your programs, you need to include the file 'ws_tools.hpp'
in each header file you intend on using the library in. Then, when compiling
your program, add the following options to g++:
	-I<ws_tools_dir>
	-L<ws_tools_dir>
	-lws_tools
assuming the header files and 'libws_tools.a' are located in <ws_tools_dir>,
e.g., if <ws_tools_dir> is '/home/john_smith/ws_tools/', then add the following
options
	-I'/home/john_smith/ws_tools/'
	-L'/home/john_smith/ws_tools/'
	-lws_tools
to g++ when compiling.
