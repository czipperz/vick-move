CFLAGS=-std=c++11 -I../../src -I../../test -Isrc
LDFLAGS=`find ../../out -type f -not \( -name main.o -o -name configuration.o \)` \
        ../../testout/main.o -lncurses
O=out
S=src
T=test
TO=testout
CXX=clang++

files=$O/move.o      \

testfiles = ${TO}/move_tests.o    \

all: ${files}

$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

${TO}/%.o: $T/%.cc
	@mkdir -p ${TO}
	${CXX} -o $@ -c $< ${CFLAGS}

clean:
	[ ! -d out ] || rm -R out
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`

cleantest:
	[ ! -d ${TO} ] || rm -R ${TO}

test: ${files} ${testfiles}
	${CXX} -o $T/out $^ ${CFLAGS} ${LDFLAGS}
	./$T/out

tags:
	etags `find src -name '*.cc'`
