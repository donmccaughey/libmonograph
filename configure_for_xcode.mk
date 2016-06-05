# Makefile to configure libmonograph source for Xcode project
#
# Xcode defines PROJECT_DIR and PROJECT_DERIVED_FILE_DIR


.PHONY : all
all : $(PROJECT_DERIVED_FILE_DIR)/src/monograph/config.h


.PHONY : clean
clean :
	-rm -rf $(PROJECT_DERIVED_FILE_DIR)


$(PROJECT_DERIVED_FILE_DIR)/src/monograph/config.h :	\
		$(PROJECT_DIR)/configure \
		$(PROJECT_DIR)/src/monograph/config.h.in
	mkdir -p $(PROJECT_DERIVED_FILE_DIR)
	cd $(PROJECT_DERIVED_FILE_DIR) && $(PROJECT_DIR)/configure


$(PROJECT_DIR)/configure : $(PROJECT_DIR)/configure.ac
	autoreconf -i
