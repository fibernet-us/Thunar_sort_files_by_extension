# $Id: Makefile.am 22971 2006-08-31 23:14:10Z benny $

SUBDIRS =								\
	design								\
	manual								\
	papers								\
	reference

docdir = $(datadir)/doc/Thunar
doc_DATA =								\
	README.gtkrc							\
	README.thunarrc							\
	README.volumes							\
	ThumbnailersCacheFormat.txt

man_MANS =								\
	Thunar.1

if MAINTAINER_MODE
%.1: %.xml
	xsltproc -nonet http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $<
endif

EXTRA_DIST =								\
	$(doc_DATA)							\
	$(man_MANS)							\
	Thunar.xml

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
