CC = gcc
prefix = /usr
bindir = $(prefix)/bin
INSTALL = /usr/bin/install -c
STRIPFLAG = -s

all: zipsplit
zipsplit: zipsplit.c
clean:
	-rm -f zipsplit
install: zipsplit
	-$(INSTALL) $(STRIPFLAG) "zipsplit" "$(DESTDIR)$(bindir)/zipsplit";$(INSTALL) "ziprecv" "$(DESTDIR)$(bindir)/ziprecv" 
