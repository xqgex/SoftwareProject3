#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>


bool queueCreateInputTest(){
	// Function variables
	int validMaxSize = 2;
	int invalidMaxSize = -2;
	int emptyQueueMaxSize = 0;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(validMaxSize);
	SPBPQueue q2 = spBPQueueCreate(invalidMaxSize);
	SPBPQueue q3 = spBPQueueCreate(emptyQueueMaxSize); // valid
	// Assertions
	ASSERT_TRUE(q1 != NULL);
	ASSERT_TRUE(q2 == NULL);
	ASSERT_TRUE(q3 != NULL);
	// Deallocation
	spBPQueueDestroy(q1);
	spBPQueueDestroy(q2);
	return true;
}

bool queueCopyInputTest(){
	// Function variables
	int maxSize = 2;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPBPQueue q2 = spBPQueueCopy(q1);
	SPListElement e1 = spListElementCreate(1,1);
	SPListElement e2 = spListElementCreate(2,2);
	spBPQueueEnqueue(q1,e1);
	spBPQueueEnqueue(q1,e2);
	SPBPQueue q3 = spBPQueueCopy(q1);
	SPBPQueue q4 = spBPQueueCopy(NULL);
	// Assertions
	ASSERT_TRUE(q1 != NULL);
	ASSERT_TRUE(q2 != NULL);
	ASSERT_TRUE(q3 != NULL);
	ASSERT_TRUE(q4 == NULL);
	ASSERT_TRUE(spBPQueueSize(q2) != spBPQueueSize(q3));
	ASSERT_TRUE(spBPQueueSize(q1) == spBPQueueSize(q3));
	ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),spBPQueuePeek(q3)) == 0);
	spBPQueueDequeue(q1);
	spBPQueueDequeue(q3);
	ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),spBPQueuePeek(q3)) == 0);
	// Deallocation
	spBPQueueDestroy(q1);
	spBPQueueDestroy(q2);
	spBPQueueDestroy(q3);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	return true;
}

bool queueCopySafetyTest(){
	// Function variables
	int maxSize = 2;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(1,1);
	SPListElement e2 = spListElementCreate(3,3);
	SPListElement e3 = spListElementCreate(2,2);
	spBPQueueEnqueue(q1,e1);
	spBPQueueEnqueue(q1,e2);
	SPBPQueue q2 = spBPQueueCopy(q1);
	// Assertions
	ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),spBPQueuePeek(q2)) == 0);
	spBPQueueDequeue(q1);
	spBPQueueEnqueue(q1,e3);
	ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),spBPQueuePeek(q2)) != 0);
	// Deallocation
	spBPQueueDestroy(q1);
	spBPQueueDestroy(q2);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	spListElementDestroy(e3);
	return true;
}

bool queueClearTest(){
	// Function variables
	int maxSize = 2;
	int numOfElements = 2;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(1,1);
	SPListElement e2 = spListElementCreate(3,3);
	spBPQueueEnqueue(q1,e1);
	spBPQueueEnqueue(q1,e2);
	// Assertions
	ASSERT_TRUE(spBPQueueSize(q1) == numOfElements);
	spBPQueueClear(q1);
	ASSERT_TRUE(q1 != NULL);
	ASSERT_TRUE(spBPQueueSize(q1) == 0);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1) == maxSize);
	spBPQueueClear(NULL); // should do nothing
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	return true;
}
bool queueSizeTest(){
	// Function variables
	int maxSize1 = 3;
	int maxSize2 = 1;
	int numOfElements = 2;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize1);
	SPBPQueue q2 = spBPQueueCreate(maxSize2);
	SPListElement e1 = spListElementCreate(1,1);
	SPListElement e2 = spListElementCreate(3,3);
	spBPQueueEnqueue(q1,e1); // 1/3
	spBPQueueEnqueue(q1,e2); // 2/3
	spBPQueueEnqueue(q2,e1); // 1/1
	spBPQueueEnqueue(q2,e2); // overflow -> 1/1
	// Assertions
	ASSERT_TRUE(spBPQueueSize(q1) == numOfElements);
	ASSERT_TRUE(spBPQueueSize(q2) != numOfElements);
	spBPQueueDequeue(q2);
	spBPQueueDequeue(q2); // Dequeue from empty queue
	ASSERT_TRUE(spBPQueueSize(q2) == 0);
	// Deallocation
	spBPQueueDestroy(q1);
	spBPQueueDestroy(q2);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	return true;
}
bool queueMaxSizeTest(){
	// Function variables
	int maxSize = 1;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(1,1);
	// Assertions
	ASSERT_TRUE(spBPQueueGetMaxSize(q1) == maxSize); // empty queue
	spBPQueueEnqueue(q1,e1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1) == maxSize); // full queue
	spBPQueueEnqueue(q1,e1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1) == maxSize); // full queue after overflow
	spBPQueueDequeue(q1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1) == maxSize); // after dequeue
	spBPQueueClear(q1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1) == maxSize); // after clear
	spBPQueueDequeue(q1);
	ASSERT_TRUE(spBPQueueGetMaxSize(q1) == maxSize); // after dequeue from empty queue
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	return true;
}

