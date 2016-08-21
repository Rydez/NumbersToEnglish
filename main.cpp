//To do:
//translate decimal numbers (http://www.basic-mathematics.com/writing-decimals-in-words.html)
//use the word "and" to indicate decimal location

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string decimalMagnitude[10] =
{
    "",            "tenth",       "hundredth",   "thousandth",  "ten thousandth",
    "hundred thousandth",         "millionth",   "ten millionth",
    "hundred millionth"
};

string ones[10] =
{
    "zero ",       "one ",        "two ",        "three ",      "four ",
    "five ",       "six ",        "seven ",      "eight ",      "nine "
};

string teens[10] =
{
    "ten ",        "eleven ",     "twelve ",     "thirteen ",   "fourteen ",
    "fifteen ",    "sixteen ",    "seventeen ",  "eighteen ",   "nineteen "
};

string tens[10] =
{
    "",            "",            "twenty",      "thirty",      "fourty",
    "fifty",       "sixty",       "seventy",     "eighty",      "ninety"
};

string magnitude[10] =
{
    "",            "thousand ",   "million ",    "billion ",    "trillion ",
    "quadrillion ","quintillion ","sextillion ", "septillion ", "octillion "
};

//This function takes a given number and reverses it
//in order to retrieve the appropriate words(including "hundred")
//for each power of 1000.
int threeDigitChunk( int number );

//Find power of 1000
long long powerValue ( long long number );

//Find corresponding index
int powerIndex ( long long number, long long power_value);

//Isolate powers of 1000 and print them
void printNumber ( long long number, long long power_value, int power_index );



int main()
{
    cout << "This program will translate a number entered in digits to the equivalent" << endl;
    cout << "in English.\n\n";
    cout << "\tCommas may be used.\n\n";
    cout << "\tDecimal number capable.\n\n";
    cout << "\tNegative number capable.\n\n";

    while ( true )
    {
        string puncCheck;
        int decimalLength;
        long long number;
        long long decimalNumber;

        cout << "Enter number: ";
        cin >> puncCheck;

//Remove commas
        puncCheck.erase( remove( puncCheck.begin(), puncCheck.end(), ',' ), puncCheck.end() );

//Find position of decimal and remove it.
        int decimalPosition = puncCheck.find( '.', 0 );
        puncCheck.erase( remove( puncCheck.begin(), puncCheck.end(), '.' ), puncCheck.end() );

        if ( decimalPosition == -1 )
        {
            number = atoi( puncCheck.c_str() );
        }
        else
        {
            number = atoi( puncCheck.substr( 0, decimalPosition ).c_str() );
            decimalLength = puncCheck.substr( decimalPosition, '\n' ).length();
            decimalNumber = atoi( puncCheck.substr( decimalPosition, '\n' ).c_str() );
        }

//Check zero
        if ( puncCheck == "0" )
        {
            cout << "zero\n";
            continue;
        }

//Validate number
        if (!number)
        {
            cin.clear();
            cin.ignore( 10000, '\n' );
            cout << "Invalid number. Try again.\n";
            continue;
        }
        cout << endl;

//Check negative (turn negative number into positive)
        if ( number < 0 )
        {
            cout << "negative ";
            number = -number;
        }

//Find the magnitude and corresponding index of the input number.
        long long power_value = powerValue ( number );
        int power_index = powerIndex ( number, power_value);

//Isolate each power of 1000 and retrieve magnitude if appropriate.
        printNumber ( number, power_value, power_index );

        if ( decimalPosition != -1 )
        {
            cout << "\nand\n";

    //Find the magnitude and corresponding index of the input decimal number.
            power_value = powerValue ( decimalNumber );
            power_index = powerIndex ( decimalNumber, power_value);

    //Isolate each power of 1000 and retrieve magnitude if appropriate.
            printNumber ( decimalNumber, power_value, power_index );
            cout << decimalMagnitude[decimalLength];

            if ( decimalNumber != 1 )
            {
                cout << "s";
            }
        }
        cout << endl << endl;
    }
}


int threeDigitChunk( int number )
{
    int digits[3];

    for ( int i = 0; i < 3; i++ )
    {
        digits[i] = (number % 10);
        number = (number / 10);
    }

    if ( digits[2] != 0 )
    {
        cout << ones[digits[2]] << "hundred ";
    }

//Check if hyphen is needed

    if ( digits[1] == 1 )
    {
        cout << teens[digits[0]];
    }

    else
    {
        if ( digits[1] != 0 && digits[0] != 0)
        {
            cout << tens[digits[1]] << '-';
        }
        else if ( digits[1] != 0 )
        {
            cout << tens[digits[1]] << ' ';
        }
        if ( digits[0] != 0 )
        {
            cout << ones[digits[0]];
        }
    }
}

long long powerValue ( long long number )
{
    long long power_value = 1000;
    while ((number / power_value) != 0)
    {
        power_value *= 1000;
    }
    power_value /= 1000;
    return power_value;
}

int powerIndex ( long long number, long long power_value)
{
    power_value = 1000;
    int power_index = 1;
    while ((number / power_value) != 0)
    {
        power_value *= 1000;
        power_index += 1;
    }
    power_value /= 1000;
    power_index -= 1;
    return power_index;
}

void printNumber ( long long number, long long power_value, int power_index )
{
    do
    {
        int tempNumber = (number / power_value);

        if ( tempNumber != 0 )
        {

            threeDigitChunk( tempNumber );

            if ( (power_index > 0) && (tempNumber != 0) )
            {
                cout << magnitude[power_index];
                cout << endl;
            }
        }
        power_value /= 1000;
        power_index -= 1;
    }
    while ( power_index >= 0 );
}
