/*
File:			DList.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Created:		1.17.2021
Last Modified:	2.14.2021
Purpose:		A hash-mapped data structure using key/value pairs and separate chaining
Notes:			Property of Full Sail University
*/

// Header protection
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
#define LAB_5	0

// Individual unit test toggles
#define LAB5_PAIR_CTOR				1	//PASS
#define LAB5_CTOR					1	//PASS
#define LAB5_DTOR					1	//PASS
#define LAB5_CLEAR					1	//PASS
#define LAB5_INSERT_NEW				1	//PASS
#define LAB5_INSERT_EXISTING		1	//PASS
#define LAB5_FIND					1	//PASS
#define LAB5_FIND_NOT_FOUND			1	//PASS
#define LAB5_REMOVE					1	//PASS
#define LAB5_REMOVE_NOT_FOUND		1	//PASS
#define LAB5_ASSIGNMENT_OP			1	//PASS
#define LAB5_COPY_CTOR				1	//PASS

/************/
/* Includes */
/************/
#include <list>

template<typename Key, typename Value>
class Dictionary {

	friend class UnitTests_Lab5;	// Giving access to test code

	// The objects stored in the hash-table
	struct Pair {
		Key key;			// The key for insertion/lookup
		Value value;		// The data

		// Constructor
		// In:	_key
		//		_value
		Pair(const Key& _key, const Value& _value) {
			// TODO: Implement this method

			key = _key;
			value = _value;

		}

		// For testing
		bool operator==(const Pair& _comp) const {
			return (_comp.key == key &&
				_comp.value == value);
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	std::list<Pair>* mTable = reinterpret_cast<std::list<Pair>*>(-1);							// A dynamic array of lists (these are the buckets)
	size_t mNumBuckets = -1;																	// Number of elements in mTable
	unsigned int(*mHashFunc)(const Key&) = reinterpret_cast<unsigned int(*)(const Key&)>(-1);	// Pointer to the hash function


public:

	// Constructor
	// In:	_numBuckets			The number of elements to allocate
	//		_hashFunc			The hashing function to be used

	Dictionary(size_t _numBuckets, unsigned int (*_hashFunc)(const Key&)) {
		// TODO: Implement this method

		mNumBuckets = _numBuckets;
		mHashFunc = _hashFunc;

		mTable = new std::list<Pair>[mNumBuckets];

	}

	// Destructor
	//		Cleans up any dynamically allocated memory
	~Dictionary() {
		// TODO: Implement this method

		delete[] mTable;

	}

	// Copy constructor
	//		Used to initialize one object to another
	// In:	_copy				The object to copy from
	Dictionary(const Dictionary& _copy) {
		// TODO: Implement this method

		/*this->mHashFunc = _copy.mHashFunc;
		this->mNumBuckets = _copy.mNumBuckets;*/
		
		this->mTable = nullptr;
		
		*this = _copy;
		

	}

	// Assignment operator
	//		Used to assign one object to another
	// In:	_assign				The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	Dictionary& operator=(const Dictionary& _assign) {
		// TODO: Implement this method		
		

		if (this != &_assign)
		{
			delete[] mTable;

			mNumBuckets = _assign.mNumBuckets;
			mHashFunc = _assign.mHashFunc;

			mTable = new std::list<Pair>[mNumBuckets];


			for (int i = 0; i < mNumBuckets; i++)
			{
				mTable[i] = _assign.mTable[i];
			}
						
		}
		return *this;

	}

	// Clear
	//		Clears all internal data being stored
	//  NOTE:	Does not delete table or reset hash function
	void Clear() {
		// TODO: Implement this method
				
		for (int i = 0; i < mNumBuckets; i++)
		{
			mTable[i].clear();
		}		

	}

	// Insert an item into the table
	// In:	_key		The key to add at	
	//		_value		The value at the key
	//
	// NOTE:	If there is already an item at the provided key, overwrite it.
	void Insert(const Key& _key, const Value& _value) {
		// TODO: Implement this method
		bool isFound = false;

		auto mIter = mTable[mHashFunc(_key)].begin();

		for (auto iter = mTable[mHashFunc(_key)].begin(); iter != mTable[mHashFunc(_key)].end();)
		{
			if (iter->key == _key)
			{
				isFound = true;
				mIter = iter;
				break;
			}
			else
				iter++;


		}

		if (isFound)
		{
			mIter->value = _value;
		}
		else
		{
			mTable[mHashFunc(_key)].push_back(Pair(_key, _value));
		}

	}

	// Find a value at a specified key
	// In:	_key		The key to search for	
	//
	// Return: A const pointer to the value at the searched key
	// NOTE:		Return a null pointer if key is not present
	const Value* Find(const Key& _key) {
		// TODO: Implement this method

		

		for (auto iter = mTable[mHashFunc(_key)].begin(); iter != mTable[mHashFunc(_key)].end();)
		{
			if (iter->key == _key)
			{
				const Value* mValue = &iter->value;
				return mValue;
				break;
			}
			else
				iter++;
		}

		return nullptr;
	}

	// Remove a value at a specified key
	// In:	_key		The key to remove
	//
	// Return: True, if an item was removed
	bool Remove(const Key& _key) {
		// TODO: Implement this method

		for (auto iter = mTable[mHashFunc(_key)].begin(); iter != mTable[mHashFunc(_key)].end();)
		{
			if (iter->key == _key)
			{
				mTable[mHashFunc(_key)].erase(iter);
				return true;
				break;
			}
			else
			{
				iter++;
			}
		}

		return false;
	}
	
};