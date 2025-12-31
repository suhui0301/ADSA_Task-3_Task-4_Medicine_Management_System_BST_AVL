/*
 * Name: Lau Su Hui (Abby)
 * Matric No.: MEC245045
 * Semester: 20252026-1
 * Course: MECS1023 ADSA
 * Group & Theme: Group 1-Pharmacy Inventory Control System
 * Assignment Title: Medicine Management System (Solution 1-BST)
 */

#include <cctype>  // For isdigit, isupper
#include <chrono>  // For measuring execution time (performance analysis)
#include <cstdlib> // For random number generation  (experiment mode)
#include <ctime>   // For seeding random generator
#include <fstream> // For writing results to file
#include <iomanip> // For table formatting (setw)
#include <iostream>
#include <limits> // For clearing input buffer
#include <string>
#include <vector> // For storing test data

using namespace std;
using namespace std::chrono; // Namespace for time functions

// ==========================================
// 1. DATA STRUCTURES
// ==========================================

// These are the details for one batch of medicine
struct Medicine {
  string batchID;      // Key: Unique Batch ID (e.g., "B101") used for sorting
  string medicineName; // Name of the medicine
  int quantity;        // Physical stock count in this specific batch
  string expiryDate;   // Safety: Expiry Date (e.g., "05-05-2026")
  string location;     // Logistics: Exact shelf location (e.g., "Shelf A01")
};

// This structure represents a "Node" in the Binary Search Tree (BST)
struct Node {
  Medicine data; // The medicine details
  Node *left;    // Pointer to left child (alphabetically smaller Batch ID)
  Node *right;   // Pointer to right child (alphabetically larger Batch ID)

  // Constructor to initialise a node with data and null pointers
  Node(Medicine med) {
    data = med;
    left = nullptr;
    right = nullptr;
  }
};

// ==========================================
// 2. BST MEDICINE MANAGER CLASS (ADT)
// ==========================================

class MedicineManager {
private:
  Node *root; // The root pointer of the BST

  // --- PRIVATE HELPERS FUNCTIONS (CORE OPERATIONS: INSERT, SEARCH, DELETE) ---
  // Recursive helper to insert a new batch
  // Logic: Smaller Batch IDs go Left, Larger Batch IDs go Right
  Node *insertInternal(Node *current, Medicine med, bool showErrors) {
    // 1. Base Case: If we reach an empty spot, create the new node here
    if (current == nullptr) {
      return new Node(med);
    }

    // 2. Recursive Step: Navigate down the tree
    if (med.batchID < current->data.batchID) {
      current->left =
          insertInternal(current->left, med, showErrors); // Go Left (Smaller)
    } else if (med.batchID > current->data.batchID) {
      current->right =
          insertInternal(current->right, med, showErrors); // Go Right (Larger)
    } else {
      // 3. Duplicate Case: Batch ID already exists
      if (showErrors) {
        cout << "Error: Batch ID " << med.batchID << " already exists.🚫"
             << endl;
      }
    }
    return current;
  }

  // Recursive helper to search for a batch by ID
  // Time Complexity: O(log n) on average, O(n) worst case
  Node *searchInternal(Node *current, string batchID) {
    // Base Case: Found it OR reached dead end of the tree
    if (current == nullptr || current->data.batchID == batchID) {
      return current;
    }
    // Binary Search Logic: Navigate Left or Right
    if (batchID < current->data.batchID) {
      return searchInternal(current->left, batchID);
    } else {
      return searchInternal(current->right, batchID);
    }
  }

