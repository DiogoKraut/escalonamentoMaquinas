/* Code adapted to maintain parity between 2 arrays when one is sorted *
 * Original at https://www.geeksforgeeks.org/quick-sort/               *
 * Adapted by Diogo Paris Kraut - GRR 20166365                         */


// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int* arr, int* arr2, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
            swap(&arr2[i], &arr2[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    swap(&arr2[i + 1], &arr2[high]);

    return (i + 1);
}
 
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int* arr, int *arr2, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, arr2, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, arr2, low, pi - 1);
        quickSort(arr, arr2, pi + 1, high);
    }
}