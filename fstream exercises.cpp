// fstream exercises
// 10/13/2021
// Amir Afunian

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Reading {
	Reading(int, double, char);
	int hour;
	double temp;
	char deg;
};
Reading::Reading(int h, double t, char d) {
	hour = h;
	temp = t;
	deg = d;
}
void fill_reading(vector<Reading>& r, int n) {
	int h = 0;
	double t = 10.0;
	char d;
	for (int i = 0; i < n; ++i) {
		d = h % 2 == 0 ? 'c' : 'f';
		r.push_back(Reading(h, t, d));
		t += .5;
		if (h + 1 > 23) {
			h = 0;
		}
		else h++;
	}
}
ostream& operator<<(ostream& os, Reading& r) {
	return os << r.hour << " h: " << r.temp << ' ' << r.deg << '\n';
}

int main() {
	// Writing data to raw_temps.txt
	vector<Reading> readings;
	int counter = 50;
	ofstream ost{ "raw_temps.txt" };
	fill_reading(readings, counter);
	for (int i = 0; i < counter; ++i) {
		ost << readings[i];
	}
	ost.close();
	// Reading data from raw_temps.txt
	vector<Reading> data;
	ifstream ist{ "raw_temps.txt" };
	ist.exceptions(ist.exceptions() | ios_base::badbit);
	int h;
	double t;
	char d;
	char temp, temp2;
	while (true) {
		if (ist >> h) {
			ist >> temp >> temp2;
			if (ist >> t && temp == 'h' && temp2 == ':') {
				if (ist >> d && (d == 'c' || d == 'f')) {
					if (d == 'c') {
						t = (t * double(9)/5) + 32;
						data.push_back(Reading(h, t, d));
					}
					else {
						data.push_back(Reading(h, t, d));
					}
				}
				else {
					cout << "Error! (1)\n";
					ist.unget();
					ist.clear(ios_base::failbit);
					return -1;
				}
			}
			else {
				cout << "Error! (2)\n";
				ist.unget();
				ist.clear(ios_base::failbit);
				return -1;
			}
		}
		else if (ist.eof()) break;
		else {
			cout << "Error! (3)\n";
			ist.unget();
			ist.clear(ios_base::failbit);
			return -1;
		}
	}
	int sum = 0;
	int median = 0;
	for (int i = 0; i < data.size(); ++i) {
		sum += data[i].temp;
	}
	if (counter % 2 == 0) {
		median = (data[counter / 2].temp + data[(counter / 2) - 1].temp) / 2;
	}
	else median = data[counter / 2].temp;
	// Output mean and median data
	cout << "Mean: " << sum/data.size() << " Median: " << median << '\n';
	return 0;
}
