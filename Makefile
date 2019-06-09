CC = clang

SOURCEDIR = src
BUILDDIR = build
TESTDIR = test
RESOURCEDIR = resources
TESTRESOURCEDIR = test-resources

main: ${BUILDDIR}/main.o

test: parse-test

clean:
	rm -rf ${BUILDDIR}/*
	rm -rf ${TESTDIR}/*

parse-test: ${TESTDIR}/parse_test.o ${TESTDIR}/schemas.txt

${BUILDDIR}/main.o: ${SOURCEDIR}/main.c
	${CC} -o $@ $^

%/parse.a: ${SOURCEDIR}/parse.c
	${CC} -c -o $@ $^

${TESTDIR}/parse_test.o: ${SOURCEDIR}/parse_test.c ${TESTDIR}/parse.a
	${CC} -o $@ $^

${TESTDIR}/schemas.txt: ${TESTRESOURCEDIR}/schemas.txt
	cp $^ $@
