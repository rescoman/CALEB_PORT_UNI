FuelPriceTrends_ZA (Python Data Analysis Project)

This project analyzes South African fuel price trends over time using Python.
It includes data cleaning, feature engineering, time-series analysis, and professional charts.

This is Project 4 of my Applied Mathematics + Computer Science portfolio.

⸻

🔍 Purpose of the Project

This project demonstrates:
	•	Python virtual environments
	•	Data manipulation using pandas
	•	Trend analysis (MoM %, SMA)
	•	Charting with matplotlib
	•	Saving clean tables for reporting
	•	Proper folder structure and reproducibility

This is similar to real work done by data analysts, research interns, and financial modelling interns.



📁 Project Structure

FuelPriceTrends_ZA/
│
├── data/
│   └── fuel_prices.csv          ← Input fuel price data
│
├── src/
│   └── main.py                  ← Analysis script
│
├── output/
│   ├── monthly_features.csv     ← Engineered dataset
│   ├── last6_summary.csv        ← Last 6-month summary
│   └── plots/
│        ├── ULP95_Rand_per_L_trend.png
│        └── Diesel50_Rand_per_L_trend.png
│
├── docs/
│
└── README.md