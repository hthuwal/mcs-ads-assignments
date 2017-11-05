#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

#define vi vector<int>

int number_of_comparisons = 0;

/**
 * Function To read input file
 * Less number of system calls
 * @param  name of input file
 * @return vector of integers read from file
 */
vi quickread(char *filename)
{
    vi arr;
    try{
        ifstream input_stream(filename, ifstream::binary);  // opening input stream from file
        
        input_stream.seekg(0, input_stream.end); // going to the end of file
        int filesize = input_stream.tellg();  // file size from the last byte of the file
        input_stream.seekg(0, input_stream.beg);  //going back to sart of file
        
        char *c = new char [filesize]; // character array to read entire file
        input_stream.read(c, filesize);  // reading entire file into character array

        stringstream ss(c); // string stream from the character array
        int a;
        
        while(ss>>a) // reading integers from string stream
            arr.push_back(a);

        input_stream.close();
        return arr;
    } 
    catch(exception e) 
    {
        cout<<"Error opening file. Make sure the file name and path is correct\n";
        exit(0);
    }
}

/*if quickread doesnt works*/
vi quickread_2(char * filename)
{
    vi arr;
    freopen(filename,"r",stdin);
    int n;
    while(cin>>n)
    {
        arr.push_back(n);
    }
    return arr;
}


/**
 * Swap two integers
 */
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


/**
 * Given a pivot index partition array into two parts: Less than pivot and greater than pivot
 * @param  arr         [array to be partitioned, must be a reference, because original array need to be modified]
 * @param  start       [consider array from start]
 * @param  end         [consider array to end]
 * @param  pivot_index [index of element to be used for partitioning]
 * @return             [final position of pivot in the partitioned array]
 */
int partition (vi &arr, int start, int end, int pivot_index)
{
    int pivot = arr[pivot_index];  // pivot element
    swap(&arr[pivot_index], &arr[end]);  // moving pivot element to the end of array

    int pos_of_pivot = start; // tentative poition of pivot

    for (int i=start;i<=end-1;i++)
    {
        number_of_comparisons++;  
        if(arr[i] <= pivot) // if this element is less than pivot
        {
            swap(&arr[i], &arr[pos_of_pivot]); // throw it back to the tentative place of pivot 
            pos_of_pivot++; // increae tentataive place of pivot
        }
    }

    /* now all elements smaller than pivot are to the left of tentative place of pivot*/
    /* that is array is partitioned */

    swap(&arr[pos_of_pivot], &arr[end]); // move the pivot to its tentative place
    return pos_of_pivot; // return position of pivot partitioned array
}


/**
 * Select kth rank element from the array using random pivot seletion
 * @param  arr   [array from whcih pivot is to be selected]
 * @param  start [consider array from start]
 * @param  end   [consider array to end]
 * @param  k     [the desired rank]
 * @return       [the element with rank k]
 */
int randmoized_selection (vi arr, int start,int end, int k)
{
    srand(time(NULL));
    if(start==end)  // if only one element in array
        return arr[start];

    // partition on random pivot_index and get pivot_index in partitioned array =  the rank of the pivot element
    int pivot_index = partition(arr, start, end, start + rand() % (end-start+1) ); 

    if(pivot_index == k)     // if pivot index the desired rank 
        return arr[k];  // return that element

    else if(pivot_index < k) // if pivot index is less than the desired rank
        return randmoized_selection(arr, pivot_index + 1, end, k); 
        // the desired rank must be in the right half, recursively call for right half

    else // pivot index is greater than the desired rank
        return randmoized_selection(arr, start, pivot_index - 1, k);
        // the desired rank must be in the left half, recursively call for left half
}



/** Forward decleration because of  mutual recursion between find_median_of_medians and deterministic_selection **/
int deterministic_selection(vi arr,int start,int end, int k);

/**
 * Divide array into groups of 5 and find the median of set of medians of each group
 * @return    median of medians of groups
 */
int find_median_of_medians(vi arr)
{
    int n = arr.size();
    int median_of_group; 

    vi list_of_medians; // vector to store median of each group

    //creating groups (of 5 memebers) and finding their medians
    for(int i = 0; i<n; i+=5)
    {
        vi group;
        if(i+4<=n-1) //if enough element to create a group of 5
            group = vi(arr.begin() + i,arr.begin() + i + 5);
        else  // if less than 5 elements remaining
            group = vi(arr.begin() + i,arr.begin() + n);
        
        // find medain of the current group, recursive call to deterministic_selection (its base case will be executed)
        median_of_group = deterministic_selection(group, 0, group.size()-1, group.size()/2); 

        list_of_medians.push_back(median_of_group); // appending this median to the list of medians
    }

    // recursively finding medain of the list of medians of groups
    int median_of_medians = deterministic_selection(list_of_medians, 0, list_of_medians.size()-1, list_of_medians.size()/2);

    return median_of_medians;
}



/**
 * Select kth rank element from the array using deterministic pivot seletion (median of medians of groups of 5 as pivot)
 * @param  arr   [array from whcih pivot is to be selected]
 * @param  start [consider array from start]
 * @param  end   [consider array to end]
 * @param  k     [the desired rank]
 * @return       [the element with rank k]
 */
