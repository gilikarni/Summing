
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -Werror

ifeq ($(DEBUG),1)
  CXXFLAGS += -g -O0
else
  CXXFLAGS += -O2
endif

OBJDIR = ~/Summing/obj
SRCDIR = ~/Summing/src

OBJ = \ 
	${OBJDIR}/additive_mistake/additive_mistake.o \
	${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.o	\
	${OBJDIR}/exact/exact.o	\
	${OBJDIR}/exact_slack_window/exact_slack_window.o \
	${OBJDIR}/multiplative_mistake/multiplative_mistake.o \
	${OBJDIR}/multiplative_mistake_slack_window/multiplative_mistake_slack_window.o \
	${OBJDIR}/parser/parser.o \
	${OBJDIR}/main.o \

BIN_OBJ = ${OBJDIR}/main.o

${OBJDIR}/additive_mistake/additive_mistake.o: \ 
	${OBJDIR}/additive_mistake/additive_mistake.cpp \
	${OBJDIR}/additive_mistake/additive_mistake.h
	
${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.o: \ 
	${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.cpp \
	${OBJDIR}/additive_mistake_slack_window/additive_mistake_slack_window.h
	
${OBJDIR}/exact/exact.o: \ 
	${OBJDIR}/exact/exact.cpp \
	${OBJDIR}/exact/exact.h
	
${OBJDIR}/exact_slack_window/exact_slack_window.o: \ 
	${OBJDIR}/exact_slack_window/exact_slack_window.cpp \
	${OBJDIR}/exact_slack_window/exact_slack_window.h
	
${OBJDIR}/multiplative_mistake/multiplative_mistake.o: \ 
	${OBJDIR}/multiplative_mistake/multiplative_mistake.cpp \
	${OBJDIR}/multiplative_mistake/multiplative_mistake.h
	
${OBJDIR}/multiplative_mistake_slack_window/multiplative_mistake_slack_window.o: \ 
	${OBJDIR}/multiplative_mistake_slack_window/multiplative_mistake_slack_window.cpp \
	${OBJDIR}/multiplative_mistake_slack_window/multiplative_mistake_slack_window.h
	
${OBJDIR}/parser/parser.o: \ 
	${OBJDIR}/parser/parser.cpp \
	${OBJDIR}/parser/parser.h

main: ${OBJDIR} ${BIN_OBJ} ${OBJ}

${OBJDIR}:	.PHONY
	mkdir -p ${OBJDIR}
	mkdir -p ${OBJDIR}/additive_mistake
	mkdir -p ${OBJDIR}/additive_mistake_slack_window
	mkdir -p ${OBJDIR}/exact
	mkdir -p ${OBJDIR}/exact_slack_window
	mkdir -p ${OBJDIR}/multiplative_mistake
	mkdir -p ${OBJDIR}/multiplative_mistake_slack_window
	mkdir -p ${OBJDIR}/parser
        
clean:	.PHONY
	rmdir -rf ${OBJDIR}