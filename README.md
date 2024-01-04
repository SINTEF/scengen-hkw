Moment-based scenario generation
================================

This repository includes the original C version of the moment-matching scenario-generation code,
as described in paper _A Heuristic for Moment-Matching Scenario Generation_ by Kjetil Høyland, Michal Kaut and Stein W. Wallace , published in [Computational Optimization and Applications, 24 (2-3), pp. 169–185, 2003](http://dx.doi.org/doi:10.1023/A:1021853807313).

The code generates scenarios for multivariate random variables with distribution specified by the first four moments and a correlation matrix.

I works by alternating between improving the moments and the correlation of the generated distribugion.
While it normally converges in a couple of iterations, there is no convergence guarantee; the code will do several trials with different start points, if needed.


Building
--------

### Code::Blocks project

The code comes with a project file for the [Code::Blocks IDE](https://www.codeblocks.org/), `scen-gen_HKW.cbp`.
The project includes the following _targets_:

- `Debug` and `Release`
	- debug and release versions of the main executable, `scen-gen_HKW[.exe]`
- `Debug_dll` and `Release_dll`
	- debug and release versions for building a dynamic library, `libscen-gen_HKW.[dll|so]`
- `Release_w_dll`
	- alternative executable, using (and therefore requiring) the dynamic library
- `cubic_trsf_dll`
	- generates `libHKW_cubic.[dll|so]` containing only the cubic transformation for moment correction


### Minimal makefile

Using `Makefile`, which is a minimal make file for building of the main executable file.


Usage of `scen-gen_HKW[.exe]`
----------------------------

The main executable uses a rather rigid input, requiring the following input files:

- `tg_moms.txt` with target moments
- `tg_corrs.txt` with the target correlation matrix

These files must include a matrix of numbers in the following format:

- number of rows
- number of columns
- data (by rows)
- rest of the file is ignored

The target-moment matrix is given with moments in rows and variables in columns, so the first number is always 4 and the second number is the number of variables.

### Specified probabilities

In addition, it is possible to specify probabilities of the generated scenarios (using command-line argument `-p`), given as a vector in the following format:

- number of elements
- data
- rest of the file is ignored

The number of elements must be equal to the number of generated scenarios, and the values must be positive and sum up to 1.0.

### Output

Output is written to file `out_scen.txt`, but this can be overwritten using `-o` argument.

For a full list of options, run `scen-gen_HKW[.exe]` without any arguments.

### Example input files

Example input files are provided in `doc/sample_inputs.7z`.
With these unpacked in the same directory as `scen-gen_HKW[.exe]`, one can do:

- `scen-gen_HKW 50 -f 1 -o 50_scens.txt` to generate 50 scenarios and save them to `50_scens.txt`
- `scen-gen_HKW 100 -f 1 -p prob.txt` to generate 100 scenarios with probabilities from `prob.txt` and save them to (the default) `out_scen.txt`.

The `-f 1` argument is needed since the provided `tg_moms.txt` uses spreadsheet-like definitions of moments (as written in the file itself). To get all possible values of `-f`, run `scen-gen_HKW` without any arguments.
