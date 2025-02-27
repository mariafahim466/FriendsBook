/*
 * MyADT.h
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
 
 
#ifndef MyADT_H
#define MyADT_H

/*
 * You can add more #include statements, if needed.
 */
 
#include <string>
#include "Profile.h"


class MyADT {

private:

/* 
 * You can add more data members (attributes) to this class, if needed,
 * but you cannot remove/change the data members below.
 * However, you can change the value "5" used to initialise MAX_ELEMENTS.
 */
 
    constexpr static unsigned int MAX_ALPHA = 26;   // 26 letters in the alphabet 
    constexpr static unsigned int MAX_ELEMENTS = 5; // Small capacity so can test when data collection becomes full 
                                                    // Feel free to change this MAX_ELEMENTS value.
    // array of pointers to profile objects 
    Profile * elements[MAX_ALPHA];                  // MAX_ALPHA arrays of elements 
    unsigned int elementCount[MAX_ALPHA];           // Current element count in each of the MAX_ALPHA arrays of elements


/* 
 * You can add private methods to this class, if needed.
 */
 
    // Utility method(s)

      
public:

/* 
 * You cannot remove/change the ***public interface*** (public methods) of this class. 
 */

    // Default constructor
    // Description: Creates this object and allocates memory for it 
    MyADT();

    // Copy constructor - Covered in Lab 3
    // Description: deep copies this object 
    MyADT(const MyADT& rhs);

    // Overloaded assignment operator - Covered in Lab 4
    // Therefore, we shall not be overloading this operator in our Assignment 1
    // MyADT & MyADT::operator=(const MyADT& rhs) { }
    
    // Destructor - Covered in Lab 3
    // Description: Destroys this object, releasing heap-allocated memory.
    ~MyADT();

    // Description: Returns the total number of elements currently stored in the data collection MyADT.  
    unsigned int getElementCount() const;

    // Description: Inserts an element in the data collection MyADT.
    //              Returns "true" when the insertion is successfull, otherwise "false".
    // Precondition: newElement must not already be in the data collection MyADT.  
    // Postcondition: newElement inserted, MyADT's class invariants are still true
	//                and the appropriate elementCount has been incremented.
	// Time Efficiency: 
    bool insert(const Profile& newElement);

    // Description: Removes an element from the data collection MyADT. 
    //              Returns "true" when the removal is successfull, otherwise "false".    
    // Precondition: The data collection MyADT is not empty.  
    // Postcondition: toBeRemoved (if found) is removed, MyADT's class invariants are still true
    //                and the appropriate elementCount is decremented.
	// Time Efficiency: 
    bool remove(const Profile& toBeRemoved);
	
    // Description: Removes all elements from the data collection MyADT. 
    // Precondition: The data collection MyADT is not empty.    
    // Postcondition: MyADT reverts back to its initialization state, i.e., 
    //                the state it is in once it has been constructed (once
    //                the default constructor has executed). 
	// Time Efficiency: 
    void removeAll();
   
    // Description: Searches for target element in the data collection MyADT. 
    //              Returns a pointer to the element if found, otherwise, returns nullptr.
	// Precondition: The data collection MyADT is not empty. 
    // Time Efficiency: 	
    Profile * search(const Profile& target);
    
    // Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
    // ***For Testing Purposes - Not part of this class' public interface.***
    // Time Efficiency: 
	void print();
   

}; // end MyADT
#endif