#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

string oddOrEven(int& n);
int getIthBit(int& n, int i);
void clearIthBit(int& n, int i);
void setIthBit(int& n, int i, int val);
void clearLastIBits(int& n, int i);
void clearRangeOfBits(int& n, int i, int j);
void replaceBits(int& n, int num, int i, int j);
string powerOf2(int& n);
string powerOf4(int& n);
vector<int> decodeXORed(vector<int> encoded, int first);
int countSetBits(int& n);
int decimalToBinary(int n);
vector<int> sortByNoOf1Bits(vector<int>& arr);
bool contain(vector<int> a, int i);
int longestContinuousRunOf1s(int n);
int hammingDistance(int x, int y);
int numberOfBits(int n);

int main() {
	int a, b;
	cout << numberOfBits(7) << endl;
	cin >> a >> b;
	cout << hammingDistance(a, b);

	return 0;
}

string oddOrEven(int& n) {
	return n & 1 ? "odd" : "even";
}

int getIthBit(int& n, int i) {
	int mask = 1 << i;
	return n & mask ? 1 : 0;
}

void clearIthBit(int& n, int i) {
	int mask = ~(1 << i);
	n = n & mask;
}

void setIthBit(int& n, int i, int val) {
	clearIthBit(n, i);
	int mask = val << i;
	n = n | mask;
}

void clearLastIBits(int& n, int i) {
	int mask = (-1 << i);
	n = n & mask;
}

void clearRangeOfBits(int& n, int i, int j) {
	int a = -1 << (j + 1);
	int b = (1 << i) - 1;
	int mask = a | b;
	n = n & mask;
}

void replaceBits(int& n, int num, int i, int j) {
	clearRangeOfBits(n, i, j);
	int mask = num << i;
	n = n | mask;
}
string powerOf2(int& n) {
	return (n & (n - 1)) == 0 ? "yes" : "no";
}

string powerOf4(int& n) {
	if (powerOf2(n) == "yes") {
		n = sqrt(n);
		if (powerOf2(n) == "yes") {
			return "yes";
		}
	}
	return "no";
}

vector<int> decodeXORed(vector<int> encoded, int first) {
	/*
	Input: encoded = [1,2,3], first = 1
					 [01,10,11]
	Output: [1,0,2,1]
					 [01,00,10,01]
	*/
	vector<int> original;
	original.push_back(first);
	for (int i = 1; i < encoded.size() + 1; i++) {
		int a = encoded[i - 1] ^ original[i - 1];
		original.push_back(a);
	}
	return original;
}

int countSetBits(int& n) {
	int set = 0;
	for (int i = 0; i < 6; i++) {
		if (n & (1 << i)) set++;
	}
	return set;
}

int decimalToBinary(int n) {
	int bin = 0;
	int pow = 1;
	//100101011
	while (n > 0) {
		int lastBit = n & 1;
		bin += lastBit * pow;
		pow = pow * 10;
		n = n >> 1;
	}
	return bin;
}

vector<int> sortByNoOf1Bits(vector<int>& arr) {
	vector<int> sorted;
	unordered_map<int, int> freqMap;
	//Input : arr    = [0, 1, 2, 3, 4, 5, 6, 7, 8]
	//Output: sorted = [0, 1, 2, 4, 8, 3, 5, 6, 7]
	for (int j = 0; j < arr.size(); j++) {
		int freq = 0;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[j] & 1 << i) {
				freq++;
			}
		}
		freqMap[j] = freq;
	}

	for (int i = 0; i < freqMap.size(); i++) {
		for (int j = 0; j < freqMap.size(); j++) {
			if ((freqMap[i] == freqMap[j]) && !(contain(sorted, j))) {
				unordered_map<int, int>::iterator it = freqMap.find(j);
				sorted.push_back(it->first);
			}
		}
	}
	for (pair<int, int> a : freqMap) {
		cout << a.first << "  " << a.second << endl;
	}
	return sorted;
}

bool contain(vector<int> a, int i) {
	for (int aa : a) {
		if (aa == i) {
			return true;
		}
	}
	return false;
}

int longestContinuousRunOf1s(int n) {
	// 10011100 - 156
	int count = 0;
	vector<int> c;
	for (int i = 0; i < 10; i++) {
		if ((n & (1 << i)) && ((n&(1<<(i+1)))) || 
			(n & (1 << i)) && !((n & (1 << (i + 1))))) {
			count++;
			continue;
		}
		c.push_back(count);
		count = 0;
	}
	return *max_element(c.begin(), c.end());
}

int hammingDistance(int x, int y) {
	//Input: x = 1, 0001
	//       y = 4, 0100    65
	//Output: 2
	int count = 0;
	int numOfBits = x > y ? numberOfBits(x) : numberOfBits(y);
	for (int i = 0; i < numOfBits; i++) {
		if ((x & (1 << i)) ^ (y & (1 << i))) {
			count++;
		}
	}
	return count;
}

int numberOfBits(int n) {
	int a = 0;
	while (n > 0) {
		n = n / 2;
		a++;
	}
	return a;
}