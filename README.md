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
<img width="1351" height="931" alt="image" src="https://github.com/user-attachments/assets/ed212c38-ba87-4431-a5e3-c0ee31d03497" />
<img width="1132" height="902" alt="image" src="https://github.com/user-attachments/assets/444a0fa0-3366-4582-8ee6-4077247cc9c7" />
<video width="600" controls>
  <source src="Shortest Path.mp4" type="video/mp4">
  Shortest Path
</video>






