# SEAPLACE-A-Text-Replacement-Program-in-C
  A command-line text replacement tool implementing and comparing multiple string search algorithms including sequential search, Boyer-Moore, and KMP( Knuth-Morris-Pratt.)


##  Description

**seaplace** (SEArch and rePLACE) is a powerful command-line utility that searches for a specified string within a file and replaces it with another string. It supports multiple search algorithms with different efficiency characteristics, making it ideal for understanding algorithm performance in real-world applications.

## Features

- **Multiple Search Algorithms:**
  - Sequential Search (seq) - using `memcmp()`
  - Character-by-Character Sequential (cbc)
  - Boyer-Moore (bm) - with bad character rule
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

## Installation And Requirement

### Prerequisites
- GCC compiler
- Make utility
- Unix-like system (Linux, macOS, WSL)

### Clone the Repository
```bash
