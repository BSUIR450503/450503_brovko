#include "header.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    cout<< "malloc" <<endl;
    int *array = (int*)_malloc(10 * sizeof(int));
    for (int i=0;i<10;i++){
        array[i]=i;
        cout<<array[i]<< " ";
    }
    cout<<endl;

    cout<< "malloc" <<endl;
    int * array1 = (int*)_malloc(10 * sizeof(int));
    for (int i=9;i>=0;i--){
        array1[i]=i;
        cout<<array1[i]<< " ";
    }
    cout<<endl;

    cout<< "realloc" <<endl;
    array1 = (int*)_realloc(array1, 15 * sizeof(int));
    for (int i=0;i<15;i++){
        array1[i] = i;
        cout<<array1[i]<< " ";
    }
    cout<<endl;

    cout<< "free and malloc" <<endl;
    free (array);
    array = (int*)_malloc(100 * sizeof(int));
    for (int i=0;i<10;i++){
        array[i] = 1;
        cout<<array[i]<< " ";
    }
    cout<<endl;

    return 0;
}
