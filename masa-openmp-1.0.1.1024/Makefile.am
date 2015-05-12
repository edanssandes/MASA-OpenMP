AUTOMAKE_OPTIONS = subdir-objects
SUBDIRS = $(LIBMASA_PATH)

bin_PROGRAMS = masa-openmp
masa_openmp_CXXFLAGS = -malign-double -fno-strict-aliasing
masa_openmp_LDADD  = $(LIBMASA_PATH)/libmasa.a -lpthread -lgomp
masa_openmp_SOURCES = \
./src/main.cpp \
./src/OpenMPAligner.cpp \
./src/OpenMPAlignerParameters.cpp 
dist_doc_DATA = README

noinst_HEADERS = \
./src/OpenMPAligner.hpp \
./src/OpenMPAlignerParameters.hpp 

dist-clone-link:
	@if test -L $(LIBMASA_PATH); then \
		mv $(LIBMASA_PATH) $(LIBMASA_PATH).link && \
		cp -r -L $(LIBMASA_PATH).link $(LIBMASA_PATH); \
	fi
 
dist-unclone-link:
	@if test -L $(LIBMASA_PATH).link; then \
		rm -rf $(LIBMASA_PATH) && \
		mv $(LIBMASA_PATH).link $(LIBMASA_PATH); \
	fi
 
dist-link: dist-clone-link dist dist-unclone-link