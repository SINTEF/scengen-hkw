/*********************************************************************/
/***  Høyland-Kaut-Wallace algorithm for scenario generation       ***/
/***                                                               ***/
/***  author: Michal Kaut                                          ***/
/*********************************************************************/

#ifndef HKW_SG_H
#define HKW_SG_H

#include "misc_macros.h" // defines DLL_PUBLIC
#include "matrix.h"


/// main scenario-generation procedure
/**
	Generates one subtree using the HKW algorithm (heuristics)
	\param[in] FormatOfMoms - format of the target moments
		It is a sum of following bits:
		- 1 -> 2nd moment is Var instead of StDev
		- 2 -> 4th moment is Kurtose - 3
		- 4 -> Higher moments are not scaled by StDev
		- 8 -> TarMom[i-1] = E{X^i} ... lower bits are ignored in this case \n
		The reasonable values are 0,1,2,3,4,5,6,7,8
	\param[in] p_TarMoms pointer to matrix of target moments
	\param[in] p_TgCorrs pointer to matrix of target correlations
	\param[in] p_Probs pointer to vector of target probabilities
	\param     p_OutMat pointer to matrix where the scenarios go
	\param[in] MaxErrMom maximum allowed error for moments
	\param[in] MaxErrCorr maximum allowed error for correlations
	\param[in] TestLevel level of output during the algorithm
	\param[in] MaxTrial maximum number of trials
	\param[in] MaxIter maximum number of iterations in each trial
	\param[in] UseStartValues use values in p_OutMat as a starting point \n
		This will only be used in the first trial. If this does not converge
		and \a MaxTrial > 1, the other trials start from a random starting point.

	The main structure of the algorithm is as follows:
	- 1	trial = 1
	- 2	if UseStartValues = true and trial = 1, use the current values in
	   	\a p_OutMat \n otherwise generate a random starting point
	- 3	iter = 1
	- 4	if error-in-moments > \a MaxErrMom, correct moments
	- 5	if error-in-correlations > \a MaxErrCorr, correct correlations
	- 6	if one of the errors > max and iter < \a MaxIter,
	   	then iter++ and go to 4
	- 7	if one of the errors > max and trial < \a MaxTrial,
	   	then trial++ and go to 2
	- 8	if both errors < max, report the results (we have convergence),
		otherwise report failure and return the best scenarios found
**/
DLL_PUBLIC int HKW_ScenGen(int const FormatOfMoms,
                           TMatrix const * const p_TarMoms,
                           TMatrix const * const p_TgCorrs,
                           TVector const * const p_Probs,
                           TMatrix * const p_OutMat,
                           double const MaxErrMom, double const MaxErrCorr,
                           int const TestLevel, int const MaxTrial,
                           int const MaxIter, int const UseStartValues);


/// wrapper for HKW_ScenGen(), using only standard C arrays
/**
	For description of parameters see HKW_ScenGen(). \n
	The only difference, apart from the types, is that \a probs is allowed
	to be NULL, meaning equiprobable scenarios, and \a outSc is allowed to
	be NULL, in which case it gets allocated.
**/
DLL_PUBLIC int scengen_HKW(double ** const tgMoms, int const FormatOfMoms,
                           double ** const tgCorrs, double * const probs,
                           int const nVar, int const nScen,
                           double ** const outSc,
                           double const MaxErrMom, double const MaxErrCorr,
                           int const TestLevel, int const MaxTrial,
                           int const MaxIter, int const UseStartValues);

#endif
