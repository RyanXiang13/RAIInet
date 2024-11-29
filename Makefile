CXX = g++
CXXFLAGS = -std=c++14 -Wall -frtti -MMD -I/usr/include/X11
LDFLAGS = -L/usr/X11R6/lib -lX11
EXEC = raiinet
OBJECTS = subject.o link.o player.o cell.o download.o firewall.o linkboost.o polarize.o scan.o teleport.o skipturn.o buff.o textobserver.o graphicsobserver.o window.o game.o main.o ability.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} -frtti ${OBJECTS} ${LDFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}