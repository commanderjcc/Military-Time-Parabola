// Name: Joshua Christensen
// Project: mtime-parabola
// File: main.cpp
// Purposes: calc elapsed time for military times, calc roots for parabola, calc intersects for a system of equation
// Date: 2/4/20

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Justify Function Definition
void justify(char direction, string str, int width, bool newLine, char fill, double num, int precision) {
    cout << resetiosflags(ios::left | ios::right) << setiosflags(ios::fixed) << setprecision(precision); //reset all of the flags
    if (num != 0) { //skip all the string stuff if the number is set, if it actually is zero then the "0.00" string we used for str will get used
        if (direction == 'r') {
            cout << setiosflags(ios::right) << setfill(fill) << setw(width) << num; //justify Right
        } else if (direction == 'c') {
            int availableSpace = width - ((int)(log10(num)+3)); //find the amount of space that is available
            if( availableSpace < 0) { //if the space for justifying is less than 0
                cout << setiosflags(ios::left) << setfill(fill) << setw(width) << num; //just output as left justify
                return;
            }
            int stringStartLength = availableSpace/2; //the width before the num
            int stringEndLength = availableSpace-stringStartLength; //the width after the num, uses subtraction to avoid rounding errors
            cout << setiosflags(ios::left) << setfill(fill) << setw(stringStartLength) << "" << num << setw(stringEndLength) << ""; //couts the num sandwiched between to pads of setw()
        } else {
            cout << setiosflags(ios::left) << setfill(fill) << setw(width) << num; //justify Left
        }
    } else if (direction == 'r') {
        cout << setiosflags(ios::right) << setfill(fill) << setw(width) << str; //justify right
    } else if (direction == 'c') {
        int availableSpace = width - str.length(); //find the amount of space that is available
        if( availableSpace < 0) { //if the space for justifying is less than 0
            cout << setiosflags(ios::left) << setfill(fill) << setw(width) << str; //just output as left justify
            return;
        }
        int stringStartLength = availableSpace/2; //the width before the num
        int stringEndLength = availableSpace-stringStartLength; //the width after the num, uses subtraction to avoid rounding errors
        cout << setiosflags(ios::left) << setfill(fill) << setw(stringStartLength) << "" << str << setw(stringEndLength) << ""; //couts the str sandwiched between to pads of setw()
    } else {
        cout << setiosflags(ios::left) << setfill(fill) << setw(width) << str; // justify left
    }

    if (newLine) {
        cout << "\n"; //if there is supposed to be a new line after the phrase, then send it out
    }

    return;
}

void mtime() {
    int h1 = 0; //store hour 1 as int
    char rawH1[3]; //char array for hour 1
    int h2 = 0; //store hour 2 as int
    char rawH2[3]; //char array for hour 2
    int m1 = 0; //store minutes 1 as int
    char rawM1[3]; //char array for min 1
    int m2 = 0; //store mintues 2 as int
    char rawM2[3]; //char array for min 2
    int hDif = 0; //store hour difference
    int mDif = 0; //store minutes difference

    //get inputs
    cout << "\nEnter the first time: ";
    cin.ignore(80,'\n'); //flush buffer
    cin.get(rawH1,3,':'); //get characters before :
    cin.ignore(1); // ignore the :
    cin.get(rawM1,3); //get characters after the :
    cin.ignore(1); //ignore the \n
    cout << "Enter the second time: ";
    cin.get(rawH2,3,':'); //get characters before :
    cin.ignore(1); //ignore the :
    cin.get(rawM2,3); //get characters after :
    cin.ignore(1); //ignore the \n

    //Convert to int from number strings
    h1 = stoi(rawH1);
    h2 = stoi(rawH2);
    m1 = stoi(rawM1);
    m2 = stoi(rawM2);

    //Calc difference
    hDif = h2 - h1; //get hour difference
    mDif = m2 - m1; //get minutes difference

    if (mDif < 0) {
        hDif--; //borrow if needed from hours
        mDif+=60; //add to minutes
    }

    if (hDif < 0) {
        hDif += 24; //add 24 if negative
    }

    cout << endl << hDif << " Hours " << mDif << " Minutes" << endl;
}

