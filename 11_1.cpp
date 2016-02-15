// You are given two corted arrays, A and B, where A has a large enough buffer
// at the end to hold B. Write a method to merge B into A in sorted order.
#include <iostream>
#include <vector>
using namespace std;

void solution(vector<int> &A, vector<int> &B) {
	int a = int(A.size()) - B.size() - 1;
	int b = int(B.size()) - 1;
	int insert_idx = int(A.size()) - 1;
	while(insert_idx >= 0) {
		if(A[a] > B[b]) {
			A[insert_idx] = A[a];
			a --;
		} else {
			A[insert_idx] = B[b];
			b --;
		}
		insert_idx --;
	}
}

int main(void) {
	{ // Test 1
		int a[] = {1, 2, 4, 6, 0, 0};
		int b[] = {3, 5};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		solution(A, B);
		for(size_t i = 1; i < A.size(); i ++) {
			if(A[i - 1] > A[i]) {
				cout << "ERROR1" << endl;
				break;
			}
		}
	}

	{ // Test 2
		int a[] = {1, 0};
		int b[] = {5};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		solution(A, B);
		for(size_t i = 1; i < A.size(); i ++) {
			if(A[i - 1] > A[i]) {
				cout << "ERROR2" << endl;
				break;
			}
		}
	}

	{ // Test 3
		int a[] = {1, 2, 3, 4, 0, 0};
		int b[] = {5, 6};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		solution(A, B);
		for(size_t i = 1; i < A.size(); i ++) {
			if(A[i - 1] > A[i]) {
				cout << "ERROR3" << endl;
				break;
			}
		}
	}

	{ // Test 4
		int a[] = {3, 4, 5, 6, 0, 0};
		int b[] = {1, 2};
		vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
		vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
		solution(A, B);
		for(size_t i = 1; i < A.size(); i ++) {
			if(A[i - 1] > A[i]) {
				cout << "ERROR4" << endl;
				break;
			}
		}
	}
	cout << "OK" << endl;
	return 0;
}
