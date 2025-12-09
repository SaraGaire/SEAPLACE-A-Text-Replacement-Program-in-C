# SEAPLACE-A-Text-Replacement-Program-in-C
  A command-line text replacement tool implementing and comparing multiple string search algorithms including sequential search, Boyer-Moore, and KMP( Knuth-Morris-Pratt.)


## Description

**seaplace** (SEArch and rePLACE) is a powerful command-line utility that searches for a specified string within a file and replaces it with another string. It supports multiple search algorithms with different efficiency characteristics, making it ideal for understanding algorithm performance in real-world applications.

##Features

- **Multiple Search Algorithms:**
  - Sequential Search (seq) - using `memcmp()`
  - Character-by-Character Sequential (cbc)
  - Boyer-Moore (bm) - with bad character rules
  - Boyer-Moore Plus (bm+) - with both bad character and good suffix rules
  - Knuth-Morris-Pratt (KMP)

- **Flexible Options:**
  - Replace all occurrences or just the first one (`-1`)
  - Create automatic backups before modification (`-b`)
  - Choose search algorithm (`-a`)

- **Robust File Handling:**
  - Safe file operations with temporary files
  - Automatic backup creation
  - Comprehensive error handling

##  Installation Requirement

### Prerequisites
- GCC compiler
- Make utility
- Unix-like system (Linux, macOS, WSL)

### Clone the Repository
```bash
git clone https://github.com/SaraGaire/SEAPLACE-A-Text-Replacement-Program-in-C.git
cd SEAPLACE-A-Text-Replacement-Program-in-C
```

### Compile
```bash
make
```

## Usage
```bash
./seaplace [-a algorithm] [-b] [-1] <filename> <original> <replacement>
```

### Options
- `-a <algorithm>` - Specify search algorithm: `seq`, `cbc`, `kmp`, `bm`, `bm+`
- `-b` - Create backup of original file before modification
- `-1` - Replace only the first occurrence

### Parameters
- `<filename>` - Text file where searching and replacing occurs
- `<original>` - The string to be replaced (searched)
- `<replacement>` - The new string for replacement

##  Examples

### Example 1: Replace all occurrences (default sequential search)
```bash
./seaplace ets.txt All HAL
```

### Example 2: Replace only first occurrence using CBC
```bash
./seaplace -a cbc -1 ets.txt ever never
```

### Example 3: Replace with backup using Boyer-Moore
```bash
./seaplace -a bm -b input.txt old_string new_string
```

### Example 4: Using Boyer-Moore Plus
```bash
./seaplace -a bm+ document.txt Lorem LOREM
```

### Example 5: Using KMP algorithm
```bash
./seaplace -a kmp file.txt dolor PAIN
```

assignment03/
│
├── 🎯 Main Program
│   └── seaplace.c              → Entry point, handles command-line arguments
│
├── 🔄 Core Functionality
│   ├── replace.c               → Performs the actual find & replace
│   ├── replace.h               → Interface for replacement functions
│   └── search.h                → Common interface for all search algorithms
│
├── 🔍 Search Algorithms (5 different implementations)
│   ├── sequential_search.c     → Basic search (uses memcmp, fastest to code)
│   ├── sequential_search_cbc.c → Character-by-character (educational)
│   ├── kmp_search.c            → Knuth-Morris-Pratt (smart pattern matching)
│   ├── boyer_moore_search.c    → Boyer-Moore basic (efficient, industry standard)
│   └── boyer_moore_plus.c      → Boyer-Moore advanced (most efficient)
│
├── ⚙️ Build System
│   └── Makefile                → Compiles everything with one command
│
└── 📄 Test Files
├── ets.txt                 → Song lyrics for testing
└── lorem_ipsum.txt         → Lorem ipsum text for testing


---

##  What Each File Does

### **Main Files** (You interact with these)
| File | Purpose | What it does |
|------|---------|--------------|
| `seaplace.c` |  Controller | Reads your command, picks the algorithm, calls replace |
| `replace.c` |  Worker | Opens files, finds text, replaces it, saves results |

### **Algorithm Files** (The brain of the operation)
| File | Speed | When to use |
|------|-------|-------------|
| `sequential_search.c` |  Slow | Small files (< 1KB) |
| `sequential_search_cbc.c` | Slow | Learning/debugging |
| `kmp_search.c` |  Medium | Repeating patterns |
| `boyer_moore_search.c` |  Fast | Most cases (default choice) |
| `boyer_moore_plus.c` | Fastest | Large files (> 100KB) |

