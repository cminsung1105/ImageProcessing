#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "lodepng.h"

using namespace std;

#ifndef GRADING_MODE
// Once you are done implementing the required functions, enable the testcases        
#define TEST_PART1_1 1
#define TEST_PART1_2 1
#define TEST_PART1_3 1
#define TEST_PART1_4 1
#define TEST_PART1_5 1
#define TEST_PART1 1 
#define TEST_PART2 1 

#define FIRST_TESTCASE 0
#define LAST_TESTCASE num_of_testcases
#endif

#ifdef GRADING_MODE
#define FIRST_TESTCASE TESTCASE_NUM-1
#define LAST_TESTCASE TESTCASE_NUM
#endif

#define ANSI_COLOR_RED     /*"\x1b[31m"*/
#define ANSI_COLOR_GREEN   /*"\x1b[32m"*/
#define ANSI_COLOR_YELLOW  /*"\x1b[33m"*/
#define ANSI_COLOR_RESET   /*"\x1b[0m"*/

extern const char *yourName;
extern const char *yourStudentID;
extern const char *yourUCInetID;

// These two functions should be implemented in lab5.cpp
extern void selectionSort(int integer_array[], int array_size);
extern void imageRotation(unsigned int* image, int dim, int n);

void test_selectionSort();
int test_rotation();

unsigned int total_num_of_tests = 0;
unsigned int total_num_of_tests_passed = 0;

int main(void)
{
	printf("ICS 51, Lab 5, %s, %s, %s\n\n", yourName, yourStudentID, yourUCInetID);

#if TEST_PART1
#ifndef GRADING_MODE
	printf("====================== PART1 ======================\n");
#endif
	test_rotation();
	printf("\n");
#endif

#if TEST_PART2
#ifndef GRADING_MODE
	printf("====================== PART2 ======================\n");
#endif
	test_selectionSort();
	printf("\n");
#endif

#ifndef GRADING_MODE
	printf("===================== SUMMARY =====================\n");

	if (total_num_of_tests_passed == 0)
		printf(ANSI_COLOR_RED "All %d tests failed.\n\n" ANSI_COLOR_RESET, total_num_of_tests);
	else if (total_num_of_tests == total_num_of_tests_passed)
		printf(ANSI_COLOR_GREEN "All %d tests passed.\n\n" ANSI_COLOR_RESET, total_num_of_tests);
	else
		printf(ANSI_COLOR_YELLOW "%d out of %d tests passed.\n\n" ANSI_COLOR_RESET,
			total_num_of_tests_passed, total_num_of_tests);
#endif

#ifndef GRADING_MODE
	getchar();
#endif

	return 0;
}


int test_rotation() {
	int i, j;
	bool failed = false;

	vector<unsigned char> png;
	vector<unsigned char> image;
	vector<unsigned char> image2;
	unsigned int width, height;
	//lodepng::State state;
	string filename, outFilename;

	// Part 1 tests
#ifndef GRADING_MODE
	cout << endl;
#endif

#if TEST_PART1_1
	total_num_of_tests++;
	unsigned int testStr2_5[3][3] = { { 0x00000000, 0x10101010, 0x20202020 },
	{ 0x30303030, 0x40404040, 0x50505050 },
	{ 0x60606060, 0x70707070, 0x80808080 } };


	unsigned int exptectedStr2_5[3][3] = { { 0x60606060,  0x30303030, 0x00000000 },
	{ 0x70707070,  0x40404040, 0x10101010 },
	{ 0x80808080,  0x50505050, 0x20202020 } };

	imageRotation(&testStr2_5[0][0], 3, 1);
	failed = false;
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j) {
			if (testStr2_5[i][j] != exptectedStr2_5[i][j]) {
#ifndef GRADING_MODE
				cout << hex << "Part 1: Test 1 failed at index: " << i << "," << j <<
					" got(Hex): " << testStr2_5[i][j] << " expected(Hex): " << exptectedStr2_5[i][j] << endl;
#endif
				failed = true;
			}
		}
	if (!failed){
#ifndef GRADING_MODE
		cout << "Part 1: Test 1 passed." << endl;
		total_num_of_tests_passed++;
	}
