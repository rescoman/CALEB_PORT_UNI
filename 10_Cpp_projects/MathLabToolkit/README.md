# MathLab Toolkit (C++)

Small console toolkit for first-year Applied Math:
- Matrix **addition** and **multiplication**
- **Determinants** (2×2, 3×3)
- Solve **Ax=b** (2×2, 3×3) via Gaussian elimination (with pivoting)

## Build & Run
```bash
cd src
g++ -std=c++17 -O2 -o mlt main.cpp
./mlt
