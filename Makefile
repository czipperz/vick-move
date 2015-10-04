CFLAGS=-std=c++11 -I../../src -I../../test -Isrc
LDFLAGS=`find ../../out -type f -not \( -name main.o -o -name configuration.o \)` \
        -lncurses
O=out
S=src
T=test
CXX=clang++

files=$O/move.o      \

testfiles = $O/move_tests.o    \

all: ${files}

$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

$O/%.o: $T/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

clean:
	[ ! -d out ] || rm -R out
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`

$T/blank:
	touch $T/blank

test: ${files} ${testfiles} $T/blank
	rm $T/blank
	${CXX} -o $T/out ${files} ${testfiles} ${CFLAGS} ${LDFLAGS} ../../src/configuration.cc -Dtesting
	./$T/out

tags:
	etags `find src -name '*.cc'`
