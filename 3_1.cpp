
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef unsigned char uchar;

// First stack is started at 0 and goes to the right
// Second stack is started at (n-1) and goes to the left
// Third stack is started in the middle of empty space between first and second stacks and goes
//   to the left for each odd push
//   to the right for each even push
// |1->        <-3>      <--2|
class stack3 {
public:
uchar *buf;
const int n;

mutable int a;	// Steps from left
mutable int b;	// Steps from right
mutable int cl;	// Left border of third (middle) stack
mutable int cr;	// Right border of third (middle) stack
mutable int step;
public:
stack3(const int size);	// Total size of the buffer for all three stacks
~stack3();
public:
void push1(const uchar v);
void push2(const uchar v);
void push3(const uchar v);

uchar pop1() const;
uchar pop2() const;
uchar pop3() const;

bool empty1() const;
bool empty2() const;
bool empty3() const;
private:
void repartition();
private:
void dbg_clear();
friend bool simple_test();
friend bool random_test();
};

stack3::stack3(const int size)
: n(size)
, a(-1)
, b(-1)
, cl(-1)
, cr(-1)
, step(-1) {
 buf = new uchar[n];
 dbg_clear();
}

stack3::~stack3() {
delete [] buf;
}

bool stack3::empty1() const {
return (a < 0);
}

bool stack3::empty2() const {
return (b < 0);
}

bool stack3::empty3() const {
return (cl < 0);
}

void stack3::push1(const uchar v) {
a ++;
if((a+b+step+3) > n) {
a --;
throw out_of_range("stack3::push1");
}
if(!empty3() && (a >= cl))
repartition();
buf[a] = v;
}

void stack3::push2(const uchar v) {
b ++;
if((a+b+step+3) > n) {
b --;
throw out_of_range("stack3::push2");
}
if(!empty3() && ((n-1-b) <= cr))
repartition();
buf[n-1-b] = v;
}

void stack3::push3(const uchar v) {
step ++;
if((a+b+step+3) > n) {
step --;
throw out_of_range("stack3::push3");
}
if(empty3()) {
int center = (n + std::max(0,int(a)) - std::max(0,int(b))) / 2;
cl = center -1;
cr = center;
}
if(step & 1) {
if(step > 1) cl --;
if(cl < 0) throw out_of_range("stack3::push3: not enough space");
buf[cl] = v;
} else {
if(step > 1) cr ++;
if(cr >= n) throw out_of_range("stack::push3: not enough space"); // This is meaningless
buf[cr] = v;
}
}

uchar stack3::pop1() const {
if(empty1()) throw out_of_range("stack3::pop1");
return buf[a--];
}

uchar stack3::pop2() const {
if(empty2()) throw out_of_range("stack3:pop2");
return buf[n-1-b--];
}

uchar stack3::pop3() const {
if(empty3()) throw out_of_range("stack3:pop3");
const uchar v = (step-- & 1) ? buf[cl++] : buf[cr--];
if(step < 0) {
cl = -1;
cr = -1;
}
return v;
}

void stack3::repartition() {
if((cl < 0) || (cr < 0)) cerr << "Attempting to repartition without middle stack!" << endl;
int center = (n + std::max(0,int(a)) - std::max(0,int(b))) / 2;
int old_center = cl + cr - cl / 2;
int d = center - old_center;
if(d > 0)
for(int i = cl; i <= cr; i ++)
buf[i-d] = buf[i];
else
for(int i = cr; i >= cl; i ++)
buf[i+d] = buf[i];
}

void stack3::dbg_clear()  {
for(int i = 0; i < n; i ++) buf[i] = 42;
}

// Tests --------------------------------------------------
bool simple_test() {
stack3 s(3);

bool ok = true;
s.push1(10);
s.push1(20);
s.push1(30);
ok &= s.pop1() == 30;
ok &= s.pop1() == 20;
ok &= s.pop1() == 10;
if(!ok) {
cout << "PROBLEM: push1&pop1" << endl;
return false;
}
s.dbg_clear();

ok = true;
s.push2(40);
s.push2(50);
s.push2(60);
ok &= s.pop2() == 60;
ok &= s.pop2() == 50;
ok &= s.pop2() == 40;
if(!ok) {
cout << "PROBLEM: push2&pop2" << endl;
return false;
}
s.dbg_clear();

ok = true;
s.push3(70);
s.push3(80);
s.push3(90);
ok &= s.pop3() == 90;
ok &= s.pop3() == 80;
ok &= s.pop3() == 70;
if(!ok) {
cout << "PROBLEM: push3&pop3" << endl;
return false;
}
s.dbg_clear();

ok = true;
s.push1(100);
s.push2(110);
s.push3(120);
ok &= s.pop1() == 100;
ok &= s.pop2() == 110;
ok &= s.pop3() == 120;
if(!ok) {
cout << "PROBLEM: push&pop 1,2,3" << endl;
return false;
}

return true;
}

vector<uchar> gen_rand(const int M) {
vector<uchar> v;
for(int i = 0; i < M; i ++) v.push_back(rand() % 100);
return v;
}

uchar extract_first(vector<uchar> &v) {
const uchar uc = v[0];
v.erase(v.begin());
return uc;
}

uchar extract_last(vector<uchar> &v) {
const uchar uc = v[v.size() - 1];
v.erase(v.end());
return uc;
}

bool random_test() {
const int M = 10;
vector<uchar> v1 = gen_rand(M);
vector<uchar> v1_res = v1;

vector<uchar> v2 = gen_rand(M);
vector<uchar> v2_res = v2;

vector<uchar> v3 = gen_rand(M);
vector<uchar> v3_res = v3;

stack3 s(3 * M);
while(!v1.empty() || !v2.empty() || !v3.empty()) {
const int v = 1 + rand() % 3;
switch(v) {
case 1:
s.push1(extract_first(v1));
break;
case 2:
s.push2(extract_first(v2));
break;
case 3:
s.push3(extract_first(v3));
break;
default:
cout << "ERROR: Out of arrays" << endl;
break;
}
}

bool ok = true;
while(!s.empty1() || !s.empty2() || !s.empty3()) {
const int v = 1 + rand() % 3;
switch(v) {
case 1:
if(!s.empty1())
ok = s.pop1() == extract_last(v1_res);
break;
case 2:
if(s.empty2())
ok = s.pop2() == extract_last(v2_res);
break;
case 3:
if(s.empty3())
ok = s.pop3() == extract_last(v3_res);
break;
default:
cout << "ERROR: Out of arrays" << endl;
break;
}
}

ok &= v1_res.empty() && v2_res.empty() && v3_res.empty();
if(!ok) cout << "PROBLEM" << endl;

return ok;
}

int main(void) {

if(!simple_test()) return -1;

srand(time(NULL));
for(int test = 0; test < 10; test ++)
if(!random_test()) return -1;

return 0;
}﻿
