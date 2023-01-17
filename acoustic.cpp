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
/* 02/20/2022:                                                                                */
/* define structure for linked list to better display data.                                   */
/*--------------------------------------------------------------------------------------------*/
/* 01/04/2023:                                                                                */
/* cleanup code of unused/redundant variables.                                                */
/* Create intermediate display format and cleanup display.                                    */
/* Begin work on insertion_sort() algotorithm.                                                */
/*--------------------------------------------------------------------------------------------*/
/* 01/12/2023:                                                                                */
/* Completed sort routine. Cleaned up code. Load into github.                                 */
/*--------------------------------------------------------------------------------------------*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

const int c =  1130;
const int loop = 5;

char file_nodal[64];

string nodal;

// index, frequency display field formatting
string str1, str2;
string padstr;

// Integer values used to determining nodal values
int p, q, r;

// Loop counter
int i, j, k;

int axil, tangnt, obliq;
int calc;
int max = 100;
int result;
int slength;
int node;
int indx;
float height;
float width;
float length;
float volume;

float frequency;
float axial;
float tangent;
float oblique;
float sqr;
/*-------------------------------------------------------------*/
/*               Structures and Pointers                       */
/*-------------------------------------------------------------*/


/*-------------------------------------------------------------*/

// Define the array structure here
struct Roomnode
{
	float frequency;
	string frstr;
	int axl, tgn, obl;
	string nodal;
};

// This is used to define the wait time to display the splash screen
unsigned int sleep(unsigned int seconds);

/*-------------------------------------------------------------*/
/*                      Function Calls                         */
/*-------------------------------------------------------------*/
void Nodal_display(struct Roomnode NodeCnt[], int lmt, string node_file, int lgth, int hght, int wdth)
{
	int i = 0;

	string output = "temp_file.txt";
	string nodal;
	string str1, str2; // index, frequency display field formatting
	string padstr;
	int result;
	int slength;
	int node;
	int room_vol;

	room_vol = lgth * hght * wdth;

	ofstream outfile(node_file);
    outfile << "Length :" << lgth << endl;
    outfile << "Height :" << hght << endl;
    outfile << "Width  :" << wdth << endl;
	outfile << "Room Volume: " << room_vol << endl;
	outfile << "Destination file: " << node_file << endl;
	outfile << "+--------+---------+---+---+---+------------+" << endl;
	outfile << "|  index |   Freq  | I | J | K |    node    |" << endl;
	outfile << "+--------+---------+---+---+---+------------+" << endl;

	cout << "+--------+---------+---+---+---+------------+" << endl;
	cout << "|  index |   Freq  | I | J | K |    node    |" << endl;
	cout << "+--------+---------+---+---+---+------------+" << endl;
	for ( i = 0; i < lmt; ++i) {

		padstr = to_string(i);
		slength= padstr.length();
		
		// padding the field to print format cleanly
		if (slength == 3) {
			str1 = "  ";
			str1 += padstr;
		} else if (slength == 2) {
			str1 = "   ";
			str1 += padstr;
		} else if (slength == 1) {
			str1 = "    ";
			str1 += padstr;
		}

		NodeCnt[indx].frstr= to_string(NodeCnt[indx].frequency);
		slength = NodeCnt[i].frstr.length();

		// Padding the field to print cleanly
		if (slength == 3) {
			str2 = "    ";
			str2 += NodeCnt[i].frstr;
		} else if (slength ==2){
			str2 = "     ";
			str2 += NodeCnt[i].frstr;
		}

		cout << "|  " << str1 << " | " <<  str2 << " | " << NodeCnt[i].axl << " | " << NodeCnt[i].tgn << " | " << NodeCnt[i].obl << " | " <<  NodeCnt[i].nodal << " | " << endl;

		outfile << "|  " << str1 << " | " <<  str2 << " | " << NodeCnt[i].axl << " | " << NodeCnt[i].tgn << " | " << NodeCnt[i].obl << " | " <<  NodeCnt[i].nodal << " | " << endl;
	}

	cout << "+--------+---------+---+---+---+------------+" << endl;
	outfile << "+--------+---------+---+---+---+------------+" << endl;

	outfile.close();
}

