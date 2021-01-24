#include <iostream>
#include <vector>
#include <limits> // For infinity
#include <algorithm> // For min
#include <string>

using std::vector; using std::cin; using std::cout; using std::endl;


// Implementation partly guided by: https://cp-algorithms.com/data_structures/fenwick.html
class FenwickTree
{
private:
	vector<int> bit; // Binary indexed tree
	int size;

public:
	// Initialize a Fenwick tree with the passed size
	FenwickTree(int size)
	{
		this->size = size;
		bit.assign(size, 0); // Initialize the vector bit to be filled with size 0s
	}

	// Initialize a Fenwick tree with a passed vector
	FenwickTree(vector<int> vectorToCopy) : FenwickTree(vectorToCopy.size())
	{
		for (size_t i = 0; i < vectorToCopy.size(); i++)
		{
			// We go through bit and add at every index the element found at vectorToCopy at i.
			add(i, vectorToCopy[i]);
		}
	}

	// Sum the values of a Fenwick tree from index 0 to the right index
	int sum(int rightIndex)
	{
		int returnSum = 0;

		// We replace all trailing 1s with 0s. This operation can be performed by 
		// (i & (i + 1))
		for (; rightIndex >= 0; rightIndex = (rightIndex & (rightIndex + 1)) - 1)
		{
			returnSum += bit[rightIndex];
		}

		return returnSum;
	}

	// Sum the values in a given range.
	int sum(int leftIndex, int rightIndex)
	{
		return sum(rightIndex) - sum(leftIndex - 1);
	}

	// At a given index add amountToAdd
	void add(int index, int amountToAdd)
	{
		for (; index < size; index = index | (index + 1))
		{
			bit[index] += amountToAdd;
		}
	}
};


int main()
{
	FenwickTree ft(4);
	ft.add(0, 100);
	ft.add(1, 200);
	ft.add(2, 1000);
	ft.add(3, 122);

	cout << ft.sum(3) << endl; // Expect 1422
	cout << ft.sum(0, 2) << endl; // Expect 1300 
	cout << ft.sum(0, 0) << endl; // Expect 100

}
