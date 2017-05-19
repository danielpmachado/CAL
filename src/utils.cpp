/*
 * utils.cpp
 *
 *  Created on: 07/04/2017
 *      Author: up201504570
 */

#include "utils.h"

int convertLongitudeToX(double longitude, string district) {

	if (district == "Brooklyn")
		return floor(
				(longitude - MIN_LNG_1) * IMAGE_X_1 / (MAX_LNG_1 - MIN_LNG_1));

	if (district == "Manhattan")
		return floor(
				(longitude - MIN_LNG_2) * IMAGE_X_2 / (MAX_LNG_2 - MIN_LNG_2));

}


int convertLatitudeToY(double latitude,string district) {

	if (district == "Brooklyn")
		return IMAGE_Y_1
				- floor((latitude - MIN_LAT_1) * IMAGE_Y_1 / (MAX_LAT_1 - MIN_LAT_1))
				+ 3.5;

	if (district == "Manhattan")
		return IMAGE_Y_2
				- floor((latitude - MIN_LAT_2) * IMAGE_Y_2 / (MAX_LAT_2 - MIN_LAT_2))
				+3.5;

}

void upCase(string &str) {
	size_t i = 0;

	while (i < str.length()) {
		str.at(i) = toupper(str.at(i));
		i++;
	}

	if (str == "de" || str == "do" || str == "da" || str == "das"
			|| str == "dos" || str == "e")
		return;

	//str.at(0)= toupper(str.at(0));
}

void normalize(string &str) {
	istringstream iss(str);
	string final_str = "";
	string token;
	while (iss >> token) {
		upCase(token);
		final_str += " " + token;
	}

	final_str.erase(0, 1);

	str = final_str;
}

vector<string> split(string str) {
	vector<string> result;
	istringstream iss(str);
	string token;

	while (iss >> token) {
		upCase(token);
		result.push_back(token);
	}
	return result;
}

void pre_kmp(string pattern, vector<int> & prefix) {
	int m = pattern.length();
	prefix[0] = -1;
	int k = -1;
	for (int q = 1; q < m; q++) {
		while (k > -1 && pattern[k + 1] != pattern[q])
			k = prefix[k];
		if (pattern[k + 1] == pattern[q])
			k = k + 1;
		prefix[q] = k;
	}
}

bool kmp(string text, string pattern) {
	int num = 0;
	int m = pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n = text.length();

	int q = -1;
	for (int i = 0; i < n; i++) {
		while (q > -1 && pattern[q + 1] != text[i])
			q = prefix[q];
		if (pattern[q + 1] == text[i])
			q++;
		if (q == m - 1) {
			return true;
		}
	}
	return false;
}

int editDistance(string pattern, string text) {
	int n = text.length();
	vector<int> d(n + 1);
	int old, neww;
	for (int j = 0; j <= n; j++)
		d[j] = j;
	int m = pattern.length();
	for (int i = 1; i <= m; i++) {
		old = d[0];
		d[0] = i;
		for (int j = 1; j <= n; j++) {
			if (pattern[i - 1] == text[j - 1])
				neww = old;
			else {
				neww = min(old, d[j]);
				neww = min(neww, d[j - 1]);
				neww = neww + 1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

void clearScreen() {
	system("cls");
}

void pauseScreen() {
	getchar();
}

string getFilePath(string file_name, string district) {

	if (district == "Brooklyn")
		return "resources\\" + file_name + "1.txt";

	if (district == "Manhattan")
		return "resources\\" + file_name + "2.txt";

}

