/*
File:			DynArray.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student: Joshua Keith

Created:		11.21.2020
Last Modified:	07.31.2021
Purpose:		A dynamically-allocated resizeable array (similar to std::vector)
Notes:			Property of Full Sail University
*/

// Header protection.
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/

// Main toggle
#include <iostream>
#define LAB_1	0

// Individual unit test toggles
#define LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS			0	//PASS
#define LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS			0	//PASS
#define LAB1_BRACKET_OPERATOR						0	//PASS
#define LAB1_SIZE_ACCESSOR							0	//PASS
#define LAB1_CAPACITY_ACCESSOR						0	//PASS
#define LAB1_RESERVE_EMPTY							0	//PASS
#define LAB1_RESERVE_DOUBLE_CAPACITY				0	//PASS
#define LAB1_RESERVE_LARGER_CAPACITY				0	//PASS
#define LAB1_RESERVE_SMALLER_CAPACITY				0	//PASS
#define LAB1_APPEND_NO_RESIZE						0	//PASS
#define LAB1_APPEND_RESIZE							0	//PASS
#define LAB1_CLEAR									0	//PASS
#define LAB1_DESTRUCTOR								0	//PASS
#define LAB1_ASSIGNMENT_OPERATOR					0	//PASS
#define LAB1_COPY_CONSTRUCTOR						0	//PASS

// Our implementation of a vector (simplified)
template<typename Type>
class DynArray {

	// Gives access to test code
	friend class UnitTests_Lab1;

	// Data members
	// NOTE: All values set to -1 for unit test purposes

	Type* mArray = reinterpret_cast<Type*>(-1);
	size_t mSize = -1;
	size_t mCapacity = -1;

public:

	// Default constructor
	//		Creates an empty object
	//
	// In:	_startingCap		Ann initial size to start the array at
	//
	// Note: Do not allocate any memory if the _startingCap is 0
	DynArray(size_t _startingCap = 0) {
		// TODO: Implement this method
		mCapacity = _startingCap;


		if (_startingCap != 0)
		{
			mArray = new Type[mCapacity];

			mSize = 0;

		}
		else
		{
			mArray = nullptr;
			mSize = 0;
		}

	};

	// Destructor
	//		Cleans up all dynamically allocated memory
	~DynArray() {
		// TODO: Implement this method
		delete[] mArray;

	}

	// Copy constructor
	//		Used to initialize one object to another
	// In:	_copy				The object to copy from
	DynArray(const DynArray& _copy) {
		// TODO: Implement this method

		mArray = nullptr;
		*this = _copy;

	}

	// Assignment operator
	//		Used to assign one object to another
	// In:	_assign				The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain

	DynArray& operator=(const DynArray& _assign) {
		// TODO: Implement this method
		if (this != &_assign)
		{
			//clean up existing memory
			delete[] mArray;

			//deep copy dynamic members
			mCapacity = _assign.Capacity();
			mSize = _assign.Size();

			mArray = new Type[mCapacity];
			
			for (int i = 0; i < mCapacity; i++)
			{
				mArray[i] = _assign.mArray[i];
			}

		}

		return *this;

	}

	// Clear
	//		Cleans up all dynamically allocated memory
	//		Sets all data members back to default values
	void Clear() {
		// TODO: Implement this method


		delete[] mArray;
		mArray = nullptr;
		mCapacity = 0;
		mSize = 0;

	}

	// Overloaded [] operator
	//		Used to access an element in the internal array (writeable)
	// In:	_index			The index to access at
	//
	// Return: The item at the specified index (by reference)
	Type& operator[](size_t _index) {
		// TODO: Implement this method

		return mArray[_index];

	}

	// Get the current number of elements actively being used
	//
	// Return: The current number of elements used
	size_t Size() const {
		// TODO: Implement this method

		return mSize;

	}

	// Get the current capacity of the internal array
	//
	// Return: The capacity of the array
	size_t Capacity() const {


		return mCapacity;

	}

	// Add an item to the end of the array
	//		Should resize the array if needed
	//
	// In:	_data			The item to be added
	void Append(const Type& _data) {
		// TODO: Implement this method

		if (mSize < mCapacity)
		{
			mArray[mSize] = _data;
			mSize++;
		}
		else
		{
			Reserve();
			mArray[mSize] = _data;
			mSize++;
		}



	}

	// Resizes the internal array, and copies all data over
	// In: _newCapacity		The new capacity of the array
	//		NOTE:	If 0 is passed, the array should double in size
	//				If _newCapacity < mCapacity, do nothing
	//
	//	SPECIAL CASE: If mCapacity is 0, then it should be set to 1

	void Reserve(size_t _newCapacity = 0)
	{
		// TODO: Implement this method

		if (_newCapacity < mCapacity && _newCapacity != 0)
		{

		}
		else
		{

			if (_newCapacity == 0 && mCapacity == 0)
			{
				mCapacity = 1;
			}
			else if (_newCapacity == 0 && mCapacity != 0)
			{
				mCapacity *= 2;
			}

			if (_newCapacity > mCapacity)
			{
				mCapacity = _newCapacity;
			}


			Type* tempArray = new Type[mCapacity];

			for (int i = 0; i < mSize; i++)
			{

				tempArray[i] = mArray[i];

			}

			delete[] mArray;

			mArray = tempArray;
		}

	}
};