bool queuePeeksTest(){
	// Function variables
	int maxSize = 2;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(2,2);
	SPListElement e2 = spListElementCreate(1,2);
	// Assertions
	ASSERT_TRUE(spBPQueuePeek(NULL) == NULL);
	ASSERT_TRUE(spBPQueuePeekLast(NULL) == NULL);
	ASSERT_TRUE(spBPQueuePeek(q1) == NULL); // empty queue
	ASSERT_TRUE(spBPQueuePeekLast(q1) == NULL);
	spBPQueueEnqueue(q1,e1);
	ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),e1) == 0); // single element
	ASSERT_TRUE(spListElementCompare(spBPQueuePeekLast(q1),e1) == 0);
	spBPQueueEnqueue(q1,e2);
	ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),e1) != 0); // two elements
	ASSERT_TRUE(spListElementCompare(spBPQueuePeekLast(q1),e1) == 0);
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	return true;
}

bool queueMinMaxTest(){
	// Function variables
	int maxSize = 2;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(2,2);
	SPListElement e2 = spListElementCreate(1,2);
	SPListElement e3 = spListElementCreate(2,1);
	SPListElement e4 = spListElementCreate(10,10);
	// Assertions
	ASSERT_TRUE(spBPQueueMinValue(NULL) == -1);
	ASSERT_TRUE(spBPQueueMaxValue(NULL) == -1);
	ASSERT_TRUE(spBPQueueMinValue(q1) == -1); // empty queue
	ASSERT_TRUE(spBPQueueMaxValue(q1) == -1);
	spBPQueueEnqueue(q1,e1);
	ASSERT_TRUE(spBPQueueMinValue(q1) == 2); // single element (2,2)
	ASSERT_TRUE(spBPQueueMaxValue(q1) == 2);
	spBPQueueEnqueue(q1,e2);
	ASSERT_TRUE(spBPQueueMinValue(q1) == 2); // two elements
	ASSERT_TRUE(spBPQueueMaxValue(q1) == 2);
	spBPQueueEnqueue(q1,e3);
	ASSERT_TRUE(spBPQueueMinValue(q1) == 1); // two elements, pushed (2,2) out
	ASSERT_TRUE(spBPQueueMaxValue(q1) == 2);
	spBPQueueEnqueue(q1,e4);
	ASSERT_TRUE(spBPQueueMinValue(q1) == 1); // two elements,(20,10) is too high to get in
	ASSERT_TRUE(spBPQueueMaxValue(q1) == 2);
	spBPQueueDequeue(q1);
	ASSERT_TRUE(spBPQueueMinValue(q1) == 2); // single element (1,2)
	ASSERT_TRUE(spBPQueueMaxValue(q1) == 2);
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	spListElementDestroy(e3);
	spListElementDestroy(e4);
	return true;
}

bool queueEmptyTest(){
	// Function variables
	int maxSize = 2;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(2,2);
	// Assertions
	ASSERT_TRUE(spBPQueueIsEmpty(q1));
	spBPQueueEnqueue(q1,e1);
	ASSERT_FALSE(spBPQueueIsEmpty(q1));
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	return true;
}

