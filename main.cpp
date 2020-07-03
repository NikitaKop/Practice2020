#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

#define STORAGE_NUMBER 20
#define ROUTE_NUMBER 38

//Разделение строки на подстроки
vector<string> split(string str) {
    vector<string> res;
    string s = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            s += str[i];
        }
        else {
            res.push_back(s);
            s.clear();
        }
    }
    res.push_back(s);
    return res;
}

//проверка, есть ли элемент в векторе
bool isExist(vector<int> v, int n) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == n) {
            return true;
        }
    }
    return false;
}


int main() {
    ifstream Storages;
    Storages.open("Storages.txt");
    if (!Storages.is_open()) {
        cout << "No such file found" << endl;
        return -1;
    }
    string line;
    vector<string> str;
    while (!Storages.eof()) {
        getline(Storages, line);
        str.push_back(line);
    }

    for (int i = 0; i < str.size(); i++) {
        cout << str[i] << endl;
    }

    int adjacentStorages[STORAGE_NUMBER + 1][STORAGE_NUMBER + 1];
    vector<int> visited;
    int minCost[STORAGE_NUMBER + 1];
    for (int i = 0; i < STORAGE_NUMBER + 1; i++) {
        minCost[i] = 999999999;
    }
    for (int i = 0; i < STORAGE_NUMBER + 1; i++) {
        for (int j = 0; j < STORAGE_NUMBER + 1; j++) {
            adjacentStorages[i][j] = -1;
        }
    }

    //считывание данных
    for (int i = 0; i < ROUTE_NUMBER; i++) {
        vector<string> v1 = split(str[i]);
        adjacentStorages[stoi(v1[0])][stoi(v1[1])] = stoi(v1[2]);
        adjacentStorages[stoi(v1[1])][stoi(v1[0])] = stoi(v1[2]); //для неорграфа

    }

    int s1, s2;
    cout << "Enter departure storage: " << endl;
    cin >> s1;
    cout << "Enter arrival storage: " << endl;
    cin >> s2;

    //сам алгоритм
    minCost[s1] = 0;
    int currentStorage = s1;
    while (currentStorage != s2) {
        for (int i = 0; i < STORAGE_NUMBER + 1; i++) {
            if (adjacentStorages[currentStorage][i] != -1 && adjacentStorages[currentStorage][i] + minCost[currentStorage] < minCost[i]) {
                minCost[i] = adjacentStorages[currentStorage][i] + minCost[currentStorage];
            }
        }
        visited.push_back(currentStorage);
        int minDist = 999999999;
        for (int i = 0; i < STORAGE_NUMBER + 1; i++) {
            if (minCost[i] < minDist && !isExist(visited, i)) {
                minDist = minCost[i];
                currentStorage = i;
            }
        }
    }

    vector<int> route;
    route.push_back(currentStorage);
    while (currentStorage != s1) {
        int minDist = 999999999;
        int x;
        for (int i = 0; i < STORAGE_NUMBER + 1; i++) {
            if (adjacentStorages[currentStorage][i] != -1 && minCost[i] < minDist) {
                minDist = minCost[i];
                x = i;
                }
        }
        currentStorage = x;
        route.push_back(currentStorage);
    }
    reverse(route.begin(), route.end());
    cout << "minimal cost: ";
    cout << minCost[s2] << endl;
    cout << "Route: ";
    for (int i = 0; i < route.size(); i++) {
        cout << route[i];
        cout << " ";
    }

    Storages.close();
    return 0;
}