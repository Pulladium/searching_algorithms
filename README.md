# Searching Algorithms

## 1. Assignment Description
Implement a C++ application demonstrating two pattern-searching algorithms:  
- Brute Force (BF)  
- Boyer-Moore (BM)  

The program should be able to:  
- Search for a user-provided pattern in a given text.  
- Compare the performance (execution time) of these algorithms.  
- (Optional) Provide both a single-threaded and a multi-threaded approach.

## 2. Implementation
### 2.1 Overview
This project consists of two main classes:
1. **BruteForceSearch**  
   - Performs a naive, character-by-character matching.  
   - Time Complexity: O(n×m) in the worst case, where n is the text size, m is the pattern size.

2. **BoyerMoore**  
   - Implements the Boyer-Moore algorithm with Bad Character and Good Suffix heuristics.  
   - Average Case Time Complexity: O(n/m), Worst Case: O(n×m).

### 2.3 Notable Details
- Logging is handled by [spdlog](https://github.com/gabime/spdlog) for debug and info messages.  
- Each class records the execution time of its `search(...)` method in milliseconds.  
- If needed, more complex design details are explained in the code comments.

## 3. Functionality and Usage
### 3.1 Building the Project in Linux
1. Clone the repository and navigate to the project root.  
2. Run the following commands:
  - ```bash mkdir```
  - ```build ```
  - ```cd build```
  - ```cmake ..```
  - ```make```
3. An executable file (`search_algorithms`) will be created in the `build/` directory.

### 3.2 Running the Program
### 3.3 Command-Line Options
- `bf` or `bm`: which algorithm to use  
- `-f "<file_path>"`: path to the text file to be searched  
- `-t "<text_string>"`: direct string input to be searched  
- `-p "<pattern>"`: the pattern to look for  

After a successful build, you can run the program in two ways: 

1. **Search in a Text String**
   - Brute Force ``` ./search_algorithms bf -t "ABAAABCDABAAABCD" -p "ABC"```
   - Boyer-moore ``` ./search_algorithms bm -t "ABAAABCDABAAABCD" -p "ABC"```


2. **Search in a File**  
   Make sure the file path is correct relative to your current directory (in this case, `build/`):
   - ```./search_algorithms bf -f "../test_data/largeText.txt" -p "gravida"```
   - ```./search_algorithms bm -f "../test_data/largeText.txt" -p "gravida"```


## 4. Results and Performance Comparison
Below are sample runs on a large text file using both algorithms:

- **Boyer-Moore Results**  
  Found multiple occurrences of "gravida."  
  Execution time: 0.439763 ms  

- **Brute Force Results**  
  Found the same occurrences of "gravida."  
  Execution time: 0.950972 ms  

