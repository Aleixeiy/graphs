#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 4;
const int MAX = 100000;
const int MIN = -100000;



vector < vector < int>> mat_min = {
{0, 1, MAX, MAX},
{MAX, 0, 2, 3},
{MAX, MAX, 0, 4},
{5, 3, MAX, 0}
};

vector < vector < int>> mat_max = {
{0, 1, MIN, MIN},
{MIN, 0, 2, 3},
{MIN, MIN, 0, 4},
{5, 3, MIN, 0}
};

vector < vector < int>> mat_ways = {
{0, 1, 0, 0},
{0, 0, 2, 3},
{0, 0, 0, 4},
{5, 3, 0, 0}
};


void printpath(vector<int>& path) {
	int size = path.size();
	int sum = 0;

	for (int i = 0; i < size - 1; ++i) {
		sum += mat_ways[path[i]][path[i + 1]];
	}

	for (int i = 0; i < size; i++)
		printf("%d ", path[i]);
	printf("length: ", sum);
}


int isNotVisited(int x, vector<int>& path) {
	int size = path.size();
	for (int i = 0; i < size; i++)
		if (path[i] == x)
			return 0;
	return 1;
}


vector < pair<int, vector<int>>> findpaths(vector<vector<int> >& g, int src,
	int dst, int v) {

	queue<vector<int>> q;

	vector < pair<int, vector<int>>> res_path;

	vector<int> path;
	path.push_back(src);
	q.push(path);
	while (!q.empty()) {
		path = q.front();
		q.pop();
		int last = path[path.size() - 1];


		if (last == dst) {

			int sum = 0;

			for (int i = 0; i < path.size() - 1; i++) {
				sum += mat_ways[path[i]][path[i + 1]];
			}
			res_path.emplace_back(make_pair(sum, path));
		}


		for (int i = 0; i < g[last].size(); i++) {
			if (g[last][i] != 0) {
				if (isNotVisited(i, path)) {
					vector<int> newpath(path);
					newpath.push_back(i);
					q.push(newpath);
				}
			}
		}
	}

	return res_path;
}


void print_mat(vector < vector < int>>& mat) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (mat[i][j] == MAX) {
				printf("  +");
			}
			else if (mat[i][j] == MIN) {
				printf("  -");
			}
			else {
				printf("%3d", mat[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}


void calc_floyd_min(vector < vector < int>>& mat) {

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {

				if (mat[i][k] + mat[k][j] < mat[i][j]) {
					mat[i][j] = mat[i][k] + mat[k][j];
				}
			}
		}
	}
	printf("\n");
}


void calc_floyd_max(vector < vector < int>>& mat) {

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {

				if (mat[i][k] + mat[k][j] > mat[i][j] && mat[i][k] != MIN && mat[k][j] != MIN) {
					mat[i][j] = mat[i][k] + mat[k][j];
				}
			}
		}
	}
	printf("\n");
}


int find_center(vector < vector < int>> mat) {
	vector<int> v(N, 0);
	for (int t = 0; t < N; t++)
		v[t] = -10000;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (v[j] < mat[i][j]) v[j] = mat[i][j];
		}
	}

	int num = 0;
	for (int t = 1; t < N; t++)
		if (v[t] < v[num]) num = t;
	return num;
}


int main() {

	print_mat(mat_ways);

	int i, j;

	i = 0;
	j = 3;

	auto path_v = findpaths(mat_ways, i, j, N);

	sort(begin(path_v), end(path_v),
		[](pair<int, vector < int>>& a, pair<int, vector < int>>& b) { return a.first < b.first; });

	for (auto& el : path_v) {
		printf("Length: %d Way: ", el.first);
		for (int path_el : el.second) {
			printf("%d ", path_el);
		}
		printf("\n");
	}

	calc_floyd_min(mat_min);
	print_mat(mat_min);

	printf("min way = %d\n", mat_min[i][j]);

	calc_floyd_max(mat_max);
	print_mat(mat_max);

	printf("max way = %d\n", mat_max[i][j]);

	printf("center = %d\n", find_center(mat_min));

	return 0;
}