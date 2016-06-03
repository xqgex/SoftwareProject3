#include "../SPPoint.h"
#include "unit_test_util.h"
#include <stdbool.h>

//Checks if copy Works
bool pointBasicCopyTest() {
	double data[2] = { 1.0, 1.0 };
	int dim = 2;
	int index = 1;
	int i;
	SPPoint p = spPointCreate(data, dim, index);
	SPPoint q = spPointCopy(p);
	ASSERT_TRUE(spPointGetIndex(p) == spPointGetIndex(q));
	ASSERT_TRUE(spPointGetDimension(p) == spPointGetDimension(q));
	for (i = 0; i < spPointGetDimension(p); i++) {
		ASSERT_TRUE(spPointGetAxisCoor(p, i) == spPointGetAxisCoor(q, i));
	}
	spPointDestroy(p);
	spPointDestroy(q);
	return true;
}

bool pointBasicL2Distance() {
	double data1[2] = { 1.0, 1.0 };
	double data2[2] = { 1.0, 0.0 };
	int dim1 = 2;
	int dim2 = 2;
	int index1 = 1;
	int index2 = 1;
	SPPoint p = spPointCreate((double *)data1, dim1, index1);
	SPPoint q = spPointCreate((double *)data2, dim2, index2);
	ASSERT_TRUE(spPointL2SquaredDistance(p,p) == 0.0);
	ASSERT_TRUE(spPointL2SquaredDistance(q,q) == 0.0);
	ASSERT_FALSE(spPointL2SquaredDistance(p,q) == 0.0);
	spPointDestroy(p);
	spPointDestroy(q);
	return true;
}

bool pointCreateInputTest(){
	// Function variables
	double data1[3] = { 1.0, 2.0, 3.0 };
	double data2[0];
	int validIndex = 1;
	int invalidIndex = -1;
	int data1Dim = 3;
	int data2Dim = 0;
	int invalidDim = -1;
	int smallerDim = 2;
	// SPPoint variables
	SPPoint validPointTest = spPointCreate(data1,data1Dim,validIndex);
	SPPoint dataTest = spPointCreate(NULL,data1Dim,validIndex); // data is NULL
	SPPoint dimTest = spPointCreate(data1,invalidDim,validIndex); // dim < 0
	SPPoint indexTest = spPointCreate(data1,data1Dim,invalidIndex); // index < 0
	SPPoint emptyTest = spPointCreate(data2,data2Dim,validIndex);// data2 size is 0
	SPPoint overflowTest = spPointCreate(data1,smallerDim,validIndex); // dim < data1 size
	// Assertions
	ASSERT_TRUE(validPointTest != NULL);
	ASSERT_TRUE(dataTest == NULL);
	ASSERT_TRUE(dimTest == NULL);
	ASSERT_TRUE(indexTest == NULL);
	ASSERT_TRUE(emptyTest == NULL);
	ASSERT_TRUE(overflowTest != NULL);
	// Deallocation
	spPointDestroy(validPointTest);
	spPointDestroy(dataTest);
	spPointDestroy(dimTest);
	spPointDestroy(indexTest);
	spPointDestroy(emptyTest);
	spPointDestroy(overflowTest);
	return true;
}

bool pointCreateSafetyTest(){
	// Function variables
	double data[3] = { 1.0, 2.0, 3.0 };
	int changeIndex = 0;
	int dim = 3;
	int index = 1;
	// SPPoint variables
	SPPoint dataTest = spPointCreate(data,dim,index);
	data[changeIndex] = 4.0;
	// Assertions
	ASSERT_TRUE(spPointGetAxisCoor(dataTest, changeIndex) == 1.0);
	// Deallocation
	spPointDestroy(dataTest);
	return true;
}

bool pointCopySafetyTest(){
	// Function variables
	double data[3] = { 1.0, 2.0, 3.0 };
	int dim = 3;
	int index = 1;
	// SPPoint variables
	SPPoint original = spPointCreate(data,dim,index);
	SPPoint copy = spPointCopy(original);
	// Assertions
	spPointDestroy(original); // destroy original, check if copy is still accessible
	ASSERT_TRUE(copy != NULL);
	ASSERT_TRUE(spPointGetIndex(copy) == index);
	ASSERT_TRUE(spPointGetDimension(copy) == dim);
	// Deallocation
	spPointDestroy(copy);
	return true;

}

bool pointGettersTest(){
	// Function variables
	double data[3] = { 1.0, 2.0, 3.0 };
	int dim = 3;
	int index = 1;
	int i; // Generic loop variable
	// SPPoint variables
	SPPoint point = spPointCreate(data,dim,index);
	// Assertions
	ASSERT_TRUE(spPointGetDimension(point) == dim);
	ASSERT_TRUE(spPointGetIndex(point) == index);
	for (i = 0; i < spPointGetDimension(point); i++) {
		ASSERT_TRUE(spPointGetAxisCoor(point, i) == data[i]);
	}
	// Deallocation
	spPointDestroy(point);
	return true;
}

bool pointL2DistanceTest(){
	// Function variables
	double data1[2] = { 1.0, 1.0 };
	double data2[2] = { -1.0, -2.0 };
	double data3[2] = { 3.0, 3.0 };
	double data4[2] = { 1.0, 0.0 };
	int dim = 2;
	int index = 1;
	int distance;
	// SPPoint variables
	SPPoint p1 = spPointCreate(data1, dim, index);
	SPPoint p2 = spPointCreate(data2, dim, index);
	SPPoint p3 = spPointCreate(data3, dim, index);
	SPPoint p4 = spPointCreate(data4, dim, index);
	// Assertions
	ASSERT_TRUE(spPointL2SquaredDistance(p1,p2) >= 0.0); // non-negativity
	ASSERT_TRUE(spPointL2SquaredDistance(p1,p1) == 0.0); // reflexive
	ASSERT_TRUE(spPointL2SquaredDistance(p1,p2) == spPointL2SquaredDistance(p2,p1)); // symmetry
	distance = spPointL2SquaredDistance(p1,p2) + spPointL2SquaredDistance(p2,p3);
	ASSERT_TRUE(spPointL2SquaredDistance(p1,p3) <= distance); // triangle inequality
	ASSERT_TRUE(spPointL2SquaredDistance(p1,p2) == spPointL2SquaredDistance(p3,p4)); // translation invariant
	// Deallocation
	spPointDestroy(p1);
	spPointDestroy(p2);
	spPointDestroy(p3);
	spPointDestroy(p4);
	return true;
}

int main() {
	RUN_TEST(pointBasicCopyTest);
	RUN_TEST(pointBasicL2Distance);
	RUN_TEST(pointCreateInputTest);
	RUN_TEST(pointCreateSafetyTest);
	RUN_TEST(pointCopySafetyTest);
	RUN_TEST(pointGettersTest);
	RUN_TEST(pointL2DistanceTest);
	return 0;
}
