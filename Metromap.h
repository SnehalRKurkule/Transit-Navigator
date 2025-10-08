#ifndef METROMAP_H
#define METROMAP_H

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    double dist;
};

class MetroMap {
private:
    vector<vector<Edge>> adj;
    unordered_map<string,int> nameToId;
    vector<string> idToName;

public:
    MetroMap();

    int addStation(const string &name);
    bool hasStation(const string &name) const;
    int getId(const string &name) const;
    string getName(int id) const;
    int stationCount() const;
    string getStationName(int id) const {
       if (id >= 0 && id < (int)idToName.size()) return idToName[id];
          return "";
   }

    void addConnection(const string &a, const string &b, double dist);
    bool removeStation(const string &name);
    bool removeConnection(const string &a, const string &b);

    void listStations() const;
    void listConnections() const;

    pair<double, vector<int>> shortestPath(const string &srcName, const string &destName) const;

    // File persistence with JSON
    bool saveToJson(const string &file = "metro.json") const;
    bool loadFromJson(const string &file = "metro.json");

    void loadSampleData();

    static string trim(const string &s);
};

double calculateFare(double distanceKm);

#endif
