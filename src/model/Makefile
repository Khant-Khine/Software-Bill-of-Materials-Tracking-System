#SBOM Makefile: updated 11/22/2024
PROG=driver
SRCS!= ls *.cpp
OBJS=${SRCS:S/cpp$/o/g}

CXXFLAGS=-Wall -g -std=c++20
CXXFLAGS+= -I/usr/local/include
LDFLAGS= -L/usr/local/lib
LDFLAGS+= -lsqlite3

.PHONY: all clean

all: ${PROG}

${PROG}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

SBOM.o: SBOM.h SBOM.cpp

ExportSubSystem.o: ExportSubSystem.h ExportSubSystem.cpp

database.o: database.h database.cpp

hashing.o: hashing.h hashing.cpp

authManager.o: authManager.h authManager.cpp

clean:
	@rm -f ${OBJS} ${PROG} *.core
