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
CND_CONF=Release
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
LDLIBSOPTIONS=-L../../../../../opencv/creado/install/x86/mingw/bin -lopencv_calib3d320 -lopencv_core320 -lopencv_features2d320 -lopencv_flann320 -lopencv_highgui320 -lopencv_imgcodecs320 -lopencv_imgproc320 -lopencv_ml320 -lopencv_objdetect320 -lopencv_photo320 -lopencv_shape320 -lopencv_stitching320 -lopencv_superres320 -lopencv_video320 -lopencv_videoio320 -lopencv_videostab320 -lopencv_ffmpeg320

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iso_tracker_img_v73.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iso_tracker_img_v73.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iso_tracker_img_v73 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/LIB_ISOPHOTES.o: LIB_ISOPHOTES.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../../opencv/creado/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LIB_ISOPHOTES.o LIB_ISOPHOTES.cpp

${OBJECTDIR}/SerialPort.o: SerialPort.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../../opencv/creado/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SerialPort.o SerialPort.cpp

${OBJECTDIR}/comandos.o: comandos.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../../opencv/creado/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/comandos.o comandos.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../../../opencv/creado/install/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
