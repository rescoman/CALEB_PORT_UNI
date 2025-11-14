from pathlib import Path
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def load_data(path: Path) -> pd.DataFrame:
    df = pd.read_csv(path)
    df.columns = [c.strip() for c in df.columns]
    df["Date"] = pd.to_datetime(df["Date"], errors="coerce")
    df = df.dropna(subset=["Date"]).sort_values("Date")
    return df

def preprocess(df: pd.DataFrame) -> pd.DataFrame:
    numeric_cols = [c for c in df.columns if c.lower().endswith("per_l")]
    out = df[["Date"] + numeric_cols].copy()
    out = out.set_index("Date").resample("MS").mean().reset_index()
    for col in numeric_cols:
        out[f"{col}_MoM_pct"] = out[col].pct_change() * 100
        out[f"{col}_SMA3"] = out[col].rolling(3, min_periods=1).mean()
    return out

def plot_series(df: pd.DataFrame, col: str, outdir: Path, title: str):
    outdir.mkdir(parents=True, exist_ok=True)
    plt.figure()
    plt.plot(df["Date"], df[col], label=col)
    plt.plot(df["Date"], df[f"{col}_SMA3"], label="SMA(3)")
    plt.title(title)
    plt.xlabel("Date")
    plt.ylabel("Rand per litre")
    plt.legend()
    plt.gcf().autofmt_xdate(rotation=45)     # Rotate dates 45 degrees
    plt.xticks(fontsize=9)                   # Smaller ticks
    plt.xlabel("Date")                       # Cleaner axis label
    plt.tight_layout()
    plt.savefig(outdir / f"{col}_trend.png", dpi=160)
    plt.close()

def main():
    project_root = Path(__file__).resolve().parents[1]
    data_path = project_root / "data" / "fuel_prices.csv"
    outdir = project_root / "output"
    plots_dir = outdir / "plots"

    df = load_data(data_path)
    df = preprocess(df)

    fuel_cols = [c for c in df.columns if c.endswith("_Rand_per_L")]
    outdir.mkdir(exist_ok=True)
    df.to_csv(outdir / "monthly_features.csv", index=False)
    df.tail(6).to_csv(outdir / "last6_summary.csv", index=False)

    titles = {
        "ULP95_Rand_per_L": "ULP95 monthly price & SMA(3)",
        "Diesel50_Rand_per_L": "Diesel50 monthly price & SMA(3)",
    }
    for col in fuel_cols:
        plot_series(df, col, plots_dir, titles.get(col, col))

    print("✅ Done. Tables saved in 'output', plots in 'output/plots'")

if __name__ == "__main__":
    main()