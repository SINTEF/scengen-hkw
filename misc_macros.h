#ifndef MISC_MACROS_H
#define MISC_MACROS_H

// ----------------------------------------------------------------
// random-number generation macros

/* Random number generator - double from [0,1]
	 rand() is the only random number generator in C++
	 Note that rand() is from 0 to RAND_MAX inclusive!
	 */
#define frand (((double) rand() + 0.5) / ((double) RAND_MAX + 1.0))

/* Random number generator - integer from 0 to Max-1
	 rand() is the only random number generator in VC++
	 Note that rand() is from 0 to RAND_MAX inclusive!
	 */
#define irand(Max) (rand() % (Max))

/* Random numbers from standard normal distribution
	 using Box-Muller formula
	 */
#define Pi 3.1415926535
#define BM_normal() (double)(sqrt(-2*log(frand))*cos(2*Pi*frand))


// ----------------------------------------------------------------
// gen. mathematical macros

/* These definitions need GNU C extensions!
   With the standard definitions (see below),
   min(x,f(x)) will cause f(x) to be computed twice.
   These definitions avoid the problem...
   */
#define min(X, Y)                     \
({ typeof (X) __x = (X), __y = (Y);   \
  (__x < __y) ? __x : __y; })
#define max(X, Y)                     \
({ typeof (X) __x = (X), __y = (Y);   \
  (__x > __y) ? __x : __y; })
/* Standard definitions:
#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define max(X, Y)  ((X) > (Y) ? (X) : (Y))
*/

// use this for comparing two float numbers
#define EPS 1e-8


// ----------------------------------------------------------------
// generic C/C++ macros

#define allocate(var, type, size) if ((var = (type *) malloc(size * sizeof(type))) == NULL) { printf("\nNOT ENOUGH MEMORY!\n\n");	exit(1); }


// ----------------------------------------------------------------
// macros for cross-platform dll-exporting

#ifndef DLL_EXPORT_DEF_H
#define DLL_EXPORT_DEF_H

#if defined _WIN32
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility("default")))
    #define DLL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

#endif


#endif
