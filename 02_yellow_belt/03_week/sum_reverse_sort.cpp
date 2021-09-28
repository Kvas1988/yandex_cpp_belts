#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	string res = "";
	for (size_t i = s.length(); i > 0; --i) {
		res += s[i-1];
	}
	return res;
}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}