#include <windows.h>
#include<bits/stdc++.h>
#include <string>
#include <iostream>
#include<vector>

using namespace std;

string rawCommands;
boolean validCommands;

//Hàm xóa dấu cách 
string trim(string command) {
    int j = -1, k = command.length(), g = command.length();
    //Tìm dấu cách ở đầu lệnh 
    for(int i = 0; i < g; ++i) {
        if(command[i] == ' ') {
            j = i;
        }
        else {
            break;
        }
    }

    //Tìm dấu cách ở cuối lệnh
    for(int i = g - 1; i > j; i--) {
        if(command[i] == ' ') {
            k = i;
        }
        else break;
    }

    string s = "";
    //Xóa dấu cách 2 đầu
    for(int i = j + 1; i < k; ++i) {
        s = s + command[i];
    }
    return s;
}

//Trả về vector thứ tự lệnh cần thực hiện theo trình tự 
// Lệnh notepad fore > list
vector<string> createJobs(string command) {
	vector<string> jobs;
	string s = "";
	int a = command.length();
	for(int i = 0; i < a; ++i) {
		if(command[i] != '>') {
			s = s + command[i];
		}
		else {
			jobs.push_back(s);
			s = "";
		}
	}
	jobs.push_back(s);
	return jobs;
}