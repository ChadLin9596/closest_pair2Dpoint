#include <bits/stdc++.h> 
typedef double dataType;
using namespace std;

class point{
public: 
	dataType x;
	dataType y;
};

int t, n;
point P[100000];
// index for conquer
int indP[100000];

bool compareX(point a, point b){ return (a.x < b.x);}
bool compareY(int a, int b){ return (P[a].y < P[b].y);}

dataType dis2D(int a, int b){
	return sqrt((P[a].x - P[b].x)*(P[a].x - P[b].x) +
	 			(P[a].y - P[b].y)*(P[a].y - P[b].y));
}

dataType compareDis(dataType a, dataType b){
	return (a < b)? a : b;
}

// s : start index, e : end index
dataType brutalMethod(int s, int e){
	dataType dis = FLT_MAX;
	for (int i = s; i <= e; i++){
		for (int j = i + 1; j <= e; j++){
			if (dis2D(i, j) < dis)
				dis = dis2D(i, j);
		}
	}
	return dis;
}

dataType findMidMin(int size, dataType dis_){
	dataType r = dis_;
	sort(indP, indP + size, compareY);
	for (int i = 0; i < size; i++){
		for (int j = i + 1; j < size; j++){
			if (P[indP[j]].y - P[indP[i]].y < r){
				if (dis2D(indP[i], indP[j]) < r)
					r = dis2D(indP[i], indP[j]);
			} else {
				break;
			}
		}
	}		
	return r;
}

// s : start index, e : end index
dataType findMin(int s, int e){
	if (e - s + 1 <= 3)
		return brutalMethod(s, e);
 
 	int m = (e - s + 1) / 2 - 1 + s;
	dataType dis_ = compareDis(findMin(s, m), findMin(m + 1, e));

	int cnt = 0;
	for (int i = s; i <= e; i++){
		if (fabs(P[i].x - P[m].x) <= dis_){
			indP[cnt] = i;
			cnt++;
		}
	}
	return compareDis(dis_, findMidMin(cnt, dis_));
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	scanf("%d", &t);
	for (int i = 0; i < t; i++){
		scanf("%d", &n);
		for (int j = 0; j < n; j++){
			scanf("%lf %lf", &P[j].x, &P[j].y);
		}
		sort(P, P + n, compareX);
		printf("%.6lf\n", findMin(0, n-1));
	}

	return 0;
}
