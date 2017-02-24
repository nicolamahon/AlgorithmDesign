/* Program to merge and sort by SURNAME, 3 files containing details about DIT student admissions.

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
#define MAXSIZE 100
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

// function prototypes
void MergeSort (struct student_rec *, int, int);
void combine (struct student_rec *, int, int, int);
void mod_bubble_sort(struct student_rec *);
    
main()
{
    // file pointers for merging the files
    FILE *fp_read1;
    FILE *fp_read2;
    FILE *fp_read3;
    FILE *fp_write;
    
    // file pointers for sorting the files
    FILE *fp_sortread;
    FILE *fp_sortwrite;
    
    // variable to read line by line when merging the files
    char line[MAXSIZE];
    
    // array to hold student records
    struct student_rec students[LIMIT];
    struct student_rec student1;
        
	// try to create a new file for merging
	fp_write = fopen("MergedStudentsBySurname.txt", "w");
	
	// error check for opening the file
    if (fp_write == NULL)
    {
        printf("WARNING: New file for merging could not be created on the disk.");
        exit(0);
    }
	else
	{
		printf("New file for merging created successfully.");
	}
	
    // try to open the first file for reading
    fp_read1 = fopen("FundedEU.txt", "r");
    
    // error check for opening the file
    if (fp_read1 == NULL)
    {
        printf("\n\nWARNING: FundedEU file could not be opened.");
        exit(0);
    }
    else
    {
        printf("\n\nFundedEU file opened successfully.");
    }
    
    // read each character in the file, until = NULL
    while (fgets(line, MAXSIZE, fp_read1) != NULL)
    {
        // write the line to the new file
        fputs(line, fp_write);
    }
    
    // close the first file
    fclose(fp_read1);
    
    // try to read second file
    fp_read2 = fopen("International.txt", "r");
    
    // error check for opening the file
    if (fp_read2 == NULL)
    {
        printf("\nWARNING: International file could not be opened...");
        exit(0);
    }
    else
    {
        printf("\nInternational file opened successfully.");
    }
    
    // read each character in the file, until = NULL
    while (fgets(line, MAXSIZE, fp_read2) != NULL)
    {
        // write the line to the new file
        fputs(line, fp_write);
    }
    
    // close the second file
    fclose(fp_read2);
    
    
    // try to read the last file
    fp_read3 = fopen("NonFundedEU.txt", "r");
    
    // error check for opening the file
    if (fp_read3 == NULL)
    {
        printf("\nWARNING: NonFundedEU file could not be opened...");
        exit(0);
    }
    else
    {
        printf("\nNonFundedEU file opened successfully.");
    }
    
    // read each character in the file, until = NULL
    while (fgets(line, MAXSIZE, fp_read3) != NULL)
    {
        // write the line to the odd file
        fputs(line, fp_write);
    }
    
    // close the last file
    fclose(fp_read3);
    
    // close the new merged file
    fclose(fp_write);
    
    printf("\n\nCongratulations!\nAll files are now merged.");
    
    // *** BEGIN SORTING FILE
    printf("\n\nOpening MergedStudentsBySurname.txt file for sorting...");
    
    // open merged file to read
    fp_sortread = fopen("MergedStudentsBySurname.txt", "r");
    
    // error check for opening the file
    if (fp_sortread == NULL)
    {
        printf("\n\nWARNING: MergedStudentsBySurname file could not be opened for reading...");
    }
    else
    {
        printf("\nMergedStudentsBySurname file opened successfully for reading.");
    }
    
    // variable for accessing the array in RAM
    register int i = 0;
	
	// read the records into the array
	while (feof(fp_sortread) == 0)
	{
        fscanf(fp_sortread, "%d %s %s %s", &student1.id, student1.type, student1.surname, student1.firstname);
        // store the record in the array
        students[i].id = student1.id;
        strcpy(students[i].type, student1.type);
        strcpy(students[i].surname, student1.surname);
        strcpy(students[i].firstname, student1.firstname);
        i++;
	}
    
    // close the file
	fclose(fp_sortread);
    
    printf("\n\nBegin sorting the merged file...");
        
    // find the size of the array (to get the number of records)
    int size;
    size = sizeof(students);
    
    // count the number of records in the array
    int num;
    num = size/sizeof(student1);
    
    // implement partition function
    MergeSort(students, 0, num-1);
    
    printf("\nMergedStudentsBySurname.txt file is now sorted.");
    printf("\n\nWriting new data to file...");
    
    // open merged file to write new sorted data, overwriting any existing data on the file
    fp_sortwrite = fopen("MergedStudentsBySurname.txt", "w");
    
    // error check for opening the file
    if (fp_sortwrite == NULL)
    {
        printf("\n\nWARNING: MergedStudentsBySurname file could not be opened for writing...");
    }
    else
    {
        printf("\nMergedStudentsBySurname file opened successfully for writing.");
    }
    
    // now print the new sorted and merged data to the file, using the sorted by surname as the first column in the results
    for (i=0; i<LIMIT; i++)
    {
        fprintf(fp_sortwrite, "%s %s %d %s\n", students[i].surname, students[i].firstname, students[i].id, students[i].type);  
    }
    
    printf("\n\nCongratulations!\nAll records are now sorted.");
    printf("\n\nFile successfully merged and sorted.\nPlease see file \"MergedStudentsBySurname.txt\" in the directory.");
    printf("\n\nPress 'enter' to exit program.");
    getchar();

} // end main)

void MergeSort (struct student_rec *temp_students, int low, int high)
{
    int mid = 0;
    
    // if the array is smaller than 3 elements
    if (mid < 4)
    {
        // call bubble sort for small arrays
        mod_bubble_sort(temp_students);
    }
    
    // otherwise keep dividing the array up into sub-arrays
    else if (low < high)
    {
        mid = (low + high) / 2;                     // split the array into 2 sub arrays
        MergeSort(temp_students, low, mid);         // continue down the left side of the array, breaking into sub arrays
        MergeSort(temp_students, mid+1, high);      // break down the right side of the array into sub arrays
        combine(temp_students, low, mid, high);     // now bring all the sorted arrays back into the array in order
    }
}

// merge the sub-arrays back together
void combine (struct student_rec *students, int low, int mid, int high)
{
    int j, k, l, m;
    struct student_rec temp[LIMIT];

    j = low;        // head of the left array
    l = low;        // head of the right array
    m = mid+1;      // head of the temp array

    // while not at the end of a sub array 
    while((l<=mid)&&(m<=high))
    {
        // compare the heads and place smallest into temp
        if (strcmp(students[j].surname, students[j+1].surname) > 0)
            {
                temp[j].id = students[l].id;
                strcpy(temp[j].type, students[l].type);
                strcpy(temp[j].surname, students[l].surname);
                strcpy(temp[j].firstname, students[l].firstname);
                l++;
            }
        else
            {
                temp[j].id = students[m].id;
                strcpy(temp[j].type, students[m].type);
                strcpy(temp[j].surname, students[m].surname);
                strcpy(temp[j].firstname, students[m].firstname);
                m++;
            }
        j++;
    }
    
    // if the end of one sub array is reached, just copy the rest of the other sub array into temp 
    if(l>mid)
        {
            for(k = m; k <= high; k++)
            {
                temp[j].id = students[k].id;
                strcpy(temp[j].type, students[k].type);
                strcpy(temp[j].surname, students[k].surname);
                strcpy(temp[j].firstname, students[k].firstname);
                j++;
            }
        }
    else
        {
            for(k=l; k <= mid; k++)
            {
                temp[j].id = students[k].id;
                strcpy(temp[j].type, students[k].type);
                strcpy(temp[j].surname, students[k].surname);
                strcpy(temp[j].firstname, students[k].firstname);
                j++;
            }
        }

    // copy the temp records back into the original array
    for(k=low; k<=high; k++)
    {
        students[k].id = temp[k].id;
        strcpy(students[k].type, temp[k].type);
        strcpy(students[k].surname, temp[k].surname);
        strcpy(students[k].firstname, temp[k].firstname);
    }
}

void mod_bubble_sort(struct student_rec *students)
{
    // indexes to use with for-loops
    // REGISTER to allow faster looping
    register int i, j;
    
    // temporary variable to store records during the sort/swapping process
    struct student_rec temp;
    
    // variable to hold a flag to tell the bubble sort when there has been no further swaps, and so the function can end without further iterations
    // this will speed up the sorting
    int sort_flag = 1;
    
    /* I have chosen to use the modified Bubble Sort, it has a potential Big O(n^2) but is more efficient with the use of a flag
        */
    
    // for-loop to begin sorting; outer loop to ensure all swaps are made
    for (i=0; i<LIMIT && sort_flag; i++)
    {
        // set the sort_flag to zero inside the loop, if the condition is not met, and no swaps are made, the flag will remain zero to indicate no changes
        sort_flag = 0;
        
        // inner for-loop to make the swap at each pair of variables if condition is true
        for (j=0; j<LIMIT-1; j++)
        {
            // if number on the left is greater than number on the right
            if (strcmp(students[j].surname, students[j+1].surname) > 0)
            {
                
                // store the values from the record in a temp variable 
                temp.id = students[j].id;
                strcpy(temp.type, students[j].type);
                strcpy(temp.surname, students[j].surname);
                strcpy(temp.firstname, students[j].firstname);
                
                // and then start swaps
                students[j] = students[j+1];
                students[j+1] = temp; 
                
                // set sort_flag to one to confirm a change has been made
                sort_flag = 1;
                
            } // end if
            
        } // end inner for-loop
        
    } // end outer for-loop
    
} // end mod_bubble_sort()
