CXX = g++
CXXFLAGS = -std=c++14 -Wall -frtti -MMD
EXEC = raiinet
OBJECTS = subject.o link.o player.o cell.o firewall.o textobserver.o game.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} -frtti ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}