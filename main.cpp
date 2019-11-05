#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>

using namespace std;

// First subarray is array[beginning..middle]
// Second subarray is array[middle+1..end]
void merge(vector<int>&array, int beginning, int middle, int end){
    int i, j, k;
    int size1 = middle - beginning + 1;
    int size2 =  end - middle;

    //create temp arrays for left size and right size
    vector<int>LeftArr;
    vector<int>RightArr;

    //Fill left array
    for (i = 0; i < size1; i++) {
        LeftArr.push_back(array[beginning + i]);
    }
    //Fill right array
    for (j = 0; j < size2; j++) {
        RightArr.push_back(array[middle + 1 + j]);
    }

    // Merge the temp arrays back into array[beginning..end]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = beginning; // Initial index of merged subarray
    while (i < size1 && j < size2){
        if (LeftArr[i] <= RightArr[j]){
            array[k] = LeftArr[i];
            i++;
        }
        else{
            array[k] = RightArr[j];
            j++;
        }
        k++;
    }
    while (i < size1){ //Copy extra element of Left Array
        array[k] = LeftArr[i];
        i++;
        k++;
    }
    while (j < size2){ //Copy extra elements of Right Array
        array[k] = RightArr[j];
        j++;
        k++;
    }
}
void MergeSort(vector<int>&array, int beginning, int end){
    if (beginning < end){
        int middle = beginning+(end-beginning)/2;
        // Sort first and second halves
        MergeSort(array, beginning, middle);
        MergeSort(array, middle+1, end);
        merge(array, beginning, middle, end);
    }
}

//Swaps two elements of an array
void swap( int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void BubbleSort(vector<int>&array, int size){
    int i = size;
    bool sorted = false;
    while (i > 1 && !sorted){
        sorted = true;
        for(int j = 1; j <= i-1; j++){
            if(array[j] < array[j-1]){
                swap(&array[j], &array[j-1]);
                sorted = false;
            }
        }
        i--;
    }
}
//Displays sorted array
/*void printSortedArray(vector<int>&array, int N){
    for (int i = 0; i< N; i++ ){
        cout<<array[i]<<endl;
    }
}*/
int main(int argc, char * argv[]) {
string SortType;
string inFile;
string numbers;
int N = 0;
if(argc == 4){
    SortType = argv[1];
    numbers = argv[2];
    stringstream convert(numbers);
    convert>>N; //DONE TO CONVERT STRING OF DIGITS INTO INTEGERS
    inFile = argv[3];
}
else{
    cout<<"Not enough arguments given."<<endl;
}
    ifstream myReadFile;
    myReadFile.open(inFile);
    int output;
    //int array[N];
    //int *array = new int[N];
    vector<int>array;
    if (myReadFile.is_open()) {
        for(int i = 0; i < N; i++){
            myReadFile >> output;
             array.push_back(output); // we save output in array
             //cout<<array[i]<<endl;
        }
        if(SortType =="m"){
            clock_t timeNeeded = clock();
            MergeSort(array,0,N-1);
            timeNeeded = clock() - timeNeeded;
            cout<<"Time needed to execute Merge sort for " << N <<" numbers is : "<<((float)timeNeeded)/CLOCKS_PER_SEC<<" seconds"<<endl;
            //printSortedArray(array,N);
        }
        else if(SortType == "b"){
            clock_t timeNeeded = clock();
            BubbleSort(array, N);
            timeNeeded = clock() - timeNeeded;
            cout<<"Time needed to execute Bubble sort for " << N <<" numbers is : "<< ((float)timeNeeded)/CLOCKS_PER_SEC<<" seconds"<<endl;
            //printSortedArray(array,N);
        }
        else{
            cout<<"Incompatible argument type(should be m or b)"<<endl;
        }
        ofstream file;
        file.open ("output.txt");
        for(int i = 0; N > i; i++){
            file << array[i];
            file << endl;// we save output in array
        }
        file.close();
    }
    else{
        cout<<"Error opening file. Please enter right txt file."<<endl;
    }
    myReadFile.close();
    //delete []array;
    return 0;
}