
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic -ggdb
DEBUG = 1

ifeq ($(DEBUG),1)
  CXXFLAGS += -g -O0
else
  CXXFLAGS += -O2
endif

OBJDIR = ../obj
SRCDIR = .

OBJ = ${OBJDIR}/additive_mistake/additive_mistake.o\
	${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.o\
	${OBJDIR}/exact/exact.o\
	${OBJDIR}/exact_slack_window/exact_slack_window.o\
	${OBJDIR}/multiplicative_mistake/multiplicative_mistake.o\
	${OBJDIR}/multiplicative_mistake_slack_window/multiplicative_mistake_slack_window.o\
	${OBJDIR}/utils.o

BIN_OBJ = ${OBJDIR}/main.o

.PHONY: ${OBJDIR} clean

all: main

main: ${OBJDIR} ${BIN_OBJ} ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} ${BIN_OBJ} -o ${OBJDIR}/main_bin

${OBJDIR}/additive_mistake/additive_mistake.o: \
	${SRCDIR}/additive_mistake/additive_mistake.cpp
	${CXX} ${CXXFLAGS} -o $@ -c $<

${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.o: \
	${SRCDIR}/additive_mistake_slack_window/additive_mistake_slack_window.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/exact/exact.o: \
	${SRCDIR}/exact/exact.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/exact_slack_window/exact_slack_window.o: \
	${SRCDIR}/exact_slack_window/exact_slack_window.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/multiplicative_mistake/multiplicative_mistake.o: \
	${SRCDIR}/multiplicative_mistake/multiplicative_mistake.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}/multiplicative_mistake_slack_window/multiplicative_mistake_slack_window.o: \
	${SRCDIR}/multiplicative_mistake_slack_window/multiplicative_mistake_slack_window.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<
	
${OBJDIR}/utils.o: \
	${SRCDIR}/utils.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${BIN_OBJ}: \
	${SRCDIR}/main.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJDIR}:
	mkdir -p ${OBJDIR}/additive_mistake
	mkdir -p ${OBJDIR}/additive_mistake_slack_window
	mkdir -p ${OBJDIR}/exact
	mkdir -p ${OBJDIR}/exact_slack_window
	mkdir -p ${OBJDIR}/multiplicative_mistake
	mkdir -p ${OBJDIR}/multiplicative_mistake_slack_window
	mkdir -p ${OBJDIR}/parser

clean:
	rm -rf ${OBJDIR}/additive_mistake
	rm -rf ${OBJDIR}/additive_mistake_slack_window
	rm -rf ${OBJDIR}/exact
	rm -rf ${OBJDIR}/exact_slack_window
	rm -rf ${OBJDIR}/multiplicative_mistake
	rm -rf ${OBJDIR}/multiplicative_mistake_slack_window
	rm -rf ${OBJDIR}/parser
	rm -f ${SRCDIR}/output