void solveImaginaryQuadratic(double a, double b, double c, bool pos) {
    double discriminant = 0;
    double root = 0;
    double imaginaryRoot = 0;

    discriminant = (b*b)-(4*a*c);

    root = (-1 * b) / (2 * a);
    imaginaryRoot = sqrt(-1 * discriminant) / (2 * a);

    if (pos) {
        cout << root << " + " << imaginaryRoot << "i";
    } else {
        cout << root << " - " << imaginaryRoot << "i";
    }
}

double solveQuadratic(double a, double b, double c, bool pos) {
    double discriminant = 0;
    double root = 0;
    double imaginaryRoot = 0;

    discriminant = (b*b)-(4*a*c);

    if (discriminant >= 0) {
        if (pos) {
            root = (sqrt(discriminant) - b) / (2 * a);
        } else {
            root = -1 * (b + sqrt(discriminant)) / (2 * a);
        }

        return root;
    } else {
        solveImaginaryQuadratic(a, b, c, pos);
    }
};

void parabola() {
    double a = 0;
    double b = 0;
    double c = 0;
    double discriminant = 0;

    char rawA[10];
    char rawB[10];
    char rawC[10];

    cout << "Enter A, B, and C:";
    cin.ignore(80,'\n');
    cin.get(rawA,10,' ');
    cin.ignore(1,' ');
    cin.get(rawB,10,' ');
    cin.ignore(1,' ');
    cin.get(rawC,10,'\n');

    a = stod(rawA);
    b = stod(rawB);
    c = stod(rawC);

    discriminant = (b*b)-(4*a*c);

    if (discriminant > 0) {

        cout << "The roots are: " << solveQuadratic(a,b,c,true) << " , " << solveQuadratic(a,b,c,false);
    } else if (discriminant < 0){
        cout << "The roots are: ";
        solveQuadratic(a,b,c,true);
        cout << " , ";
        solveQuadratic(a,b,c,false);
    } else {
        cout << "The root is: " << solveQuadratic(a,b,c,true);
    }

    cout << endl << endl;


    char rawX1[10];
    char rawY1[10];
    char rawX2[10];
    char rawY2[10];
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
    double slope = 0;
    double yIntercept = 0;
    double x1Intersect = 0;
    double y1Intersect = 0;
    double x2Intersect = 0;
    double y2Intersect = 0;

    cout << "Enter x1 and y1: ";
    cin.ignore(80,'\n');
    cin.get(rawX1,10,' ');
    cin.ignore(1,' ');
    cin.get(rawY1,10,'\n');
    cin.ignore(1,'\n');
    cout << "Enter x2 and y2: ";
    cin.get(rawX2,10, ' ');
    cin.ignore(1,' ');
    cin.get(rawY2,10, '\n');
    cin.ignore(1,'\n');

    x1 = stod(rawX1);
    x2 = stod(rawX2);
    y1 = stod(rawY1);
    y2 = stod(rawY2);

    slope = (y2-y1)/(x2-x1);
    yIntercept = y1-(slope*x1);

    cout << "\nSlope: " << slope;
    cout << "\nY-Intercept: " << yIntercept;
    cout << endl;


    discriminant = (b-slope)*(b-slope)-(4*a*(c-yIntercept));

    if (discriminant < 0) {
        cout << "No solutions";
    } else if (discriminant == 0) {
        x1Intersect = solveQuadratic(a,b-slope,c-yIntercept,false);
        y1Intersect = x1Intersect * slope + yIntercept;

        cout << "Intersection Point at: ( " << x1Intersect << " , " << y1Intersect << " )";
    } else {
        x1Intersect = solveQuadratic(a,b-slope,c-yIntercept,false);
        y1Intersect = x1Intersect * slope + yIntercept;
        x2Intersect = solveQuadratic(a,b-slope,c-yIntercept,true);
        y2Intersect = x2Intersect * slope + yIntercept;

        cout << "Intersection Points at: ( " << x1Intersect << " , " << y1Intersect << " ) and ( " << x2Intersect << " , " << y2Intersect << " )";
    }

    cout << endl << endl;
}

int main() {
    int choice = 0;
    cout << setprecision(2) << setiosflags(ios::showpoint | ios::fixed);

    do {
        cout << "Would you like use: \n"
             << "1: Military Time\n"
             << "2: Parabola\n"
             << "0: Exit\n"
             << "[Enter a number]: ";
        cin >> choice;

        if (choice == 1) {
            mtime();
        } else if (choice == 2) {
            parabola();
        } else {
            cout << "\n\nGoodbye!\n\n";
        }
    } while (choice != 0);

    return 0;
}
