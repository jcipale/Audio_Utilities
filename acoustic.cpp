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
#include <iomanip>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>


using namespace std;

char nodal[4] = "-";
char file_nodal[64];

const int c =  1130;
int height;
int width;
int length;

// Integer values used to determining nodal values
int p, q, r;

// Loop counter
int i, j, k;

float frequency;

float axial;
float tangent;
float oblique;
float sqr;

float calc;

// Define the list structure here

// This is used to define the wait time to display the splash screen
unsigned int sleep(unsigned int seconds);

int main()
{

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
    
	cout << "Save to file: ";
	cin >> file_nodal;

	strcat(file_nodal, ".txt");

    cout << "You have entered the following values:" << endl;
    cout << "Length :" << length << endl;
    cout << "Height :" << height << endl;
    cout << "Width  :" << width << endl;
	cout << "Destination file: " << file_nodal << endl;

	/*-----------------------------------------------------------------------*/
	/*            Determine the frequence values for a given node            */
	/*-----------------------------------------------------------------------*/

	p = 1;
	q = r = 0;
	frequency = c/2;
	calc = 0.0;

	ofstream outfile(file_nodal);
	
	outfile << "+--------------------------------------------------+" << endl;
	outfile << "|   Freq  |  Axial | Tangent | Oblique | I | J | K |" << endl;
	outfile << "+--------------------------------------------------+" << endl;

	for (i = 0; i <= 5; i++){
		for (j = 0; j <= 5; j++) {
			for (k = 0; k <= 5; k++){


				if ( i == 0 ) {
					axial = 000.000;
				} else {
					axial = (pow(i, 2)/pow(length, 2));
				}

				if ( j == 0 ) {
					tangent = 000.000;
				} else {
					tangent = (pow(j, 2)/pow(width, 2));
				}

				if ( k == 0 ) {
					 oblique = 000.000;
				} else {
					oblique = (pow(k, 2)/pow(height, 2));
				}

				if ((i == 0) && (j == 0) && (k ==0 )) {
					axial = (pow(1, 2)/pow(length, 2));
				}

				sqr = sqrt(axial + tangent + oblique);

				calc = frequency * sqr;

				/*cout << "| " << calc << " | " << axial << " | " << tangent << " | " << oblique << " | " << i << " | " << j << " | " << k <<  " | " << endl;
				cout << "|   ";
				printf("%4.2f", calc);
				cout << " | ";
				printf("%5.4f", axial);
				cout << "  | ";
				printf("%5.4f", tangent);
				cout << " | ";
				printf("%5.4f", oblique);
				cout << " | ";
				printf("%d", i);
				cout << "   | ";
				printf("%d", j);
				cout << "   | ";
				printf("%d", k);
				cout << "   | " << endl;
				*/
				outfile << "| " << fixed << setprecision(3) << calc << " | " << fixed << setprecision(5) << axial << " | " << fixed << setprecision(5) << tangent << " | " << fixed << setprecision(4) << oblique << " | " << i << " | " << j << " | " << k <<  " | " << endl;

			}
		}
	}
	outfile << "+--------------------------------------------------+" << endl;

	outfile.close();


    return 0;
}
