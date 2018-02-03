/**
	@file   Progress_Bar.hpp
	@author Wade Spires
	@date   2005/04/06
	@brief  Class Progress_Bar.

	Copyright 2007 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#ifndef _PROG_BAR_HPP
#define _PROG_BAR_HPP

#include <cstdio>

/**
	@class Progress_Bar
 */
class Progress_Bar
{
	/**
		@struct Rotating_Symbol Represents a rotating ascii symbol.
	 */
	struct Rotating_Symbol
	{
		char symbol;  // current symbol
		enum { Clockwise, Counter_Clockwise } direction;

		Rotating_Symbol( )
		: symbol( '|' ), direction( Clockwise )
		{ }

		~Rotating_Symbol( )
		{ }

		Rotating_Symbol operator++( )
		{
			Rotating_Symbol saved_sym = *this;
			get_next_symbol();
			return( saved_sym );	
		}

		Rotating_Symbol operator++( int )
		{
			get_next_symbol();
			return( *this );	
		}

		char get_symbol( )
		{
			return( symbol );
		}

		char get_next_symbol( )
		{
			switch( symbol )
			{
				case '-':
					symbol = (direction == Clockwise) ? '\\' : '/';
					break;

				case '\\':
					symbol = (direction == Clockwise) ? '|' : '-';
					break;

				case '/':
					symbol = (direction == Clockwise) ? '-' : '|';
					break;

				case '|':
					symbol = (direction == Clockwise) ? '/' : '\\';
					break;

				default: break;
			}

			return( symbol );
		}
	};

	static const unsigned DEFAULT_BARS = 10;
	static const char     bar_symbol = '#';

public:

	Progress_Bar( )
	: _current_item(0), num_items(100), num_bars(DEFAULT_BARS), next_mark(0),
		current_num_bars(0), have_called_update(false)
	{
		compute_num_per_bar();
	}

	Progress_Bar( unsigned t )
	: _current_item(0), num_items(t), num_bars(DEFAULT_BARS), next_mark(0),
		current_num_bars(0), have_called_update(false)
	{
		compute_num_per_bar();
	}

	Progress_Bar( unsigned t, unsigned t_bars )
	: _current_item(0), num_items(t), num_bars(t_bars), next_mark(0),
		current_num_bars(0), have_called_update(false)
	{
		compute_num_per_bar();
	}

	~Progress_Bar( ) { }

	/**
		Update progress by the given number of steps.

		@param[in] num_steps The number of steps to update the bar by.
		@retval this This bar
	 */
	inline Progress_Bar& operator+=( const unsigned num_steps )
	{
		update( _current_item + num_steps );
		return( *this );
	}

	/**
		Update progress bar by one position.

		@retval this This bar
	 */
	inline Progress_Bar& operator++( )
	{
		// update( _current_item + 1 );
		return( (*this) += 1 );
	}

	/**
		Update progress by one step.

		@param[in] not_used This parameter is unused but must be specified to
			differentiate between prefix and postfix increment.  
		@retval this This bar
	 */
	inline Progress_Bar& operator++( int not_used )
	{
		return( ++(*this) );
	}

	/**
		Update progress to the given step.

		@param current_item
	 */
	void update( unsigned current_item )
	{
		_current_item = current_item;

		// don't do anything if already finished
		if( current_item >= num_items )
		{
			return;
		}
		// else if( current_item == 0 || current_item == 1 )
		// else if( current_item == 0 )
		// else if( current_item == 1 )
		else if( !have_called_update )
		{
			// print the bar (but don't clear it) if the first time
			// (if we don't count 1 as the first time and current_item
			// is updated via the prefix increment operator, e.g., update( ++i ),
			// then text before the bar will be erased)
			print_bar();

			/*
			// TODO does this need updating?
			if( current_item != 0 )
			{
				next_mark = 1;
			}
			 */
		}

		// if adding a new bar
		else if( current_item > next_mark )
		{
			// if need to print a bar (and haven't already printed all the bars)
			while( current_item > next_mark && current_num_bars != num_bars )
			{
				next_mark += num_per_bar;
				++current_num_bars;
			}
			rot_sym = Rotating_Symbol();  // reset rotating symbol to vertical

			clear_bar();
			print_bar();
		}

		// rotate symbol to show activity--perform only 1 complete rotation
		// (must check that (num_per_bar / 9) != 0; otherwise, FP exception)
		else if( num_per_bar >= 9
			&& (next_mark - current_item) % (num_per_bar / 9) == 0 )
		{
			rot_sym.get_next_symbol();

			clear_bar();
			print_bar();
		}
		have_called_update = true;
	}

	/**
		Print bar to represent current progress.
		Note: must print to stderr so that I/O is unbuffered.
	 */
	void print_bar( )
	{
		fprintf( stderr, "|" );

		// print current number of bars
		unsigned i = 0;
		for( i = 0; i != current_num_bars; ++i )
		{
			fprintf( stderr, "%c", bar_symbol );
		}

		// print rotating symbol if not the end
		if( current_num_bars != num_bars )
		{
			fprintf( stderr, "%c", rot_sym.get_symbol() );
			++i;
		}

		// fill 'in-progress' section with spaces
		for( ; i != num_bars; ++i )
		{
			fprintf( stderr, " " );
		}

		fprintf( stderr, "|" );
	}

	/**
		Erase bar.
	 */
	void clear_bar( )
	{
		// print backspaces to erase the bar (num_bars + 2 vertical bars)
		for( unsigned i = 0; i != num_bars + 2; ++i )
		{
			fprintf( stderr, "%c", '\b' );
		}
	}

protected:

	void compute_num_per_bar( )
	{
		if( num_items > num_bars )
		{
			num_per_bar = num_items / num_bars;
		}
		else
		{
			num_per_bar = 1;
		}
	}

private:

	unsigned _current_item;

	unsigned num_items;    //< Number of items to process
	unsigned num_bars;     //< Number of bars to print
	unsigned num_per_bar;  //< Amount to count to until printing another bar

	unsigned next_mark;  //< Index when the next bar should be printed

	unsigned current_num_bars;  //< Current number of bars to print

	/// Symbol that rotates as progress is made
	Rotating_Symbol rot_sym;

	/**
		If the bar has been updated for the first time, so we know whether to clear
		the bar or not.
	 */
	bool  have_called_update;

};

#endif // _PROG_BAR_HPP