bool queueFullTest(){
	// Function variables
	int maxSize = 1;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(1,1);
	// Assertions
	ASSERT_FALSE(spBPQueueIsFull(q1));
	spBPQueueEnqueue(q1,e1);
	ASSERT_TRUE(spBPQueueIsFull(q1));
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	return true;
}

bool queueEnqueueTest(){
	// Function variables
	int maxSize = 3;
	int i; // Generic loop variable
	SP_BPQUEUE_MSG msg;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(1,1);
	SPListElement e2 = spListElementCreate(3,2);
	SPListElement e3 = spListElementCreate(2,2);
	SPListElement order[3] = {e1,e3,e3};
	// Assertions
	msg = spBPQueueEnqueue(NULL,e1);
	ASSERT_TRUE(msg == SP_BPQUEUE_INVALID_ARGUMENT);
	ASSERT_TRUE(spBPQueueSize(q1) == 0);
	msg = spBPQueueEnqueue(q1,NULL);
	ASSERT_TRUE(msg == SP_BPQUEUE_INVALID_ARGUMENT);
	ASSERT_TRUE(spBPQueueSize(q1) == 0);
	msg = spBPQueueEnqueue(q1,e1);
	ASSERT_TRUE(msg == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueSize(q1) == 1);
	spBPQueueEnqueue(q1,e2);
	msg = spBPQueueEnqueue(q1,e3);
	ASSERT_TRUE(msg == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueSize(q1) == 3);
	msg = spBPQueueEnqueue(q1,e3);
	ASSERT_TRUE(msg == SP_BPQUEUE_FULL);
	ASSERT_TRUE(spBPQueueSize(q1) == 3);
	for (i = 0; i < 3; i++) { // check if the queue saved the right elements
		ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),order[i]) == 0);
		spBPQueueDequeue(q1);
	}
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	spListElementDestroy(e3);
	return true;
}

bool queueDequeueTest(){
	// Function variables
	int maxSize = 3;
	int i; // Generic loop variable
	SP_BPQUEUE_MSG msg;
	// SPBPQueue variables
	SPBPQueue q1 = spBPQueueCreate(maxSize);
	SPListElement e1 = spListElementCreate(1,1);
	SPListElement e2 = spListElementCreate(3,2);
	SPListElement e3 = spListElementCreate(2,2);
	SPListElement order[3] = {e1,e3,e2};
	// Assertions
	msg = spBPQueueDequeue(NULL);
	ASSERT_TRUE(msg == SP_BPQUEUE_INVALID_ARGUMENT);
	spBPQueueEnqueue(q1,e1);
	spBPQueueEnqueue(q1,e2);
	spBPQueueEnqueue(q1,e3);
	for (i = 0; i < 3; i++) {
		ASSERT_TRUE(spListElementCompare(spBPQueuePeek(q1),order[i]) == 0);
		msg = spBPQueueDequeue(q1);
		ASSERT_TRUE(msg == SP_BPQUEUE_SUCCESS);
	}
	msg = spBPQueueDequeue(q1);
	ASSERT_TRUE(msg == SP_BPQUEUE_EMPTY);
	// Deallocation
	spBPQueueDestroy(q1);
	spListElementDestroy(e1);
	spListElementDestroy(e2);
	spListElementDestroy(e3);
	return true;
}
int main1() {
	RUN_TEST(queueCreateInputTest);
	RUN_TEST(queueCopyInputTest);
	RUN_TEST(queueCopySafetyTest);
	RUN_TEST(queueClearTest);
	RUN_TEST(queueSizeTest);
	RUN_TEST(queueMaxSizeTest);
	RUN_TEST(queuePeeksTest);
	RUN_TEST(queueMinMaxTest);
	RUN_TEST(queueEmptyTest);
	RUN_TEST(queueFullTest);
	RUN_TEST(queueEnqueueTest);
	RUN_TEST(queueDequeueTest);
	return 0;
}
