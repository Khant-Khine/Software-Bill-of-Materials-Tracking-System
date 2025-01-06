# Makefile for Unit tests

PROG1=sbomTest
PROG2=dbTest
PROG3=hashTest
PROG4=authTest
PROG5=exportSubSystemTest

SRCS1=sbomTest.cpp ../../src/model/SBOM.cpp
SRCS2=dbTest.cpp ../../src/model/database.cpp
SRCS3=hashTest.cpp ../../src/model/hashing.cpp
SRCS4=authTest.cpp ../../src/model/authManager.cpp ../../src/model/database.cpp
SRCS5=exportSubSystemTest.cpp ../../src/model/ExportSubSystem.cpp ../../src/model/SBOM.cpp

OBJS1=${SRCS1:S/cpp$/o/g}
OBJS2=${SRCS2:S/cpp$/o/g}
OBJS3=${SRCS3:S/cpp$/o/g}
OBJS4=${SRCS4:S/cpp$/o/g}
OBJS5=${SRCS5:S/cpp$/o/g}

CXXFLAGS=-Wall -g -std=c++20
CXXFLAGS+= -I../../src/model -I/usr/local/include
LDFLAGS= -L/usr/local/lib
LDFLAGS+= -lgtest -lgtest_main -pthread -lsqlite3

.PHONY: all clean

all: ${PROG1} ${PROG2} ${PROG3} ${PROG4} ${PROG5}

${PROG1}: ${OBJS1}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS1} ${LDFLAGS}

${PROG2}: ${OBJS2}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS2} ${LDFLAGS}

${PROG3}: ${OBJS3}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS3} ${LDFLAGS}

${PROG4}: ${OBJS4}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS4} ${LDFLAGS}

${PROG5}: ${OBJS5}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS5} ${LDFLAGS}

../../src/model/SBOM.o: ../../src/model/SBOM.cpp ../../src/model/SBOM.h
	${CXX} ${CXXFLAGS} -c ../../src/model/SBOM.cpp -o ../../src/model/SBOM.o

sbomTest.o: sbomTest.cpp ../../src/model/SBOM.h
	${CXX} ${CXXFLAGS} -c sbomTest.cpp -o sbomTest.o

../../src/model/database.o: ../../src/model/database.cpp ../../src/model/database.h
	${CXX} ${CXXFLAGS} -c ../../src/model/database.cpp -o ../../src/model/database.o

dbTest.o: dbTest.cpp ../../src/model/database.h
	${CXX} ${CXXFLAGS} -c dbTest.cpp -o dbTest.o

../../src/model/hashing.o: ../../src/model/hashing.cpp ../../src/model/hashing.h
	${CXX} ${CXXFLAGS} -c ../../src/model/hashing.cpp -o ../../src/model/hashing.o

hashTest.o: hashTest.cpp ../../src/model/hashing.h
	${CXX} ${CXXFLAGS} -c hashTest.cpp -o hashTest.o

../../src/model/authManager.o: ../../src/model/authManager.cpp ../../src/model/authManager.h
	${CXX} ${CXXFLAGS} -c ../../src/model/authManager.cpp -o ../../src/model/authManager.o

authTest.o: authTest.cpp ../../src/model/authManager.h
	${CXX} ${CXXFLAGS} -c authTest.cpp -o authTest.o

../../src/model/ExportSubSystem.o: ../../src/model/ExportSubSystem.cpp ../../src/model/ExportSubSystem.h
	${CXX} ${CXXFLAGS} -c ../../src/model/ExportSubSystem.cpp -o ../../src/model/ExportSubSystem.o

exportSubSystemTest.o: exportSubSystemTest.cpp ../../src/model/ExportSubSystem.h
	${CXX} ${CXXFLAGS} -c exportSubSystemTest.cpp -o exportSubSystemTest.o

clean:
	@rm -f ${OBJS1} ${OBJS2} ${OBJS3} ${OBJS4} ${OBJS5}  ${PROG1} ${PROG2} ${PROG3} ${PROG4} ${PROG5}
