//created by khanfarhan10 ?
//CRAZYCODERZ INC. 
//All rights reserved. 


#include<stdio.h>
//global variables
int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
/*first value is initialised as 0 as we do not want to keep confusion
between index of array and the corresponding month
to put it simply, month 0 does not exist so we put an arbitrary value to it.*/

char *months[]= { " ", "\n\n\nJanuary", "\n\n\nFebruary", "\n\n\nMarch", "\n\n\nApril", "\n\n\nMay","\n\n\nJune",
            "\n\n\nJuly", "\n\n\nAugust", "\n\n\nSeptember", "\n\n\nOctober", "\n\n\nNovember", "\n\n\nDecember" };
//2D array created using ptr to 1D array

//function to get input year
int inputyear()
{
    int year;
    printf("Please enter a year (example: 1999) : ");
    scanf("%d", &year);
    return year;
}

//
int determinedaycode (int y)
{   // function will return sun=0,mon=1,tue=2,wen=3,thu=4,fri=5,sat=6
    //y is the year
    int f,a,b,c,d,daycode;

    //we need to find out the daycode for the 1st of February for a particular month
    //Using original Zeller's formula with
    y--;  /*since february is considered as 11th month of the previous year
            in zeller's function,(since months in zeller formula start from March)
            hence we subtract a year to find out its first of february*/
            //use m=11 & k=1
    a=(y%100);
    b=a/4;
    c=(y/100);
    d=c/4;
    f=29+a+b+d-2*c;
        /*zeller's formula- f = k + [(13*m-1)/5] + D + [D/4] + [C/4] - 2*C
          for more info see readme file
          [] is called greatest integer function8*/
     /*here b & d are used as we need the greatest
      integer function value for (y%100)/4 and (y/100)/4
      respectively.This is done to avoid using the gif function
      explicitly over floating pt values.*/


    /*for a year like 1700 , f becomes -2(negative)
    so we have to add 7n to f where n is such
    an integer which gives f as a positive value*/
    //the negative case of f
    if(f<0)
        {   int temp=-f;
            /*we use the theory here that n=[mod(f)/7] +1
              for f to be positive and in between 0 & 7
              since we are using integer data type here,
              we don't actually need to use floating point
              numbers and then find out the Greatest Integer function for that*/
            int n=(temp/7)+1;
            //corrected f would be
            f=f+7*n;
        }


    daycode=f%7;
    return daycode;
}


 /*below function returns 1 for leap year and 0 for non leap year
  suitably changing the days_in_month value for february as 28
  for non leap and 29 for leap*/

int determineleapyear(int year)
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
/*output handling function with suitable decoration*/
void calendar(int year, int daycode)
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


