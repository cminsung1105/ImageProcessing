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
#define TEST_PART1_6 1

#define TEST_PART2_1 1
#define TEST_PART2_2 1
#define TEST_PART2_3 1
#define TEST_PART2_4 1
#define TEST_PART2_5 1
#define TEST_PART2_6 1
#define TEST_PART2_7 1

#define TEST_PART3_1 1
#define TEST_PART3_2 1
#define TEST_PART3_3 1
#define TEST_PART3_4 1
#define TEST_PART3_5 1
#define TEST_PART3_6 1


#endif

extern const char *yourName;
extern const char *yourStudentID;
extern const char *yourUCInetID;

void selectionSort_c(int integer_array[], int array_size);
int findMinIndex_c(int integer_array[], int i, int j);
int binarySearch_c(int data[], int toFind, int start, int end);

// These three functions should be implemented in lab6.cpp
extern void imageThresholding(unsigned char* image, int dim, unsigned char threshold);
extern int binarySearch(int integer_array[], int toFind, int start_i, int end_i);
extern void imageAveraging(unsigned char* image, int dim, unsigned char* image_out);

int main(void)
{
	int i, j;
	bool failed = false;

	vector<unsigned char> png;
	vector<unsigned char> image;
	vector<unsigned char> image2;
	vector<unsigned char> image_out;
	unsigned int width, height;
	//lodepng::State state;
	string filename, outFilename;

	printf("ICS 51, Lab 6, %s, %s, %s\n\n", yourName, yourStudentID, yourUCInetID);

	// Part 1 tests
#ifndef GRADING_MODE
	cout << endl;
	printf("\nTesting part 1 \n");
#endif

#if TEST_PART1_1
	unsigned char testStr1_1[3][3] = { { 0,  30,  60 },
	{ 90, 120, 150 },
	{ 180, 210, 240 } };

	unsigned char exptectedStr1_1[3][3] = { { 0,   0,   0 },
	{ 255, 255, 255 },
	{ 255, 255, 255 } };

	imageThresholding(&testStr1_1[0][0], 3, 90);
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j) {
			if (testStr1_1[i][j] != exptectedStr1_1[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 1 failed at index: " << i << "," << j << " got: " << int(testStr1_1[i][j]) << " expected: " << int(exptectedStr1_1[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 1: Test 1 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_2
	unsigned char testStr1_2[3][3] = { { 0,  30,  60 },
	{ 90, 120, 150 },
	{ 180, 210, 240 } };

	unsigned char exptectedStr1_2[3][3] = { { 0,   0,   0 },
	{ 0,   0, 255 },
	{ 255, 255, 255 } };
	imageThresholding(&testStr1_2[0][0], 3, 128);
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j) {
			if (testStr1_2[i][j] != exptectedStr1_2[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 2 failed at index: " << i << "," << j <<
					" got: " << int(testStr1_2[i][j]) << " expected: " << int(exptectedStr1_2[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 1: Test 2 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_3
	unsigned char testStr1_3[3][3] = { { 0,  30,  60 },
	{ 90, 120, 150 },
	{ 180, 210, 240 } };

	unsigned char exptectedStr1_3[3][3] = { { 0,   0,   0 },
	{ 0,   0,   0 },
	{ 255, 255, 255 } };

	imageThresholding(&testStr1_3[0][0], 3, 180);
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j) {
			if (testStr1_3[i][j] != exptectedStr1_3[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 3 failed at index: " << i << "," << j <<
					" got: " << int(testStr1_3[i][j]) << " expected: " << int(exptectedStr1_3[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 1: Test 3 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_4
	unsigned char testStr1_4[4][4] = { { 0,  30,  90, 120 },
	{ 127,  45, 130,  60 },
	{ 127, 128,   0, 130 },
	{ 27, 228, 255, 255 } };
	unsigned char exptectedStr1_4[4][4] = { { 0,   0,   0,   0 },
	{ 0,   0, 255,   0 },
	{ 0, 255,   0, 255 },
	{ 0, 255, 255, 255 } };
	failed = false;
	imageThresholding(&testStr1_4[0][0], 4, 128);
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j) {
			if (testStr1_4[i][j] != exptectedStr1_4[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 4 failed at index: " << i << "," << j <<
					" got: " << int(testStr1_4[i][j]) << " expected: " << int(exptectedStr1_4[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 1: Test 4 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_5
	unsigned char testStr1_5[4][4] = { { 0,   30,  90, 120 },
	{ 12,  45, 130,  60 },
	{ 12, 128,  90, 190 },
	{ 27, 228, 255, 255 } };
	unsigned char exptectedStr1_5[4][4] = { { 0,   0,   0,   0 },
	{ 0,   0,   0,   0 },
	{ 0,   0,   0,   0 },
	{ 0, 255, 255, 255 } };
	failed = false;
	imageThresholding(&testStr1_5[0][0], 4, 200);
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j) {
			if (testStr1_5[i][j] != exptectedStr1_5[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 1: Test 5 failed at index: " << i << "," << j <<
					" got: " << int(testStr1_5[i][j]) << " expected: " << int(exptectedStr1_5[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 1: Test 5 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART1_6
	filename = "bw.png";
	lodepng::decode(image, width, height, filename, LCT_GREY, 8U);
	if (image.size() == 0) {
		cerr << "bw.png not found. Make sure it exists in your solution directory." << endl;
		return -1;
	}
	assert(width == height);
	imageThresholding((unsigned char*)&image[0], width, 128);
	outFilename = "bw_binary.png";
	lodepng::encode(outFilename, image, width, height, LCT_GREY, 8U);
	image.clear();
	cout << "Check out bw_binary.png." << endl;
#endif

	int sorted_arrays[100][100] = {
		{ 4, 5, 222, 5, 5, 33, 11, -4, 12, -333, 10, -28349, 74, 323232 },
		{ +32131, +432, +232, +4, -1, -4, -5, -7, -8, -8, -9, -100000, -200000, -300000, -9999999 },
		{ -90, 1, -800, 6, -1000, 0, 0, 0, -9, 12, -1819 },
		{ 4, -5, 1, -222, 5, -5, 33, -11, -4, 12, -333, 10, +28349, 74, -323232 },
		{ 100 },
		{ -10, -100 },
		{ 666, 666, 666, 666, 666, 666, 666, -100, -100 }
	};

	int len[100] = { 15, 15, 11, 15, 1, 2, 9 };
	int correct_answer2, result2, n, index;

#ifndef GRADING_MODE
	printf("\nTesting part 2 \n");
#endif
#if TEST_PART2_1
	n = -333;
	index = 0;
	selectionSort_c(sorted_arrays[index], len[index]);
	correct_answer2 = binarySearch_c(sorted_arrays[index], n, 0, len[index] - 1);
	result2 = binarySearch(sorted_arrays[index], n, 0, len[index] - 1);
#ifndef GRADING_MODE
	if (result2 == correct_answer2)
		cout << "Part 2: Test 1 passed." << endl;
	else {
		printf("\nInput = [");
		for (int p = 0; p < len[index]; p++)
			printf(" %d ", sorted_arrays[index][p]);
		printf("] %d\nOutput = %d - %s\n", n, result2, result2 == correct_answer2 ? "CORRECT" : "INCORRECT");
	}
#endif
#ifdef GRADING_MODE
	printf("%d\n", result2 == correct_answer2 ? 1 : 0);
#endif
#endif

#if TEST_PART2_2
	n = 1000;
	index = 1;
	selectionSort_c(sorted_arrays[index], len[index]);
	correct_answer2 = binarySearch_c(sorted_arrays[index], n, 0, len[index] - 1);
	result2 = binarySearch(sorted_arrays[index], n, 0, len[index] - 1);
#ifndef GRADING_MODE
	if (result2 == correct_answer2)
		cout << "Part 2: Test 2 passed." << endl;
	else {
		printf("\nInput = [");
		for (int p = 0; p < len[index]; p++)
			printf(" %d ", sorted_arrays[index][p]);
		printf("] %d\nOutput = %d - %s\n", n, result2, result2 == correct_answer2 ? "CORRECT" : "INCORRECT");
	}
#endif
#ifdef GRADING_MODE
	printf("%d\n", result2 == correct_answer2 ? 1 : 0);
#endif
#endif

#if TEST_PART2_3
	n = 0;
	index = 2;
	selectionSort_c(sorted_arrays[index], len[index]);
	correct_answer2 = binarySearch_c(sorted_arrays[index], n, 0, len[index] - 1);
	result2 = binarySearch(sorted_arrays[index], n, 0, len[index] - 1);
#ifndef GRADING_MODE
	if (result2 == correct_answer2)
		cout << "Part 2: Test 3 passed." << endl;
	else {
		printf("\nInput = [");
		for (int p = 0; p < len[index]; p++)
			printf(" %d ", sorted_arrays[index][p]);
		printf("] %d\nOutput = %d - %s\n", n, result2, result2 == correct_answer2 ? "CORRECT" : "INCORRECT");
	}
#endif
#ifdef GRADING_MODE
	printf("%d\n", result2 == correct_answer2 ? 1 : 0);
#endif
#endif

#if TEST_PART2_4
	n = -323232;
	index = 3;
	selectionSort_c(sorted_arrays[index], len[index]);
	correct_answer2 = binarySearch_c(sorted_arrays[index], n, 0, len[index] - 1);
	result2 = binarySearch(sorted_arrays[index], n, 0, len[index] - 1);
#ifndef GRADING_MODE
	if (result2 == correct_answer2)
		cout << "Part 2: Test 4 passed." << endl;
	else {
		printf("\nInput = [");
		for (int p = 0; p < len[index]; p++)
			printf(" %d ", sorted_arrays[index][p]);
		printf("] %d\nOutput = %d - %s\n", n, result2, result2 == correct_answer2 ? "CORRECT" : "INCORRECT");
	}
#endif
#ifdef GRADING_MODE
	printf("%d\n", result2 == correct_answer2 ? 1 : 0);
#endif
#endif

#if TEST_PART2_5
	n = 1;
	index = 4;
	selectionSort_c(sorted_arrays[index], len[index]);
	correct_answer2 = binarySearch_c(sorted_arrays[index], n, 0, len[index] - 1);
	result2 = binarySearch(sorted_arrays[index], n, 0, len[index] - 1);
#ifndef GRADING_MODE
	if (result2 == correct_answer2)
		cout << "Part 2: Test 5 passed." << endl;
	else {
		printf("\nInput = [");
		for (int p = 0; p < len[index]; p++)
			printf(" %d ", sorted_arrays[index][p]);
		printf("] %d\nOutput = %d - %s\n", n, result2, result2 == correct_answer2 ? "CORRECT" : "INCORRECT");
	}
#endif
#ifdef GRADING_MODE
	printf("%d\n", result2 == correct_answer2 ? 1 : 0);
#endif
#endif

#if TEST_PART2_6
	n = -10;
	index = 5;
	selectionSort_c(sorted_arrays[index], len[index]);
	correct_answer2 = binarySearch_c(sorted_arrays[index], n, 0, len[index] - 1);
	result2 = binarySearch(sorted_arrays[index], n, 0, len[index] - 1);
#ifndef GRADING_MODE
	if (result2 == correct_answer2)
		cout << "Part 2: Test 6 passed." << endl;
	else {
		printf("\nInput = [");
		for (int p = 0; p < len[index]; p++)
			printf(" %d ", sorted_arrays[index][p]);
		printf("] %d\nOutput = %d - %s\n", n, result2, result2 == correct_answer2 ? "CORRECT" : "INCORRECT");
	}
#endif
#ifdef GRADING_MODE
	printf("%d\n", result2 == correct_answer2 ? 1 : 0);
#endif
#endif

#if TEST_PART2_7
	n = -100;
	index = 6;
	selectionSort_c(sorted_arrays[index], len[index]);
	correct_answer2 = binarySearch_c(sorted_arrays[index], n, 0, len[index] - 1);
	result2 = binarySearch(sorted_arrays[index], n, 0, len[index] - 1);
#ifndef GRADING_MODE
	if (result2 == correct_answer2)
		cout << "Part 2: Test 7 passed." << endl;
	else {
		printf("\nInput = [");
		for (int p = 0; p < len[index]; p++)
			printf(" %d ", sorted_arrays[index][p]);
		printf("] %d\nOutput = %d - %s\n", n, result2, result2 == correct_answer2 ? "CORRECT" : "INCORRECT");
	}
#endif
#ifdef GRADING_MODE
	printf("%d\n", result2 == correct_answer2 ? 1 : 0);
#endif
#endif

#ifndef GRADING_MODE
	printf("\nTesting part 3 \n");
#endif
#if TEST_PART3_1
	unsigned char arr_test3_1[5][5] =	{ { 1, 2, 3, 4, 5},
										{ 6,  7, 8, 9, 10},
										{ 11, 12,  13, 14, 15},
										{ 16, 17, 18, 19, 20}, 
										{ 21, 22, 23, 24, 25}};
	unsigned char correct_out3_1[5][5] = { { 4,  4,  5,  6,  7 },
										{ 6,  7,  8,  9,  9 },
										{ 11, 12, 13, 14, 14 },
										{ 16, 17, 18, 19, 19 },
										{ 19, 19, 20, 21, 22 } };
	unsigned char arr_out3_1[5][5];
	int dim = 5;
	imageAveraging(&arr_test3_1[0][0], dim, &arr_out3_1[0][0]);
	for (i = 0; i < dim; ++i)
		for (j = 0; j < dim; ++j) {
			if (arr_out3_1[i][j] != correct_out3_1[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 3: Test 1 failed at index: " << i << "," << j << " got: " << int(arr_out3_1[i][j]) << " expected: " << int(correct_out3_1[i][j]) << endl;
#endif
				failed = true;
			}
			}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 3: Test 1 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART3_2
	unsigned char arr_test3_2[7][7] = {{225, 3, 3, 0, 255, 3, 0},
		{6, 255, 8, 0, 234, 1, 45},
		{11, 12, 255, 14, 12, 78, 167},
		{234, 200, 255, 135, 190, 114, 98},
		{3, 150, 180, 98, 89, 245, 0},
		{1, 100, 200, 255, 225, 150, 75},
		{98, 87, 76, 65, 54, 43, 32}};
	unsigned char correct_out3_2[7][7] = {{122, 83, 44, 83, 82, 89, 12},
		{85, 86, 61, 86, 66, 88, 49},
		{119, 137, 126, 122, 86, 104, 83},
		{101, 144, 144, 136, 108, 110, 117},
		{114, 147, 174, 180, 166, 131, 113},
		{73, 99, 134, 138, 136, 101, 90},
		{71, 93, 130, 145, 132, 96, 75}};
	unsigned char arr_out3_2[7][7];
	dim = 7;
	imageAveraging(&arr_test3_2[0][0], dim, &arr_out3_2[0][0]);
	for (i = 0; i < dim; ++i)
		for (j = 0; j < dim; ++j) {
			if (arr_out3_2[i][j] != correct_out3_2[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 3: Test 2 failed at index: " << i << "," << j << " got: " << int(arr_out3_2[i][j]) << " expected: " << int(correct_out3_2[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 3: Test 2 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART3_3
	unsigned char arr_test3_3[15][15] = {{164, 57, 135, 55, 253, 246, 236, 123, 247, 193, 15, 249, 56, 156, 136},
		{110, 198, 103, 243, 1, 176, 18, 64, 132, 44, 49, 36, 78, 189, 3},
		{65, 59, 237, 107, 206, 117, 83, 106, 127, 211, 126, 120, 164, 233, 71},
		{127, 123, 179, 246, 184, 214, 223, 213, 162, 104, 226, 78, 152, 253, 40},
		{86, 129, 46, 20, 159, 30, 217, 252, 188, 152, 130, 106, 47, 83, 241},
		{193, 96, 238, 206, 224, 117, 157, 134, 85, 76, 57, 10, 185, 218, 48},
		{235, 98, 63, 192, 129, 60, 26, 46, 102, 241, 146, 12, 6, 227, 64},
		{85, 71, 186, 65, 37, 83, 116, 246, 156, 202, 86, 184, 110, 211, 166},
		{196, 213, 110, 52, 92, 101, 180, 220, 153, 190, 10, 211, 77, 4, 142},
		{206, 238, 45, 169, 162, 14, 61, 20, 175, 19, 22, 6, 81, 91, 185},
		{98, 225, 138, 62, 116, 93, 163, 227, 22, 108, 246, 99, 87, 255, 74},
		{99, 198, 111, 129, 75, 171, 251, 208, 141, 123, 36, 189, 35, 229, 96},
		{196, 97, 95, 171, 81, 71, 107, 223, 108, 232, 80, 230, 220, 35, 83},
		{73, 75, 59, 69, 146, 239, 202, 247, 195, 211, 214, 105, 87, 193, 14},
		{121, 19, 30, 193, 5, 166, 105, 21, 175, 177, 201, 145, 172, 57, 60}};
	unsigned char correct_out3_3[15][15] = {{132, 127, 131, 131, 162, 155, 143, 136, 133, 113, 97, 80, 127, 103, 121},
		{108, 125, 132, 148, 156, 148, 129, 126, 138, 127, 115, 99, 142, 120, 131},
		{113, 133, 166, 167, 166, 135, 134, 125, 129, 131, 110, 114, 144, 131, 131},
		{98, 116, 127, 153, 142, 159, 161, 174, 168, 158, 139, 127, 137, 142, 153},
		{125, 135, 142, 166, 155, 169, 173, 181, 151, 131, 104, 110, 125, 140, 147},
		{139, 131, 120, 141, 126, 124, 115, 134, 141, 130, 103, 77, 99, 124, 146},
		{129, 140, 135, 148, 123, 105, 109, 118, 143, 127, 112, 88, 129, 137, 155},
		{149, 139, 116, 102, 90, 91, 119, 138, 172, 142, 142, 93, 115, 111, 135},
		{168, 150, 127, 102, 86, 94, 115, 147, 153, 112, 103, 87, 108, 118, 133},
		{196, 163, 139, 105, 95, 109, 119, 135, 126, 105, 101, 93, 101, 110, 125},
		{177, 150, 146, 111, 110, 122, 134, 140, 115, 99, 94, 89, 119, 125, 155},
		{152, 139, 136, 108, 107, 125, 168, 161, 154, 121, 149, 135, 153, 123, 128},
		{123, 111, 111, 104, 128, 149, 191, 186, 187, 148, 157, 132, 147, 110, 108},
		{96, 85, 89, 94, 126, 124, 153, 153, 176, 177, 177, 161, 138, 102, 73},
		{72, 62, 74, 83, 136, 143, 163, 157, 171, 195, 175, 154, 126, 97, 81}};
	unsigned char arr_out3_3[15][15];
	dim = 15;
	imageAveraging(&arr_test3_3[0][0], dim, &arr_out3_3[0][0]);
	for (i = 0; i < 5; ++i)
		for (j = 0; j < 5; ++j) {
			if (arr_out3_3[i][j] != correct_out3_3[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 3: Test 3 failed at index: " << i << "," << j << " got: " << int(arr_out3_3[i][j]) << " expected: " << int(correct_out3_3[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 3: Test 3 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART3_4
	unsigned char arr_test3_4[2][2] = {{247, 133},{62, 81}};
	unsigned char correct_out3_4[2][2] = {{130, 130}, {130, 130}};
	unsigned char arr_out3_4[2][2];
	dim = 2;
	imageAveraging(&arr_test3_4[0][0], dim, &arr_out3_4[0][0]);
	for (i = 0; i < dim; ++i)
		for (j = 0; j < dim; ++j) {
			if (arr_out3_4[i][j] != correct_out3_4[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 3: Test 4 failed at index: " << i << "," << j << " got: " << int(arr_out3_4[i][j]) << " expected: " << int(correct_out3_4[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 3: Test 4 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART3_5
	unsigned char arr_test3_5[10][10] = {{152, 254, 83, 218, 117, 13, 78, 87, 84, 147},
		{186, 201, 175, 168, 80, 240, 176, 211, 255, 127},
		{189, 82, 227, 185, 35, 230, 217, 144, 30, 162},
		{70, 230, 101, 255, 242, 148, 158, 106, 200, 231},
		{248, 97, 243, 125, 205, 241, 73, 48, 224, 132},
		{227, 100, 8, 18, 107, 220, 24, 246, 61, 195},
		{3, 30, 248, 98, 219, 135, 252, 114, 71, 225},
		{158, 162, 9, 221, 48, 202, 204, 138, 6, 110},
		{240, 206, 214, 47, 217, 255, 230, 74, 2, 37},
		{235, 187, 179, 60, 83, 43, 120, 185, 247, 56}};
	unsigned char correct_out3_5[10][10] = {{198, 175, 183, 140, 139, 117, 134, 148, 151, 153},
		{177, 172, 177, 143, 142, 131, 155, 142, 138, 134},
		{159, 162, 180, 163, 175, 169, 181, 166, 162, 167},
		{152, 165, 171, 179, 185, 172, 151, 133, 141, 163},
		{162, 147, 130, 144, 173, 157, 140, 126, 160, 173},
		{117, 133, 107, 141, 152, 164, 150, 123, 146, 151},
		{113, 105, 99, 108, 140, 156, 170, 124, 129, 111},
		{133, 141, 137, 146, 160, 195, 178, 121, 86, 75},
		{198, 176, 142, 119, 130, 155, 161, 134, 95, 76},
		{217, 210, 148, 133, 117, 158, 151, 143, 100, 85}};
	unsigned char arr_out3_5[10][10];
	dim = 10;
	imageAveraging(&arr_test3_5[0][0], dim, &arr_out3_5[0][0]);
	for (i = 0; i < dim; ++i)
		for (j = 0; j < dim; ++j) {
			if (arr_out3_5[i][j] != correct_out3_5[i][j]) {
#ifndef GRADING_MODE
				cout << "Part 3: Test 5 failed at index: " << i << "," << j << " got: " << int(arr_out3_5[i][j]) << " expected: " << int(correct_out3_5[i][j]) << endl;
#endif
				failed = true;
			}
		}
	if (!failed) {
#ifndef GRADING_MODE
		cout << "Part 3: Test 5 passed." << endl;
#endif
	}
#ifdef GRADING_MODE
	cout << !failed << endl;
#endif
#endif

#if TEST_PART3_6
	filename = "ship.png";
	lodepng::decode(image, width, height, filename, LCT_GREY, 8U);
	if (image.size() == 0) {
		cerr << "ship.png not found. Make sure it exists in your solution directory." << endl;
		return -1;
	}
	assert(width == height);
	lodepng::decode(image_out, width, height, filename, LCT_GREY, 8U);
	if (image_out.size() == 0) {
		cerr << "ship.png not found. Make sure it exists in your solution directory." << endl;
		return -1;
	}
	assert(width == height);
	imageAveraging((unsigned char*)&image[0], width, (unsigned char*)&image_out[0]);
	outFilename = "ship_denoised.png";
	lodepng::encode(outFilename, image_out, width, height, LCT_GREY, 8U);
	image.clear();
	image_out.clear();
	cout << "Check out ship_denoised.png." << endl;
#endif

#ifndef GRADING_MODE
	cout << "" << endl;
	getchar();
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

int binarySearch_c(int data[], int toFind, int start, int end)
{
	//Get the midpoint.
	int mid = start + (end - start) / 2;   //Integer division

										   //Stop condition.
	if (start > end)
		return -1;
	else if (data[mid] == toFind)        //Found?
		return mid;
	else if (data[mid] > toFind)         //Data is greater than toFind, search lower half
		return binarySearch_c(data, toFind, start, mid - 1);
	else                                 //Data is less than toFind, search upper half
		return binarySearch_c(data, toFind, mid + 1, end);
}

/****************************************************************************************/
