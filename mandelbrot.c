#include "ncurses.h"
#include <complex.h>
#include <math.h>
#include <stdbool.h>

const int iterations = 50;
const int size = 100;
const int sizebytwo = size/2;
const double invertedsize = 1.0/size;
const int maxsize = 5;
const int toasc = iterations*30/20;

void genMandelbrot() {
	bool returned;
	double complex sequence[iterations];
	double complex currentval;
	unsigned char mandelbrot[size][size];
	sequence[0] = 0;
	for(int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++) {
			returned = false;
			for(int i = 1; (i < iterations) && !returned; i++) {
				currentval = 3*((x-sizebytwo)*invertedsize + (y-sizebytwo)*invertedsize*I) - 0.5;
				sequence[i] = cpow(sequence[i-1], 2) + currentval;
				mandelbrot[x][y] = i;
				if(fabs(cabs(sequence[i]))>maxsize) {
					returned = true;
					break;
				}
			}
			addch(mandelbrot[x][y]+toasc);
			addch(' ');
		}
		addch('\n');
	}
	refresh();
}

int main(int argc, char *argv[])
{
	initscr();
	genMandelbrot();
	getch();
	endwin();
	return 0;
}
