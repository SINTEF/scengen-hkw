#!/bin/sh

# -------------------------------------------------------------------
# Make package with the sources
TGDIR=scen-gen_HKW_src
mkdir -p ${TGDIR}

# copy the source files
for f in ../*.h ../*.c ../*.cbp ../Makefile ../Doxyfile ../*.txt; do
	if [ -f $f ]; then
		cp $f ${TGDIR}/
	fi
done

# example target files
mkdir -p ${TGDIR}/doc
cp ../doc/sample* ${TGDIR}/doc/

# copy license and read-me file
cp license* ${TGDIR}/
cp read-me_src.txt ${TGDIR}/read_me.txt

# create the files; tar also removes all the sources
7z a -tzip -l ${TGDIR} ${TGDIR} > /dev/null
tar -c -h --xz -f ${TGDIR}.txz ${TGDIR}
tar -c -h --remove-files -a -f ${TGDIR}.tgz ${TGDIR}


# -------------------------------------------------------------------
# Make package with the binary

ARCH=`uname -m`
ARCH=${ARCH#*_}
TGDIR=scen-gen_HKW_bin_Linux-x${ARCH}
mkdir -p ${TGDIR}

cp ../bin/Release/scen-gen_HKW ${TGDIR}/
# copy the sample target files (uncompressed)
7z x -o${TGDIR} ../doc/sample_inputs.7z > /dev/null

# copy license and read-me file
cp license* ${TGDIR}/
cp read-me_bin.txt ${TGDIR}/read_me.txt

# create the files; tar also removes all the sources
tar -c -h --xz -f ${TGDIR}.txz ${TGDIR}
tar -c -h --remove-files -a -f ${TGDIR}.tgz ${TGDIR}
