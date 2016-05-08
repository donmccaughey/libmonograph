EXTRA_DIST = LICENSE README.md

monographdir = $(includedir)/monograph
monograph_HEADERS = src/monograph/monograph.h \
					src/monograph/box.h \
					src/monograph/canvas.h \
					src/monograph/graph.h \
					src/monograph/point.h \
					src/monograph/rect.h \
					src/monograph/size.h

AM_CPPFLAGS = -I$(srcdir)/src
AM_CFLAGS = -std=c99
lib_LIBRARIES = libmonograph.a
libmonograph_a_SOURCES = $(monograph_HEADERS) \
						 src/monograph/box.c \
						 src/monograph/canvas.c \
						 src/monograph/graph.c \
						 src/monograph/point.c \
						 src/monograph/rect.c \
						 src/monograph/size.c

LDADD = $(lib_LIBRARIES)
check_PROGRAMS = test/box_test \
				 test/canvas_test \
				 test/graph_test \
				 test/point_test \
				 test/rect_test

TESTS = $(check_PROGRAMS)