### **Helper Files**
| File | Purpose |
|------|---------|
| `search.h` |  Blueprint for all algorithms |
| `replace.h` |  Blueprint for replacement |
| `Makefile` | Builds the entire program |

---

## Simple Workflow

You type command:
./seaplace -a bm file.txt old new
↓
seaplace.c reads it
↓
Picks boyer_moore_search.c
↓
Calls replace.c
↓
replace.c uses the algorithm to find "old"
↓
Replaces with "new"
↓
Saves the file
↓



---

##  Visual File Relationships

                seaplace.c (BOSS)
                     |
                     ↓
        ┌────────────┴────────────┐
        ↓                         ↓
   replace.c                  search.h
  (Does work)              (Defines rules)
        |                         |
        ↓                         ↓
  Opens files          ┌──────────┴──────────┐
  Finds text           ↓          ↓          ↓
  Replaces it    sequential  boyer_moore  kmp_search
  Saves file         .c          .c          .c


##  How They Work Together as a whole?

Think of it like a restaurant:

| File | Restaurant Role |
|------|----------------|
| `seaplace.c` |  **Manager** - Takes your order |
| `replace.c` |  **Chef** - Prepares the food |
| `search.h` |  **Menu** - Lists what's available |
| `sequential_search.c` |  **Tool 1** - Basic knife |
| `boyer_moore.c` |  **Tool 2** - Professional chef's knife |
| `Makefile` |  **Kitchen Setup** - Organizes everything |
| `ets.txt` |  **Ingredient** - What you're cooking |

---




```

##  Algorithm Comparison

| Algorithm | Time Complexity | Best For |
|-----------|----------------|----------|
| Sequential (seq) | O(n*m) | Small files, short patterns |
| CBC | O(n*m) | Educational purposes |
| KMP | O(n+m) | Patterns with repetitions |
| Boyer-Moore (bm) | O(n/m) avg | Large files, long patterns |
| Boyer-Moore Plus (bm+) | O(n/m) avg | Professional text processing |

##  Technical Details

### Memory Management
- Dynamic memory allocation using `malloc()` and `free()`
- No memory leaks (properly freed resources)
- Safe file operations with error handling

### Design Patterns
- Function pointers for algorithm selection
- Modular architecture (easy to extend)
- Strategy pattern implementation

##  Example Output
```bash
$ ./seaplace -a bm -b ets.txt All HAL
...backup created: ets.txt.bak
...replacement successful.

$ ./seaplace ets.txt silence solence
...no occurrences of 'silence' found.
```

## Testing

Run all tests:
```bash
# Test sequential search
./seaplace ets.txt All HAL

# Test CBC with first-only flag
./seaplace -a cbc -1 ets.txt ever never

# Test with backup
./seaplace -a seq -b ets.txt I 9000

# Test Boyer-Moore
./seaplace -a bm lorem_ipsum.txt dolor PAIN

# Test Boyer-Moore Plus
./seaplace -a bm+ lorem_ipsum.txt Lorem LOREM
```

## Troubleshooting

### Compilation Issues
```bash
# Manual compilation if make fails
gcc -Wall -Wextra -g -c *.c
gcc -o seaplace *.o
```



## 🌟 Real-World Applications

This type of code is used in:
-  **Text Editors** - VS Code, Sublime, Vim (Find & Replace feature)
-  **Database Systems** - String matching in queries
-  **Bioinformatics** - DNA sequence matching
-  **Search Engines** - Pattern matching in documents
-  **Security Tools** - Log analysis and data sanitization
-  **Data Processing** - ETL pipelines and data cleaning

### Permission Denied
```bash
chmod +x seaplace
```



**Sara Gaire**
- GitHub: [@SaraGaire](https://github.com/SaraGaire)

## 
- Boyer-Moore algorithm by Robert S. Boyer and J Strother Moore
- KMP algorithm by Donald Knuth, Vaughan Pratt, and James H. Morris

## References

- [Boyer-Moore String Search Algorithm](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm)
- [Knuth-Morris-Pratt Algorithm](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)
- C Programming Language (K&R)
