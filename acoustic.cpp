/*--------------------------------------------------------------------------------------------*/
/* nodal.cpp - A utility designed to calculate the nodal frequencies in a given room to       */
/* assist in the determineation of room characteristics.                                      */
/*--------------------------------------------------------------------------------------------*/
/* A command-line interface (CLI) to determine nodal frequencies for a given room based on    */
/* the user supplied height, width, length of a given room. The primary, oblique and          */
/* tangential frequencies will be displayd in a column format. Nodal frequences will be       */
/* marked by a '*'                                                                            */
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */
/*--------------------------------------------------------------------------------------------*/
/* 11/21/2021:                                                                                */
/* Define splash screen and CLI                                                               */
/*--------------------------------------------------------------------------------------------*/

#include <iostream>
#include <cmath>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int height;
int width;
int length;

unsigned int sleep(unsigned int seconds);

int main(){


    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "|                                                                     |" << endl;
    cout << "| Nodal Acoustic Determination Utility:                               |" << endl;
    cout << "| An application to determine the Axial, Tangential and Oblique       |" << endl;
    cout << "| frequency nodes for any given room given the Length (Axial),        |" << endl;
    cout << "| Height (Tangential)and Width (Oblique) dimensions of a given room.  |" << endl;
    cout << "|                                                                     |" << endl;
    cout << "+---------------------------------------------------------------------+" << endl;
    
    sleep(5);
    system("clear");

    /*-----------------------------------------------------------------------*/
    /* Prompt user for Length, Width and Height of a given room              */
    /*-----------------------------------------------------------------------*/

    cout << "Specify the room length(L):";
    cin >> length;

    cout << "Specify the room height(H):";
    cin >> height;

    cout << "Specify the room width(W):";
    cin >> width;
    
    cout << "You have entered the following values:" << endl;
    cout << "Length :" << length << endl;
    cout << "Height :" << height << endl;
    cout << "Width  :" << width << endl;
    return 0;
}
