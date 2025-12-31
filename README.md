# 💊 Medicine Management System (BST vs. AVL Analysis)

**Description:**
A high-performance pharmacy inventory solution designed to manage medicine batches with precision. This project serves as a technical comparative study between **Binary Search Trees (BST)** and **Self-Balancing AVL Trees**, evaluating their efficiency in high-traffic medical environments with datasets of up to 10,000 records.

---


## 👤 Student Details

| Name | Matric ID | Project Focus |
| --- | --- | --- |
| **Lau Su Hui (Abby)** | MEC245045 | Medicine Management System (C++) |

---


## 📂 Project Modules

This repository contains two independent C++ implementations of the Medicine Management System to demonstrate the performance trade-offs of two search tree-based solutions.

### 1. Solution 1: Binary Search Tree (BST)
**File:** `UTM MECS1023 ADSA Assignment Task 4 BST Code - Lau Su Hui MEC245045.cpp`
* **Maximun Dataset Size/Input:** N = 10,000
* **Performance:** High insertion speed due to zero balancing overhead (**73.29 µs** at ).
* **Risk:** Susceptible to  linear degradation if data is entered in a sorted/skewed manner.


### 2. Solution 2: AVL Tree (Self-Balancing)
**File:** `UTM MECS1023 ADSA Assignment Task 4 AVL Code - Lau Su Hui MEC245045.cpp`
* **Maximun Dataset Size/Input:** N = 10,000
* **Performance:** Superior search efficiency (**1.65 µs**) and guaranteed  stability.
* **Key Mechanism:** Uses LL, RR, LR, and RL rotations to maintain a strict height balance (approx. 14 levels for 10,000 nodes).


### 🚀 Core Features (Both Systems)
* **Batch Tracking:** Manage Batch ID (Unique), Medicine Name, Quantity, Expiry Date, and Location.
* **Analysis Report Mode:** Built-in "Experiment Mode" to stress-test the system with automated datasets.
* **Data Integrity:** Mandatory pre-insertion search protocols to block duplicate Batch IDs.
* **Future Improvement:** Proposed **"Edit Medicine Batch"** feature for direct in-place node updates.

---

## 🛠️ Technologies Used

* **Language:** C++
* **Data Structures:** Binary Search Tree (BST), Adelson-Velsky and Landis Tree (AVL).
* **Concepts:** Recursive Traversal, Tree Rebalancing, Time-Complexity Analysis.
* **Libraries:**
  `<chrono>`: High-resolution time tracking for nanosecond precision.
  `<iomanip>`: Table formatting for professional console output.
  `<fstream>`: Results logging for performance reports.

---


## 🚀 How to Run

### 1. Compile the Source Code
Ensure you have a C++ compiler (like G++) installed. Open your terminal and navigate to the project folder.

**To run the BST Version:**
```bash
g++ "UTM MECS1023 ADSA Assignment Task 4 BST Code - Lau Su Hui MEC245045.cpp" -o meds_bst
./meds_bst

```

**To run the AVL Version (Recommended):**
```bash
g++ "UTM MECS1023 ADSA Assignment Task 4 AVL Code - Lau Su Hui MEC245045.cpp" -o meds_avl
./meds_avl

```

### 2. Enter "Analysis Report Mode"
Once the program is running, select **Option 5 (Performance Experiment)** to test the system with 1,000 to 10,000 records and view real-time execution benchmarks.

---


## 📑 Project Slides

[![Slides cover](slides/COVERIMAGE.png)](https://tinyurl.com/5x4rx55c)
**Click the image above to view the full presentation slides.**

---


## 📺 Project Demo

[![Watch the video](slides/COVERIMAGE.png)](https://youtu.be/PDWffA9j2Gs)
**Click the image above to watch the presentation and demo of my systems.**
