#coding: UTF-8
import curses
import serial

stdscr = curses.initscr()
curses.noecho()
stdscr.nodelay(1)

out = "";
sr = serial.Serial('/dev/ttyACM0', 9600) 
while 1:
    str = sr.readline()
    stdscr.clrtoeol()
    stdscr.addstr( "> "+str.replace("\n", "" ) )
    s = stdscr.getch()
    if( s == ord(' ') ):
       stdscr.insertln()
       out = out + str
    if( s == ord('q') ): break
sr.close()

curses.echo()
curses.endwin()

print out
