#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void getInfoFromInput(char *fileName) 
{

    /* Pointer to the file */
    FILE *fp1;
    /* Character variable to read the content of file */
    char c;
    /* Opening a file in r mode*/
    fp1 = fopen (fileName, "r");

    // Tracker
    bool tracker = false;

    /* Infinite loop –I have used break to come out of the loop*/
    while(1)
    {
    c = fgetc(fp1);
    if(c==EOF)
        break;
    else
        if(c == '#') {
            tracker = true;   
        } else if(c == '\n') {
            tracker = false;
        }
        if(!tracker) {
            printf("%c", c);
        }
    }
    fclose(fp1);
}

// Function to write to file, where a is a string of text, and b is an int and fp is the file pointer
void writeToFile(char *a, int b, FILE *fp) {
    fprintf(fp, "%s", a);
    fprintf(fp, "%d\n", b);
}

// Utility function to turn int to string
char* intToString(int n)
{
    char *result; 
    sprintf(result, "%d", n);
    return result;
}