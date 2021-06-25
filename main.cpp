#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

const char passLibType1[] = "0123456789";
const char passLibType2[] = "abcdefghijklmnopqrstuvwxyz";
const char passLibType3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char passLibType4[] = "!@#$%^&*()_+-=/.,<>`~";
const char fileName[] = "results.txt";

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
    if (passLength == 1)
        return libLength;
    return libLength * getVariants(passLength - 1, libLength);
}

void main() {
    cout << "Enter a password length ( 1 - 256 ) : ";
    int passLength = getNumber(1, 256);
	cout << "Password length : " << passLength << endl;
    cout << "Enter a password count ( 1 - 1024 ): ";
    int passCount = getNumber(1, 1024);
    cout << "Password count : " << passCount << endl;
    cout << "Select password type ( 1 - 4 ): " << endl;
    cout << "1. \"0123456789\"" << endl;
    cout << "2. \"0123456789abc\"" << endl;
    cout << "3. \"0123456789abcABC\"" << endl;
    cout << "4. \"0123456789abcABC!@#$%\"" << endl;
    int passType = getNumber(1, 4);
    char passLib[128] = "";
    int libLength;
    switch (passType)
    {
    case 1:
        libLength = sizeof(passLibType1) / sizeof(char) - 1;
        strcat_s(passLib, passLibType1);
        break;
    case 2:
        libLength = (sizeof(passLibType1) + sizeof(passLibType2)) / sizeof(char) - 2;
        strcat_s(passLib, passLibType1);
        strcat_s(passLib, passLibType2);
        break;
    case 3:
        libLength = (sizeof(passLibType1) + sizeof(passLibType2) + sizeof(passLibType3)) / sizeof(char) - 3;
        strcat_s(passLib, passLibType1);
        strcat_s(passLib, passLibType2);
        strcat_s(passLib, passLibType3);
        break;
    case 4:
        libLength = (sizeof(passLibType1) + sizeof(passLibType2) + sizeof(passLibType3) + sizeof(passLibType4)) / sizeof(char) - 4;
        strcat_s(passLib, passLibType1);
        strcat_s(passLib, passLibType2);
        strcat_s(passLib, passLibType3);
        strcat_s(passLib, passLibType4);
        break;
    }
    cout << "Password type : " << passType << endl;
    srand(static_cast<unsigned int>(time(0)));
    cout << "Library length : " << libLength << endl;
    cout << "Your passwords : " << endl;
    ofstream outFile;
    outFile.open(fileName);
    if (outFile.is_open()) {
        for (int i = 0; i <= passCount - 1; i++) {
            for (int j = 0; j <= passLength - 1; j++) {
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
    system("PAUSE");
}