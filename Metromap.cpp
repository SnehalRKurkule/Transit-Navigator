#include "MetroMap.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;


MetroMap::MetroMap() {}

int MetroMap::addStation(const string &name) {
    string key = trim(name);
    auto it = nameToId.find(key);
    if(it != nameToId.end()) return it->second;
    int id = (int)idToName.size();
    idToName.push_back(key);
    nameToId[key] = id;
    adj.emplace_back();
    return id;
}

bool MetroMap::hasStation(const string &name) const {
    return nameToId.find(trim(name)) != nameToId.end();
}

int MetroMap::getId(const string &name) const {
    auto it = nameToId.find(trim(name));
    if(it == nameToId.end()) return -1;
    return it->second;
}

string MetroMap::getName(int id) const {
    if(id < 0 || id >= (int)idToName.size()) return "";
    return idToName[id];
}

int MetroMap::stationCount() const { return (int)idToName.size(); }

void MetroMap::addConnection(const string &a, const string &b, double dist) {
    int u = addStation(a);
    int v = addStation(b);
    adj[u].push_back({v, dist});
    adj[v].push_back({u, dist});
}

bool MetroMap::removeStation(const string &name) {
    int id = getId(name);
    if(id == -1) return false;
    for(auto &ne : adj) {
        ne.erase(remove_if(ne.begin(), ne.end(), [id](const Edge &e){ return e.to == id; }), ne.end());
    }
    adj[id].clear();
    nameToId.erase(trim(name));
    idToName[id] = "";
    return true;
}

bool MetroMap::removeConnection(const string &a, const string &b) {
    int u = getId(a), v = getId(b);
    if(u == -1 || v == -1) return false;
    adj[u].erase(remove_if(adj[u].begin(), adj[u].end(), [v](const Edge &e){ return e.to == v; }), adj[u].end());
    adj[v].erase(remove_if(adj[v].begin(), adj[v].end(), [u](const Edge &e){ return e.to == u; }), adj[v].end());
    return true;
}

void MetroMap::listStations() const {
    cout << "Stations:\n";
    for(size_t i=0;i<idToName.size();++i) {
        if(!idToName[i].empty())
            cout << "  [" << i << "] " << idToName[i] << "\n";
    }
}

void MetroMap::listConnections() const {
    cout << "Connections:\n";
    for(size_t u=0; u<adj.size(); ++u) {
        if(idToName[u].empty()) continue;
        for(const Edge &e : adj[u]) {
            if((int)u < e.to && !idToName[e.to].empty()) {
                cout << "  " << idToName[u] << " <--> " << idToName[e.to] << " : " << e.dist << " km\n";
            }
        }
    }
}

pair<double, vector<int>> MetroMap::shortestPath(const string &srcName, const string &destName) const {
    int src = getId(srcName);
    int dest = getId(destName);
    if(src == -1 || dest == -1) return {numeric_limits<double>::infinity(), {}};
    int n = (int)adj.size();
    const double INF = numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> parent(n, -1);
    using PDI = pair<double,int>;
    priority_queue<PDI, vector<PDI>, greater<PDI>> pq;
    dist[src] = 0.0;
    pq.push({0.0, src});
    while(!pq.empty()) {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(d > dist[u]) continue;
        if(u == dest) break;
        for(const Edge &e : adj[u]) {
            if(idToName[e.to].empty()) continue;
            double nd = d + e.dist;
            if(nd < dist[e.to]) {
                dist[e.to] = nd;
                parent[e.to] = u;
                pq.push({nd, e.to});
            }
        }
    }
    if(dist[dest] == INF) return {INF, {}};
    vector<int> path;
    for(int cur = dest; cur != -1; cur = parent[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());
    return {dist[dest], path};
}

bool MetroMap::saveToJson(const string &file) const {
    json j;
    j["stations"] = idToName;
    j["edges"] = json::array();
    for(size_t u=0; u<adj.size(); ++u) {
        for(const Edge &e : adj[u]) {
            if((int)u < e.to) {
                j["edges"].push_back({{"from", (int)u}, {"to", e.to}, {"dist", e.dist}});
            }
        }
    }
    ofstream ofs(file);
    if(!ofs) return false;
    ofs << j.dump(4);
    return true;
}

bool MetroMap::loadFromJson(const string &file) {
    ifstream ifs(file);
    if(!ifs) return false;
    json j;
    ifs >> j;
    idToName = j["stations"].get<vector<string>>();
    nameToId.clear();
    for(size_t i=0;i<idToName.size();++i) {
        if(!idToName[i].empty()) nameToId[idToName[i]] = (int)i;
    }
    adj.assign(idToName.size(), {});
    for(auto &edge : j["edges"]) {
        int u = edge["from"], v = edge["to"];
        double d = edge["dist"];
        if(u >= 0 && v >= 0 && u < (int)idToName.size() && v < (int)idToName.size()) {
            adj[u].push_back({v,d});
            adj[v].push_back({u,d});
        }
    }
    return true;
}

void MetroMap::loadSampleData() {
    adj.clear();
    nameToId.clear();
    idToName.clear();
    addConnection("Central", "Park Street", 1.2);
    addConnection("Park Street", "Museum", 0.9);
    addConnection("Museum", "City Hall", 1.1);
    addConnection("Central", "Airport", 12.5);
    addConnection("Central", "University", 3.4);
    addConnection("University", "Tech Park", 2.1);
    addConnection("Tech Park", "Airport", 10.0);
    addConnection("Museum", "University", 2.6);
}

string MetroMap::trim(const string &s) {
    size_t a = 0;
    while(a < s.size() && isspace((unsigned char)s[a])) ++a;
    if(a == s.size()) return "";
    size_t b = s.size()-1;
    while(b > a && isspace((unsigned char)s[b])) --b;
    return s.substr(a, b-a+1);
}

double calculateFare(double distanceKm) {
    if(distanceKm <= 0.0) return 0.0;
    if(distanceKm <= 2.0) return 10.0;
    if(distanceKm <= 5.0) return 20.0;
    if(distanceKm <= 10.0) return 30.0;
    double extra = distanceKm - 10.0;
    return 30.0 + extra * 2.5;
}
