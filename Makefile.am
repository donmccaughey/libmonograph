AM_CPPFLAGS = -D_BSD_SOURCE \
              -D_GNU_SOURCE \
			  -I$(srcdir)/src
AM_CFLAGS = -std=c99

monographdir = $(includedir)/monograph
monograph_HEADERS = src/monograph/monograph.h \
					src/monograph/box.h \
					src/monograph/canvas.h \
					src/monograph/graph.h \
					src/monograph/point.h \
					src/monograph/rect.h \
					src/monograph/size.h

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
				 test/rect_test \
				 test/size_test

test_data = test/data/test1.monograph

TESTS = $(check_PROGRAMS)

xcode_files = configure_for_xcode.mk \
			  libmonograph.xcodeproj/project.pbxproj \
			  src/monograph/Info.plist

EXTRA_DIST = LICENSE README.md $(test_data) $(xcode_files)

