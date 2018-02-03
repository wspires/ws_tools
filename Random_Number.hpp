/**
	@file   Random_Number.hpp
	@author Wade Spires
	@date   2006/10/20
	@brief  Class Random_Number.

	Copyright 2007 Wade Spires.
	Distributed under the GNU Lesser General Public License, Version 2.1.
	(See accompanying file LICENSE.txt or copy at
	http://www.gnu.org/licenses/lgpl.txt)
 */

#ifndef _RANDOM_NUMBER_HPP
#define _RANDOM_NUMBER_HPP

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

// boost headers
#define HAVE_BOOST_WS_TOOLS
#ifdef HAVE_BOOST_WS_TOOLS

#include "boost/random.hpp"
#include <boost/generator_iterator.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/normal_distribution.hpp>

#endif // HAVE_BOOST_WS_TOOLS

// tools headers
#include "ws_tools.hpp"

namespace ws_tools
{

/**
	@brief Random_Number Base class for other random number generators.
 */
class Random_Number
{
	
public:

	/**
		Default constructor.
	 */
   Random_Number( )
	: _seed( std::time(0) )
	{ }

	/**
		Destructor does nothing since no member variables are dynamically
		allocated.
	 */
   virtual ~Random_Number( )
	{ }

	/**
		Return the next random number.
		@retval number Next random number
	 */
	virtual double next( ) = 0;

	/**
		Return the next random number.
		@retval number Next random number
	 */
	virtual double operator()( ) = 0;

protected:

	/**
		Get the pointer to the seed being used for the generator.
		@retval seed_pointer Pointer to the seed
	 */
	inline unsigned* get_seed( )
	{
		return( &_seed );
	}

private:

	/// Seed for random number generator
	unsigned _seed;

};

/**
	@brief Uniform_Number
 */
class Uniform_Number : public Random_Number
{
	
public:


	/**
		Default constructor that seeds the number generator with the current time.
	 */
   Uniform_Number( double min = 0.0, double max = 1.0 )
	: Random_Number(), _min(min), _max(max)
	{
		if( _min >= _max )
		{
			err_quit( "Uniform_Number: min (%lf) >= max (%lf)\n",
					_min, _max );
		}
	}

	/**
		Destructor does nothing since no member variables are dynamically
		allocated.
	 */
   virtual ~Uniform_Number( )
	{ }

	/**
		Return a uniformly distributed random number in the range [min, max).

		@retval number Next random number
	 */
	virtual inline double next( )
	{
		return( min()
				+ (max() - min()) * (rand_r( get_seed() ) / (RAND_MAX + 1.0)) );
	}

	/**
		Return a uniformly distributed random number in the range [min, max).
		@retval number Next random number
	 */
	virtual inline double operator()( )
	{
		return( next() );
	}

	/**
		Set new range for the distribution.
		@param[in] new_min New minimum value in the distribution's range
		@param[in] new_max New maximum value in the distribution's range
	 */
	virtual inline void range( double new_min, double new_max )
	{
		_min = new_min;
		_max = new_max;
		if( _min >= _max )
		{
			err_quit( "Uniform_Number::range: min (%lf) >= max (%lf)\n",
					_min, _max );
		}
	}

	/**
		Return minimum value in the distribution's range.
		@retval min Minimum value in the distribution's range
	 */
	virtual inline double min( ) const
	{
		return( _min );
	}

	/**
		Set new minimum value in the distribution's range.
		@param[in] new_min New minimum value in the distribution's range
	 */
	virtual inline void min( double new_min )
	{
		// just change the range using the new min. and old max.
		range( new_min, max() );
	}

	/**
		Return maximum value in the distribution's range.
		@retval max Maximum value in the distribution's range
	 */
	virtual inline double max( ) const
	{
		return( _max );
	}

	/**
		Set new maximum value in the distribution's range.
		@param[in] new_max New maximum value in the distribution's range
	 */
	virtual inline void max( double new_max )
	{
		// just change the range using the old min. and new max.
		range( min(), new_max );
	}

	double _min;  //< Minimum value in the distribution's range
	double _max;  //< Maximum value in the distribution's range

};

#ifdef HAVE_BOOST_WS_TOOLS

/**
	@brief Normal_Number
 */
class Normal_Number : public Random_Number
{

	// define a random number generator type
	// also, try boost::mt19937 or boost::ecuyer1988 instead of
	// boost::minstd_rand
	typedef boost::minstd_rand base_generator_type;

	// define a probability distribution type
	typedef boost::normal_distribution<>  distribution_type;
	
public:

	/**
		Construct a normally distributed random number generator with the given
		mean and standard deviation.

		Define a random number generator and initialize it with a repeatable
		seed. (The seed is unsigned; otherwise, the wrong overload may be
		selected when using mt19937 as the base_generator_type.)
			base_generator_type generator( _seed );

		Uniform distribution for the real range [0,1) (used by the normal dist.):
			boost::uniform_01<base_generator_type>  uni_01 ( generator );

		Create normal distribution (Gaussian) with the given mean and std. dev.:
			dist = boost::normal_distribution<>( mean, std_dev ) ;
	 */
   Normal_Number( double mean = 0, double std_dev = 1 )
	: Random_Number(),
		uni_01( base_generator_type( *Random_Number::get_seed() ) ),
		dist( mean, std_dev )
	{ }

	/**
		Destructor does nothing since no member variables are dynamically
		allocated.
	 */
   virtual ~Normal_Number( )
	{ }

	/**
		Return a normally distributed random number.
		@retval number Next random number
	 */
	virtual inline double next( )
	{
		return( dist(uni_01) );
	}

	/**
		Return a normally distributed random number.
		@retval number Next random number
	 */
	virtual inline double operator()( )
	{
		return( next() );
	}

private:

	boost::uniform_01<base_generator_type>  uni_01;
	distribution_type                       dist;

};

#else  // boost::random is not installed

/**
	@brief Normal_Number
 */
class Normal_Number : public Random_Number
{
	
public:

	/**
		Construct a normally distributed random number generator with the given
		mean and standard deviation.
	 */
   Normal_Number( double mean = 0, double std_dev = 1 )
	: Random_Number()
	{
		err_warn( "Normal_Number::Normal_Number: "
				" Unable to create normally distributed random number object: "
				" Boost (http://www.boost.org/) is not installed.\n" );
	}

	/**
		Destructor does nothing since no member variables are dynamically
		allocated.
	 */
   virtual ~Normal_Number( )
	{ }

	/**
		Return a normally distributed random number.
		@retval number Next random number
	 */
	virtual inline double next( )
	{
		err_warn( "Normal_Number::next: "
				" Unable to generate normally distributed random number: "
				" Boost (http://www.boost.org/) is not installed.\n" );
		return( 0.0 );
	}

	/**
		Return a normally distributed random number.
		@retval number Next random number
	 */
	virtual inline double operator()( )
	{
		return( next() );
	}

};

#endif // HAVE_BOOST_WS_TOOLS

} // namespace ws_tools

#endif // _RANDOM_NUMBER_HPP
