/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 *                    Its concrete data structure (CDT) is not expandable.  
 *                    This signifies that when this data collection becomes full,
 *                    you do not have to resize its data structure (not in this Assignment 1).  
 * 
 * Class Invariant: Data collection with the following characteristics:
 *                  - This is a value-oriented data collection and 
 *                    the elements are kept in ascending sort order of search key.
 *                  - Each element is unique (no duplicates). 
 *
 * Author: AL and Maria Fahim
 * Last modified on: May 2024
 */

/*
Question: What does this imply in terms of the insert method of 
MyADT class? In other words, how is the insert method of MyADT 
class to behave in order for the print method of this class to 
have a time efficiency of O(n)?

Answer: this implies that the insert function has to do the sorting of
the profiles usernames in alphabetical order because if it doesn't, then
the printing function would be left to do the sorting, which would make
the time efficiency no longer O(n).
*/

#include <iostream>
#include <cctype>
#include "MyADT.h"     // Header file of MyADT file
#include "Profile.h"   // Header file of Profile class

using std::cout;
using std::endl;

    
// Default constructor.
// Description: Creates this object and allocates memory for it 
MyADT::MyADT() {
    //cout << "MyADT::default constructor executed!" << endl;   // For testing purposes ...
   // You can also use the above cout to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
    // initialize all pointers to nullptr 
    for(int i=0; i<MAX_ALPHA; i++) {
      //  elements[i]= new Profile[MAX_ELEMENTS];
        elements[i] = nullptr;
    //initialize all elementcount variables to 0 
        elementCount[i]=0;
    }
}  
  
// Copy constructor - Covered in Lab 3
// Description: does a deepy copy of the object into rhs 
MyADT::MyADT(const MyADT& rhs) {
    //cout << "MyADT::copy constructor" << endl; // For testing purposes ... 
   // You can also use the above cout to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
    for (int i = 0; i < MAX_ALPHA; ++i) {
        elementCount[i] = rhs.elementCount[i];
        elements[i] = new Profile[MAX_ELEMENTS];
        for (unsigned int j = 0; j < elementCount[i]; ++j) {
            elements[i][j] = rhs.elements[i][j];
        }
    }
   /* Put your code here */
   
}  

// Overloaded assignment operator - Covered in Lab 4
// Therefore, we shall not be overloading this operator in our Assignment 1
// MyADT & MyADT::operator=(const MyADT& rhs) { }
	
// Destructor - Covered in Lab 3
// Description: Destroys this object, releasing heap-allocated memory.
MyADT::~MyADT() {
  //  cout << "MyADT::destructor" << endl;  // For testing purposes ...
   // You can also use the above cout to figure out when this destructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
  
   /* Put your code here */
    for (int i = 0; i < MAX_ALPHA; ++i) {
        delete[] elements[i];  // deallocate each sub-array
    }
}  

// Description: Returns the total number of elements currently stored in the data collection MyADT.  
// Postcondition: returns the total number of elements in the data collection MyADT
unsigned int MyADT::getElementCount() const {
    unsigned int element_count=0;
   /* Put your code here */
    for(int i=0; i<MAX_ALPHA; i++) {
        element_count = element_count + elementCount[i];
            // ex if  i=0 then we get how many a's there are and etc
    }
    return element_count;
}


// Description: Inserts an element in the data collection MyADT.
//              Returns "true" when the insertion is successfull, otherwise "false".
// Precondition: newElement must not already be in the data collection MyADT.  
// Postcondition: newElement inserted, MyADT's class invariants are still true
//                and the appropriate elementCount has been incremented.
// Time Efficiency: O(m) // elementCount[index] is the number of profile elements that start with the same letter 
bool MyADT::insert(const Profile& newElement) {
   /* Put your code here */
    char firstChar = newElement.getSearchKey(); //getting first letter of username
    int currentLetter = firstChar - 'a';       
    int i;
    if(elements[currentLetter] == nullptr) {
        elements[currentLetter] = new Profile[MAX_ELEMENTS];
    }
    // return false if already full
    if (elementCount[currentLetter] >= MAX_ELEMENTS) {
        return false;
    }

    // search for index to insert
    for (i=0; i < elementCount[currentLetter]; i++) {
        if(elements[currentLetter][i] == newElement) {
            // return false if we find a duplicate 
            return false; 
        }
        // checking if newElement is < the current element so it inserts in alphabetical order
        if (elements[currentLetter][i] > newElement) {
            break;
        }
    }
    // shift elements to make room for newElement
    for (unsigned int j= elementCount[currentLetter]; j>i; j--) {
        elements[currentLetter][j] = elements[currentLetter][j-1];
    }
    // insert newElement and incremenet elementCount by 1
    elements[currentLetter][i] = newElement;
    elementCount[currentLetter]++;

    return true;
}  

// Description: Removes an element from the data collection MyADT. 
//              Returns "true" when the removal is successfull, otherwise "false".    
// Precondition: The data collection MyADT is not empty.  
// Postcondition: toBeRemoved (if found) is removed, MyADT's class invariants are still true
//                and the appropriate elementCount is decremented.
// Time Efficiency: O(m)
bool MyADT::remove(const Profile& toBeRemoved) {

   /* Put your code here */
   //loop through the alphabetized groups of objects
    for(int i=0; i<MAX_ALPHA; i++) {
        //loop through the groups of letters of objects
        for(int j=0; j<elementCount[i]; j++) {
            //compare each element check if its the one we wanna remove
            if(elements[i][j]==toBeRemoved) {
                //delete &elements[i][j];
                // moved the decrement into the if statemnt instead of 
                // outside the for loop 
                elementCount[i]--;
                // after deleting we need to shift eerything to the left
                // so there are no gaps in the array 
                for(int k=j+1; k<elementCount[i]; k++) {
                    elements[i][k-1] = elements[i][k];
                }
                return true; 
            } 
        }
    }

    return false;
}  

// Description: Removes all elements from the data collection MyADT. 
// Precondition: The data collection MyADT is not empty. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
// Time Efficiency: O(1)
void MyADT::removeAll() {
    for(int i = 0; i < MAX_ALPHA; i++) {
        // If elements[i] is dynamically allocated, delete the memory first
        if (elements[i] != nullptr) {
            delete[] elements[i];
            elements[i] = nullptr;
        }
        elementCount[i] = 0;
    }
}



// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
// Precondition: The data collection MyADT is not empty.
// Time Efficiency: O(m)
Profile* MyADT::search(const Profile& target) {
    
    /* Put your code here */
    for(int i=0; i<MAX_ALPHA; i++) {
        for(int j=0; j<elementCount[i]; j++) {
            if(elements[i][j] == target) {
                return &elements[i][j];
            }
        }
     }
     // if we dont find it return nullptr 
     return nullptr;
}  
//

// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
// Time Efficiency: O(1)
void MyADT::print() {
  
    /* Put your code here */  
    for (int i = 0; i < MAX_ALPHA; ++i) {
        for (int j = 0; j < elementCount[i]; ++j) {
            cout << elements[i][j]; 
        }
    }

} 

//  End of implementation file