

#include <bits/stdc++.h>
using namespace std;

class Point 
{ 
	public:
	long x, y; 
}; 

int compareX(const void* a, const void* b) 
{ 
	Point *p1 = (Point *)a, *p2 = (Point *)b; 
	return (p1->x - p2->x); 
} 

int compareY(const void* a, const void* b) 
{ 
	Point *p1 = (Point *)a, *p2 = (Point *)b; 
	return (p1->y - p2->y); 
} 

long dist(Point p1, Point p2) 
{ 
	return ( (p1.x - p2.x)*(p1.x - p2.x) + 
				(p1.y - p2.y)*(p1.y - p2.y) 
			); 
} 

long bruteForce(Point P[], int n) 
{ 
	long min = LONG_MAX; 
	for (int i = 0; i < n; ++i) 
		for (int j = i+1; j < n; ++j) 
			if (dist(P[i], P[j]) < min) 
				min = dist(P[i], P[j]); 
	return min; 
} 

long min(long x, long y) 
{ 
	return (x < y)? x : y; 
} 

long stripClosest(Point strip[], int size, long d) 
{ 
	long min = d;

	qsort(strip, size, sizeof(Point), compareY); 
	for (int i = 0; i < size; ++i) 
		for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) 
			if (dist(strip[i],strip[j]) < min) 
				min = dist(strip[i], strip[j]); 

	return min; 
} 

long closestUtil(Point P[], int n) 
{ 
	if (n <= 3) 
		return bruteForce(P, n); 

	int mid = n/2; 
	Point midPoint = P[mid]; 

	long dl = closestUtil(P, mid); 
	long dr = closestUtil(P + mid, n - mid); 

	long d = min(dl, dr); 

	Point strip[n]; 
	int j = 0; 
	for (int i = 0; i < n; i++) 
		if (abs(P[i].x - midPoint.x) < d) 
			strip[j] = P[i], j++; 

	return min(d, stripClosest(strip, j, d) ); 
} 

long closest(Point P[], int n) 
{ 
	qsort(P, n, sizeof(Point), compareX); 

	return closestUtil(P, n); 
} 

long closestSquaredDistance(vector<int> x, vector<int> y){
    int n=x.size();
    Point P[n];
    for(int i = 0; i < n; i++){
        P[i] = {(long)x[i], (long)y[i]};
    }
    return closest(P, n);
}

int main(){
    vector<int> x={77, 1000, 992, 1000000};
    vector<int> y={0, 1000, 500, 0};
    cout<<closestSquaredDistance(x, y);
    
}
