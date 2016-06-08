// 18.2 Write a method to shuffle a deck of cards. It must be a perfect shuffle
// - in other words, each of the 52! permutations of the deck has to be equally
// likely. Assume that you are given a random number generator which is perfect.
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int rnd() {
	return rand() % 52;
}

void swap(int *deck, int i, int j) {
	int tmp = deck[i];
	deck[i] = deck[j];
	deck[j] = tmp;
}

void shuffle_rec(int *deck, int n) {
	if(n == 1)
		return;

	shuffle_rec(deck, n - 1);
	swap(deck, n - 1, rnd());
}

void shuffle(int *deck) {
	for(int i = 0; i < 52; i ++)
		swap(deck, rnd(), i);
}

int main(void) {

	srand(time(NULL));

	{ // 1
		int *deck = new int[52];
		for(int i = 0; i < 52; i ++)
			deck[i] = i;
		shuffle_rec(deck, 52);
		for(int i = 0; i < 52; i ++) cout << deck[i] << " "; cout << endl;
		delete [] deck;
	}

	{ // 2
		int *deck = new int[52];
		for(int i = 0; i < 52; i ++)
			deck[i] = i;
		shuffle(deck);
		for(int i = 0; i < 52; i ++) cout << deck[i] << " "; cout << endl;
		delete [] deck;
	}

	return 0;
}
