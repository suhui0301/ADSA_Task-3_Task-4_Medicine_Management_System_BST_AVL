# 💊 Pharmacy Inventory Control System (Group 1)

**Description:**
A comprehensive pharmacy management solution comprising three independent systems/modules. 
All systems are built using the **Binary Search Tree (BST)** data structure to ensure efficient O(log n) performance for searching, sorting, and inventory management.

---


## 👥 Group Members & Roles

| Name | Matric ID | Assigned System (BST-Based) |
| :--- | :--- | :--- |
| **Lau Su Hui (Abby)** | MEC245045 | Medicine Management System (in C++)|
| **Nurul ‘Aini Binti Hamdan** | MEC245046 | Supplier & Vendor Mgmt System (in Python)|
| **Winnie Ngu** | MEC245065 | Pharmacy Stock System (in C++)|

---


## 📂 Project Modules

This repository contains three distinct independent BST-based applications/systems:

### 1. Medicine Management System (Batch Tracking)
**File Location:** `src/Meds Mgmt System Source Code - Group 1 Abby (Solution 1 BST).cpp`
* **Language:** C++
* **Description:** Manages medicine batches including expiry dates and physical shelf locations.
* **Key Features:**
    * Add new medicine batches with ID, Name, Quantity, Expiry, and Location.
    * Search for specific batches using Batch ID.
    * Delete expired or empty batches.
    * **Performance Tracking:** Displays execution time (in nanoseconds) for operations.

### 2. Pharmacy Stock System (Inventory)
**File Location:** `src/Pharmacy Stock System Source Code - Group 1 Winnie (Solution 1 BST).cpp`
* **Language:** C++
* **Description:** A core inventory system for tracking stock levels and pricing.
* **Key Features:**
    * Pre-loaded with default stock data.
    * Update quantity and price for existing items.
    * Full inventory display (Sorted by ID).
    * Robust input validation for prices and quantities.
      
### 3. Supplier & Vendor Management System
**File Location:** `srcSupplier & Vendor Mgmt System Source Code - Group 1 Aini (Solution 1 BST).py`
* **Language:** Python
* **Description:** A system to manage pharmacy suppliers and their ratings.
* **Key Features:**
    * Add, Update, and Delete supplier profiles.
    * Track Supplier Ratings (1-5 stars) and contact info.
    * Display all suppliers sorted by ID.
    * **Performance Tracking:** Displays execution time (in microseconds) for all BST operations.

---


## 🛠️ Technologies Used
* **Languages:** C++, Python
* **Data Structure:** Binary Search Tree (BST)
    * Used for all Insert, Search, and Delete operations to maintain sorted data.
    * Efficient for handling unique IDs (Batch ID, Supplier ID, Medicine ID).
* **Libraries:** C++: `chrono` (Time tracking), `iostream`, `iomanip`
    * Python: `numpy`, `pandas`, `time`, `os`

---


## 🚀 How to Run

### Running the C++ Files (Medicine & Stock Systems)
1. You need a C++ compiler (like G++).
2. Open your terminal/command prompt.
3. Navigate to the folder containing the files.
4. Compile and run the specific module/system.
#### -For Medicine System
g++ "Meds Mgmt System Source Code - Group 1 Abby (Solution 1 BST).cpp" -o meds_system
./meds_system
#### -For Stock System
g++ "Pharmacy Stock System Source Code - Group 1 Winnie (Solution 1 BST).cpp" -o stock_system
./stock_system

### Running the Python File
1. Ensure Python is installed.
2. Navigate to the folder containing the file.
3. Run:
#### -For Supplier System
python "Supplier & Vendor Mgmt System Source Code - Group 1 Aini (Solution 1 BST).py"

---


## 📑 Project Slides
[![Slides Cover](slides/COVERIMAGE.png)](https://tinyurl.com/44bbdf49)
**Click the image above to view our full presentation. Access is restricted to UTM accounts only.**

---


## 📺 Project Demo
[![Watch the video](https://img.youtube.com/vi/NgSbu7_eTZ0/maxresdefault.jpg)](https://youtu.be/NgSbu7_eTZ0)
**Click the image above to watch the demo of our systems.**
