## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = election

election_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
 	condidat.c condidat.h utilisateur.h \
	liste.c liste.h \
	bureaudevote.c bureaudevote.h\
	election.c election.h \
	utilisateur.c utilisateur.h \
	fonction.c fonction.h \
	login.c login.h
	
	 

election_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

