
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -Werror

ifeq ($(DEBUG),1)
  CXXFLAGS += -g -O0
else
  CXXFLAGS += -O2
endif

OBJDIR = ~/Summing/obj
SRCDIR = ~/Summing/src

OBJ = ${OBJDIR}/additive_mistake/additive_mistake.o\
	${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.o\
	${OBJDIR}/exact/exact.o\
	${OBJDIR}/exact_slack_window/exact_slack_window.o\
	${OBJDIR}/multiplative_mistake/multiplative_mistake.o\
	${OBJDIR}/multiplative_mistake_slack_window/multiplative_mistake_slack_window.o\
	${OBJDIR}/parser/parser.o\
	${OBJDIR}/parser/time.o

BIN_OBJ = ${OBJDIR}/main.o

.PHONY: ${OBJDIR} clean

all: main

main: ${OBJDIR} ${BIN_OBJ} ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} ${BIN_OBJ} -o ${OBJDIR}/main_bin

${OBJDIR}/additive_mistake/additive_mistake.o: \
	${SRCDIR}/additive_mistake/additive_mistake.cpp
	${CXX} ${CXXFLAGS} -o $@ -c $^
	
${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.o: \
	${SRCDIR}/additive_mistake_slack_window/additive_mistake_slack_window.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^
	
${OBJDIR}/exact/exact.o: \
	${SRCDIR}/exact/exact.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^
	
${OBJDIR}/exact_slack_window/exact_slack_window.o: \
	${SRCDIR}/exact_slack_window/exact_slack_window.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^
	
${OBJDIR}/multiplative_mistake/multiplative_mistake.o: \
	${SRCDIR}/multiplative_mistake/multiplative_mistake.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^
	
${OBJDIR}/multiplative_mistake_slack_window/multiplative_mistake_slack_window.o: \
	${SRCDIR}/multiplative_mistake_slack_window/multiplative_mistake_slack_window.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^
	
${OBJDIR}/parser/time.o: \
	${SRCDIR}/parser/time.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^
	
${OBJDIR}/parser/parser.o: \
	${SRCDIR}/parser/parser.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^

${BIN_OBJ}: \
	${SRCDIR}/main.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^

${OBJDIR}:
	mkdir -p ${OBJDIR}/additive_mistake
	mkdir -p ${OBJDIR}/additive_mistake_slack_window
	mkdir -p ${OBJDIR}/exact
	mkdir -p ${OBJDIR}/exact_slack_window
	mkdir -p ${OBJDIR}/multiplative_mistake
	mkdir -p ${OBJDIR}/multiplative_mistake_slack_window
	mkdir -p ${OBJDIR}/parser
        
clean:
	rm -rf ${OBJDIR}/additive_mistake
	rm -rf ${OBJDIR}/additive_mistake_slack_window
	rm -rf ${OBJDIR}/exact
	rm -rf ${OBJDIR}/exact_slack_window
	rm -rf ${OBJDIR}/multiplative_mistake
	rm -rf ${OBJDIR}/multiplative_mistake_slack_window
	rm -rf ${OBJDIR}/parser
	
	
	
	
	
	
	
	
	