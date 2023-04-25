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
/* 04/18/2023:                                                                                */
/* Completed speaker placement measurement for Cardas method.                                 */
/* Cleaned up file write method to append to txt file.                                        */
/* Added in error checking to handle invalid data for width/length for speaker placement.     */
/*--------------------------------------------------------------------------------------------*/
/* 04/25/2023:                                                                                */
/* Revised frequency computation into a pass-by-reference function.                           */
/* Cleaned up comments and debug statements.                                                  */
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

string file_nodal = "";

string nodal, units;

// index, frequency display field formatting
string str1, str2;
string padstr;

// Integer values used to determining nodal values
int p, q, r;

// Loop counter
int i, j, k;

// Entry error check
int bad_val = 0;

int axil, tangnt, obliq;
int calc;
int max = 100;
int result;
int slength;
int node;
int indx;
double height;
double width;
double length;
double volume;

double frequency;
double axial;
double tangent;
double oblique;
double sqr;
double conversion;

/*-------------------------------------------------------------*/
/*               Structures and Pointers                       */
/*-------------------------------------------------------------*/

// Define the array structure here
typedef struct Roomnode
{
	float frequency;
	string frstr;
	int axl, tgn, obl;
	string nodal;
} NodeCnt;

// This is used to define the wait time to display the splash screen
unsigned int sleep(unsigned int seconds);

/*-------------------------------------------------------------*/
/*                      Function Calls                         */
/*-------------------------------------------------------------*/
void Nodal_compute(Roomnode *NodeCnt, int loop)
{
	int i, j, k;

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
}
/*-------------------------------------------------------------*/
void Nodal_display(Roomnode NodeCnt[], int lmt, string node_file, int lgth, int hght, int wdth, float conversion)
{
	int i = 0;

	string nodal;
	string str1, str2; // index, frequency display field formatting
	string padstr;

	int result;
	int slength;
	int node;
	int room_vol;

	float seating;
	float seperation;
	float diagonal;
	float ctr_pt;
	float vert_line;
	float sep;
	float base_pt;
	const float GR = 1.62;
	float midpoint;
	
	room_vol = (lgth * hght * wdth)/conversion;

	ofstream outfile(node_file, ios::app);
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

	//outfile.close();
}

/*-------------------------------------------------------------*/
void Nodal_entry(double &length, double &height, double &width, double &conversion, string &node_file, string &units)
{
	int result;

	/*-----------------------------------------------------------------------*/
	/* Prompt user for Length, Width and Height of a given room              */
	/*-----------------------------------------------------------------------*/

	cout << "(M)etric or (I)mperial units of measure      : ";
	cin >> units;

	result = units.compare("I");

    cout << "Conversion measurement is: " << units << endl;
	cout << "Conversion factor is: " << result << endl;

	// Convert between Metric and Imperial (feet)
	if ( result > 0) {
		//&*conversion = 3.28084;
		conversion = 3.28084;
	} else {
		//&*conversion = 1;
		conversion = 1.0;
	}

	cout << "Specify the room length(L) in feet or meters: ";
	cin >> length;
	//scanf("%f", &*length);

	length = conversion*(abs(length));

	cout << "Specify the room height(H): ";
	cin >> height;
	//scanf("%f", &*height);

	height = conversion*(abs(height));

	cout << "Specify the room width(W): ";
	cin >> width;
	//scanf("%f", &*width);

	width = conversion*(abs(width));

	cout << "Save to file: ";
	cin >> node_file;

	//strcat(node_file, ".txt");
	node_file = node_file + ".txt";

	cout << "You have entered the following values:" << endl;
	cout << "Length :" << length << endl;
	cout << "Height :" << height << endl;
	cout << "Width  :" << width << endl;

	cout << "Destination file: " << file_nodal << endl;

}
/*-------------------------------------------------------------*/
void Nodal_sort(Roomnode NodeCnt[], int lmt)
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
void Nodal_speaker(float width, float length, string node_file, float conversion)
{
	int flg_wide = 0;
	int flg_seat = 0;

	float seating;
	float seperation;
	float diagonal;
	float ctr_pt;
	float vert_line;
	float sep;
	float base_pt;
	const float GR = 1.62;
	float midpoint;

	char unit[8];
	
	ofstream outfile(node_file, ios::app);

	seating = 0.0;
	seperation = 0.0;

	// The approached used below is 100% kluge, but will be used for now.
	if (conversion != 1) {
		cout << "Metric conversion:" << endl;
		strcpy(unit, "meters");
	} else {
		cout << "Imperial conversion:" << endl;
		strcpy(unit, "feet");
	}

	while  ( !flg_seat ){
		cout << "Enter Seating position from FrontWall (FW): ";
		cin >> seating;
	
		if (seating <= 0) {
			seating = conversion * abs(seating);
		}
	
		if (length <= seating) {
			cout << "the seating postion is deeper then the room length" << endl;
			cout << "Program error - re-enter data" << endl;
		} else {
			flg_seat = 1;
		}
	}
	flg_seat = 0;

	while  ( !flg_wide ){
		cout << "Enter speaker seperation                  : ";
   		cin >> seperation;
	
		if (seperation <= 0) {
			seperation = conversion * abs(seperation);
		}
	
		if (width <= seperation) {
			cout << "the seating postion is wider then the room width" << endl;
			cout << "Program error - re-enter data" << endl;
		} else {
			flg_wide = 1;
		}
	}
	flg_wide = 0;
	
	cout << "DBG - conversion value: " << conversion << endl;

	if (length > width) {
		cout << "This is a normal length-oriented room" << endl;
		cout << "Length is: " << (length/conversion) << endl;
		cout << "Width is: " << (width/conversion)<< endl;
	} else if (length < width) {
		cout << "This is a abnormal width-oriented room" << endl;
		cout << "Length is: " << (length/conversion) << endl;
		cout << "Width is: " << (width/conversion)<< endl;
	} else {
		// Square room
		cout << "This is a square room" << endl;
		cout << "Length is: " << (length/conversion) << endl;
		cout << "Width is: " << (width/conversion)<< endl;
	}

	sep = (seperation/2.0) * GR;
	vert_line = seating - sep;
	base_pt = seating - vert_line;

	cout << "---------------------------------------" << endl;
	cout << "- Ideal experimental speaker position: " << endl;
	cout << "- Speaker width - " << seperation << " " << unit << endl;
	cout << "- Speaker position from FW - " << base_pt << " " << unit << endl;
	cout << "- Seating position from FW - " << seating << " " << unit << endl;
	cout << "---------------------------------------" << endl;

	outfile << "+--------------------------------------+" << endl;
	outfile << "- Ideal experimental speaker position: " << endl;
	outfile << "- Speaker width - " << seperation << " " << unit << endl;
	outfile << "- Speaker position from FW - " << base_pt << " " << unit << endl;
	outfile << "+--------------------------------------+" << endl;
	
	//outfile.close();
}
/*-------------------------------------------------------------*/
/*                       MAIN PROGRAM                          */
/*-------------------------------------------------------------*/
int main()
{

	Roomnode NodeCnt[250];

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

	ofstream outfile(file_nodal);

	Nodal_entry(length, height, width, conversion, file_nodal, units);

	Nodal_compute(NodeCnt, loop);

	Nodal_sort(NodeCnt, indx);

	Nodal_display(NodeCnt, indx, file_nodal, length, height, width, conversion);

	Nodal_speaker(width, length, file_nodal, conversion);

	outfile.close();

    return 0;
}
