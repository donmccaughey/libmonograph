EXTRA_DIST = LICENSE README.md

monographdir = $(includedir)/monograph
monograph_HEADERS = src/monograph/monograph.h \
					src/monograph/box.h \
					src/monograph/point.h \
					src/monograph/rect.h \
					src/monograph/size.h

AM_CPPFLAGS = -I$(srcdir)/src
lib_LIBRARIES = libmonograph.a
libmonograph_a_SOURCES = src/monograph/monograph.h \
						 src/monograph/box.h src/monograph/box.c \
						 src/monograph/point.h src/monograph/point.c \
						 src/monograph/rect.h src/monograph/rect.c \
						 src/monograph/size.h src/monograph/size.c

LDADD = $(lib_LIBRARIES)
check_PROGRAMS = test/box_test

TESTS = $(check_PROGRAMS)



