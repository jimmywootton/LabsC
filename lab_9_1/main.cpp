#include <ctime>
#include <algorithm>
using namespace std;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) 
{
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[])
{
    for(int i = 0; i < NUMBERS_SIZE; ++i)
    {
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int findMedian(int a, int b, int c) 
{
    int arr[3] = {a, b, c};
    sort(arr, arr + 3); // Sort the array in ascending order
    return arr[1]; // Return the middle element (median)
}

int Partition(int numbers[], int lowIndex, int highIndex, bool isMidPoint) 
{
    // Pick middle element as pivot
    int midpoint = (lowIndex + highIndex) / 2;
    int pivot;
    if (isMidPoint)
    {
        pivot = numbers[midpoint];
    }
    else
    {
        pivot = findMedian(numbers[lowIndex], numbers[midpoint], numbers[highIndex]);
    }
    bool done = false;
    while (!done) 
    {
        // Increment lowIndex while numbers[lowIndex] < pivot
        while (numbers[lowIndex] < pivot) 
        {
            lowIndex += 1;
        }
        // Decrement highIndex while pivot < numbers[highIndex]
        while (pivot < numbers[highIndex]) 
        {
            highIndex -= 1;
        }
        // If zero or one elements remain, then all numbers are 
        // partitioned. Return highIndex.
        if (lowIndex >= highIndex) 
        {
            done = true;
        }
        else 
        {
            // Swap numbers[lowIndex] and numbers[highIndex]
            int temp = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = temp;
            // Update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

void Quicksort(int numbers[], int i, int k, bool isMidPoint)
{
    // Base case: If the partition size is 1 or zero 
    // elements, then the partition is already sorted
    if (i >= k) 
    {
        return;
    }
    // Partition the data within the array. Value lowEndIndex 
    // returned from partitioning is the index of the low 
    // partition's last element.
    int lowEndIndex = Partition(numbers, i, k, isMidPoint);
    // Recursively sort low partition (lowIndex to lowEndIndex) 
    // and high partition (lowEndIndex + 1 to highIndex)
    Quicksort(numbers, i, lowEndIndex,isMidPoint);
    Quicksort(numbers, lowEndIndex + 1, k, isMidPoint);
}

void Quicksort_midpoint(int numbers[], int i, int k)
{
    bool isMidPoint = true;
    Quicksort(numbers, i, k, isMidPoint);
}

void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    bool isMidPoint = false;
    Quicksort(numbers, i, k, isMidPoint);
}

void InsertionSort(int numbers[], int numbersSize)
{
    int i = 0;
    int j = 0;
    int temp = 0; // Temporary variable for swap
    for (i = 1; i < numbersSize; ++i) 
    {
        j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) 
        {
            // Swap numbers[j] and numbers[j - 1]
            temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }
}

int runtime(int arr[])
{
    clock_t Start = clock();
    //runtime function
    clock_t End = clock();
    return (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
}

int main()
{

}