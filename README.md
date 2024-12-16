# **Observe**
An imitation game of *I'm on Observation Duty*

## **DEVELOPED BY LEE SI HYEON / KHU DIGITAL CONTENTS**  
### **Developed through 2 months**  
**<PORTFOLIO>**  

---

### **Development Overview**  
- **Development:** Indie (Solo) Development  
- **Engine:** Unreal Engine 5.1  
- **IDE:** Visual Studio Code  
- **Compiler:** Visual Studio 2022  
- **Code Composition:** C++ (70%) / Blueprint (30%)  

---

## **1) Demo Video**  
[Insert demo video link here.]

---

## **2) Game Architecture**

### **2-1) Player**  
#### **Class Structure**  
- `APlayerController` → **`AObservationPlayerController`**  
- `APlayerCameraManager` → **`AObservationPlayerCameraManager`**  

#### **Key Features**  
- **Camera Switching:**  
  - `AObservationPlayerCameraManager` handles transitions between security cameras.  
  - Manages an array of camera Actors and tracks the currently active camera.  
  - Hidden cameras are activated under specific conditions (e.g., elapsed time).  

- **Input Handling:**  
  - `AObservationPlayerController` processes player inputs, enabling camera switching and anomaly reporting.  
  - Functions exposed to Blueprint for interaction between C++ and UMG.  

---

### **2-2) Anomaly**  
#### **Class Structure**  
- `AActor` → **`AAnomalyBase`** (Abstract Class)  
  - **`AFurnitureAnomaly`**  
  - **`APaintingAnomaly`**  
  - **`AGhostAnomaly`**  
  - **`AIntruderAnomaly`**  

#### **Key Features**  
- **Anomaly Types:**  
  - Each anomaly has unique visuals and behavior (e.g., material changes, movements, animations).  
  - `AAnomalyBase` provides shared interfaces and logic for spawning, removal, and reporting.  
  - Specific anomalies use Skeletal Mesh to implement animation-based actions.  

- **Anomaly Manager:**  
  - `AActor` → **`AAnomalyManager`**  
  - Maintains a list of active anomalies and tracks previously triggered anomalies to prevent repetition.  
  - Adjusts anomaly spawn frequency based on `CurrentElapsedTime`.  

---

### **2-3) Gamemode**  
#### **Class Structure**  
- `AGameModeBase` → **`AObservationGameMode`**  

#### **Key Features**  
- **Time Management:**  
  - `AObservationGameMode` manages game start time and elapsed time.  
  - Activates hidden cameras or increases anomaly frequency after specific time intervals.  

- **Dynamic Anomaly Triggering:**  
  - Difficulty scales automatically based on game progression.  
  - Collaborates with `AAnomalyManager` to determine the frequency and type of anomalies.  

---

### **2-4) Widget (UI)**  
#### **Class Structure**  
- `UUserWidget` → **`UWBP_GameHUD`**, **`UWBP_GameOverWidget`**  

#### **Key Features**  
- **HUD Elements:**  
  - `UWBP_GameHUD` displays game progress, active camera index, and anomaly status.  
  - Real-time binding of variables such as `CurrentElapsedTime` and `ActiveAnomalyCount` to widget text.  

- **Game Over Screen:**  
  - `UWBP_GameOverWidget` is activated at the end of the game to display statistics.  
  - Easily customizable through Blueprint.  

---

### **Acknowledgments**  
This project was developed with partial help from ChatGPT and primarily through YouTube tutorials.  

---

### **DEVELOPMENT STILL IN PROGRESS**  
Since 2024  

---

### **COPYRIGHT**  
**© Sitheleon. All Rights Reserved.**
