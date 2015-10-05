CFLAGS=-std=c++11 -I../../src -I../../test -Isrc
LDFLAGS=`find ../../out -type f -not \( -name main.o -o -name configuration.o \)` \
        -lncurses
O=out
S=src
T=test
TO=testout
CXX=clang++

files=$O/mv.o        \
      $O/mv_text.o   \
      $O/mvbw.o      \
      $O/mvbww.o     \
      $O/mvcol.o     \
      $O/mvd.o       \
      $O/mvf_mvb.o   \
      $O/mvfeow.o    \
      $O/mvfeoww.o   \
      $O/mvfw.o      \
      $O/mvfww.o     \
      $O/mvline.o    \

testfiles=${TO}/move_tests.o    \

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
	[ ! -d $O ] || rm -R $O
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	[ ! -d ${TO} ] || rm -R ${TO}

$T/blank:
	@mkdir -p $T
	@touch $T/blank

test: ${files} ${testfiles} $T/blank
	@rm $T/blank
	${CXX} -o ${TO}/out ${files} ${testfiles} ${CFLAGS} ${LDFLAGS} ../../src/configuration.cc -Dtesting ../../testout/test_main.o
	./${TO}/out

tags:
	etags `find src -name '*.cc'`
