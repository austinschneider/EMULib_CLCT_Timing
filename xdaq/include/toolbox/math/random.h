// $Id: random.h,v 1.4 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_math_random_h_
#define _toolbox_random_h_

#include <math.h>
#include <stdint.h>

namespace toolbox {
namespace math {

//----------------------------------------------------------------------------//
// class RandomGenerator: base class for all random generators		      //
//----------------------------------------------------------------------------//

class RandomGenerator {
  protected:
    uint32_t seed;		// the seed of the random generator
    uint32_t max_val;		// uniform uint32_t values within [0...max_val]
    RandomGenerator *gen;	// pointer to generator    
  public:
    RandomGenerator (uint32_t new_seed = 0)
	{ seed = (new_seed & 0x7fffffff); }
    RandomGenerator (RandomGenerator* ran)
	{ gen = ran; max_val = ran->max_val; seed = ran->seed; }  
    virtual ~RandomGenerator() { }
    uint32_t Seed (void) const { return seed; }
    uint32_t Maximum (void) const { return max_val; }
    RandomGenerator* Generator (void) const { return gen; }
    virtual uint32_t Long (void) = 0;
};

class Ran002: public RandomGenerator {	// Press's combined MLCG "ran2"
  private:
    int32_t idum, idum2, iy, iv[32];
  public:
    virtual ~Ran002();
    Ran002 (uint32_t seed = 0);
    virtual uint32_t Long (void);
};

//----------------------------------------------------------------------------//
// class NormalDistribution: normal (Gaussian) distributed random numbers     //
//----------------------------------------------------------------------------//

class NormalDistribution : public RandomGenerator 
{
  protected:
    double m, s, scale, cacheval;
    int cached;
  public:
    NormalDistribution (void) {}
    NormalDistribution (double mean, double stdev, 
			RandomGenerator *ran) : RandomGenerator(ran) 
        { cached = 0; m = mean; s = stdev; scale  = 2.0 / max_val; }
    virtual ~NormalDistribution ();
    double operator () (void);
    uint32_t Long (void) { return gen->Long(); };
    double Mean (void) const { return m; }
    double Stdev (void) const { return s; }
};

//----------------------------------------------------------------------------//
// class LogNormalDistribution: log-normal distributed random numbers         //
//----------------------------------------------------------------------------//

class LogNormalDistribution 
    : public NormalDistribution {
  protected:
    double m_log, s_log;
    void Initialize (double mean, double stdev);
  public:
    LogNormalDistribution (void) {}
    LogNormalDistribution (double mean, double stdev, 
			   RandomGenerator* ran) 
	: NormalDistribution(mean,stdev,ran) { Initialize(mean,stdev); }
    virtual ~LogNormalDistribution();
    double operator () (void) 
        { return exp(this->NormalDistribution::operator()()); }
    double Mean (void) const { return m_log; }
    double Stdev (void) const { return s_log; }
};

class LogNormalGen {
	
	public:
	
	LogNormalGen (uint32_t seed, double mean, double stdev, uint32_t min, uint32_t max ) {
		
		r002_ = new Ran002(seed);		
		lognorm_ = new LogNormalDistribution (mean, stdev, r002_);
		min_ = min;
		max_ = max;
	}
	
	LogNormalGen (uint32_t seed, double mean, double stdev) 
	{
		r002_ = new Ran002(seed);		
		lognorm_ = new LogNormalDistribution (mean, stdev, r002_);
		min_ = 0;
		max_ = 0xffffffff;
	}	
	
	~LogNormalGen()
	{
		delete lognorm_;
		delete r002_;
	}
	
	uint32_t getRandomSize() {
		while(1) {
			uint32_t esize = ((uint32_t)(*lognorm_)() & 0xfffffffc ); // multiple of 4
			if (esize >= max_) return max_;
			if (esize >= min_) return esize;
		}
	}

	uint32_t getRawRandomSize() 
	{
		  uint32_t esize = (uint32_t)(*lognorm_)(); 
		  return esize;
	}

	protected:
	
	Ran002 * r002_;		
	LogNormalDistribution * lognorm_;
	uint32_t min_;
	uint32_t max_;
	
};

}
}

#endif
