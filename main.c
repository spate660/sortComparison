//  sortComparison.c
//
//  See how fast bubble, selection, insertion, and quick sort are
//  on arrays of random numbers, that exponentially grow.
//  This program also illustrates how to measure elapsed time.
//
//  Author: Dale Reed 11/3/22
//  test commit
/*  Sample output:
        Welcome to the Sort timing example program.

        Choose the type of sort:
        1. Bubble Sort
        2. Selection Sort
        3. Insertion Sort
        4. Quick Sort
        Your choice --> 1

         Elapsed    Array Size     Sort Time
        (seconds)   (thousands)    (seconds)
            7            2          0.0067
            7            4          0.0314
            7            8          0.1395
            8           16          0.5847
           10           32          2.3748
           20           64          9.7179
           59          128         39.0808
           ...
*/

#include <stdio.h>    // For printf
#include <stdlib.h>   // For malloc
#include <time.h>     // For time functions
#include <math.h>     // For pow()


// Swap two array elements.  Used in sorting.
void swap( int theArray [], int i, int j)
{
    int temp = theArray[i];		// store temporarily
    theArray[i] = theArray[j];
    theArray[j] = temp;
}


// Bubble sort array to put into ascending order
void bubbleSort( int theArray[], int arraySize)
{
    for( int pass=1; pass < arraySize; pass++)  {
        for( int current=0; current < arraySize-pass; current++) {
            if ( theArray[ current] > theArray[ current+1]) {
                // swap the two array elements
                swap( theArray, current, current+1);
            }
        }//end for ( current…
    }//end for (pass…
}//end bubbleSort


// Selection sort array to put into ascending order
void selectionSort( int theArray[], int arraySize)
{
    int indexOfSmallest = 0;
    
    for( int pass=0; pass < arraySize; pass++)  {
        indexOfSmallest = pass;
        // Find smallest element among those still being sorted
        for ( int i=pass+1; i < arraySize; i++) {
            if ( theArray[ i] < theArray[ indexOfSmallest]) {
                // we have a new smallest value, so record it
                indexOfSmallest = i;
            }
        }//end for ( int i...
        
        // swap the smallest value found on this pass into place
        swap( theArray, pass, indexOfSmallest);
    }//end for (pass…
}//end selectionSort()


// Insertion sort array to put into ascending order
void insertionSort( int theArray[], int arraySize)
{
    int indexOfSmallest = 0;
    
    for( int pass=1; pass<arraySize; pass++)  {
        indexOfSmallest = pass;
        // Find smallest element among those still being sorted
        while( (indexOfSmallest > 0) && (theArray[ indexOfSmallest] < theArray[indexOfSmallest - 1]))  {
            swap( theArray, indexOfSmallest, indexOfSmallest-1);
            indexOfSmallest--;
        }
    }//end for (pass…
}//end selectionSort()


// For debugging:
void displayArray( int theArray[], int start, int end)
{
    for( int j=0; j<=start; j++) {
        printf("  ");
    }
    for( int i=start; i<=end; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    for( int j=0; j<=start; j++) {
        printf("  ");
    }
    for( int i=start; i<=end; i++) {
        printf("%2d ", theArray[ i]);
    }
    printf("\n");
}


// Partition() - used as part of quickSort()
//    Partition array on a pivot so that all elements < pivot
// are to the left of the pivot position, and all elements >= pivot
// are to the right of the pivot position.
//   Select the pivot as the middle array element, then store it
// out of the way at the far right end of the array, swapping it
// back into the middle at the end of the partitioning.
int partition( int theArray[],   // the array
               int left,     // index of left-most element
               int right)    // index of right-most element
{
    // To find index of middle do it the funky way shown below to avoid integer overflow
    int pivotIndex = left + (right-left) / 2;
    int pivotValue = theArray[ pivotIndex];
    int storeIndex = left;    // destination on the left for first swap
    // Number of elements in subarray is: right-left+1
    
    // Put pivot value out of the way at far right of array, to be swapped back
    // into place at the end.
    swap( theArray, pivotIndex, right);

    // Go through the current range being considered of array elements,
    // moving each element into the left part of the partition if its value
    // is less than the pivot value.
    for( int i=left; i<=right; i++) {
        if( theArray[i] < pivotValue) {
            swap( theArray, i, storeIndex);
            storeIndex++;
        }
    }
    // storeIndex is now the index of the location just to the right of the last
    // element that is < pivot, so its value >= pivot.  Swap the pivot back
    // into this spot.
    swap( theArray, storeIndex, right);    // Move pivot to its final place
    return storeIndex;
} // end partition()


void quickSort(int theArray[ ], int first, int last)
{
    int pivotIndex;
    
    if( first < last) {
        // Partition around a pivot and return index of pivot
        pivotIndex = partition( theArray, first, last);
        
        quickSort(theArray, first, pivotIndex - 1);
        quickSort(theArray, pivotIndex + 1, last);
    }
}// end quickSort()


int main()
{
    int arraySize;
    time_t beginTime = time( NULL);  // set the start time
    
    printf("Welcome to the Sort timing example program. \n\n");
    
    int menuOption = 0;
    printf("Choose the type of sort:\n");
    printf("1. Bubble Sort    \n");
    printf("2. Selection Sort \n");
    printf("3. Insertion Sort \n");
    printf("4. Quick Sort     \n");
    printf("Your choice --> ");
    scanf("%d", &menuOption);
    
    printf("\n");
    printf(" Elapsed    Array Size     Sort Time  \n");
    printf("(seconds)   (thousands)    (seconds)  \n");

    // Main loop, doing multiple iterations for different array sizees
    //for( int i=2; i<pow(2,20); i=i*2) {
    for( int i=2; i<pow(2,6); i=i*2) {
        arraySize = 1000 * i;
        
        // allocate space for the array
        int *pTheArray = (int *) malloc( sizeof(int) * arraySize);
        
        // initialize each array element to some random value 0..(arraySize-1)
        for( int j=0; j<arraySize; j++) {
            pTheArray[ j] = random()%arraySize;
        }
    
        // Store the start time
        clock_t startTime = clock();
        
        // Sort the array, using the selected sorting approach
        switch( menuOption) {
            case 1: bubbleSort( pTheArray, arraySize);
                    break;
            case 2: selectionSort( pTheArray, arraySize);
                    break;
            case 3: insertionSort( pTheArray, arraySize);
                    break;
            case 4: // send indices of first and last elements
                    quickSort( pTheArray, 0, arraySize-1);
                    break;
            default: printf("Invalid menu option.  Exiting...\n");
                    break;
        }
    
        // Display number of seconds elapsed.
        double elapsedTime = difftime(time( NULL), beginTime);
        double sortSecondsThisIteration = (clock() - startTime)/(double)CLOCKS_PER_SEC;
        printf("%5.0f     %8d %15.4f\n",
                elapsedTime,               // Elapsed time
                i,                         // Array size in thousands
                sortSecondsThisIteration); // Sort seconds on this iteration
    }
    
    return 0;
} // end main()