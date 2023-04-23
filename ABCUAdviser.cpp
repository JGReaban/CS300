// ABCUAdviser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//  Author: Jeremy Reaban
//  Date:   April 15th, 2023
//  Version: 1.0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;




// Define a Structure to Hold Courses
struct Course {
	string courseId; // unique identifier
	string title;
	string preReq1;
	string preReq2;
	
};

/* Function Declarations
*
* Function Bodies Appear After Main
* Normally Would Put them in Separate .cpp File
* But I wanted to keep things simple
*/
string nCharString(size_t n, char c);
void printMenu(int menuWidth, vector<string> menuItems, int padding);
unsigned int getMenuChoice(unsigned int maxChoice);
void displayCourse(Course course);
void displayCourses(vector<Course> courses);
vector<Course> loadCourses(string fname);
int partition(vector<Course>& courses, int begin, int end);
void quickSort(vector<Course>& courses, int begin, int end);
void searchCourses(string courseName,vector<Course> courses);





int main()
{

	// Declare Variables
	// Menu Variables
	unsigned int menuChoice;
	int leftMenuPad = 25;
	int rightMenuPad = 16;
	vector<string> menuItems = { "Load Data Structure", "Print Course List", "Print Course", "Quit" };

	// Define Vector to hold Courses
	vector<Course> courses;
	// String to hold Filename
	string fname;
	// String to hold courseName
	string courseName;

	// Print Menu
	printMenu(leftMenuPad, menuItems, rightMenuPad);
	// Get Choice From Menu
	menuChoice = getMenuChoice(4);

	// Process Choice
	while (menuChoice != 4) {
		switch (menuChoice) {

		// Load Data Structure
		case 1:

			fname = "ABCU.txt";
			cout << "\n Please enter the file name: ";
			cin >> fname;
			courses = loadCourses(fname);
			break;

		// Print Sorted List of Courses
		case 2:
			quickSort(courses, 0, courses.size() - 1);
			displayCourses(courses);
			break;
		// Print Course
		case 3:
			//courseName = "MATH201";
			cout << "\nPlease Enter Valid Course ID: ";
			cin >> courseName;
			searchCourses(courseName, courses);
			break;
		}

		// Print Menu
		printMenu(leftMenuPad, menuItems, rightMenuPad);
		// Get Choice From Menu
		menuChoice = getMenuChoice(4);


	}



    cout << "Goodbye!\n";
	


	
	return 0;
}


/**
 * Creates a string of a certain amount of a certain character
 *
 * @param n number of characters in string
 * @param c character to use to make string
 *
 * @return string of n amount of c
 */
string nCharString(size_t n, char c) {
	string tempString = "";
	for (int i = 0; i < n; ++i) {
		tempString = tempString + c;
	}
	return tempString;
}

/**
 * Prints a menu
 *
 * @param menuWidth - how wide (in characters) should the menu be
 * @param menuItems - string vector with a list of menu items to display
 * @param padding - optional, how many characters should the menu indent
 */
void printMenu(int menuWidth, vector<string> menuItems, int padding = 0) {
	cout << endl;
	cout << nCharString(padding, ' ') << nCharString(menuWidth, '*') << endl;
	for (int i = 0; i < menuItems.size(); i++) {

		cout << nCharString(padding, ' ') << "*" << i + 1 << ") " << menuItems.at(i) << nCharString(menuWidth - 5 - menuItems.at(i).size(), ' ') << "*" << endl;
	}
	cout << nCharString(padding, ' ') << nCharString(menuWidth, '*') << endl;
	cout << endl;
}

/**
 * Gets menu choice 1 through maxChoice, inclusive
 *
 * @param maxChoice, maximum choice index, a number between 2 and 9, inclusive
 * @return the first legal choice input, could be 1 through maxChoice, inclusive
 */
