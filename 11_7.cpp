// 11.7 A circus is designing a tower routine consisting of people standing atop
// one another's shoulders. For practical and aesthetic reasons, each person
// must be both shorter and lighter than the person below him or her. Given the
// heights and weights of each person in the circus,write a method to compute
// the largest possible number of people in such tower.
// EXAMPLE:
// Input (wt, ht): (65, 100) (70, 150) (56, 90) (75, 190) (60, 95) (68, 110)
// Output: The longest tower is length 6 and includes from top to bottom:
// (56, 90) (60, 95) (65, 100) (68, 110) (70, 150) (75, 190)

// ---------------------------------------------
// Solution, more optimal, than in the book, O(n*log(n):
// Sorting with heap_sort will create a tower on the right part of the
// array and remain "invalid" components, which doesn't match tower conditions
//on the left side.

#include <iostream>
using namespace std;

typedef struct _person {
	int w, h;
} person;

void swap(person *a, int i, int j) {
	person tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void max_heapify(person *a, int i, int n) {
	int l = 2 * (i + 1) -1;
	if((l < n) && (a[i].w <= a[l].w) && (a[i].h <= a[l].h)) {
		swap(a, i, l);
		max_heapify(a, l, n);
	}

	int r = 2 * (i + 1);
	if((r < n) && (a[i].w <= a[r].w) && (a[i].h <= a[r].h)) {
		swap(a, i, r);
		max_heapify(a, r, n);
	}
}

void heap_sort(person *a, int n) {
	if(n == 0)
		return;
;

	for(int i = int(n / 2); i >= 0; i --)
		max_heapify(a, i, n);

	int cur_len = n;
	for(int i = 0; i < n; i ++) {
		swap(a, 0, cur_len - 1);
		max_heapify(a, 0, cur_len - 1);
		cur_len --;
	}
}

int build_tower(person *a, int n) {

	heap_sort(a, n);

	if( n <= 0)
		return 0;
	if(n == 1) {
		cout << "(" << a[0].w << ", " << a[0].h << ")" << endl;
		return 1;
	}
	int tower_height = 1;
	cout << "(" << a[n - 1].w << ", " << a[n - 1].h << ")" << " ";
	for(int i = (n - 2); i >= 0; i --) {
		if((a[i + 1].w > a[i].w) && (a[i + 1].h > a[i].h)) {
			cout << "(" << a[i + 1].w
				<< ", " << a[i + 1].h << ")" << "";
			tower_height ++;
		} else {
			break;
		}
	}
	cout << endl;
	return tower_height;
}

int main(void) {
	{ //1
		person a[] = { {65, 100}, {70, 150}, {56, 90}, {75, 190},
			{60, 95}, {68, 110} };
		int r = build_tower(a, 6);
		if(r != 6) {
			cout << "ERROR1" << endl;
			return -1;
		}
	}

	{ //2
		person a[] = { {65, 100}, {70, 150}, {58, 80}, {56, 90},
			{75, 190}, {60, 95}, {68, 110} };
		int r = build_tower(a, 7);
		if(r != 6) {
			cout << "ERROR2" << endl;
			return -1;
		}
	}

	cout << "OK" << endl;
	return 0;
}
