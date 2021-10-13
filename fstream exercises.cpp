// fstream exercises
// 10/13/2021
// Amir Afunian

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Reading {
	Reading(int, double);
	int hour;
	double temp;
};
Reading::Reading(int h, double t) {
	hour = h;
	temp = t;
}
void fill_reading(vector<Reading>& r, int n) {
	int h = 0;
	double t = 10.0;
	for (int i = 0; i < n; ++i) {
		r.push_back(Reading(h, t));
		t += .5;
		if (h + 1 > 23) {
			h = 0;
		}
		else h++;
	}
}
ostream& operator<<(ostream& os, Reading& r) {
	return os << "Temperature at " << r.hour << "h: " << r.temp << '\n';
}

int main() {
	vector<Reading> readings;
	int counter = 50;
	ofstream ost{ "raw_temps.txt" };
	fill_reading(readings, counter);
	for (int i = 0; i < counter; ++i) {
		ost << readings[i];
	}

	return 0;
}
