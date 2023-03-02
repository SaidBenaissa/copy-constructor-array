// When we call default constructor, the pointer is pointing to the original data.
// The result can be critical since the copied object can go away with the original object
// when the scope is over(when the copied object gets out of scope). This can trigger a non-desirable destructor
// behavoir: trying to delete the same memory twice ( trying to delete an already deleted pointer

#include <iostream>

using namespace std;

class IntegerArray {
public:
    explicit IntegerArray(int size) {
        m_array = new int[m_size];
        this->m_size = size;
        cout << "Constructor called" << endl;
    }

    ~IntegerArray() {
        delete[] m_array;
        cout << "Destructor called" << endl;
    }

public:
    int* m_array;
    int m_size;
};


int main() {
    IntegerArray array(2);
    array.m_array[0] = 1;
    array.m_array[1] = 2;

    cout << "array.m_array[0] = " << array.m_array[0] << endl;
    cout << "array.m_array[1] = " << array.m_array[1] << endl;

    if(true){
        // copy constructor is called here
        cout << "array2 is getting into scope" << endl;
        cout << "array2 is copied from original copy array " << endl;
        IntegerArray array2 = array;
        cout << "array2.m_array[0] = " << array2.m_array[0] << endl;
        cout << "array2.m_array[1] = " << array2.m_array[1] << endl;

        cout << "array2 is getting out of scope" << endl;

        // first destructor is called here
    }
    cout << "array.m_array[0] = " << array.m_array[0] << endl; // dangling pointer,  // When array goes out of scope, destructor is called (deallocates array), array2.pArray now a dangling pointer.
    cout << "array.m_array[1] = " << array.m_array[1] << endl; //     when array2 goes out of scope (main()), its destructor tries to delete the already-deleted array.

    return 0; // second destructor is called here
}