int deterministic_selection(vi arr,int start,int end, int k)
{
    // base case, if number of elements less than 10 then just sort and return kth element
    // constant time because number of elements is 10
    if(end-start+1 <= 10)
    {
        sort(arr.begin() + start, arr.begin() + end+1);
        number_of_comparisons += (end-start+1)*log2(end-start+1);   // approx n log n comparisons in sorting
        if(k<start || k>end)
        {
            printf("This should not have happened\n");
            return -1;
        }
        
        return arr[k]; 
    }

    // recursive call to find the pivot element = the median of the medians of the groups in arr[start, end]
    int median_of_medians = find_median_of_medians(vi(arr.begin()+start, arr.begin()+end));
    
    // index of the pivot element in the array
    int index_of_median_of_medians = find(arr.begin(), arr.end(), median_of_medians) - arr.begin();

    // partition the array using the above index, and get pivot index in partitioned array =  the rank of the pivot element
    int pivot_index = partition(arr, start, end, index_of_median_of_medians);
    
    if(pivot_index == k) // if pivot index the desired rank 
        return arr[k]; // return that element

    else if(pivot_index < k) // if pivot index is less than the desired rank
        return deterministic_selection(arr, pivot_index + 1, end, k);
        // the desired rank must be in the right half, recursively call for right half
        
    else // pivot index is greater than the desired rank
        return deterministic_selection(arr, start, pivot_index - 1, k);
        // the desired rank must be in the left half, recursively call for left half
}



/*To check correctness of both selections*/
void check_correctness(vi arr)
{
    cout<<"Running Correctness check code\n";
    ofstream rand_out("rand_out.txt",ofstream::out);
    ofstream detr_out("detr_out.txt",ofstream::out);
    vi brr = arr;
    sort(brr.begin(),brr.end());
    for(int i=0;i<arr.size();i++)
    {
        int a = randmoized_selection (arr,0,arr.size()-1,i);
        int b = deterministic_selection (arr,0,arr.size()-1,i);

        assert( a == brr[i]);
        assert( b == brr[i]);
        rand_out<<a<<"\n";
        detr_out<<b<<"\n";
    }
    rand_out.close();
    detr_out.close();
}



int main(int argc, char *argv[])
{
    /*If two arguments are not given */
    if(argc != 3)
    {
        cout<<"Program Accepts two command line arguments,but only "<< argc-1 <<" were given.\n";
        exit(0);
    }
    
    char *filename = argv[1];  // Filename
    int k = atoi(argv[2]);  // the desired rank

    /***** Reading Input *****/
    clock_t read_start = clock();
    vi arr = quickread(filename);
    clock_t read_stop = clock();

    cout<<"Input Size : "<<arr.size()<<endl;
    printf("Time taken to read input : %0.10lf\n\n",(double) (read_stop-read_start)/CLOCKS_PER_SEC );

    if(k<1)
    {
        cout<<"Error! The specified rank should be greater than 0\n";
        exit(0);
    }
    else if(k>arr.size())
    {
        cout<<"Error! The specified rank should be less than or equal to the set size "<<arr.size()<<endl;
        exit(0);
    }

    /***** Randomized_selection (Averaging over 10 iterations) *****/
    int iterations = 10;

    int rand_kth = randmoized_selection (arr,0,arr.size()-1,k-1);
    printf("Randomized Selection (Average over %d iterations)\n",iterations);
    printf("Element with rank %d : %d\n", k, rand_kth);

    /* several iterations to find average running time */
    double rand_time=0;
    int comparisons=0;

    for(int i=0;i<iterations;i++)
    {
        number_of_comparisons=0;
        clock_t rand_start = clock();
        randmoized_selection (arr,0,arr.size()-1,k-1);
        rand_time += (double) (clock() - rand_start) / CLOCKS_PER_SEC;    
        comparisons += number_of_comparisons;
    }
    rand_time /= iterations;
    comparisons /= iterations;

    printf("Average Number of comparisons : %d\n", comparisons);
    printf("Average Time Taken : %0.10lf\n", rand_time);


    /***** Deterministic_selection *****/
    number_of_comparisons=0;    
    clock_t detr_start = clock();
    int detr_kth = deterministic_selection (arr,0,arr.size()-1,k-1);
    double detr_time = (double) (clock() - detr_start) / CLOCKS_PER_SEC;

    printf("\nDeterministic Selection\n");
    printf("Element with rank %d : %d\n", k, detr_kth);
    printf("Number of comparisons : %d\n", number_of_comparisons);
    printf("Time Taken : %0.10lf\n", detr_time);

    // vi brr =arr;
    /* Calling Brute force sorting */
    clock_t sort_start = clock();
    sort(arr.begin(), arr.end());
    int sort_kth = arr[k-1];
    double sort_time = (double) (clock() - sort_start) / CLOCKS_PER_SEC;

    printf("\nSorting\n");
    printf("Element with rank %d : %d\n", k, sort_kth);
    printf("Time Taken : %0.10lf\n", sort_time);
    
    printf("\nRandom : Deterministic : Sort = %0.10lf : %0.10lf : %0.10lf\n",1.0, detr_time/rand_time, sort_time/rand_time);
 
    // check_correctness(brr);
}