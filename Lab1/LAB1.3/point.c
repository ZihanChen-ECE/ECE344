#include <assert.h>
#include "common.h"
#include "point.h"
#include <math.h>


double point_distance(const struct point *p1, const struct point *p2)
{
	double distance;
	distance = sqrt(pow((p1->x - p2->x),2) + pow((p1->y - p2->y),2));
	return distance;
}

int point_compare(const struct point *p1, const struct point *p2)
{
	double d1 = pow(p1->x, 2) + pow(p1->y, 2);
	double d2 = pow(p2->x, 2) + pow(p2->y, 2);
	if (d1 > d2)
		return 1;
	else if (d1 < d2)
		return -1;
	return 0;
}

void point_translate(struct point *p, double x, double y)
{
	p->x += x;
	p->y += y;
}