/*-------------------------------------------------------------*/
void Sort_Nodal(struct Roomnode NodeCnt[], int lmt)
{
	Roomnode temp;
	int i, j;
	int cntr;
	int iteration;

	cout << "Node Sort in asscending order" << endl;

	for (i = 0; i < lmt; i++) {
		for (j =  i + 1; j < lmt; j++) {
			if (NodeCnt[i].frequency > NodeCnt[j].frequency) {
				temp = NodeCnt[i];
				NodeCnt[i] = NodeCnt[j];
				NodeCnt[j] = temp;
			}
		}
	}
}
/*-------------------------------------------------------------*/
/*                       MAIN PROGRAM                          */
/*-------------------------------------------------------------*/
int main()
{

	struct Roomnode NodeCnt[250];

    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "|                                                                     |" << endl;
    cout << "| Nodal Acoustic Determination Utility:                               |" << endl;
    cout << "| An application to determine the Axial, Tangential and Oblique       |" << endl;
    cout << "| frequency nodes for any given room given the Length (Axial),        |" << endl;
    cout << "| Height (Tangential)and Width (Oblique) dimensions of a given room.  |" << endl;
    cout << "|                                                                     |" << endl;
    cout << "+---------------------------------------------------------------------+" << endl;
    
    sleep(3);
    system("clear");

    /*-----------------------------------------------------------------------*/
    /* Prompt user for Length, Width and Height of a given room              */
    /*-----------------------------------------------------------------------*/

    cout << "Specify the room length(L): ";
    cin >> length;

    cout << "Specify the room height(H): ";
    cin >> height;

    cout << "Specify the room width(W): ";
    cin >> width;
    
	cout << "Save to file: ";
	cin >> file_nodal;

	strcat(file_nodal, ".txt");

	volume = length * height * width;

    cout << "You have entered the following values:" << endl;
    cout << "Length :" << length << endl;
    cout << "Height :" << height << endl;
    cout << "Width  :" << width << endl;
	cout << "Destination file: " << file_nodal << endl;

	/*-----------------------------------------------------------------------*/
	/*            Determine the frequence values for a given node            */
	/*-----------------------------------------------------------------------*/

	for (i = 0; i <= loop; i++){
		for (j = 0; j <= loop; j++) {
			for (k = 0; k <= loop; k++){
				frequency = c/2;
				calc = 0.0;
				node = 0;
				axil = 0;
				tangnt = 0;
				obliq = 0;

				// node is used to determine if this is a nodal 
				// point and the type of node for a given frequency.

				if ( i == 0 ) {
					axial = 000.000;
					axil = 0;
				} else {
					axial = (pow(i, 2)/pow(length, 2));
					axil = 1;
				}
				NodeCnt[indx].axl = i;

				if ( j == 0 ) {
					tangent = 000.000;
					tangnt = 0;
				} else {
					tangent = (pow(j, 2)/pow(width, 2));
					tangnt = 3;
				}
				NodeCnt[indx].tgn = j;

				if ( k == 0 ) {
					oblique = 000.000;
					obliq = 0;
				} else {
					oblique = (pow(k, 2)/pow(height, 2));
					obliq = 5;
				}
				NodeCnt[indx].obl = k;

				if ((i == 0) && (j == 0) && (k ==0 )) {
					axial = (pow(1, 2)/pow(length, 2));
				}

				node = axil + tangnt + obliq;

				if (node == 1) {
					NodeCnt[indx].nodal = "     axial";
				} else if (node == 3) {
					NodeCnt[indx].nodal = "tangential";
				} else if (node == 5) {
					NodeCnt[indx].nodal = "   oblique";
				} else {
					NodeCnt[indx].nodal = "----------";
					node = node;
				}

				sqr = sqrt(axial + tangent + oblique);

				calc = frequency * sqr;

				NodeCnt[indx].frequency = calc;

				// casting to integer to improve display, then finding string length
				// to determine the width to fill the display cleanly.
				padstr = to_string(indx);
				slength= padstr.length();

				// padding the field to print format cleanly
				if (slength == 3) {
					str1 = "  ";
					str1 += padstr;
				} else if (slength == 2) {
					str1 = "   ";
					str1 += padstr;
				} else if (slength == 1) {
					str1 = "    ";
					str1 += padstr;
				}

				NodeCnt[indx].frstr= to_string(calc);
				slength = NodeCnt[indx].frstr.length();

				// Padding the field to print cleanly
				if (slength == 3) {
					str2 = "    ";
					str2 += NodeCnt[indx].frstr;
				} else if (slength ==2){
					str2 = "     ";
					str2 += NodeCnt[indx].frstr;
				}

				indx++;
			}
		}
	}

	Sort_Nodal(NodeCnt, indx);

	Nodal_display(NodeCnt, indx, file_nodal, length, height, width);

    return 0;
}
