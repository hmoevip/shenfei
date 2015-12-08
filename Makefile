#############################################################################
# Makefile for building: opengl
# Generated by qmake (2.01a) (Qt 4.8.7) on: Sun Dec 6 22:30:21 2015
# Project:  opengl.pro
# Template: app
# Command: /usr/local/bin/qmake -spec /usr/local/Cellar/qt/4.8.7/mkspecs/unsupported/macx-clang-libc++ CONFIG+=x86_64 -o Makefile opengl.pro
#############################################################################

####### Compiler, tools and options

CC            = clang
CXX           = clang++
DEFINES       = -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -mmacosx-version-min=10.7 -O2 -arch x86_64 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -stdlib=libc++ -mmacosx-version-min=10.7 -O2 -arch x86_64 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/Cellar/qt/4.8.7/mkspecs/unsupported/macx-clang-libc++ -I. -I/usr/local/Cellar/qt/4.8.7/lib/QtCore.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.7/lib/QtCore.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.7/lib/QtGui.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.7/lib/QtGui.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.7/lib/QtOpenGL.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.7/lib/QtOpenGL.framework/Versions/4/Headers -I/usr/local/Cellar/qt/4.8.7/include -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -F/usr/local/Cellar/qt/4.8.7/lib
LINK          = clang++
LFLAGS        = -headerpad_max_install_names -stdlib=libc++ -mmacosx-version-min=10.7 -arch x86_64
LIBS          = $(SUBLIBS) -F/usr/local/Cellar/qt/4.8.7/lib -L/usr/local/Cellar/qt/4.8.7/lib -framework GLUT -framework QtOpenGL -L/usr/local/Cellar/qt/4.8.7/lib -F/usr/local/Cellar/qt/4.8.7/lib -framework QtGui -framework QtCore -framework OpenGL -framework AGL 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/local/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.7

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		glwidget.cpp \
		process.cpp moc_mainwindow.cpp \
		moc_glwidget.cpp
OBJECTS       = main.o \
		mainwindow.o \
		glwidget.o \
		process.o \
		moc_mainwindow.o \
		moc_glwidget.o
DIST          = /usr/local/Cellar/qt/4.8.7/mkspecs/common/unix.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/mac.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/gcc-base.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/gcc-base-macx.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/clang.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/qconfig.pri \
		/usr/local/Cellar/qt/4.8.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt_functions.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt_config.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/default_pre.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/release.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/default_post.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/x86_64.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/shared.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/warn_on.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/unix/opengl.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/unix/thread.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/moc.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/rez.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/resources.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/uic.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/yacc.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/lex.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/include_source_dir.prf \
		opengl.pro
QMAKE_TARGET  = opengl
DESTDIR       = 
TARGET        = opengl

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-O2 \
		-arch \
		x86_64 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: opengl.pro  /usr/local/Cellar/qt/4.8.7/mkspecs/unsupported/macx-clang-libc++/qmake.conf /usr/local/Cellar/qt/4.8.7/mkspecs/common/unix.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/mac.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/gcc-base.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/gcc-base-macx.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/common/clang.conf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/qconfig.pri \
		/usr/local/Cellar/qt/4.8.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt_functions.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt_config.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/default_pre.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/release.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/default_post.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/x86_64.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/shared.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/warn_on.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/unix/opengl.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/unix/thread.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/moc.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/rez.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/resources.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/uic.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/yacc.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/lex.prf \
		/usr/local/Cellar/qt/4.8.7/mkspecs/features/include_source_dir.prf \
		/usr/local/Cellar/qt/4.8.7/lib/QtOpenGL.framework/QtOpenGL.prl \
		/usr/local/Cellar/qt/4.8.7/lib/QtGui.framework/QtGui.prl \
		/usr/local/Cellar/qt/4.8.7/lib/QtCore.framework/QtCore.prl
	$(QMAKE) -spec /usr/local/Cellar/qt/4.8.7/mkspecs/unsupported/macx-clang-libc++ CONFIG+=x86_64 -o Makefile opengl.pro
/usr/local/Cellar/qt/4.8.7/mkspecs/common/unix.conf:
/usr/local/Cellar/qt/4.8.7/mkspecs/common/mac.conf:
/usr/local/Cellar/qt/4.8.7/mkspecs/common/gcc-base.conf:
/usr/local/Cellar/qt/4.8.7/mkspecs/common/gcc-base-macx.conf:
/usr/local/Cellar/qt/4.8.7/mkspecs/common/clang.conf:
/usr/local/Cellar/qt/4.8.7/mkspecs/qconfig.pri:
/usr/local/Cellar/qt/4.8.7/mkspecs/modules/qt_webkit_version.pri:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt_functions.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt_config.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/exclusive_builds.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/default_pre.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/default_pre.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/release.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/default_post.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/default_post.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/x86_64.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/objective_c.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/shared.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/warn_on.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/qt.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/unix/opengl.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/unix/thread.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/moc.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/rez.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/mac/sdk.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/resources.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/uic.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/yacc.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/lex.prf:
/usr/local/Cellar/qt/4.8.7/mkspecs/features/include_source_dir.prf:
/usr/local/Cellar/qt/4.8.7/lib/QtOpenGL.framework/QtOpenGL.prl:
/usr/local/Cellar/qt/4.8.7/lib/QtGui.framework/QtGui.prl:
/usr/local/Cellar/qt/4.8.7/lib/QtCore.framework/QtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Cellar/qt/4.8.7/mkspecs/unsupported/macx-clang-libc++ CONFIG+=x86_64 -o Makefile opengl.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/opengl1.0.0 || $(MKDIR) .tmp/opengl1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/opengl1.0.0/ && $(COPY_FILE) --parents mainwindow.h glwidget.h process.h .tmp/opengl1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp glwidget.cpp process.cpp .tmp/opengl1.0.0/ && (cd `dirname .tmp/opengl1.0.0` && $(TAR) opengl1.0.0.tar opengl1.0.0 && $(COMPRESS) opengl1.0.0.tar) && $(MOVE) `dirname .tmp/opengl1.0.0`/opengl1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/opengl1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_mainwindow.cpp moc_glwidget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_glwidget.cpp
moc_mainwindow.cpp: glwidget.h \
		process.h \
		MyClass.h \
		mainwindow.h
	/usr/local/Cellar/qt/4.8.7/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ mainwindow.h -o moc_mainwindow.cpp

moc_glwidget.cpp: process.h \
		MyClass.h \
		glwidget.h
	/usr/local/Cellar/qt/4.8.7/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ glwidget.h -o moc_glwidget.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		glwidget.h \
		process.h \
		MyClass.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		glwidget.h \
		process.h \
		MyClass.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

glwidget.o: glwidget.cpp glwidget.h \
		process.h \
		MyClass.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glwidget.o glwidget.cpp

process.o: process.cpp process.h \
		MyClass.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o process.o process.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_glwidget.o: moc_glwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glwidget.o moc_glwidget.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

