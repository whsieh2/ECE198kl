.ALL := ../prog7

#
# WARNING: THIS FILE HAS BEEN GENERATED AUTOMATICALLY BY
# WALY TARGET SETUP.  IF YOU WANT TO EDIT, EDIT THE ORIGINAL
# IN target-files/cygwin/jni-Makefile.def
#
# *** This package's source files are listed in Make.inc ***
#

CFLAGS = -g -Wall -DWALY_TARGET_CYGWIN
#CFLAGS = -Wall

LFLAGS = -g -LWALY
G++ = g++

INCLUDE = -IWALY
LIBS = -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL -lpthread

include Make.inc

WALY_HEADERS = Makefile WALY/WALY.h WALY/WALYButton.h WALY/WALYDataFile.h     \
	       WALY/WALYDigitDraw.h WALY/WALYEntryBox.h WALY/WALYEntryBoxIP.h \
	       WALY/WALYFilter.h WALY/WALYFont.h WALY/WALYFrame.h             \
	       WALY/WALYImage.h WALY/WALYLabel.h WALY/WALYNetwork.h	      \
	       WALY/WALYPlatform.h WALY/WALYScreen.h WALY/WALYSDLStubs.h      \
	       WALY/WALYSound.h WALY/WALYWidget.h WALYmain.h
WALY_FILES = WALYmain.o

%.o: %.c ${HEADERS} ${WALY_HEADERS}
	${G++} -c ${CFLAGS} -o $@ ${INCLUDE} $<

%.o: %.cpp ${HEADERS} ${WALY_HEADERS}
	${G++} -c ${CFLAGS} -o $@ ${INCLUDE} $<

../prog7: ${OBJ_FILES} ${WALY_FILES} WALY/libWALY.a
	${G++} ${LFLAGS} -o ../prog7 ${OBJ_FILES} ${WALY_FILES} -lWALY ${LIBS}

WALY/libWALY.a::
	(cd WALY ; make)

clean::
	rm -f *.o *~ *.stackdump
	(cd WALY ; make clean)

clear: clean
	rm -f ../prog7
	(cd WALY ; make clear)
