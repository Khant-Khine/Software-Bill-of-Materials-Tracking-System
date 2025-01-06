#Generic Witty Makefile

PROG=sbomView
PORT=8086 #Port Number Range 8080-8099

SRCS!= ls ./*.cpp
SRCS1= ../../src/model/SBOM.cpp ../../src/model/ExportSubSystem.cpp ../../src/model/database.cpp ../../src/model/hashing.cpp ../../src/model/authManager.cpp

OBJS=${SRCS:S/cpp$/o/g} ${SRCS1:S/cpp$/o/g}

CXXFLAGS=-Wall -g -std=c++20
CXXFLAGS+=-I../../src/model -I/usr/local/include
LDFLAGS= -L/usr/local/lib
LDFLAGS+= -lwt -lwthttp -lsqlite3

.PHONY: all clean start stop

all: ${PROG}

${PROG}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${LDFLAGS}

sbomApplication.o: sbomApplication.h sbomApplication.cpp

signIn.o: signIn.h signIn.cpp

signUp.o: signUp.h signUp.cpp

sbom_library.o: sbom_library.h sbom_library.cpp

sbom_details.o: sbom_details.h sbom_details.cpp

../../src/model/SBOM.o: ../../src/model/SBOM.h ../../src/model/SBOM.cpp
	${CXX} ${CXXFLAGS} -c ../../src/model/SBOM.cpp -o ../../src/model/SBOM.o

../../src/model/ExportSubSystem.o: ../../src/model/ExportSubSystem.h ../../src/model/ExportSubSystem.cpp
	${CXX} ${CXXFLAGS} -c ../../src/model/ExportSubSystem.cpp -o ../../src/model/ExportSubSystem.o

../../src/model/database.o: ../../src/model/database.h ../../src/model/database.cpp
	${CXX} ${CXXFLAGS} -c ../../src/model/database.cpp -o ../../src/model/database.o

../../src/model/hashing.o: ../../src/model/hashing.h ../../src/model/hashing.cpp
	${CXX} ${CXXFLAGS} -c ../../src/model/hashing.cpp -o ../../src/model/hashing.o

../../src/model/authManager.o: ../../src/model/authManager.h ../../src/model/authManager.cpp
	${CXX} ${CXXFLAGS} -c ../../src/model/authManager.cpp -o ../../src/model/authManager.o

clean:
	@rm -f ${PROG} ${OBJS} resources

start: ${PROG}
	@ln -fs /usr/local/share/Wt/resources ./resources
	@./${PROG} --docroot ./ --http-address 0.0.0.0 --http-port ${PORT} &

stop:
	@pkill ${PROG}
	@rm -f ./resources
