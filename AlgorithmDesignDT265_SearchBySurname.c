/* Program to search for a specific student by surname, using user input of the student's name. 

Name: Nicola Mahon C15755031
Date: 2016-04-12

Compiler: Borland
OS: Windows 10

*/

// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// symbollic names
#define MINSIZE 20
#define LIMIT 36

// structure templates
struct student_rec
{
	int id;
    char type[MINSIZE];
	char surname[MINSIZE];
	char firstname[MINSIZE];
};
    
main()
{
    // file pointers for merging the files
    FILE *fp_read;
    
    // search parameters
    char search_str[MINSIZE]; 
    
    // variable to hold student record
    struct student_rec student1;
        
    // array to hold student records for binary search
    struct student_rec students[LIMIT];
        
	// try to create a new file for merging
	fp_read = fopen("MergedStudentsBySurname.txt", "r");
	
	// error check for opening the file
    if (fp_read == NULL)
    {
        printf("WARNING: MergedStudentsBySurname.txt could not be opened at this time.");
        exit(0);
    }
	else
	{
		printf("MergedStudentsBySurname.txt opened successfully.");
	}
	
    // ask user what type of student they want to find
    printf("\n\nWhat surname do you want to search for?");
    printf("\nNOTE: Surnames are CASE SENSITIVE and begin with a capital letter i.e. Byrne, Cullen, Waldron)");
    printf("\n\nPlease enter your selection now:\n");
    gets(search_str);
    
    
    // index for reading records into the array
    int i = 0;
    
    // while the pointer is not at the end of the file
    while (feof(fp_read) == 0)
    {
        // read a record
        fscanf(fp_read, "%s %s %d %s", student1.surname, student1.firstname, &student1.id, student1.type);
        
        // store the record in the array
        strcpy(students[i].surname, student1.surname);
        strcpy(students[i].firstname, student1.firstname);
        students[i].id = student1.id;
        strcpy(students[i].type, student1.type);
        
        // move the array pointer to the next space
        i++;
    }
    
    // close the file, after it is read into the array
    fclose(fp_read);
    
    // begin the binary search of the array
    
    //variables for holding indexes
    int low = 0;
    int high = LIMIT-1;
    int middle;
    
    // count the number of records found, catch records NOT found
    int count = 0;
    
    // while there are still records to read in the array
    while (low <= high)
    {
        // find the midpoint of the array
        middle = (low + high)/2;
        
        // compare the user's search string to the surname at the midpoint of the array
        // if they are the same, print the record and exit. 
        if (strcmp(students[middle].surname, search_str) == 0)
        {
            printf("\nRecord Found!\nID: %d\nType: %s\nSurname: %s\nFirstname: %s\n", students[middle].id, students[middle].type, students[middle].surname, students[middle].firstname);
            count++;
            break;
        }
        // otherwise if the search string is less than the surname at the midpoint of the array, search the left side of the array
        else if (strcmp(students[middle].surname, search_str) > 0)
        {
            high = middle -1;
        }
        // otherwise if the search string is greater than the surname at the midpoint of the array, search the right side of the array
        else if  (strcmp(students[middle].surname, search_str) < 0)
        {
            low = middle + 1;
        }
    }
    
    // catch any input that doesnt match the string compare
    if (count == 0)
    {
        printf("\nSorry, no records were found of that type, please try again, ensuring your selection is case sensitive.");
    }
    
    printf("\n\nPress 'enter' to exit program.");
    getchar();

} // end main)