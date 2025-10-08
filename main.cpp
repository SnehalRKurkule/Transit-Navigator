
#include <iostream>
#include <limits>   // for numeric_limits
#include "MetroMap.h"
#include "utils.h"

#include "nlohmann/json.hpp"
#include <fstream>
using json = nlohmann::json;

using namespace std;

int main() {
    MetroMap metro;
    int choice;

    cout << "Metro App (C++ with JSON)\n";

    do {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Show stations\n";
        cout << "2. Show connections\n";
        cout << "3. Add station\n";
        cout << "4. Remove station\n";
        cout << "5. Add connection\n";
        cout << "6. Remove connection\n";
        cout << "7. Find shortest path & fare\n";
        cout << "8. Save to metro.json\n";
        cout << "9. Load from metro.json\n";
        cout << "10. Load sample data\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (choice) {
            case 1:
                metro.listStations();
                pauseScreen();
                break;

            case 2:
                metro.listConnections();
                pauseScreen();
                break;

            case 3: {
                cout << "Enter new station name: ";
                string name = readline_trim();
                metro.addStation(name);
                break;
            }

            case 4: {
                cout << "Enter station name to remove: ";
                string name = readline_trim();
                metro.removeStation(name);
                break;
            }

            case 5: {
                cout << "Enter station A: ";
                string a = readline_trim();
                cout << "Enter station B: ";
                string b = readline_trim();
                cout << "Enter distance: ";
                double dist;
                cin >> dist;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                metro.addConnection(a, b, dist);
                break;
            }

            case 6: {
                cout << "Enter station A: ";
                string a = readline_trim();
                cout << "Enter station B: ";
                string b = readline_trim();
                metro.removeConnection(a, b);
                break;
            }

            case 7: 
        {
            cout << "Enter source: ";
            string src = readline_trim();
            cout << "Enter destination: ";
            string dst = readline_trim();

            auto result = metro.shortestPath(src, dst);

            if (result.first == numeric_limits<double>::infinity()) 
            {
                cout << "No route.\n";
            } 
            else 
            {
                cout << "Shortest distance: " << result.first << " km\n";
                cout << "Path: ";
                for (int id : result.second)
                {
                    cout << metro.getName(id) << " ";
                    if (id + 1 < result.second.size()) cout << " -> ";
                }
                cout << "\n";

                // ✅ Write path.json
                json j;
                j["path"] = json::array();
                for (int id : result.second) 
                {
                    j["path"].push_back(metro.getName(id));
                }
                std::ofstream out("path.json");
                out << j.dump(4);   // pretty print
                out.close();
                cout << "Path written to path.json\n";
            }
            pauseScreen();
            break;
        }
            case 8:
                metro.saveToJson("metro.json");
                cout << "Data saved to metro.json\n";
                break;

            case 9:
                metro.loadFromJson("metro.json");
                cout << "Data loaded from metro.json\n";
                break;

            case 10:
                metro.loadSampleData();
                cout << "Sample data loaded.\n";
                break;

            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 0);

    return 0;
}

