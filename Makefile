CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++20
INCLUDE = -I.
TARGET=$(word 2, $(MAKECMDGOALS))
OUTPUTDIR=bin/${TARGET}
OUTPUT=${OUTPUTDIR}/solution.out

compile:
	@echo "Compiling $(TARGET) ..."
	@mkdir -p ${OUTPUTDIR}
	@${CXX} ${CXXFLAGS} ${INCLUDE} main.cpp ${TARGET}/solution.cpp -o ${OUTPUT}
	@if [ -f ${OUTPUT} ]; then \
	   echo "Output file is available as $(OUTPUT)"; \
	fi
run:
	@./${OUTPUT}

clean:
	@rm -rf bin