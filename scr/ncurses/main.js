/**
 * @file scr/a.js
 * @author Ockert van Schalkwyk
 * @brief main function
 * @version 0.1
 */
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function ncurses_test(){
	log("info:jstestncurses:start");
	var win=initscr();
	raw();
	cbreak();
	noecho();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	curs_set(0);
	{//newwin and box test
		mvaddstr(0,0,"[newwintest]");
		var height=4;
		var width=4;
		var startx=4;
		var starty=4;
		var win2=newwin(height,width,startx,starty);
		box(win2,0,0);
		wborder(
			win2,
			'.'.charCodeAt(0),
			'.'.charCodeAt(0),
			'.'.charCodeAt(0),
			'.'.charCodeAt(0),
			'.'.charCodeAt(0),
			'.'.charCodeAt(0),
			'.'.charCodeAt(0),
			'.'.charCodeAt(0)
		);
		wrefresh(win2);//.charCodeAt(0)
		refresh();//.charCodeAt(0)
		getch();
		delwin(win2);
	}
	{//getstr test
		mvaddstr(0,0,"[getstr test]Enter value and press enter");
		var val=getstr();
		mvaddstr(1,0,"value:"+val);
		getch();
	}
	{//clear test
		wclear(win);
		clear();
	}
	{//addstr test
		addstr("[addstr]");
		mvaddstr(1,1,"[mvaddstr]");
		waddstr(win,"[waddstr]");
		mvwaddstr(win,2,2,"[mvwaddstr]");
		getch();
		wclear(win);
	}
	{//getmaxx getmaxy test
		var x=getmaxx(win);
		var y=getmaxy(win);
		mvprintw(0,0,"max x:"+x);
		mvprintw(1,0,"max y:"+y);
		refresh();
		getch();
		wclear(win);
	}
	{//getcurx getcury test
		var x=getcurx(win);
		var y=getcury(win);
		mvprintw(0,0,"cur x:"+x);
		mvprintw(1,0,"cur y:"+y);
		refresh();
		getch();
		wclear(win);
	}

	{//test addch
		for(var i=0;i<8;i++){
			addch('a'.charCodeAt(0)|A_BOLD|A_UNDERLINE);
			refresh();
		}
		getch();
		wclear(win);
	}
	{//test mvaddch
		for(var i=0;i<8;i++){
			mvaddch(i,i,'x'.charCodeAt(0));
			refresh();
		}
		getch();
		wclear(win);
	}

	{//input loop demo
		mvprintw(0,0,"Enter key [q to quit]:");//Math.random());
		refresh();
		var ch=null;
		while(ch!='q'){
			var chcod=getch();
			var ch=String.fromCharCode(chcod);
			mvprintw(1,0,"Character entered: "+ch);
			refresh();
		}
	}
	{
		clear();
		var i=0;
		var width=getmaxx(win);
		var height=getmaxy(win);
		for(var i=0;i<8192*16;i++){
			//printw("hello");
			var x=Math.floor(Math.random()*width)+1
			var y=Math.floor(Math.random()*height)+1
			//mvprintw(x,y,Math.random()<0.5?".":" ");
			attron(COLOR_PAIR(i%4+1));
			mvaddch(y,x,(Math.random()<0.5?".":" ").charCodeAt(0));
			attron(COLOR_PAIR(1));
			mvprintw(0,0,"I:"+i);
			refresh();
		}
	}
	//wprintw(stdscr,"lorem");//err
	a=getch();
	log(a);
	endwin();
	log("info:jstestncurses:end");

	return 0;
}
function ncurses_test_(){
}

//--------------------------------------------------------------------------------
