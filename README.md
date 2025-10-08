# Transit Navigator

 **Transit Navigator** is a Shortest pathfinding and visualization project that helps users find the shortest route between two stations and visualize the journey.  
The project combines **C++ (for backend shortest path logic)** with **HTML, CSS, and JavaScript (for frontend visualization)**.  

## Features
- Add/remove stations and connections dynamically  
- Save and load network data in **JSON format**  
- Compute shortest path using **Dijkstra’s algorithm**  
- Export computed path to JSON and visualize it in the browser  
- Animated path visualization (station-to-station movement)  

## 🛠️ Tech Stack
- **C++** → Core logic for graph and shortest path  
- **nlohmann/json** → JSON handling in C++  
- **HTML, CSS, JavaScript** → Visualization and animation  


## Run Instructions

### C++ Program
g++ main.cpp MetroMap.cpp utils.cpp -I. -o METROAPP.exe                              
.\METROAPP.exe     
### Output
<img width="1056" height="721" alt="image" src="https://github.com/user-attachments/assets/a10081b1-4b69-4622-97ef-86f86a1141f8" />

<img width="1132" height="902" alt="image" src="https://github.com/user-attachments/assets/444a0fa0-3366-4582-8ee6-4077247cc9c7" />
#### Shortest Path Demo

<!-- GIF animation -->
![Shortest Path Demo](Output/Shortest_Path.gif).