#endif
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_2
	total_num_of_tests++;
	unsigned int testStr2_6[4][4] = { { 0,   1,  2,  3 },
	{ 4,   5,  6,  7 },
	{ 8,   9, 10, 11 },
	{ 12, 13, 14, 15 } };
	unsigned int exptectedStr2_6[4][4] = { { 15, 14, 13, 12 },
	{ 11, 10, 9, 8 },
	{ 7, 6, 5, 4 },
	{ 3, 2, 1, 0 } };
	failed = false;
	imageRotation(&testStr2_6[0][0], 4, 2);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (testStr2_6[i][j] != exptectedStr2_6[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 2 failed at index: " << i << "," << j <<
					" got(Hex): " << testStr2_6[i][j] << " expected(Hex): " << exptectedStr2_6[i][j] << endl;
#endif
				failed = true;
			}
		}
	}
	if (!failed){
#ifndef GRADING_MODE
		cout << "Part 1: Test 2 passed." << endl;
		total_num_of_tests_passed++;
	}
#endif
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_3
	total_num_of_tests++;
	unsigned int testStr2_7[4][4] = { { 10, 1,   2, 13 },
	{ 4,  5,   6,  7 },
	{ 8,  9,  10, 11 },
	{ 12, 13, 14, 15 } };
	unsigned int exptectedStr2_7[4][4] = { { 13,  7, 11, 15 },
	{ 2,  6, 10, 14 },
	{ 1, 5, 9, 13 },
	{ 10, 4, 8, 12 } };
	failed = false;
	imageRotation(&testStr2_7[0][0], 4, 7);
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (testStr2_7[i][j] != exptectedStr2_7[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 3 failed at index: " << i << "," << j <<
					" got(Hex): " << testStr2_7[i][j] << " expected(Hex): " << exptectedStr2_7[i][j] << endl;
#endif
				failed = true;
			}
		}
	}
	if (!failed){
#ifndef GRADING_MODE
		cout << "Part 1: Test 3 passed." << endl;
		total_num_of_tests_passed++;
	}
#endif
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_4
	total_num_of_tests++;
#define DIM 11
	unsigned int testStr2_8[DIM][DIM];
	unsigned int exptectedStr2_8[DIM][DIM];
	for (i = 0; i < DIM; ++i) {
		for (j = 0; j < DIM; ++j) {
			testStr2_8[i][j] = DIM*(i + j);
			exptectedStr2_8[j][DIM - i - 1] = DIM*(i + j);
		}
	}

	failed = false;
	imageRotation(&testStr2_8[0][0], DIM, 9);
	for (i = 0; i < DIM; ++i) {
		for (j = 0; j < DIM; ++j) {
			if (testStr2_8[i][j] != exptectedStr2_8[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 4 failed at index: " << i << "," << j <<
					" got(Hex): " << testStr2_8[i][j] << " expected(Hex): " << exptectedStr2_8[i][j] << endl;
#endif
				failed = true;
			}
		}
	}
	if (!failed){
#ifndef GRADING_MODE
		cout << "Part 1: Test 4 passed." << endl;
		total_num_of_tests_passed++;
	}
#endif
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_5
	// Load a RGBA png (4-Bytes per pixel)
	filename = "lion.png";
	lodepng::decode(image2, width, height, filename, LCT_RGBA, 8U);
	if (image2.size() == 0) {
		cerr << "lion.png not found. Make sure you have this file in your solution directory." << endl;
		return -1;
	}
	assert(width == height);
	imageRotation((unsigned int*)&image2[0], width, 22);
	outFilename = "lion_rotated_22.png";
	lodepng::encode(outFilename, image2, width, height, LCT_RGBA, 8U);
	cout << "Check out lion_rotated_22.png" << endl;
#endif

#ifndef GRADING_MODE
	cout << "" << endl;
#endif
	return 0;
}

