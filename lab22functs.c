/** lab22functs.h
 * ===========================================================
 * Name: Cowie, 15 Oct 2020
 * Section: T1/2
 * Project: Lab 22
 * ===========================================================
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "lab22functs.h"

/** ----------------------------------------------------------
 * writeDataBlk() is used to the entire cadet record array
 * to a binary file
 * @param cadetRecords is the array of cadet records
 * @param numCadets is the total number of cadets to write
 * @return number of records wrote
 * ----------------------------------------------------------
 */
int writeDataBlk(MyCadetInfo cadetRecords[], int numCadets) {

    // Open an output file for writing
    FILE *out = fopen("lab22Data.bin", "wb");
    if (out == NULL) {
        printf("Error creating data file: %s.\n", strerror(errno));
        exit(1);
    }

    size_t retVal = fwrite(cadetRecords,sizeof(MyCadetInfo), numCadets, out);
    fclose(out);
    return retVal;

}

/** ----------------------------------------------------------
 * writeCadetBlk() is used to write a single cadet records
 * to a binary file the previous contents of the file are
 * not changed
 * @param cadet is the address of the cadet structure to write
 * @param location is the offset from the from of the file to
 *                 write the record to
 * @return number of records wrote
 * ----------------------------------------------------------
 */
int writeCadetBlk(MyCadetInfo* cadet, int location) {

    // Open an output file for writing
    FILE *out = fopen("lab22Data.bin", "rb+");
    if (out == NULL) {
        printf("Error creating data file: %s.\n", strerror(errno));
        exit(1);
    }
    fseek(out, sizeof(MyCadetInfo) * (long) location, SEEK_SET);
    int retVal = fwrite(cadet,sizeof(MyCadetInfo), 1, out);
    fclose(out);
    return retVal;
}

/** ----------------------------------------------------------
 * getDataText() is used to read MyCadetInfo typed records
 * from a file
 * @param cadetRecords is the array of cadet records
 * @return number of records read
 * ----------------------------------------------------------
 */
int getDataText(MyCadetInfo cadetRecords[]) {

    // Open an input file for reading
    FILE *in = fopen("lab22Data.txt", "r");
    if (in == NULL) {
        printf("Error opening data file: %s.\n", strerror(errno));
        exit(1);
    }

    char firstName[30];
    char lastName[45];
    int numRead = 0;

    while (numRead < MAXSTUDENTS && !feof(in)) {
        fscanf(in, "%s %s %d %d", firstName, lastName, &cadetRecords[numRead].squad,
               &cadetRecords[numRead].classYear);
        strcat(firstName, " ");
        strcpy(cadetRecords[numRead].name, strcat(firstName, lastName));
        numRead++;
    }
    fclose(in);
    return numRead;
}

/** ----------------------------------------------------------
 * printCadetInfo() is used to print a MyCadetInfo typed variable
 * to the console
 * @param cadetRecord is the cadet info struct to be printed
 * @return n/a
 */
void printCadetInfo(MyCadetInfo cadetRecord) {
    printf("Cadet name = \t%s\n", cadetRecord.name);
    printf("Cadet squad = \t%d\n", cadetRecord.squad);
    printf("Cadet year = \t%d\n\n", cadetRecord.classYear);
}

/** ----------------------------------------------------------
 * printData() is used to print MyCadetInfo typed records
 * from a file
 * @param datums is the array of cadet records
 * @param numCadets is the number of cadets in datums
 * @return n/a
 */
void printData(MyCadetInfo* datums, int numCadets) {
    for (int i = 0; i < numCadets; i++) {
        printCadetInfo(datums[i]);
    }
}

MyCadetInfo readCadetBlk(int fileLocation) {

    FILE * in = fopen("lab22Data.bin", "rb");
	MyCadetInfo cadet;
	if (in == NULL) {
		printf("Error reading data file: %s.\n", strerror(errno));
		exit(1);
	}

	fseek(in,sizeof(MyCadetInfo)*fileLocation, SEEK_SET);
	fread(&cadet, sizeof(MyCadetInfo), 1, in);
	fclose(in);
	return cadet;
}




int updateSqdBlk(MyCadetInfo cadetRecord[],int numCadets,char cadetName[],int squad) {

    FILE * in = fopen("lab22Data.bin", "rb");
    int numRead = 0;
    int numUpdate = 0;

    while (numRead < numCadets) {
        if (strcmp(cadetRecord[numRead].name,cadetName)==0) {
            cadetRecord[numRead].squad = squad;
            fwrite(&cadetRecord[numRead].squad, 1, sizeof(MyCadetInfo),in);
            numUpdate++;
        }

        numRead++;
        
    }
return numUpdate;
}

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

int updateClassYearNameBlk(MyCadetInfo cadetRecord[],int numCadets) {
    char original[100];
    int numUpdate =0;
    char hi[10]="C2C ";
    int numRead = 0;
    FILE * in = fopen("lab22Data.bin", "rb");

    while (numRead < numCadets) {
        if (cadetRecord[numRead].classYear == 2022)
        {
            strcpy(original,cadetRecord[numRead].name);
            strcpy(cadetRecord[numRead].name,hi);
            strcat(cadetRecord[numRead].name,original);
            printf("%s\n", cadetRecord[numRead].name);
            fwrite(&cadetRecord[numRead].name, 1, sizeof(MyCadetInfo),in);
            numUpdate++;
            
        }
        numRead++;
    }
    return numUpdate;
}