unsigned int getMenuChoice(unsigned int maxChoice) {
	unsigned int tempChoice;
	cout << "Please Enter Number of Menu Selection (from 1 to " << maxChoice << ") and hit return" << endl;
	cin >> tempChoice;

	// Check to make sure an integer is entered (cin.fail() ), if a number is 0 or less, or greater than the number of options
	while (cin.fail() || tempChoice <= 0 || tempChoice > maxChoice) {
		cout << "Invalid Selection!" << endl;
		cout << "Please Enter Number of Menu Selection (from 1 to " << maxChoice << ") and hit return" << endl;
		cin.clear();                // clears error flag on cin
		cin.ignore(256, '\n');      // clears input buffer
		cin >> tempChoice;
	}

	// return the value
	return tempChoice;

}
/**
* Displays courseID, title, preReq1, and preReq2 values of course structure
* 
* @param course, a structure with  courseID, title, preReq1, and preReq2 values 
* 
*/
void displayCourse(Course course) {
	cout << course.courseId << " " << course.title << endl;
	if (course.preReq1 != "") {
		cout << "The first prequuisite is " << course.preReq1 << endl;
	}
	if (course.preReq2 != "") {
		cout << "The second prequisite is " << course.preReq2 << endl;
	}
	return;
}
/**
*  Invokes displayCourse for each member of courses vector
* 
* @param courses, a vector of course structs
*/

void displayCourses(vector<Course> courses) {
	for (int i = 0; i < courses.size(); ++i) {
		displayCourse(courses[i]);
	}
	cout << endl;
	return;
}
/**
*  Loads course data from specified CSV file into a vector of course structs
*
* @param fname  the filename for the file to load from
* @return the data loaded from file as a vector of course structs
*/


vector<Course> loadCourses(string fname) {
	vector<Course> courses;
	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file(fname, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "\n\nCould not open the file " << fname << endl;
	// 
	// i is the line # being accessed
	for (int i = 0; i < content.size(); i++)
	{
		// Create Course Object to Hold Data in
		Course course;
		// Read Data From Line
		// j is the word being accessed
		for (int j = 0; j < content[i].size(); j++)
		{
			cout << content[i][j] << " ";


			// Add Data to Course Object
			// 
			// Check if Course ID is 7 characters in length
			// Do not really know enough about course format
			// To do more thorough checking
			if (j == 0 && content[i][0].length() != 7) {
				cout << "\nInvalid Course ID" << endl;
			}
			course.courseId = content[i][0];
			course.title = content[i][1];
			// Is there a PreRequsite?
			// IF so add it to preReq1
			if (j == 2) {
				course.preReq1 = content[i][j];
				// check to see if Course ID is long enough for Prequisite 1
				if (content[i][j].length() != 7) {
					cout << "\nInvalid Course ID for Prerequsitie 1!" << endl;
				}
			}
			// Is there a second PreRequisite?
			// If so add it to preReq2
			if (j == 3) {
				course.preReq2 = content[i][j];
				// check to see if Course ID is long enough for Prequisite 1
				if (content[i][j].length() != 7) {
					cout << "\nInvalid Course ID for Prerequsitie 2!" << endl;
				}
			}



		}
		cout << "\n";
		courses.push_back(course);
	}

	return courses;
}

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Course>& courses, int begin, int end) {
	//set low and high equal to begin and end
	int midPoint;
	string Pivot;
	bool done;
	int lowIndex = begin;
	int highIndex = end;

	midPoint = begin + (end - begin) / 2;

	Pivot = courses[midPoint].courseId;
	done = false;

	while (!done) {
		// increment lowIndex when it's < Pivot
		while (courses[lowIndex].courseId < Pivot) {
			lowIndex += 1;
		}
		// decrease highIndex when its > Pivot
		while (Pivot < courses[highIndex].courseId) {
			highIndex -= 1;
		}
		if (lowIndex >= highIndex) {
			done = true;
		}
		else {
			// Swap numbers
			swap(courses[lowIndex], courses[highIndex]);
			// update lowIndex and highIndex
			lowIndex += 1;
			highIndex -= 1;
		}

	}
	// return highIndex

	return highIndex;
}
/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Course>& courses, int begin, int end) {
	//set mid equal to 0

	/* Base case: If there are 1 or zero bids to sort,
	 partition is already sorted otherwise if begin is greater
	 than or equal to end then return*/
	if (begin >= end) {
		return;
	}

	int lowEndIndex;

	lowEndIndex = partition(courses, begin, end);

	quickSort(courses, begin, lowEndIndex);
	quickSort(courses, lowEndIndex + 1, end);

	/* Partition bids into low and high such that
	 midpoint is location of last element in low */

	 // recursively sort low partition (begin to mid)

	 // recursively sort high partition (mid+1 to end)

}
void searchCourses(string courseName, vector<Course> courses) {
	for (int i = 0; i < courses.size(); ++i) {
		if (courseName == courses[i].courseId) {
			displayCourse(courses[i]);
			return;
		}
		
	}
	cout << "\n Course Not Found" << endl;
	return;
}