int findMinIndex_c(int integer_array[], int i, int j)
{
	int iMin = i;
	// test against elements after i and before j to find the smallest 
	for (i; i < j; i++) {
		// if this element is less, then it is the new minimum   
		if (integer_array[i] < integer_array[iMin]) {
			// found new minimum; remember its index 
			iMin = i;
		}
	}

	return iMin;
}

void selectionSort_c(int integer_array[], int array_size)
{
	int j;
	int iMin;
	int temp;

	// advance the position through the entire array //
	// (could do j < n-1 because single element is also min element) //
	for (j = 0; j < array_size - 1; j++) {

		// find the index of min element in the unsorted a[j .. n-1] //
		iMin = findMinIndex_c(integer_array, j, array_size);

		if (iMin != j) { // swap values
			temp = integer_array[iMin];
			integer_array[iMin] = integer_array[j];
			integer_array[j] = temp;
		}
	}
}

int compare_arrays(int a[], int b[], int len)
{
	for (int ii = 1; ii <= len; ii++) {
		if (a[ii] != b[ii])
			return 0;
	}
	return 1;
}

void test_selectionSort()
{
	int num_of_testcases = 7;
	int student_arrayOfNumbers[100][100] = {
		{ 4, 5, 1, 222, 5, 5, 33, 11, -4, 12, -333, 10, -28349, 74, 323232 },
		{ +32131, +432, +232, +4, -1, -4, -5, -7, -8, -8, -9, -100000, -200000, -300000, -9999999 },
		{ -90, 1, -800, 6, -1000, 0, 0, 0, -9, 12, -1819 },
		{ 4, -5, 1, -222, 5, -5, 33, -11, -4, 12, -333, 10, +28349, 74, -323232 },
		{ 100 },
		{ -10, -100 },
		{ 666, 666, 666, 666, 666, 666, 666, -100, -100 }
	};

	int golden_arrayOfNumbers[100][100] = {
		{ 4, 5, 1, 222, 5, 5, 33, 11, -4, 12, -333, 10, -28349, 74, 323232 },
		{ +32131, +432, +232, +4, -1, -4, -5, -7, -8, -8, -9, -100000, -200000, -300000, -9999999 },
		{ -90, 1, -800, 6, -1000, 0, 0, 0, -9, 12, -1819 },
		{ 4, -5, 1, -222, 5, -5, 33, -11, -4, 12, -333, 10, +28349, 74, -323232 },
		{ 100 },
		{ -10, -100 },
		{ 666, 666, 666, 666, 666, 666, 666, -100, -100 }
	};

	int len[100] = { 15, 15, 11, 15, 1, 2, 9 };

	int err = 0;
	int i;
	for (i = FIRST_TESTCASE; i < LAST_TESTCASE; i++) {
		total_num_of_tests++;
		selectionSort_c((golden_arrayOfNumbers[i]), len[i]);
		selectionSort((student_arrayOfNumbers[i]), len[i]);
		if (!compare_arrays(golden_arrayOfNumbers[i], student_arrayOfNumbers[i], len[i])) {
			err = 1;
#ifndef GRADING_MODE
			printf("\nCorrect output:\n");
			for (int j = 0; j<len[i]; j++) {
				printf("%d ", golden_arrayOfNumbers[i][j]);
			}

			printf("\nYour output:\n");
			for (int j = 0; j<len[i]; j++) {
				printf("%d ", student_arrayOfNumbers[i][j]);
			}
			printf("\n");
#endif
		}
		else {
			total_num_of_tests_passed++;
		}
	}

	if (!err) {
#ifndef GRADING_MODE
		printf(ANSI_COLOR_GREEN "All tests passed.\n" ANSI_COLOR_RESET);
#endif
	}

#ifdef GRADING_MODE
	printf("%d\n", !err);
#endif
}

/****************************************************************************************/