  // Helper to find the node with the minimum Batch ID in a subtree
  // Used during deletion (Case 3: Two Children)
  Node *findMinNode(Node *node) {
    Node *current = node;
    // Keep going left until we hit the last node
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  // Recursive helper to delete a specific batch
  Node *removeInternal(Node *current, string batchID) {
    if (current == nullptr)
      return current;

    // 1. Navigation phase: Find the node to delete
    if (batchID < current->data.batchID) {
      current->left = removeInternal(current->left, batchID);
    } else if (batchID > current->data.batchID) {
      current->right = removeInternal(current->right, batchID);
    } else {
      // 2. The node is found. Handle the 3 Deletion Cases:
      // Case 1 & Case 2: Only one child or no child
      if (current->left == nullptr) {
        Node *temp = current->right;
        delete current;
        return temp;
      } else if (current->right == nullptr) {
        Node *temp = current->left;
        delete current;
        return temp;
      }
      // Case 3: Two children
      // Find the In-Order Successor (smallest node in right subtree)
      Node *temp = findMinNode(current->right);
      // Copy the successor's data to this node
      current->data = temp->data;
      // Delete the duplicate successor node from the right subtree
      current->right = removeInternal(current->right, temp->data.batchID);
    }
    return current;
  }

  // Recursive helper: In-Order Traversal (alphabetical order display)
  void inorderInternal(Node *current) {
    if (current != nullptr) {
      inorderInternal(current->left); // 1. Visit Left

      // 2. Display current node details
      cout << left << setw(15) << current->data.batchID << setw(25)
           << current->data.medicineName << setw(10) << current->data.quantity
           << setw(15) << current->data.expiryDate << setw(15)
           << current->data.location << endl;

      inorderInternal(current->right); // 3. Visit Right
    }
  }

  // Helper: Clears memory recursively to reset tree for experiments
  void clearTree(Node *node) {
    if (node == nullptr)
      return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
  }

public:
  // Constructor: Initialise empty tree
  MedicineManager() { root = nullptr; }

  // Public Interface for Insertion
  bool addMedicine(Medicine med, bool showErrors = true) {
    if (findMedicine(med.batchID) != nullptr) {
      if (showErrors) {
        cout << "Error: Batch ID " << med.batchID << " already exists.🚫"
             << endl;
      }
      return false;
    }
    root = insertInternal(root, med, showErrors);
    return true;
  }

  // Public Interface for Search
  // Returns a pointer to Medicine data if found, otherwise nullptr
  Medicine *findMedicine(string batchID) {
    Node *result = searchInternal(root, batchID);
    if (result != nullptr) {
      return &(result->data);
    }
    return nullptr;
  }

  // Public Interface for Deletion
  void removeMedicine(string batchID) { root = removeInternal(root, batchID); }

  // Public Interface for Display
  void showAllMedicines() {
    if (root == nullptr) {
      cout << "No medicines in the system.⚠️" << endl;
      return;
    }
    cout << left << setw(15) << "Batch ID" << setw(25) << "Name" << setw(10)
         << "Quantity" << setw(15) << "Expiry" << setw(20) << "Location"
         << endl;
    cout << string(85, '-') << endl;
    inorderInternal(root);
  }

  // --- EXPERIMENT MODE ---
  // This function populates random data to create the Analysis Report
  void runExperiment(int n) {
    // 1. Clear existing data to ensure fair test
    clearTree(root);
    root = nullptr;
    vector<Medicine> dataset;

    cout << "\nCreating " << n << " random medicines..." << endl;

    // 2. Generate N random data or medicines
    for (int i = 0; i < n; i++) {
      Medicine m;
      // Generate somewhat random IDs (e.g., B1045)
      // Using n*2 range to allow some gaps in IDs
      m.batchID = "B" + to_string(rand() % (n * 2));
      m.medicineName = "Med " + to_string(i);
      m.quantity = 10;
      m.expiryDate = "01-JAN-2027"; // Updated format for experiment data
      m.location = "Shelf";
      dataset.push_back(m);
    }

    // 3. Measure Insertion Time (Average)
    auto startIns = high_resolution_clock::now();
    for (auto &med : dataset) {
      addMedicine(med, false); // To suppress duplicate error messages
    }
    auto stopIns = high_resolution_clock::now();
    auto durIns = duration_cast<microseconds>(stopIns - startIns);

    // 4. Measure Search Time (Average)
    auto startSearch = high_resolution_clock::now();
    for (auto &med : dataset) {
      findMedicine(med.batchID);
    }
    auto stopSearch = high_resolution_clock::now();
    auto durSearch = duration_cast<microseconds>(stopSearch - startSearch);

    // 5. Print Analysis Report
    ofstream outFile("bst_results_task4.txt");
    outFile << "Avg Insert Time: " << (double)durIns.count() / n << endl;
    outFile << "Avg Search Time: " << (double)durSearch.count() / n << endl;
    outFile.close();

    cout << "\n--- BST Analysis Report Data (Size: " << n << ") ---" << endl;
    cout << "Avg Insert Time: " << (double)durIns.count() / n << " microseconds"
         << endl;
    cout << "Avg Search Time: " << (double)durSearch.count() / n
         << " microseconds" << endl;
    cout << "Total Time: " << durIns.count() << " (Insert) / "
         << durSearch.count() << " (Search)" << endl;
  }
};

// ==========================================
// 3. UTILITY FUNCTIONS
// ==========================================

// Clears the input buffer to prevent infinite loops on invalid input
void clearInputBuffer() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Ensures the user enters a valid integer (prevents crashing)
int getValidInt() {
  int value;
  while (!(cin >> value)) {
    cout << "Invalid input. Please enter a number: ";
    cin.clear();                                         // Clear error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
  }
  cin.ignore();
  return value;
}

// Validates date format (DD-MMM-YYYY), e.g., 01-JAN-2025
bool isValidDate(const string &date) {
  // 1. Basic Length Check
  if (date.length() != 11)
    return false;

  // 2. Hyphen Check
  if (date[2] != '-' || date[6] != '-')
    return false;

  // 3. Digit Check (Day and Year)
  if (!isdigit(date[0]) || !isdigit(date[1]))
    return false;
  if (!isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9]) ||
      !isdigit(date[10]))
    return false;

  // 4. Uppercase Check (Structure)
  if (!isupper(date[3]) || !isupper(date[4]) || !isupper(date[5]))
    return false;

  // 5. VALID MONTH CHECK (The missing piece!)
  string monthPart = date.substr(3, 3);
  string validMonths[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                          "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

  bool isRealMonth = false;
  for (const string &m : validMonths) {
    if (monthPart == m) {
      isRealMonth = true;
      break;
    }
  }
  return isRealMonth;
}

