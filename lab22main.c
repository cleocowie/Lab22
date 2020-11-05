/** lab22main.c
* ===========================================================
 * Name: Cowie, 15 Oct 2020
 * Section: T1/2
 * Project: Lab 22
* ===========================================================
*
* Instructions:
*    1) Complete TASKS Below
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "lab22functs.h"

int main() {
    MyCadetInfo cadetRecs[MAXSTUDENTS];

    // read cadet records from a text file
    int numCadets = getDataText(cadetRecs);

    // write the array of structures to a binary file
    writeDataBlk(cadetRecs,numCadets);

    // modify the 4th record and rewrite only
    // that record to the binary file
    // strncpy(cadetRecs[3].name, "Da Cadet",20);
    // writeCadetBlk(&cadetRecs[3],3);

    /* Exercise 1 - Write a function, called, readCadetBlk() that
     * uses fseek() and fread() to read a single cadet
     * record from the binary file
     * Note:  This lab requires lab22Data.txt to be in your
     * Lab22 folder
     * Warning: Be sure to properly open and close the file
     * 0) Figure out the required parameters and write the function
     * prototype in the *.h file
     * 1) The function returns the MyCadetInfo structure read from disk
     *      dataType varName = functionCall
     *      MyCadetInfo yourChosenVarName = readCadetBlk(someRecord);
     * 2) Call your function below with parameters of your choice
     * 3) Verify that it works by printing the returned struct
     *      The struct is yourChosenVarName from above.
     */
    printf("Enter cadet.\n");
    int location;
    scanf("%d",&location);
    int actualLocation=location-1;
    MyCadetInfo cadet;
    cadet=readCadetBlk(actualLocation);
    printCadetInfo(cadet);

    /* Exercise 2 - Write a function, called, updateSqdBlk() that
     * uses a cadet's full name to find the cadet in the array of
     * records, updates their squadron to the given value,
     * and then writes the new record in the correct location
     * in the binary file
     * 0) Figure out the required parameters and write the function
     * prototype in the *.h file
     * 1) The function returns the number of records written and on
     * error it returns a -1
     * 2) Call your function below with parameters of your choice
     * 3) Verify that it works by reading the record from the file
     * and printing it.
     */
    //printf("Input cadet name.\n");
    char name1[20] = "Jake Cooley";
    int data;
    //scanf("%s %s", name1, name2);
    //printf("Input new squad.\n");
    //scanf("%d",&squad);
    data=updateSqdBlk(cadetRecs,numCadets,name1,38);
    printf("Number of records written: %d\n",data);
    
    printf("%s %d %d\n", cadetRecs[18].name, cadetRecs[18].squad, cadetRecs[18].classYear);


    /* Exercise 3 - Write a function, called, updateClassYearNameBlk()
     * that overwrites the file, lab22Data.bin, with the class
     * year prepended to the cadet name.  For example, Troy Weingart
     * would become C1C Troy Weingart if I were in class of 2021.
     * 0) Figure out the required parameters and write the function
     * prototype in the *.h file
     * 1) The function returns the number of records written and on
     * error it returns a -1
     * 2) Call your function below
     * 3) Verify that your function works by using readCadetBlk()
     * and printing the results.
    */
   int num1;
   num1=updateClassYearNameBlk(cadetRecs,numCadets);
   printf("Number of 22ers: %d\n", num1);
   printf("%s\n", cadetRecs[0].name);

   system("pause");
    return 0;
}