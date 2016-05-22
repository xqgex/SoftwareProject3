#include "SPPoint.h"
#include <stdlib.h>

typedef struct sp_point_t{
	double* data;
	int dim;
	int index;
};
// TODO add assertions
SPPoint spPointCreate(double* data, int dim, int index){
	// Function variables
	SPPoint point;
	double* pointData;
	int i; // Generic loop variable
	if(index < 0 || dim <= 0 || data == NULL){
		return NULL; // Invalid parameters
	}
	point = (SPPoint) malloc(sizeof(SPPoint));
	if (point == NULL) { //Allocation Fails
		return NULL;
	}
	pointData = (double*) malloc(sizeof(double)*dim);  // TODO check if they meant to allocate new array (probably yes)
	if (pointData == NULL) { //Allocation Fails
		free(point);
		return NULL;
	}
	for (i=0;i<dim;i++){
		pointData[i] = data[i];
	}
	point->data = pointData;
	point->index = index;
	point->dim = dim;
	return point;
}

SPPoint spPointCopy(SPPoint source){
	SPPoint newPoint;
	if (source == NULL)
		return NULL; // Invalid source point
	newPoint = spPointCreate(source->data, source->dim, source->index); // Create new copy of source
	return newPoint;
}

void spPointDestroy(SPPoint point){
	if (point != NULL){
		free(point->data);
		free(point);
	}

}

int spPointGetDimension(SPPoint point){
	if (point == NULL){
		return 0; //TODO check return value in the case of point = null
	}
	return point->dim;
}

int spPointGetIndex(SPPoint point){
	if (point == NULL){
		return 0; //TODO check return value in the case of point = null
	}
	return point->index;
}

double spPointGetAxisCoor(SPPoint point, int axis){
	if (point == NULL || axis < point->dim){
		return 0.0; //TODO check return value in the case of point = null
	}
	return point->data[axis];
}

double spPointL2SquaredDistance(SPPoint p, SPPoint q){
	// Function variables
	int i; // Generic loop variable
	double L2Dist=0,axis;
	if (p == NULL || q == NULL || p->dim != q->dim)
		return 0; //TODO check return value
	// Calculate squared distance
	for (i=0;i<p->dim;i++) {
		axis = p->data[i] - q->data[i];
		L2Dist += axis*axis;
	}
	return L2Dist;
}

