#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

char passLib[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char fileName[] = "results.txt";

int getNumber(int minValue, int maxValue) {
    while (true)
    {
        int value;
        cin >> value;
        if (cin.fail() || value < minValue || value > maxValue) 
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "That input is invalid.  Please try again.\n";
        }
        else
        {
            cin.ignore(32767, '\n');
            return value;
        }
    }
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

double getVariants(int passLength, int libLength)
{
    if (passLength == 0)
        return libLength;
    return passLength * getVariants(passLength - 1, libLength);
}

void main() {
    cout << "Enter a password length ( 1 - 256 ) : ";
    int passLength = getNumber(1, 256);
	cout << "Password length : " << passLength << endl;
    cout << "Enter a password count ( 1 - 1024 ): ";
    int passCount = getNumber(1, 1024);
    cout << "Password count : " << passCount << endl;
    srand(static_cast<unsigned int>(time(0)));
    int libLength = sizeof(passLib) / sizeof(char) - 1;
    cout << "Your passwords : " << endl;
    ofstream outFile;
    outFile.open(fileName);
    if (outFile.is_open()) {
        for (int i = 1; i <= passCount; i++) {
            for (int j = 1; j <= passLength; j++) {
                char passSymbol = passLib[getRandomNumber(0, libLength - 1)];
                outFile << passSymbol;
                cout << passSymbol;
            }
            outFile << endl;
            cout << endl;
        }
    }
    cout << "Your passwords save in file : " << fileName << endl;
    cout << "Every password have " << getVariants (passLength, libLength) << " variants !" << endl;
}