CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic
INCLUDE = -Ihelpers
TARGET=$(word 2, $(MAKECMDGOALS))

compile:
	echo "this is $(TARGET)"
	${CXX} ${CXXFLAGS} ${INCLUDE} main.cpp ${TARGET}/solution.cpp -o ${TARGET}/solution.out

run:
	./${TARGET}/solution.out

%:
	@: