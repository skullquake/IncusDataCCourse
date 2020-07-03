/*!@file duk/caca.c
 * @brief Various libcaca native functions to expose to Duktape
 */
#ifdef DUK_USE_NCURSES
#include"duktape/ncurses.h"
#include<ncurses.h>
//#include<zlib.h>
//extern NCURSES_EXPORT(int) raw (void);
static duk_ret_t native_raw(duk_context*ctx){
	duk_push_int(ctx,raw());
	return 1;
}
//extern NCURSES_EXPORT(int) noraw (void);
static duk_ret_t native_noraw(duk_context*ctx){
	duk_push_int(ctx,noraw());
	return 1;
}

static duk_ret_t native_getch(duk_context*ctx){
	duk_push_int(ctx,getch());
	return 1;
}
//--------------------------------------------------------------------------------
//keypad(3)
//--------------------------------------------------------------------------------
//extern NCURSES_EXPORT(int) cbreak (void);
static duk_ret_t native_cbreak(duk_context*ctx){
	duk_push_int(ctx,cbreak());
	return 1;
}
//extern NCURSES_EXPORT(int) nocbreak (void);
static duk_ret_t native_nocbreak(duk_context*ctx){
	duk_push_int(ctx,nocbreak());
	return 1;
}
//extern NCURSES_EXPORT(int) keypad (WINDOW *,bool);
static duk_ret_t native_keypad(duk_context*ctx){
	duk_push_int(ctx,keypad(duk_get_pointer(ctx,0),duk_get_boolean(ctx,1)));
	return 1;
}
//extern NCURSES_EXPORT(int) noecho (void);
static duk_ret_t native_noecho(duk_context*ctx){
	duk_push_int(ctx,noecho());
	return 1;
}
//extern NCURSES_EXPORT(int) echo (void);
static duk_ret_t native_echo(duk_context*ctx){
	duk_push_int(ctx,echo());
	return 1;
}
//extern NCURSES_EXPORT(int) curs_set (int);
static duk_ret_t native_curs_set(duk_context*ctx){
	duk_push_int(ctx,curs_set(duk_get_int(ctx,0)));
	return 1;
}
//extern NCURSES_EXPORT(int) halfdelay (int);
static duk_ret_t native_halfdelay(duk_context*ctx){
	duk_push_int(ctx,halfdelay(duk_get_int(ctx,0)));
	return 1;
}
//extern NCURSES_EXPORT(int) intrflush (WINDOW *,bool);
static duk_ret_t native_intrflush(duk_context*ctx){
	duk_push_int(ctx,intrflush((WINDOW*)duk_get_pointer(ctx,0),duk_get_boolean(ctx,1)));
	return 1;
}
//extern NCURSES_EXPORT(int) meta (WINDOW *,bool);
static duk_ret_t native_meta(duk_context*ctx){
	duk_push_int(ctx,meta((WINDOW*)duk_get_pointer(ctx,0),duk_get_boolean(ctx,1)));
	return 1;
}
//extern NCURSES_EXPORT(int) nodelay (WINDOW *,bool);
static duk_ret_t native_nodelay(duk_context*ctx){
	duk_push_int(ctx,nodelay((WINDOW*)duk_get_pointer(ctx,0),duk_get_boolean(ctx,1)));
	return 1;
}
//extern NCURSES_EXPORT(void) noqiflush (void);
static duk_ret_t native_noqiflush(duk_context*ctx){
	noqiflush();
	return 1;
}
//extern NCURSES_EXPORT(void) qiflush (void);
static duk_ret_t native_qiflush(duk_context*ctx){
	qiflush();
	return 0;
}
//extern NCURSES_EXPORT(int) notimeout (WINDOW *,bool);
static duk_ret_t native_notimeout (duk_context*ctx){
	duk_push_int((WINDOW*)duk_get_pointer(ctx,0),duk_get_boolean(ctx,1));
	return 1;
}
//extern NCURSES_EXPORT(void) timeout (int);
static duk_ret_t native_timeout(duk_context*ctx){
	duk_get_int(ctx,0);
	return 0;
}
//extern NCURSES_EXPORT(void) wtimeout (WINDOW *,int);
static duk_ret_t native_wtimeout(duk_context*ctx){
	wtimeout((WINDOW*)duk_get_pointer(ctx,0),duk_get_int(ctx,1));
	return 0;
}
//extern NCURSES_EXPORT(int) typeahead (int);
static duk_ret_t native_typeahead(duk_context*ctx){
	duk_push_int(ctx,typeahead(duk_get_int(ctx,0)));
	return 1;
}
//--------------------------------------------------------------------------------
//initscr(3)
//--------------------------------------------------------------------------------
//extern NCURSES_EXPORT(WINDOW *) initscr (void);
static duk_ret_t native_initscr(duk_context*ctx){
	initscr();
	return 0;
}
//extern NCURSES_EXPORT(int) endwin (void);
static duk_ret_t native_endwin(duk_context*ctx){
	endwin();
	return 0;
}
//extern NCURSES_EXPORT(bool) isendwin (void);
static duk_ret_t native_isendwin(duk_context*ctx){
	duk_push_boolean(ctx,endwin());
	return 1;
}
//extern NCURSES_EXPORT(SCREEN *) newterm (const char *,FILE *,FILE *);
static duk_ret_t native_newterm(duk_context*ctx){
	duk_push_pointer(ctx,newterm(
		duk_get_string(ctx,0),
		(FILE*)duk_get_pointer(ctx,1),
		(FILE*)duk_get_pointer(ctx,2)
	));
	return 1;
}
//extern NCURSES_EXPORT(SCREEN *) set_term (SCREEN *);
static duk_ret_t native_set_term(duk_context*ctx){
	duk_push_pointer(ctx,set_term((SCREEN*)duk_get_pointer(ctx,0)));
	return 1;
}
//extern NCURSES_EXPORT(void) delscreen (SCREEN *);
static duk_ret_t native_delscreen(duk_context*ctx){
	delscreen((SCREEN*)duk_get_pointer(ctx,0));
	return 0;
}
//--------------------------------------------------------------------------------
//curs_refresh(3)
//--------------------------------------------------------------------------------
//extern NCURSES_EXPORT(int) refresh (void);
static duk_ret_t native_refresh(duk_context*ctx){
	duk_push_int(ctx,refresh());
	return 1;
}
//extern NCURSES_EXPORT(int) wrefresh (WINDOW *);
static duk_ret_t native_wrefresh(duk_context*ctx){
	duk_push_int(ctx,wrefresh((WINDOW*)duk_get_pointer(ctx,0)));
	return 1;
}
//extern NCURSES_EXPORT(int) wnoutrefresh (WINDOW *);
static duk_ret_t native_wnoutrefresh(duk_context*ctx){
	duk_push_int(ctx,wnoutrefresh((WINDOW*)duk_get_pointer(ctx,0)));
	return 1;
}
//extern NCURSES_EXPORT(int) doupdate (void);
static duk_ret_t native_doupdate(duk_context*ctx){
	duk_push_int(ctx,doupdate());
	return 1;
}
//extern NCURSES_EXPORT(int) redrawwin (WINDOW *);
static duk_ret_t native_redrawwin(duk_context*ctx){
	duk_push_int(ctx,redrawwin((WINDOW*)duk_get_pointer(ctx,0)));
	return 1;
}
//extern NCURSES_EXPORT(int) wredrawln (WINDOW *,int,int);
static duk_ret_t native_wredrawln(duk_context*ctx){
	duk_push_int(ctx,wredrawln((WINDOW*)duk_get_pointer(ctx,0),duk_get_int(ctx,1),duk_get_int(ctx,2)));
	return 1;
}
//--------------------------------------------------------------------------------
//printw(3)
//--------------------------------------------------------------------------------
//extern NCURSES_EXPORT(int) printw (const char *,...)GCC_PRINTFLIKE(1,2);
static duk_ret_t native_printw(duk_context*ctx){
	duk_push_int(ctx,printw(duk_get_string(ctx,0)));
	return 1;
}
//extern NCURSES_EXPORT(int) wprintw (WINDOW *, const char *,...)GCC_PRINTFLIKE(2,3);
static duk_ret_t native_wprintw(duk_context*ctx){
	duk_push_int(ctx,wprintw(duk_get_pointer(ctx,0),duk_get_string(ctx,1)));
	return 1;
}
//extern NCURSES_EXPORT(int) mvprintw (int,int, const char *,...)GCC_PRINTFLIKE(3,4);
static duk_ret_t native_mvprintw (duk_context*ctx){
	duk_push_int(ctx,mvprintw(duk_get_int(ctx,0),duk_get_int(ctx,1),duk_get_string(ctx,2)));
	return 1;
}
//extern NCURSES_EXPORT(int) mvwprintw (WINDOW*,int,int, const char *,...)GCC_PRINTFLIKE(4,5);
static duk_ret_t native_mvwprintw(duk_context*ctx){
	duk_push_int(ctx,mvwprintw((WINDOW*)duk_get_pointer(ctx,0),duk_get_int(ctx,1),duk_get_int(ctx,2),duk_get_string(ctx,3)));
	return 1;
}
#if 0 //va_list???
//extern NCURSES_EXPORT(int) vwprintw (WINDOW *, const char *,va_list) GCC_DEPRECATED(use vw_printw);
static duk_ret_t native_vwprintw(duk_context*ctx){
	duk_push_int(ctx,vwprintw((WINDOW*)duk_get_pointer(ctx,0),duk_get_string(ctx,1),/* valist?? */))
	return 1;
}
#endif
#if 0 //va_list???
/* define vw_printw		vwprintw */
static duk_ret_t native_vw_printw(duk_context*ctx){
	duk_push_int(ctx,vw_printw((WINDOW*)duk_get_pointer(ctx,0),duk_get_string(ctx,1),/* valist?? */))
	return 1;
}
#endif
/*! Register native function on context
 *  \return `duk_ret_t` return type
 */
void duk_register_ncurses(duk_context*ctx){
#if 0
	duk_push_int(ctx,SQLITE_WIN32_TEMP_DIRECTORY_TYPE);
	duk_put_global_string(ctx,"SQLITE_WIN32_TEMP_DIRECTORY_TYPE");
	duk_push_c_function(ctx,native_sqlite3_bind_zeroblob64,3);
	duk_put_global_string(ctx,"bind_zeroblob64");
#endif
	//constants
	duk_push_int(ctx,A_BOLD);
	duk_put_global_string(ctx,"A_BOLD");
	//external variables
	duk_push_pointer(ctx,stdscr);
	duk_put_global_string(ctx,stdscr);
	//functions
	duk_push_c_function(ctx,native_initscr,0);
	duk_put_global_string(ctx,"initscr");
	duk_push_c_function(ctx,native_printw,1);
	duk_put_global_string(ctx,"printw");
	duk_push_c_function(ctx,native_wprintw,2);
	duk_put_global_string(ctx,"wprintw");
	duk_push_c_function(ctx,native_endwin,0);
	duk_put_global_string(ctx,"endwin");
	duk_push_c_function(ctx,native_refresh,0);
	duk_put_global_string(ctx,"refresh");
	duk_push_c_function(ctx,native_getch,0);
	duk_put_global_string(ctx,"getch");
	duk_push_c_function(ctx,native_echo,0);
	duk_put_global_string(ctx,"echo");
	duk_push_c_function(ctx,native_noecho,0);
	duk_put_global_string(ctx,"noecho");
	duk_push_c_function(ctx,native_raw,0);
	duk_put_global_string(ctx,"raw");
	duk_push_c_function(ctx,native_noraw,0);
	duk_put_global_string(ctx,"noraw");
	duk_push_c_function(ctx,native_mvprintw,3);
	duk_put_global_string(ctx,"mvprintw");
	duk_push_c_function(ctx,native_curs_set,1);
	duk_put_global_string(ctx,"curs_set");
	duk_push_c_function(ctx,native_keypad,2);
	duk_put_global_string(ctx,"keypad");
	duk_push_c_function(ctx,native_cbreak,0);
	duk_put_global_string(ctx,"cbreak");
	duk_push_c_function(ctx,native_nocbreak,0);
	duk_put_global_string(ctx,"nocbreak");
	duk_push_c_function(ctx,native_halfdelay,1);
	duk_put_global_string(ctx,"halfdelay");
	duk_push_c_function(ctx,native_intrflush,2);
	duk_put_global_string(ctx,"intrflush");
	duk_push_c_function(ctx,native_meta,2);
	duk_put_global_string(ctx,"meta");
	duk_push_c_function(ctx,native_nodelay,2);
	duk_put_global_string(ctx,"nodelay");
	duk_push_c_function(ctx,native_qiflush,0);
	duk_put_global_string(ctx,"qiflush");
	duk_push_c_function(ctx,native_noqiflush,0);
	duk_put_global_string(ctx,"noqiflush");
	duk_push_c_function(ctx,native_notimeout ,1);
	duk_put_global_string(ctx,"notimeout");
	duk_push_c_function(ctx,native_timeout,0);
	duk_put_global_string(ctx,"timeout");
	duk_push_c_function(ctx,native_wtimeout,2);
	duk_put_global_string(ctx,"wtimeout");
	duk_push_c_function(ctx,native_typeahead,1);
	duk_put_global_string(ctx,"typeahead");
	duk_push_c_function(ctx,native_isendwin,0);
	duk_put_global_string(ctx,"isendwin");
	duk_push_c_function(ctx,native_newterm,3);
	duk_put_global_string(ctx,"newterm");
	duk_push_c_function(ctx,native_set_term,1);
	duk_put_global_string(ctx,"set_term");
	duk_push_c_function(ctx,native_delscreen,1);
	duk_put_global_string(ctx,"delscreen");


	duk_push_c_function(ctx,native_wrefresh,1);
	duk_put_global_string(ctx,"wrefresh");
	duk_push_c_function(ctx,native_wnoutrefresh,1);
	duk_put_global_string(ctx,"wnoutrefresh");
	duk_push_c_function(ctx,native_doupdate,0);
	duk_put_global_string(ctx,"doupdate");
	duk_push_c_function(ctx,native_redrawwin,1);
	duk_put_global_string(ctx,"redrawwin");
	duk_push_c_function(ctx,native_wredrawln,3);
	duk_put_global_string(ctx,"wredrawln");
	duk_push_c_function(ctx,native_mvwprintw,4);
	duk_put_global_string(ctx,"mvwprintw");
#if 0 //va_list???
	duk_push_c_function(ctx,native_vwprintw,3);
	duk_put_global_string(ctx,"vwprintw");
	duk_push_c_function(ctx,native_vw_printw,3);
	duk_put_global_string(ctx,"vw_printw");
#endif
}
#endif



#if 0 // moving to registration
//NCURSES_VERSION_MAJOR 0
//NCURSES_VERSION_MINOR 0
//NCURSES_VERSION_PATCH 0
//NCURSES_VERSION "6.1"
//NCURSES_MOUSE_VERSION 2
//NCURSES_ENABLE_STDBOOL_H 1
////NCURSES_ATTR_T int
////NCURSES_COLOR_T short
////NCURSES_PAIRS_T short
//NCURSES_OPAQUE       0
//NCURSES_OPAQUE_FORM  0
//NCURSES_OPAQUE_MENU  0
//NCURSES_OPAQUE_PANEL 0
//NCURSES_WATTR_MACROS 1
//NCURSES_REENTRANT 0
//NCURSES_INTEROP_FUNCS 1
////NCURSES_SIZE_T short
//NCURSES_TPARM_VARARGS 1
////NCURSES_TPARM_ARG intptr_t
//NCURSES_WCWIDTH_GRAPHICS 1
////NCURSES_CH_T cchar_t
//NCURSES_WIDECHAR 1
////NCURSES_BOOL bool
//WA_ATTRIBUTES	A_ATTRIBUTES
//WA_NORMAL	A_NORMAL
//WA_STANDOUT	A_STANDOUT
//WA_UNDERLINE	A_UNDERLINE
//WA_REVERSE	A_REVERSE
//WA_BLINK	A_BLINK
//WA_DIM		A_DIM
//WA_BOLD		A_BOLD
//WA_ALTCHARSET	A_ALTCHARSET
//WA_INVIS	A_INVIS
//WA_PROTECT	A_PROTECT
//WA_HORIZONTAL	A_HORIZONTAL
//WA_LEFT		A_LEFT
//WA_LOW		A_LOW
//WA_RIGHT	A_RIGHT
//WA_TOP		A_TOP
//WA_VERTICAL	A_VERTICAL
//WA_ITALIC	A_ITALIC
//COLOR_BLACK	0
//COLOR_RED	1
//COLOR_GREEN	2
//COLOR_YELLOW	3
//COLOR_BLUE	4
//COLOR_MAGENTA	5
//COLOR_CYAN	6
//COLOR_WHITE	7
//
//ACS_ULCORNER	NCURSES_ACS('l')
//ACS_LLCORNER	NCURSES_ACS('m')
//ACS_URCORNER	NCURSES_ACS('k')
//ACS_LRCORNER	NCURSES_ACS('j')
//ACS_LTEE	NCURSES_ACS('t')
//ACS_RTEE	NCURSES_ACS('u')
//ACS_BTEE	NCURSES_ACS('v')
//ACS_TTEE	NCURSES_ACS('w')
//ACS_HLINE	NCURSES_ACS('q')
//ACS_VLINE	NCURSES_ACS('x')
//ACS_PLUS	NCURSES_ACS('n')
//ACS_S1		NCURSES_ACS('o')
//ACS_S9		NCURSES_ACS('s')
//ACS_DIAMOND	NCURSES_ACS('`')
//ACS_CKBOARD	NCURSES_ACS('a')
//ACS_DEGREE	NCURSES_ACS('f')
//ACS_PLMINUS	NCURSES_ACS('g')
//ACS_BULLET	NCURSES_ACS('~')
//ACS_LARROW	NCURSES_ACS(',')
//ACS_RARROW	NCURSES_ACS('+')
//ACS_DARROW	NCURSES_ACS('.')
//ACS_UARROW	NCURSES_ACS('-')
//ACS_BOARD	NCURSES_ACS('h')
//ACS_LANTERN	NCURSES_ACS('i')
//ACS_BLOCK	NCURSES_ACS('0')
//ACS_S3		NCURSES_ACS('p')
//ACS_S7		NCURSES_ACS('r')
//ACS_LEQUAL	NCURSES_ACS('y')
//ACS_GEQUAL	NCURSES_ACS('z')
//ACS_PI		NCURSES_ACS('{')
//ACS_NEQUAL	NCURSES_ACS('|')
//ACS_STERLING	NCURSES_ACS('}')
//ACS_BSSB	ACS_ULCORNER
//ACS_SSBB	ACS_LLCORNER
//ACS_BBSS	ACS_URCORNER
//ACS_SBBS	ACS_LRCORNER
//ACS_SBSS	ACS_RTEE
//ACS_SSSB	ACS_LTEE
//ACS_SSBS	ACS_BTEE
//ACS_BSSS	ACS_TTEE
//ACS_BSBS	ACS_HLINE
//ACS_SBSB	ACS_VLINE
//ACS_SSSS	ACS_PLUS
//ERR     (-1)
//OK      (0)
//_SUBWIN         0x01
//_ENDLINE        0x02
//_FULLWIN        0x04
//_SCROLLWIN      0x08
//_ISPAD	        0x10
//_HASMOVED       0x20
//_WRAPPED        0x40
//_NOCHANGE       -1
//_NEWINDEX	-1
//CCHARW_MAX	5
//_NC_EVENT_TIMEOUT_MSEC	1
//_NC_EVENT_FILE		2
//_NC_EVENT_FILE_READABLE	2
//extern NCURSES_EXPORT(int) addch (const chtype);
//extern NCURSES_EXPORT(int) addchnstr (const chtype *, int);
//extern NCURSES_EXPORT(int) addchstr (const chtype *);
//extern NCURSES_EXPORT(int) addnstr (const char *, int);
//extern NCURSES_EXPORT(int) addstr (const char *);
//extern NCURSES_EXPORT(int) attroff (NCURSES_ATTR_T);
//extern NCURSES_EXPORT(int) attron (NCURSES_ATTR_T);
//extern NCURSES_EXPORT(int) attrset (NCURSES_ATTR_T);
//extern NCURSES_EXPORT(int) attr_get (attr_t *, NCURSES_PAIRS_T *, void *);
//extern NCURSES_EXPORT(int) attr_off (attr_t, void *);
//extern NCURSES_EXPORT(int) attr_on (attr_t, void *);
//extern NCURSES_EXPORT(int) attr_set (attr_t, NCURSES_PAIRS_T, void *);
//extern NCURSES_EXPORT(int) baudrate (void);
//extern NCURSES_EXPORT(int) beep  (void);
//extern NCURSES_EXPORT(int) bkgd (chtype);
//extern NCURSES_EXPORT(void) bkgdset (chtype);
//extern NCURSES_EXPORT(int) border (chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);
//extern NCURSES_EXPORT(int) box (WINDOW *, chtype, chtype);
//extern NCURSES_EXPORT(bool) can_change_color (void);
//extern NCURSES_EXPORT(int) chgat (int, attr_t, NCURSES_PAIRS_T, const void *);
//extern NCURSES_EXPORT(int) clear (void);
//extern NCURSES_EXPORT(int) clearok (WINDOW *,bool);
//extern NCURSES_EXPORT(int) clrtobot (void);
//extern NCURSES_EXPORT(int) clrtoeol (void);
//extern NCURSES_EXPORT(int) color_content (NCURSES_COLOR_T,NCURSES_COLOR_T*,NCURSES_COLOR_T*,NCURSES_COLOR_T*);
//extern NCURSES_EXPORT(int) color_set (NCURSES_PAIRS_T,void*);
//extern NCURSES_EXPORT(int) COLOR_PAIR (int);
//extern NCURSES_EXPORT(int) copywin (const WINDOW*,WINDOW*,int,int,int,int,int,int,int);
//extern NCURSES_EXPORT(int) def_prog_mode (void);
//extern NCURSES_EXPORT(int) def_shell_mode (void);
//extern NCURSES_EXPORT(int) delay_output (int);
//extern NCURSES_EXPORT(int) delch (void);
//extern NCURSES_EXPORT(int) delwin (WINDOW *);
//extern NCURSES_EXPORT(int) deleteln (void);
//extern NCURSES_EXPORT(WINDOW *) derwin (WINDOW *,int,int,int,int);
//extern NCURSES_EXPORT(WINDOW *) dupwin (WINDOW *);
//extern NCURSES_EXPORT(int) echochar (const chtype);
//extern NCURSES_EXPORT(int) erase (void);
//extern NCURSES_EXPORT(char) erasechar (void);
//extern NCURSES_EXPORT(void) filter (void);
//extern NCURSES_EXPORT(int) flash (void);
//extern NCURSES_EXPORT(int) flushinp (void);
//extern NCURSES_EXPORT(chtype) getbkgd (WINDOW *);
//extern NCURSES_EXPORT(int) getch (void);
//extern NCURSES_EXPORT(int) getnstr (char *, int);
//extern NCURSES_EXPORT(int) getstr (char *);
//extern NCURSES_EXPORT(WINDOW *) getwin (FILE *);
//extern NCURSES_EXPORT(int) halfdelay (int);
//extern NCURSES_EXPORT(bool) has_colors (void);
//extern NCURSES_EXPORT(bool) has_ic (void);
//extern NCURSES_EXPORT(bool) has_il (void);
//extern NCURSES_EXPORT(int) hline (chtype, int);
//extern NCURSES_EXPORT(void) idcok (WINDOW *, bool);
//extern NCURSES_EXPORT(int) idlok (WINDOW *, bool);
//extern NCURSES_EXPORT(void) immedok (WINDOW *, bool);
//extern NCURSES_EXPORT(chtype) inch (void);
//extern NCURSES_EXPORT(int) inchnstr (chtype *, int);
//extern NCURSES_EXPORT(int) inchstr (chtype *);
//extern NCURSES_EXPORT(int) init_color (NCURSES_COLOR_T,NCURSES_COLOR_T,NCURSES_COLOR_T,NCURSES_COLOR_T);
//extern NCURSES_EXPORT(int) init_pair (NCURSES_PAIRS_T,NCURSES_COLOR_T,NCURSES_COLOR_T);
//extern NCURSES_EXPORT(int) innstr (char *, int);
//extern NCURSES_EXPORT(int) insch (chtype);
//extern NCURSES_EXPORT(int) insdelln (int);
//extern NCURSES_EXPORT(int) insertln (void);
//extern NCURSES_EXPORT(int) insnstr (const char *, int);
//extern NCURSES_EXPORT(int) insstr (const char *);
//extern NCURSES_EXPORT(int) instr (char *);
//extern NCURSES_EXPORT(int) intrflush (WINDOW *,bool);
//extern NCURSES_EXPORT(bool) is_linetouched (WINDOW *,int);
//extern NCURSES_EXPORT(bool) is_wintouched (WINDOW *);
//extern NCURSES_EXPORT(NCURSES_CONST char *) keyname (int);
//extern NCURSES_EXPORT(char) killchar (void);
//extern NCURSES_EXPORT(int) leaveok (WINDOW *,bool);
//extern NCURSES_EXPORT(char *) longname (void);
//extern NCURSES_EXPORT(int) move (int, int);
//extern NCURSES_EXPORT(int) mvaddch (int, int, const chtype);
//extern NCURSES_EXPORT(int) mvaddchnstr (int, int, const chtype *, int);
//extern NCURSES_EXPORT(int) mvaddchstr (int, int, const chtype *);
//extern NCURSES_EXPORT(int) mvaddnstr (int, int, const char *, int);
//extern NCURSES_EXPORT(int) mvaddstr (int, int, const char *);
//extern NCURSES_EXPORT(int) mvchgat (int, int, int, attr_t, NCURSES_PAIRS_T, const void *);
//extern NCURSES_EXPORT(int) mvcur (int,int,int,int);
//extern NCURSES_EXPORT(int) mvdelch (int, int);
//extern NCURSES_EXPORT(int) mvderwin (WINDOW *, int, int);
//extern NCURSES_EXPORT(int) mvgetch (int, int);
//extern NCURSES_EXPORT(int) mvgetnstr (int, int, char *, int);
//extern NCURSES_EXPORT(int) mvgetstr (int, int, char *);
//extern NCURSES_EXPORT(int) mvhline (int, int, chtype, int);
//extern NCURSES_EXPORT(chtype) mvinch (int, int);
//extern NCURSES_EXPORT(int) mvinchnstr (int, int, chtype *, int);
//extern NCURSES_EXPORT(int) mvinchstr (int, int, chtype *);
//extern NCURSES_EXPORT(int) mvinnstr (int, int, char *, int);
//extern NCURSES_EXPORT(int) mvinsch (int, int, chtype);
//extern NCURSES_EXPORT(int) mvinsnstr (int, int, const char *, int);
//extern NCURSES_EXPORT(int) mvinsstr (int, int, const char *);
//extern NCURSES_EXPORT(int) mvinstr (int, int, char *);
//extern NCURSES_EXPORT(int) mvprintw (int,int, const char *,...)GCC_PRINTFLIKE(3,4);
//extern NCURSES_EXPORT(int) mvscanw (int,int, const char *,...)GCC_SCANFLIKE(3,4);
//extern NCURSES_EXPORT(int) mvvline (int, int, chtype, int);
//extern NCURSES_EXPORT(int) mvwaddch (WINDOW *, int, int, const chtype);
//extern NCURSES_EXPORT(int) mvwaddchnstr (WINDOW *, int, int, const chtype *, int);
//extern NCURSES_EXPORT(int) mvwaddchstr (WINDOW *, int, int, const chtype *);
//extern NCURSES_EXPORT(int) mvwaddnstr (WINDOW *, int, int, const char *, int);
//extern NCURSES_EXPORT(int) mvwaddstr (WINDOW *, int, int, const char *);
//extern NCURSES_EXPORT(int) mvwchgat (WINDOW *, int, int, int, attr_t, NCURSES_PAIRS_T, const void *);
//extern NCURSES_EXPORT(int) mvwdelch (WINDOW *, int, int);
//extern NCURSES_EXPORT(int) mvwgetch (WINDOW *, int, int);
//extern NCURSES_EXPORT(int) mvwgetnstr (WINDOW *, int, int, char *, int);
//extern NCURSES_EXPORT(int) mvwgetstr (WINDOW *, int, int, char *);
//extern NCURSES_EXPORT(int) mvwhline (WINDOW *, int, int, chtype, int);
//extern NCURSES_EXPORT(int) mvwin (WINDOW *,int,int);
//extern NCURSES_EXPORT(chtype) mvwinch (WINDOW *, int, int);
//extern NCURSES_EXPORT(int) mvwinchnstr (WINDOW *, int, int, chtype *, int);
//extern NCURSES_EXPORT(int) mvwinchstr (WINDOW *, int, int, chtype *);
//extern NCURSES_EXPORT(int) mvwinnstr (WINDOW *, int, int, char *, int);
//extern NCURSES_EXPORT(int) mvwinsch (WINDOW *, int, int, chtype);
//extern NCURSES_EXPORT(int) mvwinsnstr (WINDOW *, int, int, const char *, int);
//extern NCURSES_EXPORT(int) mvwinsstr (WINDOW *, int, int, const char *);
//extern NCURSES_EXPORT(int) mvwinstr (WINDOW *, int, int, char *);
//extern NCURSES_EXPORT(int) mvwscanw (WINDOW *,int,int, const char *,...)GCC_SCANFLIKE(4,5);
//extern NCURSES_EXPORT(int) mvwvline (WINDOW *,int, int, chtype, int);
//extern NCURSES_EXPORT(int) napms (int);
//extern NCURSES_EXPORT(WINDOW *) newpad (int,int);
//extern NCURSES_EXPORT(WINDOW *) newwin (int,int,int,int);
//extern NCURSES_EXPORT(int) nl (void);
//extern NCURSES_EXPORT(int) nonl (void);
//extern NCURSES_EXPORT(int) overlay (const WINDOW*,WINDOW *);
//extern NCURSES_EXPORT(int) overwrite (const WINDOW*,WINDOW *);
//extern NCURSES_EXPORT(int) pair_content (NCURSES_PAIRS_T,NCURSES_COLOR_T*,NCURSES_COLOR_T*);
//extern NCURSES_EXPORT(int) PAIR_NUMBER (int);
//extern NCURSES_EXPORT(int) pechochar (WINDOW *, const chtype);
//extern NCURSES_EXPORT(int) pnoutrefresh (WINDOW*,int,int,int,int,int,int);
//extern NCURSES_EXPORT(int) prefresh (WINDOW *,int,int,int,int,int,int);
//extern NCURSES_EXPORT(int) putwin (WINDOW *, FILE *);
//extern NCURSES_EXPORT(int) resetty (void);
//extern NCURSES_EXPORT(int) reset_prog_mode (void);
//extern NCURSES_EXPORT(int) reset_shell_mode (void);
//extern NCURSES_EXPORT(int) ripoffline (int, int (*)(WINDOW *, int));
//extern NCURSES_EXPORT(int) savetty (void);
//extern NCURSES_EXPORT(int) scanw (const char *,...)GCC_SCANFLIKE(1,2);
//extern NCURSES_EXPORT(int) scr_dump (const char *);
//extern NCURSES_EXPORT(int) scr_init (const char *);
//extern NCURSES_EXPORT(int) scrl (int);
//extern NCURSES_EXPORT(int) scroll (WINDOW *);
//extern NCURSES_EXPORT(int) scrollok (WINDOW *,bool);
//extern NCURSES_EXPORT(int) scr_restore (const char *);
//extern NCURSES_EXPORT(int) scr_set (const char *);
//extern NCURSES_EXPORT(int) setscrreg (int,int);
//extern NCURSES_EXPORT(int) slk_attroff (const chtype);
//extern NCURSES_EXPORT(int) slk_attr_off (const attr_t, void *);
//extern NCURSES_EXPORT(int) slk_attron (const chtype);
//extern NCURSES_EXPORT(int) slk_attr_on (attr_t,void*);
//extern NCURSES_EXPORT(int) slk_attrset (const chtype);
//extern NCURSES_EXPORT(attr_t) slk_attr (void);
//extern NCURSES_EXPORT(int) slk_attr_set (const attr_t,NCURSES_PAIRS_T,void*);
//extern NCURSES_EXPORT(int) slk_clear (void);
//extern NCURSES_EXPORT(int) slk_color (NCURSES_PAIRS_T);
//extern NCURSES_EXPORT(int) slk_init (int);
//extern NCURSES_EXPORT(char *) slk_label (int);
//extern NCURSES_EXPORT(int) slk_noutrefresh (void);
//extern NCURSES_EXPORT(int) slk_refresh (void);
//extern NCURSES_EXPORT(int) slk_restore (void);
//extern NCURSES_EXPORT(int) slk_set (int,const char *,int);
//extern NCURSES_EXPORT(int) slk_touch (void);
//extern NCURSES_EXPORT(int) standout (void);
//extern NCURSES_EXPORT(int) standend (void);
//extern NCURSES_EXPORT(int) start_color (void);
//extern NCURSES_EXPORT(WINDOW *) subpad (WINDOW *, int, int, int, int);
//extern NCURSES_EXPORT(WINDOW *) subwin (WINDOW *, int, int, int, int);
//extern NCURSES_EXPORT(int) syncok (WINDOW *, bool);
//extern NCURSES_EXPORT(chtype) termattrs (void);
//extern NCURSES_EXPORT(char *) termname (void);
//extern NCURSES_EXPORT(int) touchline (WINDOW *, int, int);
//extern NCURSES_EXPORT(int) touchwin (WINDOW *);
//extern NCURSES_EXPORT(int) ungetch (int);
//extern NCURSES_EXPORT(int) untouchwin (WINDOW *);
//extern NCURSES_EXPORT(void) use_env (bool);
//extern NCURSES_EXPORT(void) use_tioctl (bool);
//extern NCURSES_EXPORT(int) vidattr (chtype);
//extern NCURSES_EXPORT(int) vidputs (chtype, NCURSES_OUTC);
//extern NCURSES_EXPORT(int) vline (chtype, int);
//extern NCURSES_EXPORT(int) vw_printw (WINDOW *, const char *,va_list);
//extern NCURSES_EXPORT(int) vwscanw (WINDOW *, const char *,va_list) GCC_DEPRECATED(use vw_scanw);
//extern NCURSES_EXPORT(int) vw_scanw (WINDOW *, const char *,va_list);
//extern NCURSES_EXPORT(int) waddch (WINDOW *, const chtype);
//extern NCURSES_EXPORT(int) waddchnstr (WINDOW *,const chtype *,int);
//extern NCURSES_EXPORT(int) waddchstr (WINDOW *,const chtype *);
//extern NCURSES_EXPORT(int) waddnstr (WINDOW *,const char *,int);
//extern NCURSES_EXPORT(int) waddstr (WINDOW *,const char *);
//extern NCURSES_EXPORT(int) wattron (WINDOW *, int);
//extern NCURSES_EXPORT(int) wattroff (WINDOW *, int);
//extern NCURSES_EXPORT(int) wattrset (WINDOW *, int);
//extern NCURSES_EXPORT(int) wattr_get (WINDOW *, attr_t *, NCURSES_PAIRS_T *, void *);
//extern NCURSES_EXPORT(int) wattr_on (WINDOW *, attr_t, void *);
//extern NCURSES_EXPORT(int) wattr_off (WINDOW *, attr_t, void *);
//extern NCURSES_EXPORT(int) wattr_set (WINDOW *, attr_t, NCURSES_PAIRS_T, void *);
//extern NCURSES_EXPORT(int) wbkgd (WINDOW *, chtype);
//extern NCURSES_EXPORT(void) wbkgdset (WINDOW *,chtype);
//extern NCURSES_EXPORT(int) wborder (WINDOW *,chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);
//extern NCURSES_EXPORT(int) wchgat (WINDOW *, int, attr_t, NCURSES_PAIRS_T, const void *);
//extern NCURSES_EXPORT(int) wclear (WINDOW *);
//extern NCURSES_EXPORT(int) wclrtobot (WINDOW *);
//extern NCURSES_EXPORT(int) wclrtoeol (WINDOW *);
//extern NCURSES_EXPORT(int) wcolor_set (WINDOW*,NCURSES_PAIRS_T,void*);
//extern NCURSES_EXPORT(void) wcursyncup (WINDOW *);
//extern NCURSES_EXPORT(int) wdelch (WINDOW *);
//extern NCURSES_EXPORT(int) wdeleteln (WINDOW *);
//extern NCURSES_EXPORT(int) wechochar (WINDOW *, const chtype);
//extern NCURSES_EXPORT(int) werase (WINDOW *);
//extern NCURSES_EXPORT(int) wgetch (WINDOW *);
//extern NCURSES_EXPORT(int) wgetnstr (WINDOW *,char *,int);
//extern NCURSES_EXPORT(int) wgetstr (WINDOW *, char *);
//extern NCURSES_EXPORT(int) whline (WINDOW *, chtype, int);
//extern NCURSES_EXPORT(chtype) winch (WINDOW *);
//extern NCURSES_EXPORT(int) winchnstr (WINDOW *, chtype *, int);
//extern NCURSES_EXPORT(int) winchstr (WINDOW *, chtype *);
//extern NCURSES_EXPORT(int) winnstr (WINDOW *, char *, int);
//extern NCURSES_EXPORT(int) winsch (WINDOW *, chtype);
//extern NCURSES_EXPORT(int) winsdelln (WINDOW *,int);
//extern NCURSES_EXPORT(int) winsertln (WINDOW *);
//extern NCURSES_EXPORT(int) winsnstr (WINDOW *, const char *,int);
//extern NCURSES_EXPORT(int) winsstr (WINDOW *, const char *);
//extern NCURSES_EXPORT(int) winstr (WINDOW *, char *);
//extern NCURSES_EXPORT(int) wmove (WINDOW *,int,int);
//extern NCURSES_EXPORT(int) wscanw (WINDOW *, const char *,...)GCC_SCANFLIKE(2,3);
//extern NCURSES_EXPORT(int) wscrl (WINDOW *,int);
//extern NCURSES_EXPORT(int) wsetscrreg (WINDOW *,int,int);
//extern NCURSES_EXPORT(int) wstandout (WINDOW *);			/* generated */
//extern NCURSES_EXPORT(int) wstandend (WINDOW *);
//extern NCURSES_EXPORT(void) wsyncdown (WINDOW *);
//extern NCURSES_EXPORT(void) wsyncup (WINDOW *);
//extern NCURSES_EXPORT(int) wtouchln (WINDOW *,int,int,int);
//extern NCURSES_EXPORT(int) wvline (WINDOW *,chtype,int);
//extern NCURSES_EXPORT(int) tigetflag (const char *);
//extern NCURSES_EXPORT(int) tigetnum (const char *);
//extern NCURSES_EXPORT(char *) tigetstr (const char *);
//extern NCURSES_EXPORT(int) putp (const char *);
//extern NCURSES_EXPORT(char *) tparm (const char *, ...);
//extern NCURSES_EXPORT(char *) tparm (const char *, NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG,NCURSES_TPARM_ARG);
//extern NCURSES_EXPORT(char *) tparm_varargs (const char *, ...);
//extern NCURSES_EXPORT(char *) tiparm (const char *, ...);
//extern NCURSES_EXPORT(int) getattrs (const WINDOW *);
//extern NCURSES_EXPORT(int) getcurx (const WINDOW *);
//extern NCURSES_EXPORT(int) getcury (const WINDOW *);
//extern NCURSES_EXPORT(int) getbegx (const WINDOW *);
//extern NCURSES_EXPORT(int) getbegy (const WINDOW *);
//extern NCURSES_EXPORT(int) getmaxx (const WINDOW *);
//extern NCURSES_EXPORT(int) getmaxy (const WINDOW *);
//extern NCURSES_EXPORT(int) getparx (const WINDOW *);
//extern NCURSES_EXPORT(int) getpary (const WINDOW *);
//#define vid_attr(a,pair,opts) vidattr(a)
//extern NCURSES_EXPORT(bool) is_term_resized (int, int);
//extern NCURSES_EXPORT(char *) keybound (int, int);
//extern NCURSES_EXPORT(const char *) curses_version (void);
//extern NCURSES_EXPORT(int) alloc_pair (int, int);
//extern NCURSES_EXPORT(int) assume_default_colors (int, int);
//extern NCURSES_EXPORT(int) define_key (const char *, int);
//extern NCURSES_EXPORT(int) extended_color_content(int, int *, int *, int *);
//extern NCURSES_EXPORT(int) extended_pair_content(int, int *, int *);
//extern NCURSES_EXPORT(int) extended_slk_color(int);
//extern NCURSES_EXPORT(int) find_pair (int, int);
//extern NCURSES_EXPORT(int) free_pair (int);
//extern NCURSES_EXPORT(int) get_escdelay (void);
//extern NCURSES_EXPORT(int) init_extended_color(int, int, int, int);
//extern NCURSES_EXPORT(int) init_extended_pair(int, int, int);
//extern NCURSES_EXPORT(int) key_defined (const char *);
//extern NCURSES_EXPORT(int) keyok (int, bool);
//extern NCURSES_EXPORT(void) reset_color_pairs (void);
//extern NCURSES_EXPORT(int) resize_term (int, int);
//extern NCURSES_EXPORT(int) resizeterm (int, int);
//extern NCURSES_EXPORT(int) set_escdelay (int);
//extern NCURSES_EXPORT(int) set_tabsize (int);
//extern NCURSES_EXPORT(int) use_default_colors (void);
//extern NCURSES_EXPORT(int) use_extended_names (bool);
//extern NCURSES_EXPORT(int) use_legacy_coding (int);
//extern NCURSES_EXPORT(int) use_screen (SCREEN *, NCURSES_SCREEN_CB, void *);
//extern NCURSES_EXPORT(int) use_window (WINDOW *, NCURSES_WINDOW_CB, void *);
//extern NCURSES_EXPORT(int) wresize (WINDOW *, int, int);
//extern NCURSES_EXPORT(void) nofilter(void);
//extern NCURSES_EXPORT(WINDOW *) wgetparent (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_cleared (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_idcok (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_idlok (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_immedok (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_keypad (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_leaveok (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_nodelay (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_notimeout (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_pad (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_scrollok (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_subwin (const WINDOW *);
//extern NCURSES_EXPORT(bool) is_syncok (const WINDOW *);
//extern NCURSES_EXPORT(int) wgetdelay (const WINDOW *);
//extern NCURSES_EXPORT(int) wgetscrreg (const WINDOW *, int *, int *);
//#define curses_version() NCURSES_VERSION
//NCURSES_SP_FUNCS 20190511
//extern NCURSES_EXPORT(SCREEN *) new_prescr (void);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(baudrate) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(beep) (SCREEN*);
//extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(can_change_color) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(cbreak) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(curs_set) (SCREEN*, int);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(color_content) (SCREEN*, NCURSES_PAIRS_T, NCURSES_COLOR_T*, NCURSES_COLOR_T*, NCURSES_COLOR_T*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(def_prog_mode) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(def_shell_mode) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(delay_output) (SCREEN*, int);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(doupdate) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(echo) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(endwin) (SCREEN*);
//extern NCURSES_EXPORT(char) NCURSES_SP_NAME(erasechar) (SCREEN*);
//extern NCURSES_EXPORT(void) NCURSES_SP_NAME(filter) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(flash) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(flushinp) (SCREEN*);
//extern NCURSES_EXPORT(WINDOW *) NCURSES_SP_NAME(getwin) (SCREEN*, FILE *);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(halfdelay) (SCREEN*, int);
//extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(has_colors) (SCREEN*);
//extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(has_ic) (SCREEN*);
//extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(has_il) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_color) (SCREEN*, NCURSES_COLOR_T, NCURSES_COLOR_T, NCURSES_COLOR_T, NCURSES_COLOR_T);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_pair) (SCREEN*, NCURSES_PAIRS_T, NCURSES_COLOR_T, NCURSES_COLOR_T);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(intrflush) (SCREEN*, WINDOW*, bool);
//extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(isendwin) (SCREEN*);
//extern NCURSES_EXPORT(NCURSES_CONST char *) NCURSES_SP_NAME(keyname) (SCREEN*, int);
//extern NCURSES_EXPORT(char) NCURSES_SP_NAME(killchar) (SCREEN*);
//extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(longname) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(mvcur) (SCREEN*, int, int, int, int);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(napms) (SCREEN*, int);
//extern NCURSES_EXPORT(WINDOW *) NCURSES_SP_NAME(newpad) (SCREEN*, int, int);
//extern NCURSES_EXPORT(SCREEN *) NCURSES_SP_NAME(newterm) (SCREEN*, const char *, FILE *, FILE *);
//extern NCURSES_EXPORT(WINDOW *) NCURSES_SP_NAME(newwin) (SCREEN*, int, int, int, int);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(nl) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(nocbreak) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(noecho) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(nonl) (SCREEN*);
//extern NCURSES_EXPORT(void) NCURSES_SP_NAME(noqiflush) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(noraw) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(pair_content) (SCREEN*, NCURSES_PAIRS_T, NCURSES_COLOR_T*, NCURSES_COLOR_T*);
//extern NCURSES_EXPORT(void) NCURSES_SP_NAME(qiflush) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(raw) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(reset_prog_mode) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(reset_shell_mode) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(resetty) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(ripoffline) (SCREEN*, int, int (*)(WINDOW *, int));
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(savetty) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(scr_init) (SCREEN*, const char *);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(scr_restore) (SCREEN*, const char *);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(scr_set) (SCREEN*, const char *);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attroff) (SCREEN*, const chtype);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attron) (SCREEN*, const chtype);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attrset) (SCREEN*, const chtype);
//extern NCURSES_EXPORT(attr_t) NCURSES_SP_NAME(slk_attr) (SCREEN*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_attr_set) (SCREEN*, const attr_t, NCURSES_PAIRS_T, void*);
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_clear) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_color) (SCREEN*, NCURSES_PAIRS_T); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_init) (SCREEN*, int); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(slk_label) (SCREEN*, int); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_noutrefresh) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_refresh) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_restore) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_set) (SCREEN*, int, const char *, int); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(slk_touch) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(start_color) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(chtype) NCURSES_SP_NAME(termattrs) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(termname) (SCREEN*); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(typeahead) (SCREEN*, int); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(ungetch) (SCREEN*, int); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(void) NCURSES_SP_NAME(use_env) (SCREEN*, bool); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(void) NCURSES_SP_NAME(use_tioctl) (SCREEN*, bool); /* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vidattr) (SCREEN*, chtype);	/* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vidputs) (SCREEN*, chtype, NCURSES_SP_OUTC); /* implemented:SP_FUNC */
//#if 1
//extern NCURSES_EXPORT(char *) NCURSES_SP_NAME(keybound) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(alloc_pair) (SCREEN*, int, int); /* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(assume_default_colors) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(define_key) (SCREEN*, const char *, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(extended_color_content) (SCREEN*, int, int *, int *, int *);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(extended_pair_content) (SCREEN*, int, int *, int *);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(extended_slk_color) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(get_escdelay) (SCREEN*);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(find_pair) (SCREEN*, int, int); /* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(free_pair) (SCREEN*, int); /* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_extended_color) (SCREEN*, int, int, int, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(init_extended_pair) (SCREEN*, int, int, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(bool) NCURSES_SP_NAME(is_term_resized) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(key_defined) (SCREEN*, const char *);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(keyok) (SCREEN*, int, bool);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(void) NCURSES_SP_NAME(nofilter) (SCREEN*); /* implemented */	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(void) NCURSES_SP_NAME(reset_color_pairs) (SCREEN*); /* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(resize_term) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(resizeterm) (SCREEN*, int, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(set_escdelay) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(set_tabsize) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(use_default_colors) (SCREEN*);	/* implemented:EXT_SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(use_legacy_coding) (SCREEN*, int);	/* implemented:EXT_SP_FUNC */
//#endif
//#else
//#undef  NCURSES_SP_FUNCS
//#define NCURSES_SP_FUNCS 0
//#define NCURSES_SP_NAME(name) name
//#define NCURSES_SP_OUTC NCURSES_OUTC
//#endif
//
///* attributes */
//
//#define NCURSES_ATTR_SHIFT       8
//#define NCURSES_BITS(mask,shift) (NCURSES_CAST(chtype,(mask)) << ((shift) + NCURSES_ATTR_SHIFT))
//
//#define A_NORMAL	(1U - 1U)
//#define A_ATTRIBUTES	NCURSES_BITS(~(1U - 1U),0)
//#define A_CHARTEXT	(NCURSES_BITS(1U,0) - 1U)
//#define A_COLOR		NCURSES_BITS(((1U) << 8) - 1U,0)
//#define A_STANDOUT	NCURSES_BITS(1U,8)
//#define A_UNDERLINE	NCURSES_BITS(1U,9)
//#define A_REVERSE	NCURSES_BITS(1U,10)
//#define A_BLINK		NCURSES_BITS(1U,11)
//#define A_DIM		NCURSES_BITS(1U,12)
//#define A_BOLD		NCURSES_BITS(1U,13)
//#define A_ALTCHARSET	NCURSES_BITS(1U,14)
//#define A_INVIS		NCURSES_BITS(1U,15)
//#define A_PROTECT	NCURSES_BITS(1U,16)
//#define A_HORIZONTAL	NCURSES_BITS(1U,17)
//#define A_LEFT		NCURSES_BITS(1U,18)
//#define A_LOW		NCURSES_BITS(1U,19)
//#define A_RIGHT		NCURSES_BITS(1U,20)
//#define A_TOP		NCURSES_BITS(1U,21)
//#define A_VERTICAL	NCURSES_BITS(1U,22)
//
//#if 1
//#define A_ITALIC	NCURSES_BITS(1U,23)	/* ncurses extension */
//#endif
//
///*
// * Most of the pseudo functions are macros that either provide compatibility
// * with older versions of curses, or provide inline functionality to improve
// * performance.
// */
//
///*
// * These pseudo functions are always implemented as macros:
// */
//
//#define getyx(win,y,x)		(y = getcury(win), x = getcurx(win))
//#define getbegyx(win,y,x)	(y = getbegy(win), x = getbegx(win))
//#define getmaxyx(win,y,x)	(y = getmaxy(win), x = getmaxx(win))
//#define getparyx(win,y,x)	(y = getpary(win), x = getparx(win))
//
//#define getsyx(y,x) do { if (newscr) { \
//			     if (is_leaveok(newscr)) \
//				(y) = (x) = -1; \
//			     else \
//				 getyx(newscr,(y), (x)); \
//			} \
//		    } while(0)
//
//#define setsyx(y,x) do { if (newscr) { \
//			    if ((y) == -1 && (x) == -1) \
//				leaveok(newscr, TRUE); \
//			    else { \
//				leaveok(newscr, FALSE); \
//				wmove(newscr, (y), (x)); \
//			    } \
//			} \
//		    } while(0)
//
//#ifndef NCURSES_NOMACROS
//
///*
// * These miscellaneous pseudo functions are provided for compatibility:
// */
//
//#define wgetstr(w, s)		wgetnstr(w, s, -1)
//#define getnstr(s, n)		wgetnstr(stdscr, s, (n))
//
//#define setterm(term)		setupterm(term, 1, (int *)0)
//
//#define fixterm()		reset_prog_mode()
//#define resetterm()		reset_shell_mode()
//#define saveterm()		def_prog_mode()
//#define crmode()		cbreak()
//#define nocrmode()		nocbreak()
//#define gettmode()
//
///* It seems older SYSV curses versions define these */
//#if !NCURSES_OPAQUE
//#define getattrs(win)		NCURSES_CAST(int, NCURSES_OK_ADDR(win) ? (win)->_attrs : A_NORMAL)
//#define getcurx(win)		(NCURSES_OK_ADDR(win) ? (win)->_curx : ERR)
//#define getcury(win)		(NCURSES_OK_ADDR(win) ? (win)->_cury : ERR)
//#define getbegx(win)		(NCURSES_OK_ADDR(win) ? (win)->_begx : ERR)
//#define getbegy(win)		(NCURSES_OK_ADDR(win) ? (win)->_begy : ERR)
//#define getmaxx(win)		(NCURSES_OK_ADDR(win) ? ((win)->_maxx + 1) : ERR)
//#define getmaxy(win)		(NCURSES_OK_ADDR(win) ? ((win)->_maxy + 1) : ERR)
//#define getparx(win)		(NCURSES_OK_ADDR(win) ? (win)->_parx : ERR)
//#define getpary(win)		(NCURSES_OK_ADDR(win) ? (win)->_pary : ERR)
//#endif /* NCURSES_OPAQUE */
//
//#define wstandout(win)		(wattrset(win,A_STANDOUT))
//#define wstandend(win)		(wattrset(win,A_NORMAL))
//
//#define wattron(win,at)		wattr_on(win, NCURSES_CAST(attr_t, at), NULL)
//#define wattroff(win,at)	wattr_off(win, NCURSES_CAST(attr_t, at), NULL)
//
//#if !NCURSES_OPAQUE
//#if NCURSES_WATTR_MACROS
//#if NCURSES_WIDECHAR && 1
//#define wattrset(win,at) \
//	(NCURSES_OK_ADDR(win) \
//	  ? ((win)->_color = NCURSES_CAST(int, PAIR_NUMBER(at)), \
//	     (win)->_attrs = NCURSES_CAST(attr_t, at), \
//	     OK) \
//	  : ERR)
//#else
//#define wattrset(win,at) \
//	(NCURSES_OK_ADDR(win) \
//	  ? ((win)->_attrs = NCURSES_CAST(attr_t, at), \
//	     OK) \
//	  : ERR)
//#endif
//#endif /* NCURSES_WATTR_MACROS */
//#endif /* NCURSES_OPAQUE */
//
//#define scroll(win)		wscrl(win,1)
//
//#define touchwin(win)		wtouchln((win), 0, getmaxy(win), 1)
//#define touchline(win, s, c)	wtouchln((win), s, c, 1)
//#define untouchwin(win)		wtouchln((win), 0, getmaxy(win), 0)
//
//#define box(win, v, h)		wborder(win, v, v, h, h, 0, 0, 0, 0)
//#define border(ls, rs, ts, bs, tl, tr, bl, br)	wborder(stdscr, ls, rs, ts, bs, tl, tr, bl, br)
//#define hline(ch, n)		whline(stdscr, ch, (n))
//#define vline(ch, n)		wvline(stdscr, ch, (n))
//
//#define winstr(w, s)		winnstr(w, s, -1)
//#define winchstr(w, s)		winchnstr(w, s, -1)
//#define winsstr(w, s)		winsnstr(w, s, -1)
//
//#if !NCURSES_OPAQUE
//#define redrawwin(win)		wredrawln(win, 0, (NCURSES_OK_ADDR(win) ? (win)->_maxy+1 : -1))
//#endif /* NCURSES_OPAQUE */
//
//#define waddstr(win,str)	waddnstr(win,str,-1)
//#define waddchstr(win,str)	waddchnstr(win,str,-1)
//
///*
// * These apply to the first 256 color pairs.
// */
//#define COLOR_PAIR(n)	(NCURSES_BITS((n), 0) & A_COLOR)
//#define PAIR_NUMBER(a)	(NCURSES_CAST(int,((NCURSES_CAST(unsigned long,(a)) & A_COLOR) >> NCURSES_ATTR_SHIFT)))
//
///*
// * pseudo functions for standard screen
// */
//
//#define addch(ch)		waddch(stdscr,(ch))
//#define addchnstr(str,n)	waddchnstr(stdscr,(str),(n))
//#define addchstr(str)		waddchstr(stdscr,(str))
//#define addnstr(str,n)		waddnstr(stdscr,(str),(n))
//#define addstr(str)		waddnstr(stdscr,(str),-1)
//#define attr_get(ap,cp,o)	wattr_get(stdscr,(ap),(cp),(o))
//#define attr_off(a,o)		wattr_off(stdscr,(a),(o))
//#define attr_on(a,o)		wattr_on(stdscr,(a),(o))
//#define attr_set(a,c,o)		wattr_set(stdscr,(a),(c),(o))
//#define attroff(at)		wattroff(stdscr,(at))
//#define attron(at)		wattron(stdscr,(at))
//#define attrset(at)		wattrset(stdscr,(at))
//#define bkgd(ch)		wbkgd(stdscr,(ch))
//#define bkgdset(ch)		wbkgdset(stdscr,(ch))
//#define chgat(n,a,c,o)		wchgat(stdscr,(n),(a),(c),(o))
//#define clear()			wclear(stdscr)
//#define clrtobot()		wclrtobot(stdscr)
//#define clrtoeol()		wclrtoeol(stdscr)
//#define color_set(c,o)		wcolor_set(stdscr,(c),(o))
//#define delch()			wdelch(stdscr)
//#define deleteln()		winsdelln(stdscr,-1)
//#define echochar(c)		wechochar(stdscr,(c))
//#define erase()			werase(stdscr)
//#define getch()			wgetch(stdscr)
//#define getstr(str)		wgetstr(stdscr,(str))
//#define inch()			winch(stdscr)
//#define inchnstr(s,n)		winchnstr(stdscr,(s),(n))
//#define inchstr(s)		winchstr(stdscr,(s))
//#define innstr(s,n)		winnstr(stdscr,(s),(n))
//#define insch(c)		winsch(stdscr,(c))
//#define insdelln(n)		winsdelln(stdscr,(n))
//#define insertln()		winsdelln(stdscr,1)
//#define insnstr(s,n)		winsnstr(stdscr,(s),(n))
//#define insstr(s)		winsstr(stdscr,(s))
//#define instr(s)		winstr(stdscr,(s))
//#define move(y,x)		wmove(stdscr,(y),(x))
//#define refresh()		wrefresh(stdscr)
//#define scrl(n)			wscrl(stdscr,(n))
//#define setscrreg(t,b)		wsetscrreg(stdscr,(t),(b))
//#define standend()		wstandend(stdscr)
//#define standout()		wstandout(stdscr)
//#define timeout(delay)		wtimeout(stdscr,(delay))
//#define wdeleteln(win)		winsdelln(win,-1)
//#define winsertln(win)		winsdelln(win,1)
//
///*
// * mv functions
// */
//
//#define mvwaddch(win,y,x,ch)		(wmove((win),(y),(x)) == ERR ? ERR : waddch((win),(ch)))
//#define mvwaddchnstr(win,y,x,str,n)	(wmove((win),(y),(x)) == ERR ? ERR : waddchnstr((win),(str),(n)))
//#define mvwaddchstr(win,y,x,str)	(wmove((win),(y),(x)) == ERR ? ERR : waddchnstr((win),(str),-1))
//#define mvwaddnstr(win,y,x,str,n)	(wmove((win),(y),(x)) == ERR ? ERR : waddnstr((win),(str),(n)))
//#define mvwaddstr(win,y,x,str)		(wmove((win),(y),(x)) == ERR ? ERR : waddnstr((win),(str),-1))
//#define mvwchgat(win,y,x,n,a,c,o)	(wmove((win),(y),(x)) == ERR ? ERR : wchgat((win),(n),(a),(c),(o)))
//#define mvwdelch(win,y,x)		(wmove((win),(y),(x)) == ERR ? ERR : wdelch(win))
//#define mvwgetch(win,y,x)		(wmove((win),(y),(x)) == ERR ? ERR : wgetch(win))
//#define mvwgetnstr(win,y,x,str,n)	(wmove((win),(y),(x)) == ERR ? ERR : wgetnstr((win),(str),(n)))
//#define mvwgetstr(win,y,x,str)		(wmove((win),(y),(x)) == ERR ? ERR : wgetstr((win),(str)))
//#define mvwhline(win,y,x,c,n)		(wmove((win),(y),(x)) == ERR ? ERR : whline((win),(c),(n)))
//#define mvwinch(win,y,x)		(wmove((win),(y),(x)) == ERR ? NCURSES_CAST(chtype, ERR) : winch(win))
//#define mvwinchnstr(win,y,x,s,n)	(wmove((win),(y),(x)) == ERR ? ERR : winchnstr((win),(s),(n)))
//#define mvwinchstr(win,y,x,s)		(wmove((win),(y),(x)) == ERR ? ERR : winchstr((win),(s)))
//#define mvwinnstr(win,y,x,s,n)		(wmove((win),(y),(x)) == ERR ? ERR : winnstr((win),(s),(n)))
//#define mvwinsch(win,y,x,c)		(wmove((win),(y),(x)) == ERR ? ERR : winsch((win),(c)))
//#define mvwinsnstr(win,y,x,s,n)		(wmove((win),(y),(x)) == ERR ? ERR : winsnstr((win),(s),(n)))
//#define mvwinsstr(win,y,x,s)		(wmove((win),(y),(x)) == ERR ? ERR : winsstr((win),(s)))
//#define mvwinstr(win,y,x,s)		(wmove((win),(y),(x)) == ERR ? ERR : winstr((win),(s)))
//#define mvwvline(win,y,x,c,n)		(wmove((win),(y),(x)) == ERR ? ERR : wvline((win),(c),(n)))
//
//#define mvaddch(y,x,ch)			mvwaddch(stdscr,(y),(x),(ch))
//#define mvaddchnstr(y,x,str,n)		mvwaddchnstr(stdscr,(y),(x),(str),(n))
//#define mvaddchstr(y,x,str)		mvwaddchstr(stdscr,(y),(x),(str))
//#define mvaddnstr(y,x,str,n)		mvwaddnstr(stdscr,(y),(x),(str),(n))
//#define mvaddstr(y,x,str)		mvwaddstr(stdscr,(y),(x),(str))
//#define mvchgat(y,x,n,a,c,o)		mvwchgat(stdscr,(y),(x),(n),(a),(c),(o))
//#define mvdelch(y,x)			mvwdelch(stdscr,(y),(x))
//#define mvgetch(y,x)			mvwgetch(stdscr,(y),(x))
//#define mvgetnstr(y,x,str,n)		mvwgetnstr(stdscr,(y),(x),(str),(n))
//#define mvgetstr(y,x,str)		mvwgetstr(stdscr,(y),(x),(str))
//#define mvhline(y,x,c,n)		mvwhline(stdscr,(y),(x),(c),(n))
//#define mvinch(y,x)			mvwinch(stdscr,(y),(x))
//#define mvinchnstr(y,x,s,n)		mvwinchnstr(stdscr,(y),(x),(s),(n))
//#define mvinchstr(y,x,s)		mvwinchstr(stdscr,(y),(x),(s))
//#define mvinnstr(y,x,s,n)		mvwinnstr(stdscr,(y),(x),(s),(n))
//#define mvinsch(y,x,c)			mvwinsch(stdscr,(y),(x),(c))
//#define mvinsnstr(y,x,s,n)		mvwinsnstr(stdscr,(y),(x),(s),(n))
//#define mvinsstr(y,x,s)			mvwinsstr(stdscr,(y),(x),(s))
//#define mvinstr(y,x,s)			mvwinstr(stdscr,(y),(x),(s))
//#define mvvline(y,x,c,n)		mvwvline(stdscr,(y),(x),(c),(n))
//
///*
// * Some wide-character functions can be implemented without the extensions.
// */
//#if !NCURSES_OPAQUE
//#define getbkgd(win)                    (NCURSES_OK_ADDR(win) ? ((win)->_bkgd) : 0)
//#endif /* NCURSES_OPAQUE */
//
//#define slk_attr_off(a,v)		((v) ? ERR : slk_attroff(a))
//#define slk_attr_on(a,v)		((v) ? ERR : slk_attron(a))
//
//#if !NCURSES_OPAQUE
//#if NCURSES_WATTR_MACROS
//#if NCURSES_WIDECHAR && 1
//#define wattr_set(win,a,p,opts) \
//	(NCURSES_OK_ADDR(win) \
//	 ? ((void)((win)->_attrs = ((a) & ~A_COLOR), \
//		   (win)->_color = (opts) ? *(int *)(opts) : (p)), \
//	    OK) \
//	 : ERR)
//#define wattr_get(win,a,p,opts) \
//	(NCURSES_OK_ADDR(win) \
//	 ? ((void)(NCURSES_OK_ADDR(a) \
//		   ? (*(a) = (win)->_attrs) \
//		   : OK), \
//	    (void)(NCURSES_OK_ADDR(p) \
//		   ? (*(p) = (NCURSES_PAIRS_T) (win)->_color) \
//		   : OK), \
//	    (void)(NCURSES_OK_ADDR(opts) \
//		   ? (*(int *)(opts) = (win)->_color) \
//		   : OK), \
//	    OK) \
//	 : ERR)
//#else /* !(NCURSES_WIDECHAR && NCURSES_EXE_COLORS) */
//#define wattr_set(win,a,p,opts) \
//	 (NCURSES_OK_ADDR(win) \
//	  ? ((void)((win)->_attrs = (((a) & ~A_COLOR) | \
//				     (attr_t)COLOR_PAIR(p))), \
//	     OK) \
//	  : ERR)
//#define wattr_get(win,a,p,opts) \
//	(NCURSES_OK_ADDR(win) \
//	 ? ((void)(NCURSES_OK_ADDR(a) \
//		   ? (*(a) = (win)->_attrs) \
//		   : OK), \
//	    (void)(NCURSES_OK_ADDR(p) \
//		   ? (*(p) = (NCURSES_PAIRS_T) PAIR_NUMBER((win)->_attrs)) \
//		   : OK), \
//	    OK) \
//	 : ERR)
//#endif /* (NCURSES_WIDECHAR && NCURSES_EXE_COLORS) */
//#endif /* NCURSES_WATTR_MACROS */
//#endif /* NCURSES_OPAQUE */
//
///*
// * X/Open curses deprecates SVr4 vwprintw/vwscanw, which are supposed to use
// * varargs.h.  It adds new calls vw_printw/vw_scanw, which are supposed to
// * use POSIX stdarg.h.  The ncurses versions of vwprintw/vwscanw already
// * use stdarg.h, so...
// */
///* define vw_printw		vwprintw */
///* define vw_scanw		vwscanw */
//
///*
// * Export fallback function for use in C++ binding.
// */
//#if !1
//#define vsscanf(a,b,c) _nc_vsscanf(a,b,c)
//NCURSES_EXPORT(int) vsscanf(const char *, const char *, va_list);
//#endif
//
///*
// * These macros are extensions - not in X/Open Curses.
// */
//#if 1
//#if !NCURSES_OPAQUE
//#define is_cleared(win)		(NCURSES_OK_ADDR(win) ? (win)->_clear : FALSE)
//#define is_idcok(win)		(NCURSES_OK_ADDR(win) ? (win)->_idcok : FALSE)
//#define is_idlok(win)		(NCURSES_OK_ADDR(win) ? (win)->_idlok : FALSE)
//#define is_immedok(win)		(NCURSES_OK_ADDR(win) ? (win)->_immed : FALSE)
//#define is_keypad(win)		(NCURSES_OK_ADDR(win) ? (win)->_use_keypad : FALSE)
//#define is_leaveok(win)		(NCURSES_OK_ADDR(win) ? (win)->_leaveok : FALSE)
//#define is_nodelay(win)		(NCURSES_OK_ADDR(win) ? ((win)->_delay == 0) : FALSE)
//#define is_notimeout(win)	(NCURSES_OK_ADDR(win) ? (win)->_notimeout : FALSE)
//#define is_pad(win)		(NCURSES_OK_ADDR(win) ? ((win)->_flags & _ISPAD) != 0 : FALSE)
//#define is_scrollok(win)	(NCURSES_OK_ADDR(win) ? (win)->_scroll : FALSE)
//#define is_subwin(win)		(NCURSES_OK_ADDR(win) ? ((win)->_flags & _SUBWIN) != 0 : FALSE)
//#define is_syncok(win)		(NCURSES_OK_ADDR(win) ? (win)->_sync : FALSE)
//#define wgetdelay(win)		(NCURSES_OK_ADDR(win) ? (win)->_delay : 0)
//#define wgetparent(win)		(NCURSES_OK_ADDR(win) ? (win)->_parent : 0)
//#define wgetscrreg(win,t,b)	(NCURSES_OK_ADDR(win) ? (*(t) = (win)->_regtop, *(b) = (win)->_regbottom, OK) : ERR)
//#endif
//#endif
//
///*
// * X/Open says this returns a bool; SVr4 also checked for out-of-range line.
// * The macro provides compatibility:
// */
//#define is_linetouched(w,l) ((!(w) || ((l) > getmaxy(w)) || ((l) < 0)) ? ERR : (is_linetouched)((w),(l)))
//
//#endif /* NCURSES_NOMACROS */
//
///*
// * Public variables.
// *
// * Notes:
// *	a. ESCDELAY was an undocumented feature under AIX curses.
// *	   It gives the ESC expire time in milliseconds.
// *	b. ttytype is needed for backward compatibility
// */
//#if NCURSES_REENTRANT
//
//NCURSES_WRAPPED_VAR(WINDOW *, curscr);
//NCURSES_WRAPPED_VAR(WINDOW *, newscr);
//NCURSES_WRAPPED_VAR(WINDOW *, stdscr);
//NCURSES_WRAPPED_VAR(char *, ttytype);
//NCURSES_WRAPPED_VAR(int, COLORS);
//NCURSES_WRAPPED_VAR(int, COLOR_PAIRS);
//NCURSES_WRAPPED_VAR(int, COLS);
//NCURSES_WRAPPED_VAR(int, ESCDELAY);
//NCURSES_WRAPPED_VAR(int, LINES);
//NCURSES_WRAPPED_VAR(int, TABSIZE);
//
//#define curscr      NCURSES_PUBLIC_VAR(curscr())
//#define newscr      NCURSES_PUBLIC_VAR(newscr())
//#define stdscr      NCURSES_PUBLIC_VAR(stdscr())
//#define ttytype     NCURSES_PUBLIC_VAR(ttytype())
//#define COLORS      NCURSES_PUBLIC_VAR(COLORS())
//#define COLOR_PAIRS NCURSES_PUBLIC_VAR(COLOR_PAIRS())
//#define COLS        NCURSES_PUBLIC_VAR(COLS())
//#define ESCDELAY    NCURSES_PUBLIC_VAR(ESCDELAY())
//#define LINES       NCURSES_PUBLIC_VAR(LINES())
//#define TABSIZE     NCURSES_PUBLIC_VAR(TABSIZE())
//
//#else
//
//extern NCURSES_EXPORT_VAR(WINDOW *) curscr;
//extern NCURSES_EXPORT_VAR(WINDOW *) newscr;
//extern NCURSES_EXPORT_VAR(WINDOW *) stdscr;
//extern NCURSES_EXPORT_VAR(char) ttytype[];
//extern NCURSES_EXPORT_VAR(int) COLORS;
//extern NCURSES_EXPORT_VAR(int) COLOR_PAIRS;
//extern NCURSES_EXPORT_VAR(int) COLS;
//extern NCURSES_EXPORT_VAR(int) ESCDELAY;
//extern NCURSES_EXPORT_VAR(int) LINES;
//extern NCURSES_EXPORT_VAR(int) TABSIZE;
//
//#endif
//
///*
// * Pseudo-character tokens outside ASCII range.  The curses wgetch() function
// * will return any given one of these only if the corresponding k- capability
// * is defined in your terminal's terminfo entry.
// *
// * Some keys (KEY_A1, etc) are arranged like this:
// *	a1     up    a3
// *	left   b2    right
// *	c1     down  c3
// *
// * A few key codes do not depend upon the terminfo entry.
// */
//#define KEY_CODE_YES	0400		/* A wchar_t contains a key code */
//#define KEY_MIN		0401		/* Minimum curses key */
//#define KEY_BREAK	0401		/* Break key (unreliable) */
//#define KEY_SRESET	0530		/* Soft (partial) reset (unreliable) */
//#define KEY_RESET	0531		/* Reset or hard reset (unreliable) */
///*
// * These definitions were generated by ./MKkey_defs.sh /home/builder/.termux-build/ncurses/src/include/Caps /home/builder/.termux-build/ncurses/src/include/Caps-ncurses
// */
//#define KEY_DOWN	0402		/* down-arrow key */
//#define KEY_UP		0403		/* up-arrow key */
//#define KEY_LEFT	0404		/* left-arrow key */
//#define KEY_RIGHT	0405		/* right-arrow key */
//#define KEY_HOME	0406		/* home key */
//#define KEY_BACKSPACE	0407		/* backspace key */
//#define KEY_F0		0410		/* Function keys.  Space for 64 */
//#define KEY_F(n)	(KEY_F0+(n))	/* Value of function key n */
//#define KEY_DL		0510		/* delete-line key */
//#define KEY_IL		0511		/* insert-line key */
//#define KEY_DC		0512		/* delete-character key */
//#define KEY_IC		0513		/* insert-character key */
//#define KEY_EIC		0514		/* sent by rmir or smir in insert mode */
//#define KEY_CLEAR	0515		/* clear-screen or erase key */
//#define KEY_EOS		0516		/* clear-to-end-of-screen key */
//#define KEY_EOL		0517		/* clear-to-end-of-line key */
//#define KEY_SF		0520		/* scroll-forward key */
//#define KEY_SR		0521		/* scroll-backward key */
//#define KEY_NPAGE	0522		/* next-page key */
//#define KEY_PPAGE	0523		/* previous-page key */
//#define KEY_STAB	0524		/* set-tab key */
//#define KEY_CTAB	0525		/* clear-tab key */
//#define KEY_CATAB	0526		/* clear-all-tabs key */
//#define KEY_ENTER	0527		/* enter/send key */
//#define KEY_PRINT	0532		/* print key */
//#define KEY_LL		0533		/* lower-left key (home down) */
//#define KEY_A1		0534		/* upper left of keypad */
//#define KEY_A3		0535		/* upper right of keypad */
//#define KEY_B2		0536		/* center of keypad */
//#define KEY_C1		0537		/* lower left of keypad */
//#define KEY_C3		0540		/* lower right of keypad */
//#define KEY_BTAB	0541		/* back-tab key */
//#define KEY_BEG		0542		/* begin key */
//#define KEY_CANCEL	0543		/* cancel key */
//#define KEY_CLOSE	0544		/* close key */
//#define KEY_COMMAND	0545		/* command key */
//#define KEY_COPY	0546		/* copy key */
//#define KEY_CREATE	0547		/* create key */
//#define KEY_END		0550		/* end key */
//#define KEY_EXIT	0551		/* exit key */
//#define KEY_FIND	0552		/* find key */
//#define KEY_HELP	0553		/* help key */
//#define KEY_MARK	0554		/* mark key */
//#define KEY_MESSAGE	0555		/* message key */
//#define KEY_MOVE	0556		/* move key */
//#define KEY_NEXT	0557		/* next key */
//#define KEY_OPEN	0560		/* open key */
//#define KEY_OPTIONS	0561		/* options key */
//#define KEY_PREVIOUS	0562		/* previous key */
//#define KEY_REDO	0563		/* redo key */
//#define KEY_REFERENCE	0564		/* reference key */
//#define KEY_REFRESH	0565		/* refresh key */
//#define KEY_REPLACE	0566		/* replace key */
//#define KEY_RESTART	0567		/* restart key */
//#define KEY_RESUME	0570		/* resume key */
//#define KEY_SAVE	0571		/* save key */
//#define KEY_SBEG	0572		/* shifted begin key */
//#define KEY_SCANCEL	0573		/* shifted cancel key */
//#define KEY_SCOMMAND	0574		/* shifted command key */
//#define KEY_SCOPY	0575		/* shifted copy key */
//#define KEY_SCREATE	0576		/* shifted create key */
//#define KEY_SDC		0577		/* shifted delete-character key */
//#define KEY_SDL		0600		/* shifted delete-line key */
//#define KEY_SELECT	0601		/* select key */
//#define KEY_SEND	0602		/* shifted end key */
//#define KEY_SEOL	0603		/* shifted clear-to-end-of-line key */
//#define KEY_SEXIT	0604		/* shifted exit key */
//#define KEY_SFIND	0605		/* shifted find key */
//#define KEY_SHELP	0606		/* shifted help key */
//#define KEY_SHOME	0607		/* shifted home key */
//#define KEY_SIC		0610		/* shifted insert-character key */
//#define KEY_SLEFT	0611		/* shifted left-arrow key */
//#define KEY_SMESSAGE	0612		/* shifted message key */
//#define KEY_SMOVE	0613		/* shifted move key */
//#define KEY_SNEXT	0614		/* shifted next key */
//#define KEY_SOPTIONS	0615		/* shifted options key */
//#define KEY_SPREVIOUS	0616		/* shifted previous key */
//#define KEY_SPRINT	0617		/* shifted print key */
//#define KEY_SREDO	0620		/* shifted redo key */
//#define KEY_SREPLACE	0621		/* shifted replace key */
//#define KEY_SRIGHT	0622		/* shifted right-arrow key */
//#define KEY_SRSUME	0623		/* shifted resume key */
//#define KEY_SSAVE	0624		/* shifted save key */
//#define KEY_SSUSPEND	0625		/* shifted suspend key */
//#define KEY_SUNDO	0626		/* shifted undo key */
//#define KEY_SUSPEND	0627		/* suspend key */
//#define KEY_UNDO	0630		/* undo key */
//#define KEY_MOUSE	0631		/* Mouse event has occurred */
//#define KEY_RESIZE	0632		/* Terminal resize event */
//#define KEY_EVENT	0633		/* We were interrupted by an event */
//
//#define KEY_MAX		0777		/* Maximum key value is 0633 */
///* $Id: curses.wide,v 1.50 2017/03/26 16:05:21 tom Exp $ */
///*
// * vile:cmode:
// * This file is part of ncurses, designed to be appended after curses.h.in
// * (see that file for the relevant copyright).
// */
//#define _XOPEN_CURSES 1
//
//#if NCURSES_WIDECHAR
//
//extern NCURSES_EXPORT_VAR(cchar_t *) _nc_wacs;
//
//#define NCURSES_WACS(c)	(&_nc_wacs[NCURSES_CAST(unsigned char,(c))])
//
//#define WACS_BSSB	NCURSES_WACS('l')
//#define WACS_SSBB	NCURSES_WACS('m')
//#define WACS_BBSS	NCURSES_WACS('k')
//#define WACS_SBBS	NCURSES_WACS('j')
//#define WACS_SBSS	NCURSES_WACS('u')
//#define WACS_SSSB	NCURSES_WACS('t')
//#define WACS_SSBS	NCURSES_WACS('v')
//#define WACS_BSSS	NCURSES_WACS('w')
//#define WACS_BSBS	NCURSES_WACS('q')
//#define WACS_SBSB	NCURSES_WACS('x')
//#define WACS_SSSS	NCURSES_WACS('n')
//
//#define WACS_ULCORNER	WACS_BSSB
//#define WACS_LLCORNER	WACS_SSBB
//#define WACS_URCORNER	WACS_BBSS
//#define WACS_LRCORNER	WACS_SBBS
//#define WACS_RTEE	WACS_SBSS
//#define WACS_LTEE	WACS_SSSB
//#define WACS_BTEE	WACS_SSBS
//#define WACS_TTEE	WACS_BSSS
//#define WACS_HLINE	WACS_BSBS
//#define WACS_VLINE	WACS_SBSB
//#define WACS_PLUS	WACS_SSSS
//
//#define WACS_S1		NCURSES_WACS('o') /* scan line 1 */
//#define WACS_S9 	NCURSES_WACS('s') /* scan line 9 */
//#define WACS_DIAMOND	NCURSES_WACS('`') /* diamond */
//#define WACS_CKBOARD	NCURSES_WACS('a') /* checker board */
//#define WACS_DEGREE	NCURSES_WACS('f') /* degree symbol */
//#define WACS_PLMINUS	NCURSES_WACS('g') /* plus/minus */
//#define WACS_BULLET	NCURSES_WACS('~') /* bullet */
//
//	/* Teletype 5410v1 symbols */
//#define WACS_LARROW	NCURSES_WACS(',') /* arrow left */
//#define WACS_RARROW	NCURSES_WACS('+') /* arrow right */
//#define WACS_DARROW	NCURSES_WACS('.') /* arrow down */
//#define WACS_UARROW	NCURSES_WACS('-') /* arrow up */
//#define WACS_BOARD	NCURSES_WACS('h') /* board of squares */
//#define WACS_LANTERN	NCURSES_WACS('i') /* lantern symbol */
//#define WACS_BLOCK	NCURSES_WACS('0') /* solid square block */
//
//	/* ncurses extensions */
//#define WACS_S3		NCURSES_WACS('p') /* scan line 3 */
//#define WACS_S7		NCURSES_WACS('r') /* scan line 7 */
//#define WACS_LEQUAL	NCURSES_WACS('y') /* less/equal */
//#define WACS_GEQUAL	NCURSES_WACS('z') /* greater/equal */
//#define WACS_PI		NCURSES_WACS('{') /* Pi */
//#define WACS_NEQUAL	NCURSES_WACS('|') /* not equal */
//#define WACS_STERLING	NCURSES_WACS('}') /* UK pound sign */
//
//	/* double lines */
//#define WACS_BDDB	NCURSES_WACS('C')
//#define WACS_DDBB	NCURSES_WACS('D')
//#define WACS_BBDD	NCURSES_WACS('B')
//#define WACS_DBBD	NCURSES_WACS('A')
//#define WACS_DBDD	NCURSES_WACS('G')
//#define WACS_DDDB	NCURSES_WACS('F')
//#define WACS_DDBD	NCURSES_WACS('H')
//#define WACS_BDDD	NCURSES_WACS('I')
//#define WACS_BDBD	NCURSES_WACS('R')
//#define WACS_DBDB	NCURSES_WACS('Y')
//#define WACS_DDDD	NCURSES_WACS('E')
//
//#define WACS_D_ULCORNER	WACS_BDDB
//#define WACS_D_LLCORNER	WACS_DDBB
//#define WACS_D_URCORNER	WACS_BBDD
//#define WACS_D_LRCORNER	WACS_DBBD
//#define WACS_D_RTEE	WACS_DBDD
//#define WACS_D_LTEE	WACS_DDDB
//#define WACS_D_BTEE	WACS_DDBD
//#define WACS_D_TTEE	WACS_BDDD
//#define WACS_D_HLINE	WACS_BDBD
//#define WACS_D_VLINE	WACS_DBDB
//#define WACS_D_PLUS	WACS_DDDD
//
//	/* thick lines */
//#define WACS_BTTB	NCURSES_WACS('L')
//#define WACS_TTBB	NCURSES_WACS('M')
//#define WACS_BBTT	NCURSES_WACS('K')
//#define WACS_TBBT	NCURSES_WACS('J')
//#define WACS_TBTT	NCURSES_WACS('U')
//#define WACS_TTTB	NCURSES_WACS('T')
//#define WACS_TTBT	NCURSES_WACS('V')
//#define WACS_BTTT	NCURSES_WACS('W')
//#define WACS_BTBT	NCURSES_WACS('Q')
//#define WACS_TBTB	NCURSES_WACS('X')
//#define WACS_TTTT	NCURSES_WACS('N')
//
//#define WACS_T_ULCORNER	WACS_BTTB
//#define WACS_T_LLCORNER	WACS_TTBB
//#define WACS_T_URCORNER	WACS_BBTT
//#define WACS_T_LRCORNER	WACS_TBBT
//#define WACS_T_RTEE	WACS_TBTT
//#define WACS_T_LTEE	WACS_TTTB
//#define WACS_T_BTEE	WACS_TTBT
//#define WACS_T_TTEE	WACS_BTTT
//#define WACS_T_HLINE	WACS_BTBT
//#define WACS_T_VLINE	WACS_TBTB
//#define WACS_T_PLUS	WACS_TTTT
//
///*
// * Function prototypes for wide-character operations.
// *
// * "generated" comments should include ":WIDEC" to make the corresponding
// * functions ifdef'd in lib_gen.c
// *
// * "implemented" comments do not need this marker.
// */
//
//extern NCURSES_EXPORT(int) add_wch (const cchar_t *);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) add_wchnstr (const cchar_t *, int);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) add_wchstr (const cchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) addnwstr (const wchar_t *, int);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) addwstr (const wchar_t *);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) bkgrnd (const cchar_t *);			/* generated:WIDEC */
//extern NCURSES_EXPORT(void) bkgrndset (const cchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) border_set (const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*); /* generated:WIDEC */
//extern NCURSES_EXPORT(int) box_set (WINDOW *, const cchar_t *, const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) echo_wchar (const cchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) erasewchar (wchar_t*);			/* implemented */
//extern NCURSES_EXPORT(int) get_wch (wint_t *);				/* generated:WIDEC */
//extern NCURSES_EXPORT(int) get_wstr (wint_t *);				/* generated:WIDEC */
//extern NCURSES_EXPORT(int) getbkgrnd (cchar_t *);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) getcchar (const cchar_t *, wchar_t*, attr_t*, NCURSES_PAIRS_T*, void*);	/* implemented */
//extern NCURSES_EXPORT(int) getn_wstr (wint_t *, int);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) hline_set (const cchar_t *, int);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) in_wch (cchar_t *);				/* generated:WIDEC */
//extern NCURSES_EXPORT(int) in_wchnstr (cchar_t *, int);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) in_wchstr (cchar_t *);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) innwstr (wchar_t *, int);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) ins_nwstr (const wchar_t *, int);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) ins_wch (const cchar_t *);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) ins_wstr (const wchar_t *);			/* generated:WIDEC */
//extern NCURSES_EXPORT(int) inwstr (wchar_t *);				/* generated:WIDEC */
//extern NCURSES_EXPORT(NCURSES_CONST char*) key_name (wchar_t);		/* implemented */
//extern NCURSES_EXPORT(int) killwchar (wchar_t *);			/* implemented */
//extern NCURSES_EXPORT(int) mvadd_wch (int, int, const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvadd_wchnstr (int, int, const cchar_t *, int);/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvadd_wchstr (int, int, const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvaddnwstr (int, int, const wchar_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvaddwstr (int, int, const wchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvget_wch (int, int, wint_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvget_wstr (int, int, wint_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvgetn_wstr (int, int, wint_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvhline_set (int, int, const cchar_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvin_wch (int, int, cchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvin_wchnstr (int, int, cchar_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvin_wchstr (int, int, cchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvinnwstr (int, int, wchar_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvins_nwstr (int, int, const wchar_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvins_wch (int, int, const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvins_wstr (int, int, const wchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvinwstr (int, int, wchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvvline_set (int, int, const cchar_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwadd_wch (WINDOW *, int, int, const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwadd_wchnstr (WINDOW *, int, int, const cchar_t *, int); /* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwadd_wchstr (WINDOW *, int, int, const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwaddnwstr (WINDOW *, int, int, const wchar_t *, int);/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwaddwstr (WINDOW *, int, int, const wchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwget_wch (WINDOW *, int, int, wint_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwget_wstr (WINDOW *, int, int, wint_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwgetn_wstr (WINDOW *, int, int, wint_t *, int);/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwhline_set (WINDOW *, int, int, const cchar_t *, int);/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwin_wch (WINDOW *, int, int, cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwin_wchnstr (WINDOW *, int,int, cchar_t *,int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwin_wchstr (WINDOW *, int, int, cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwinnwstr (WINDOW *, int, int, wchar_t *, int);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwins_nwstr (WINDOW *, int,int, const wchar_t *,int); /* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwins_wch (WINDOW *, int, int, const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwins_wstr (WINDOW *, int, int, const wchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwinwstr (WINDOW *, int, int, wchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) mvwvline_set (WINDOW *, int,int, const cchar_t *,int); /* generated:WIDEC */
//extern NCURSES_EXPORT(int) pecho_wchar (WINDOW *, const cchar_t *);	/* implemented */
//extern NCURSES_EXPORT(int) setcchar (cchar_t *, const wchar_t *, const attr_t, NCURSES_PAIRS_T, const void *);	/* implemented */
//extern NCURSES_EXPORT(int) slk_wset (int, const wchar_t *, int);	/* implemented */
//extern NCURSES_EXPORT(attr_t) term_attrs (void);			/* implemented */
//extern NCURSES_EXPORT(int) unget_wch (const wchar_t);			/* implemented */
//extern NCURSES_EXPORT(int) vid_attr (attr_t, NCURSES_PAIRS_T, void *);		/* implemented */
//extern NCURSES_EXPORT(int) vid_puts (attr_t, NCURSES_PAIRS_T, void *, NCURSES_OUTC); /* implemented */
//extern NCURSES_EXPORT(int) vline_set (const cchar_t *, int);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) wadd_wch (WINDOW *,const cchar_t *);		/* implemented */
//extern NCURSES_EXPORT(int) wadd_wchnstr (WINDOW *,const cchar_t *,int);	/* implemented */
//extern NCURSES_EXPORT(int) wadd_wchstr (WINDOW *,const cchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) waddnwstr (WINDOW *,const wchar_t *,int);	/* implemented */
//extern NCURSES_EXPORT(int) waddwstr (WINDOW *,const wchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) wbkgrnd (WINDOW *,const cchar_t *);		/* implemented */
//extern NCURSES_EXPORT(void) wbkgrndset (WINDOW *,const cchar_t *);	/* implemented */
//extern NCURSES_EXPORT(int) wborder_set (WINDOW *,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*,const cchar_t*);	/* implemented */
//extern NCURSES_EXPORT(int) wecho_wchar (WINDOW *, const cchar_t *);	/* implemented */
//extern NCURSES_EXPORT(int) wget_wch (WINDOW *, wint_t *);		/* implemented */
//extern NCURSES_EXPORT(int) wget_wstr (WINDOW *, wint_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) wgetbkgrnd (WINDOW *, cchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) wgetn_wstr (WINDOW *, wint_t *, int);	/* implemented */
//extern NCURSES_EXPORT(int) whline_set (WINDOW *, const cchar_t *, int);	/* implemented */
//extern NCURSES_EXPORT(int) win_wch (WINDOW *, cchar_t *);		/* implemented */
//extern NCURSES_EXPORT(int) win_wchnstr (WINDOW *, cchar_t *, int);	/* implemented */
//extern NCURSES_EXPORT(int) win_wchstr (WINDOW *, cchar_t *);		/* generated:WIDEC */
//extern NCURSES_EXPORT(int) winnwstr (WINDOW *, wchar_t *, int);		/* implemented */
//extern NCURSES_EXPORT(int) wins_nwstr (WINDOW *, const wchar_t *, int);	/* implemented */
//extern NCURSES_EXPORT(int) wins_wch (WINDOW *, const cchar_t *);	/* implemented */
//extern NCURSES_EXPORT(int) wins_wstr (WINDOW *, const wchar_t *);	/* generated:WIDEC */
//extern NCURSES_EXPORT(int) winwstr (WINDOW *, wchar_t *);		/* implemented */
//extern NCURSES_EXPORT(wchar_t*) wunctrl (cchar_t *);			/* implemented */
//extern NCURSES_EXPORT(int) wvline_set (WINDOW *, const cchar_t *, int);	/* implemented */
//
//#if NCURSES_SP_FUNCS
//extern NCURSES_EXPORT(attr_t) NCURSES_SP_NAME(term_attrs) (SCREEN*);		/* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(unget_wch) (SCREEN*, const wchar_t);	/* implemented:SP_FUNC */
//extern NCURSES_EXPORT(wchar_t*) NCURSES_SP_NAME(wunctrl) (SCREEN*, cchar_t *);	/* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vid_attr) (SCREEN*, attr_t, NCURSES_PAIRS_T, void *);	/* implemented:SP_FUNC */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(vid_puts) (SCREEN*, attr_t, NCURSES_PAIRS_T, void *, NCURSES_SP_OUTC);	/* implemented:SP_FUNC */
//#endif
//
//#ifndef NCURSES_NOMACROS
//
///*
// * XSI curses macros for XPG4 conformance.
// */
//#define add_wch(c)			wadd_wch(stdscr,(c))
//#define add_wchnstr(str,n)		wadd_wchnstr(stdscr,(str),(n))
//#define add_wchstr(str)			wadd_wchstr(stdscr,(str))
//#define addnwstr(wstr,n)		waddnwstr(stdscr,(wstr),(n))
//#define addwstr(wstr)			waddwstr(stdscr,(wstr))
//#define bkgrnd(c)			wbkgrnd(stdscr,(c))
//#define bkgrndset(c)			wbkgrndset(stdscr,(c))
//#define border_set(l,r,t,b,tl,tr,bl,br) wborder_set(stdscr,(l),(r),(t),(b),tl,tr,bl,br)
//#define box_set(w,v,h)			wborder_set((w),(v),(v),(h),(h),0,0,0,0)
//#define echo_wchar(c)			wecho_wchar(stdscr,(c))
//#define get_wch(c)			wget_wch(stdscr,(c))
//#define get_wstr(t)			wget_wstr(stdscr,(t))
//#define getbkgrnd(wch)			wgetbkgrnd(stdscr,(wch))
//#define getn_wstr(t,n)			wgetn_wstr(stdscr,(t),(n))
//#define hline_set(c,n)			whline_set(stdscr,(c),(n))
//#define in_wch(c)			win_wch(stdscr,(c))
//#define in_wchnstr(c,n)			win_wchnstr(stdscr,(c),(n))
//#define in_wchstr(c)			win_wchstr(stdscr,(c))
//#define innwstr(c,n)			winnwstr(stdscr,(c),(n))
//#define ins_nwstr(t,n)			wins_nwstr(stdscr,(t),(n))
//#define ins_wch(c)			wins_wch(stdscr,(c))
//#define ins_wstr(t)			wins_wstr(stdscr,(t))
//#define inwstr(c)			winwstr(stdscr,(c))
//#define vline_set(c,n)			wvline_set(stdscr,(c),(n))
//#define wadd_wchstr(win,str)		wadd_wchnstr((win),(str),-1)
//#define waddwstr(win,wstr)		waddnwstr((win),(wstr),-1)
//#define wget_wstr(w,t)			wgetn_wstr((w),(t),-1)
//#define win_wchstr(w,c)			win_wchnstr((w),(c),-1)
//#define wins_wstr(w,t)			wins_nwstr((w),(t),-1)
//
//#if !NCURSES_OPAQUE
//#define wgetbkgrnd(win,wch)		(NCURSES_OK_ADDR(wch) ? ((win) ? (*(wch) = (win)->_bkgrnd) : *(wch), OK) : ERR)
//#endif
//
//#define mvadd_wch(y,x,c)		mvwadd_wch(stdscr,(y),(x),(c))
//#define mvadd_wchnstr(y,x,s,n)		mvwadd_wchnstr(stdscr,(y),(x),(s),(n))
//#define mvadd_wchstr(y,x,s)		mvwadd_wchstr(stdscr,(y),(x),(s))
//#define mvaddnwstr(y,x,wstr,n)		mvwaddnwstr(stdscr,(y),(x),(wstr),(n))
//#define mvaddwstr(y,x,wstr)		mvwaddwstr(stdscr,(y),(x),(wstr))
//#define mvget_wch(y,x,c)		mvwget_wch(stdscr,(y),(x),(c))
//#define mvget_wstr(y,x,t)		mvwget_wstr(stdscr,(y),(x),(t))
//#define mvgetn_wstr(y,x,t,n)		mvwgetn_wstr(stdscr,(y),(x),(t),(n))
//#define mvhline_set(y,x,c,n)		mvwhline_set(stdscr,(y),(x),(c),(n))
//#define mvin_wch(y,x,c)			mvwin_wch(stdscr,(y),(x),(c))
//#define mvin_wchnstr(y,x,c,n)		mvwin_wchnstr(stdscr,(y),(x),(c),(n))
//#define mvin_wchstr(y,x,c)		mvwin_wchstr(stdscr,(y),(x),(c))
//#define mvinnwstr(y,x,c,n)		mvwinnwstr(stdscr,(y),(x),(c),(n))
//#define mvins_nwstr(y,x,t,n)		mvwins_nwstr(stdscr,(y),(x),(t),(n))
//#define mvins_wch(y,x,c)		mvwins_wch(stdscr,(y),(x),(c))
//#define mvins_wstr(y,x,t)		mvwins_wstr(stdscr,(y),(x),(t))
//#define mvinwstr(y,x,c)			mvwinwstr(stdscr,(y),(x),(c))
//#define mvvline_set(y,x,c,n)		mvwvline_set(stdscr,(y),(x),(c),(n))
//
//#define mvwadd_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : wadd_wch((win),(c)))
//#define mvwadd_wchnstr(win,y,x,s,n)	(wmove(win,(y),(x)) == ERR ? ERR : wadd_wchnstr((win),(s),(n)))
//#define mvwadd_wchstr(win,y,x,s)	(wmove(win,(y),(x)) == ERR ? ERR : wadd_wchstr((win),(s)))
//#define mvwaddnwstr(win,y,x,wstr,n)	(wmove(win,(y),(x)) == ERR ? ERR : waddnwstr((win),(wstr),(n)))
//#define mvwaddwstr(win,y,x,wstr)	(wmove(win,(y),(x)) == ERR ? ERR : waddwstr((win),(wstr)))
//#define mvwget_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : wget_wch((win),(c)))
//#define mvwget_wstr(win,y,x,t)		(wmove(win,(y),(x)) == ERR ? ERR : wget_wstr((win),(t)))
//#define mvwgetn_wstr(win,y,x,t,n)	(wmove(win,(y),(x)) == ERR ? ERR : wgetn_wstr((win),(t),(n)))
//#define mvwhline_set(win,y,x,c,n)	(wmove(win,(y),(x)) == ERR ? ERR : whline_set((win),(c),(n)))
//#define mvwin_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : win_wch((win),(c)))
//#define mvwin_wchnstr(win,y,x,c,n)	(wmove(win,(y),(x)) == ERR ? ERR : win_wchnstr((win),(c),(n)))
//#define mvwin_wchstr(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : win_wchstr((win),(c)))
//#define mvwinnwstr(win,y,x,c,n)		(wmove(win,(y),(x)) == ERR ? ERR : winnwstr((win),(c),(n)))
//#define mvwins_nwstr(win,y,x,t,n)	(wmove(win,(y),(x)) == ERR ? ERR : wins_nwstr((win),(t),(n)))
//#define mvwins_wch(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : wins_wch((win),(c)))
//#define mvwins_wstr(win,y,x,t)		(wmove(win,(y),(x)) == ERR ? ERR : wins_wstr((win),(t)))
//#define mvwinwstr(win,y,x,c)		(wmove(win,(y),(x)) == ERR ? ERR : winwstr((win),(c)))
//#define mvwvline_set(win,y,x,c,n)	(wmove(win,(y),(x)) == ERR ? ERR : wvline_set((win),(c),(n)))
//
//#endif /* NCURSES_NOMACROS */
//
//#if defined(TRACE) || defined(NCURSES_TEST)
//extern NCURSES_EXPORT(const char *) _nc_viswbuf(const wchar_t *);
//extern NCURSES_EXPORT(const char *) _nc_viswibuf(const wint_t *);
//#endif
//
//#endif /* NCURSES_WIDECHAR */
///* $Id: curses.tail,v 1.23 2016/02/13 16:37:45 tom Exp $ */
///*
// * vile:cmode:
// * This file is part of ncurses, designed to be appended after curses.h.in
// * (see that file for the relevant copyright).
// */
//
///* mouse interface */
//
//#if NCURSES_MOUSE_VERSION > 1
//#define NCURSES_MOUSE_MASK(b,m) ((m) << (((b) - 1) * 5))
//#else
//#define NCURSES_MOUSE_MASK(b,m) ((m) << (((b) - 1) * 6))
//#endif
//
//#define	NCURSES_BUTTON_RELEASED	001L
//#define	NCURSES_BUTTON_PRESSED	002L
//#define	NCURSES_BUTTON_CLICKED	004L
//#define	NCURSES_DOUBLE_CLICKED	010L
//#define	NCURSES_TRIPLE_CLICKED	020L
//#define	NCURSES_RESERVED_EVENT	040L
//
///* event masks */
//#define	BUTTON1_RELEASED	NCURSES_MOUSE_MASK(1, NCURSES_BUTTON_RELEASED)
//#define	BUTTON1_PRESSED		NCURSES_MOUSE_MASK(1, NCURSES_BUTTON_PRESSED)
//#define	BUTTON1_CLICKED		NCURSES_MOUSE_MASK(1, NCURSES_BUTTON_CLICKED)
//#define	BUTTON1_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(1, NCURSES_DOUBLE_CLICKED)
//#define	BUTTON1_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(1, NCURSES_TRIPLE_CLICKED)
//
//#define	BUTTON2_RELEASED	NCURSES_MOUSE_MASK(2, NCURSES_BUTTON_RELEASED)
//#define	BUTTON2_PRESSED		NCURSES_MOUSE_MASK(2, NCURSES_BUTTON_PRESSED)
//#define	BUTTON2_CLICKED		NCURSES_MOUSE_MASK(2, NCURSES_BUTTON_CLICKED)
//#define	BUTTON2_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(2, NCURSES_DOUBLE_CLICKED)
//#define	BUTTON2_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(2, NCURSES_TRIPLE_CLICKED)
//
//#define	BUTTON3_RELEASED	NCURSES_MOUSE_MASK(3, NCURSES_BUTTON_RELEASED)
//#define	BUTTON3_PRESSED		NCURSES_MOUSE_MASK(3, NCURSES_BUTTON_PRESSED)
//#define	BUTTON3_CLICKED		NCURSES_MOUSE_MASK(3, NCURSES_BUTTON_CLICKED)
//#define	BUTTON3_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(3, NCURSES_DOUBLE_CLICKED)
//#define	BUTTON3_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(3, NCURSES_TRIPLE_CLICKED)
//
//#define	BUTTON4_RELEASED	NCURSES_MOUSE_MASK(4, NCURSES_BUTTON_RELEASED)
//#define	BUTTON4_PRESSED		NCURSES_MOUSE_MASK(4, NCURSES_BUTTON_PRESSED)
//#define	BUTTON4_CLICKED		NCURSES_MOUSE_MASK(4, NCURSES_BUTTON_CLICKED)
//#define	BUTTON4_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(4, NCURSES_DOUBLE_CLICKED)
//#define	BUTTON4_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(4, NCURSES_TRIPLE_CLICKED)
//
///*
// * In 32 bits the version-1 scheme does not provide enough space for a 5th
// * button, unless we choose to change the ABI by omitting the reserved-events.
// */
//#if NCURSES_MOUSE_VERSION > 1
//
//#define	BUTTON5_RELEASED	NCURSES_MOUSE_MASK(5, NCURSES_BUTTON_RELEASED)
//#define	BUTTON5_PRESSED		NCURSES_MOUSE_MASK(5, NCURSES_BUTTON_PRESSED)
//#define	BUTTON5_CLICKED		NCURSES_MOUSE_MASK(5, NCURSES_BUTTON_CLICKED)
//#define	BUTTON5_DOUBLE_CLICKED	NCURSES_MOUSE_MASK(5, NCURSES_DOUBLE_CLICKED)
//#define	BUTTON5_TRIPLE_CLICKED	NCURSES_MOUSE_MASK(5, NCURSES_TRIPLE_CLICKED)
//
//#define	BUTTON_CTRL		NCURSES_MOUSE_MASK(6, 0001L)
//#define	BUTTON_SHIFT		NCURSES_MOUSE_MASK(6, 0002L)
//#define	BUTTON_ALT		NCURSES_MOUSE_MASK(6, 0004L)
//#define	REPORT_MOUSE_POSITION	NCURSES_MOUSE_MASK(6, 0010L)
//
//#else
//
//#define	BUTTON1_RESERVED_EVENT	NCURSES_MOUSE_MASK(1, NCURSES_RESERVED_EVENT)
//#define	BUTTON2_RESERVED_EVENT	NCURSES_MOUSE_MASK(2, NCURSES_RESERVED_EVENT)
//#define	BUTTON3_RESERVED_EVENT	NCURSES_MOUSE_MASK(3, NCURSES_RESERVED_EVENT)
//#define	BUTTON4_RESERVED_EVENT	NCURSES_MOUSE_MASK(4, NCURSES_RESERVED_EVENT)
//
//#define	BUTTON_CTRL		NCURSES_MOUSE_MASK(5, 0001L)
//#define	BUTTON_SHIFT		NCURSES_MOUSE_MASK(5, 0002L)
//#define	BUTTON_ALT		NCURSES_MOUSE_MASK(5, 0004L)
//#define	REPORT_MOUSE_POSITION	NCURSES_MOUSE_MASK(5, 0010L)
//
//#endif
//
//#define	ALL_MOUSE_EVENTS	(REPORT_MOUSE_POSITION - 1)
//
///* macros to extract single event-bits from masks */
//#define	BUTTON_RELEASE(e, x)		((e) & NCURSES_MOUSE_MASK(x, 001))
//#define	BUTTON_PRESS(e, x)		((e) & NCURSES_MOUSE_MASK(x, 002))
//#define	BUTTON_CLICK(e, x)		((e) & NCURSES_MOUSE_MASK(x, 004))
//#define	BUTTON_DOUBLE_CLICK(e, x)	((e) & NCURSES_MOUSE_MASK(x, 010))
//#define	BUTTON_TRIPLE_CLICK(e, x)	((e) & NCURSES_MOUSE_MASK(x, 020))
//#define	BUTTON_RESERVED_EVENT(e, x)	((e) & NCURSES_MOUSE_MASK(x, 040))
//
//typedef struct
//{
//    short id;		/* ID to distinguish multiple devices */
//    int x, y, z;	/* event coordinates (character-cell) */
//    mmask_t bstate;	/* button state bits */
//}
//MEVENT;
//
//extern NCURSES_EXPORT(bool)    has_mouse(void);
//extern NCURSES_EXPORT(int)     getmouse (MEVENT *);
//extern NCURSES_EXPORT(int)     ungetmouse (MEVENT *);
//extern NCURSES_EXPORT(mmask_t) mousemask (mmask_t, mmask_t *);
//extern NCURSES_EXPORT(bool)    wenclose (const WINDOW *, int, int);
//extern NCURSES_EXPORT(int)     mouseinterval (int);
//extern NCURSES_EXPORT(bool)    wmouse_trafo (const WINDOW*, int*, int*, bool);
//extern NCURSES_EXPORT(bool)    mouse_trafo (int*, int*, bool);              /* generated */
//
//#if NCURSES_SP_FUNCS
//extern NCURSES_EXPORT(bool)    NCURSES_SP_NAME(has_mouse) (SCREEN*);
//extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(getmouse) (SCREEN*, MEVENT *);
//extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(ungetmouse) (SCREEN*,MEVENT *);
//extern NCURSES_EXPORT(mmask_t) NCURSES_SP_NAME(mousemask) (SCREEN*, mmask_t, mmask_t *);
//extern NCURSES_EXPORT(int)     NCURSES_SP_NAME(mouseinterval) (SCREEN*, int);
//#endif
//
//#ifndef NCURSES_NOMACROS
//#define mouse_trafo(y,x,to_screen) wmouse_trafo(stdscr,y,x,to_screen)
//#endif
//
///* other non-XSI functions */
//
//extern NCURSES_EXPORT(int) mcprint (char *, int);	/* direct data to printer */
//extern NCURSES_EXPORT(int) has_key (int);		/* do we have given key? */
//
//#if NCURSES_SP_FUNCS
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(has_key) (SCREEN*, int);    /* do we have given key? */
//extern NCURSES_EXPORT(int) NCURSES_SP_NAME(mcprint) (SCREEN*, char *, int);	/* direct data to printer */
//#endif
//
///* Debugging : use with libncurses_g.a */
//
//extern NCURSES_EXPORT(void) _tracef (const char *, ...) GCC_PRINTFLIKE(1,2);
//extern NCURSES_EXPORT(char *) _traceattr (attr_t);
//extern NCURSES_EXPORT(char *) _traceattr2 (int, chtype);
//extern NCURSES_EXPORT(char *) _tracechar (int);
//extern NCURSES_EXPORT(char *) _tracechtype (chtype);
//extern NCURSES_EXPORT(char *) _tracechtype2 (int, chtype);
//#if NCURSES_WIDECHAR
//#define _tracech_t		_tracecchar_t
//extern NCURSES_EXPORT(char *) _tracecchar_t (const cchar_t *);
//#define _tracech_t2		_tracecchar_t2
//extern NCURSES_EXPORT(char *) _tracecchar_t2 (int, const cchar_t *);
//#else
//#define _tracech_t		_tracechtype
//#define _tracech_t2		_tracechtype2
//#endif
//extern NCURSES_EXPORT(void) trace (const unsigned int);
//
///* trace masks */
//#define TRACE_DISABLE	0x0000	/* turn off tracing */
//#define TRACE_TIMES	0x0001	/* trace user and system times of updates */
//#define TRACE_TPUTS	0x0002	/* trace tputs calls */
//#define TRACE_UPDATE	0x0004	/* trace update actions, old & new screens */
//#define TRACE_MOVE	0x0008	/* trace cursor moves and scrolls */
//#define TRACE_CHARPUT	0x0010	/* trace all character outputs */
//#define TRACE_ORDINARY	0x001F	/* trace all update actions */
//#define TRACE_CALLS	0x0020	/* trace all curses calls */
//#define TRACE_VIRTPUT	0x0040	/* trace virtual character puts */
//#define TRACE_IEVENT	0x0080	/* trace low-level input processing */
//#define TRACE_BITS	0x0100	/* trace state of TTY control bits */
//#define TRACE_ICALLS	0x0200	/* trace internal/nested calls */
//#define TRACE_CCALLS	0x0400	/* trace per-character calls */
//#define TRACE_DATABASE	0x0800	/* trace read/write of terminfo/termcap data */
//#define TRACE_ATTRS	0x1000	/* trace attribute updates */
//
//#define TRACE_SHIFT	13	/* number of bits in the trace masks */
//#define TRACE_MAXIMUM	((1 << TRACE_SHIFT) - 1) /* maximum trace level */
//
//#if defined(TRACE) || defined(NCURSES_TEST)
//extern NCURSES_EXPORT_VAR(int) _nc_optimize_enable;		/* enable optimizations */
//extern NCURSES_EXPORT(const char *) _nc_visbuf (const char *);
//#define OPTIMIZE_MVCUR		0x01	/* cursor movement optimization */
//#define OPTIMIZE_HASHMAP	0x02	/* diff hashing to detect scrolls */
//#define OPTIMIZE_SCROLL		0x04	/* scroll optimization */
//#define OPTIMIZE_ALL		0xff	/* enable all optimizations (dflt) */
//#endif
//
//#include <unctrl.h>
//
//#ifdef __cplusplus
//
//#ifndef NCURSES_NOMACROS
//
///* these names conflict with STL */
//#undef box
//#undef clear
//#undef erase
//#undef move
//#undef refresh
//
//#endif /* NCURSES_NOMACROS */
//
//}
#endif
