/* Program to search for students by type. 
Optional user entry of field_type. 

Name: Nicola Mahon C15755031
Date: 2016-04-21

Compiler: Borland
OS: Windows 10

*/

// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// symbollic names
#define MINSIZE 20

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
    // file pointer for reading from the file
    FILE *fp_read;
    
    // file pointer for placing returning search results
    FILE *fp_write; 
    
    // search parameters
    char search_str[MINSIZE]; 
    
    // array to hold student records
    struct student_rec student1;
        
	// try to create a new file for merging
	fp_read = fopen("MergedStudents.txt", "r");
	
	// error check for opening the file
    if (fp_read == NULL)
    {
        printf("WARNING: File could not be opened.");
        exit(0);
    }
	else
	{
		printf("File opened successfully.\n");
	}
    
    // try to create a new file for merging
	fp_write = fopen("SearchResults.txt", "w");
	
	// error check for opening the file
    if (fp_read == NULL)
    {
        printf("WARNING: Search results could not be written to file at this time.");
        exit(0);
    }
	
	
    // ask user what type of student they want to find
    printf("\nWhat category of student do you want to search for?");
    printf("\n\nCategories include: (case sensitive)");
    printf("\nInternational");
    printf("\nNonFundedEU");
    printf("\nFundedEU");
    printf("\n\nPlease enter your selection now:\n");
    gets(search_str);
    
    
    // count the number of records found, catch records NOT found
    int count = 0;
    
    // while the pointer is not at the end of the file
    while (feof(fp_read) == 0)
    {
        // read a record
        fscanf(fp_read, "%d %s %s %s", &student1.id, student1.type, student1.surname, student1.firstname);
        
        // if the record type matches the search parameter 
        if (strcmp(search_str, student1.type) == 0)
        {
            printf("\nRecord Found!\nID: %d\nType: %s\nSurname: %s\nFirstname: %s\n", student1.id, student1.type, student1.surname, student1.firstname);
            count++;
            fprintf(fp_write, "%d %s %s %s\n", student1.id, student1.type, student1.surname, student1.firstname);
        }
    }
    
    // catch any input that doesnt match the string compare
    if (count == 0)
    {
        printf("\nSorry, no records were found of that type, please try again, ensuring your selection is case sensitive.");
    }
    else
    {
        printf("\nFor convenience, these records have been written to file for you. See \"SearchResults.txt\" in the current folder.");
    }
    
    // close the files
    fclose(fp_read);
    fclose(fp_write);
    
    printf("\n\nPress 'enter' to exit program.");
    getchar();

} // end main)