// ==========================================
// 4. MAIN PROGRAM (USER INTERFACE)
// ==========================================

int main() {
  srand(time(0)); // Seed random generator
  MedicineManager system;
  int choice;

  // Pre-load some sample data for demo
  system.addMedicine(
      {"B303", "Ascorbic Acid 1000mg", 100, "03-MAR-2027", "Shelf A01"});
  system.addMedicine(
      {"B101", "Insulin Pen U-100", 20, "01-JAN-2027", "Fridge FR01"});
  system.addMedicine(
      {"B505", "Paracetamol 500mg", 500, "05-MAY-2027", "Shelf P02"});

  do {
    // Main Menu
    cout << "\nWelcome to the Medicine Management System!💊" << endl;
    cout << "\n=== Medicine Management System (BST) ===" << endl;
    cout << "1. Add New Medicine Batch➕" << endl;
    cout << "2. Search by Batch ID🔎" << endl;
    cout << "3. Display All Batches💻" << endl;
    cout << "4. Delete Batch➖" << endl;
    cout << "5. Analysis Report: Run Performance Experiment📊" << endl;
    cout << "6. Exit👋" << endl;
    cout << "Enter your choice: ";

    // Validate Menu Input
    if (!(cin >> choice)) {
      cout << "Invalid choice. Please enter a number.⚠️" << endl;
      clearInputBuffer();
      continue;
    }

    cin.ignore();

    // Handle Menu Choices
    if (choice == 1) {
      Medicine med;
      cout << "\n--- ➕Add Medicine Batch➕ ---" << endl;
      cout << "Enter Batch ID (e.g., B202): ";
      getline(cin, med.batchID);
      cout << "Enter Medicine Name: ";
      getline(cin, med.medicineName);

      cout << "Enter Quantity: ";
      med.quantity = getValidInt(); // Use valid int input

      while (true) {
        cout << "Enter Expiry Date (DD-MMM-YYYY, e.g., 01-JAN-2027): ";
        getline(cin, med.expiryDate);
        if (isValidDate(med.expiryDate)) {
          break;
        } else {
          cout
              << "Invalid format! Please use DD-MMM-YYYY (e.g., 01-JAN-2025).❌"
              << endl;
        }
      }

      cout << "Enter Location (e.g., Shelf A01): ";
      getline(cin, med.location);

      // Measure Execution Time for Insertion
      auto start = high_resolution_clock::now();
      bool isAdded = system.addMedicine(med);
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<nanoseconds>(
          stop - start); // Use Nanoseconds for single operation
      if (isAdded) {
        cout << "Batch added successfully!✅" << endl;
        cout << "Execution Time: " << duration.count() << " nanoseconds"
             << endl;
      }
    } else if (choice == 2) {
      string id;
      cout << "\n--- 🔎Search Medicine🔎 ---" << endl;
      cout << "Enter Batch ID to search: ";
      getline(cin, id);

      // Measure Execution Time for Search
      auto start = high_resolution_clock::now();
      Medicine *foundMed = system.findMedicine(id);
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<nanoseconds>(stop - start);

      if (foundMed != nullptr) {
        cout << "\n[FOUND] Batch Details:" << endl;
        cout << "Batch ID: " << foundMed->batchID << endl;
        cout << "Name:     " << foundMed->medicineName << endl;
        cout << "Quantity: " << foundMed->quantity << endl;
        cout << "Expiry:   " << foundMed->expiryDate << endl;
        cout << "Location: " << foundMed->location << endl;
      } else {
        cout << "\n[NOT FOUND] Batch " << id << " does not exist.❌" << endl;
      }
      cout << "Execution Time: " << duration.count() << " nanoseconds" << endl;

    } else if (choice == 3) {
      cout << "\n--- 💊All Medicine Batches💊 ---" << endl;

      // Measure Execution Time for Traversal
      auto start = high_resolution_clock::now();
      system.showAllMedicines();
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<nanoseconds>(stop - start);
      cout << "Execution Time: " << duration.count() << " nanoseconds" << endl;

    } else if (choice == 4) {
      string id;
      cout << "\n--- ➖Delete Batch➖ ---" << endl;
      cout << "Enter Batch ID to delete: ";
      getline(cin, id);

      // Measure Execution Time for Deletion
      auto start = high_resolution_clock::now();
      system.removeMedicine(id);
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<nanoseconds>(stop - start);
      cout << "Delete operation completed.✅" << endl;
      cout << "Execution Time: " << duration.count() << " nanoseconds" << endl;

    } else if (choice == 5) { // Experiment Mode
      int n;
      cout << "\n--- 📊Performance Experiment📊 ---" << endl;
      cout << "Enter dataset size N (e.g. 1000, 5000, 10000): ";
      if (cin >> n) {
        system.runExperiment(n);
      } else {
        cout << "Invalid number.❌" << endl;
        clearInputBuffer();
      }

    } else if (choice == 6) {
      cout << "Exiting... Goodbye!👋" << endl;
    } else {
      cout << "Invalid choice.❌" << endl;
    }

  } while (choice != 6); // Loop until user chooses to exit

  return 0;

}
