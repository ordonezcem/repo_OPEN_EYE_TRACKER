#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW_1-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/LIB_ISOPHOTES.o \
	${OBJECTDIR}/SerialPort.o \
	${OBJECTDIR}/comandos.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/D/opencv_mybuild/opencv-3.4.1/creado_cristian/install/x86/mingw/bin -L/D/opencv_mybuild/opencv-3.4.1/creado_cristian/install/x64/mingw/bin -lopencv_calib3d341 -lopencv_core341 -lopencv_dnn341 -lopencv_features2d341 -lopencv_flann341 -lopencv_highgui341 -lopencv_imgcodecs341 -lopencv_imgproc341 -lopencv_ml341 -lopencv_objdetect341 -lopencv_photo341 -lopencv_shape341 -lopencv_stitching341 -lopencv_superres341 -lopencv_video341 -lopencv_videoio341 -lopencv_videostab341 -lopencv_ffmpeg341_64

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iso_tracker_v1.0.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iso_tracker_v1.0.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iso_tracker_v1.0 ${OBJECTFILES} ${LDLIBSOPTIONS} -static-libgcc -static-libstdc++

${OBJECTDIR}/LIB_ISOPHOTES.o: LIB_ISOPHOTES.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/opencv_mybuild/opencv-3.4.1/creado_cristian/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LIB_ISOPHOTES.o LIB_ISOPHOTES.cpp

${OBJECTDIR}/SerialPort.o: SerialPort.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/opencv_mybuild/opencv-3.4.1/creado_cristian/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SerialPort.o SerialPort.cpp

${OBJECTDIR}/comandos.o: comandos.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/opencv_mybuild/opencv-3.4.1/creado_cristian/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/comandos.o comandos.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/opencv_mybuild/opencv-3.4.1/creado_cristian/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
