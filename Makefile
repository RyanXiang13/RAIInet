CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = raiinet
OBJECTS = main.o link.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}