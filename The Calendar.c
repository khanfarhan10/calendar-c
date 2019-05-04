#include<stdio.h>
//global variables
int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
/*first value is initialised as 0 as we do not want to keep confusion
between index of array and the corresponding month*/
//to put it simply, moth 0 does not exist so we put an arbitrary value to it.

char *months[]= { " ", "\n\n\nJanuary", "\n\n\nFebruary", "\n\n\nMarch", "\n\n\nApril", "\n\n\nMay","\n\n\nJune",
            "\n\n\nJuly", "\n\n\nAugust", "\n\n\nSeptember", "\n\n\nOctober", "\n\n\nNovember", "\n\n\nDecember" };

int inputyear()
{
    int year;
    printf("Please enter a year (example: 1999) : ");
    scanf("%d", &year);
    return year;
}

/*
int determinedaycode(int year, int month=1, int day=1)
        { // initialised day and month as 1 because 01/01/yyyy  here we only need year
                //Using original Zeller's formula
            int d1, d2, d3, d4, code;
            if (month == 1)
            {
                month = 13; year--;
            }
            if (month == 2)
            {
                month = 14; year--;
            }
            d1 = year / 4;
            d2 = year / 100;
            d3 = year / 400;
            d4 = day + 2 * month + 3 * (month + 1) / 5 + year;
            code = (d4 + d1 - d2 + d3 + 1) % 7;
            return code;
                // code will return sun=0,mon=1,tue=2,wen=3,thu=4,fri=5,sat=6
        }*/
//modified zeller's function
int determinedaycode(int year)
{
    int daycode;
    int d1, d2, d3;
    d1 = (year )/ 4.0; //normal leap year (excluding century leap)
    d2 = (year )/ 100.0; //century year
    d3 = (year)/ 400.; //century leap year
    daycode = (year + d1 - d2 + d3) %7; //(year +all leap - all century years) modulus 7
    return daycode; // code returns sun=0,mon=1,tue=2,wen=3,thu=4,fri=5,sat=6
}

int determineleapyear(int year) //returns 1 for leap year and 0 for non leap year
{
    if(year% 4 == 0 && year%100 != 0 || year%400 == 0)
    {
        days_in_month[2] = 29;
        return 1;
    }
    else
    {
        days_in_month[2] = 28;
        return 0;
    }
}

void calendar(int year, int daycode) //output handling code
    {
         int month, day;
         for ( month = 1; month <= 12; month++ )
        {
             printf("%s", months[month]);
             printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );

           // Correct the position for the first date
             for ( day = 1; day <= 1 + daycode * 5; day++ )
             {
                  printf(" "); //space for correctly aligning the days
             }

           // Print all the dates for one month
             for ( day = 1; day <= days_in_month[month]; day++ )
            {
                     printf("%2d", day ); //to format the output to display only 2 digits

               // Is day before Sat? Else start next line Sun.
                   if ( ( day + daycode ) % 7 > 0 )
                          printf("   " );
                   else
                          printf("\n " );
            }

              // Setting the position for next month

           daycode = ( daycode + days_in_month[month] ) % 7;
       }
}

int main()
{
      int year, daycode, leapyear;
      year = inputyear(); //takes in the input for a year
      daycode = determinedaycode(year);
      //daycode holds the following essential values sun=0,mon=1,tue=2,wen=3,thu=4,fri=5,sat=6
      determineleapyear(year);
      // returns one for leap and 0 for non leap year . Modifies the month February accordingly
      calendar(year, daycode);
      // the code responsible for handling the output part
      printf("\n");
}
