#bin_PROGRAMS = fakturino

AM_CPPFLAGS = -I $(top_srcdir)/src/isz -I $(top_srcdir)/src
LDADD = $(top_builddir)/src/libisz.a
#LDADD = $(top_builddir)/src/libpri.a $(top_builddir)/src/isz/libisz.a

noinst_PROGRAMS =\
main_text\
main_fail\
main_list\
main_text_canvas\
main_grid

main_fail_SOURCES =\
main_fail.c

main_text_SOURCES =\
main_text.c

main_list_SOURCES =\
main_list.c

main_grid_SOURCES =\
main_grid.c

main_text_canvas_SOURCES=\
main_text_canvas.c
