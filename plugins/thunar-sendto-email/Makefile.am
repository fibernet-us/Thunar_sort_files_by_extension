# $Id: Makefile.am 24675 2007-01-20 20:37:43Z benny $

INCLUDES =								\
	-I$(top_builddir)						\
	-I$(top_builddir)/plugins					\
	-I$(top_srcdir)							\
	-I$(top_srcdir)/plugins						\
	-DG_LOG_DOMAIN=\"thunar-sendto-email\"				\
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\"				\
	$(PLATFORM_CPPFLAGS)

libexec_PROGRAMS =							\
	thunar-sendto-email

thunar_sendto_email_SOURCES =						\
	main.c

thunar_sendto_email_CFLAGS =						\
	$(EXO_CFLAGS)							\
	$(PLATFORM_CFLAGS)

thunar_sendto_email_DEPENDENCIES =					\
	$(top_builddir)/thunar-vfs/libthunar-vfs-$(THUNAR_VERSION_API).la

thunar_sendto_email_LDADD =						\
	$(top_builddir)/thunar-vfs/libthunar-vfs-$(THUNAR_VERSION_API).la \
	$(EXO_LIBS)							\
	$(PLATFORM_LDFLAGS)

desktopdir = $(datadir)/Thunar/sendto
desktop_in_in_files = thunar-sendto-email.desktop.in.in
desktop_in_files = $(desktop_in_in_files:.desktop.in.in=.desktop.in)
%.desktop.in: %.desktop.in.in
	sed -e "s,\@libexecdir\@,$(libexecdir),g" < $< > $@
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST =								\
	$(desktop_in_in_files)						\
	README

DISTCLEANFILES =							\
	$(desktop_in_files)						\
	$(desktop_DATA)

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
