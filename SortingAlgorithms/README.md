# Sorting Algorithms Analysis

In this repository, we delve into the practical application and performance evaluation of classic sorting algorithms. Leveraging a dataset of film ratings and production dates, we transitioned from an Excel-based database to a more programmatic data structure, specifically a list of tuples in Python, to enable efficient data manipulation and sorting.

## Data

The dataset, a compilation of film ratings with corresponding production dates, originated from an Excel file and was systematically transferred into a Python data structure that consists of lists of tuples. This format was chosen to optimize the sorting operations that followed.

## Code

The Python script `SortingAlgorithms.py` within this repository encapsulates the complete logic for:

- Importing the dataset from the Excel file.
- Converting it into a list of tuples for internal use.
- Implementing and testing various sorting algorithms, such as:
  - Merge Sort
  - Quick Sort
  - Bucket Sort

We investigate each algorithm's time complexity, and compute key statistics of the sorted data, including the median and average ratings, post-sorting based on film ratings.

## Experiments

Our approach includes:

- Execution time measurement for each sorting algorithm to determine efficiency.
- Complexity analysis to understand the theoretical versus practical performance.
- Statistical analysis to extract insights from the sorted data, particularly focusing on the ratings' median and average.

## Results

The `SortingAlgorithms_Report.pdf` houses a comprehensive account of our findings, featuring:

- Detailed methodology and experimental setup.
- Graphical representations of performance metrics.
- A theoretical expectations against empirical data.

All results, including plots and a theoretical vs. practical comparison of the sorting algorithms, are thoroughly documented in the accompanying PDF report.

_Note: The repository serves as a transparent medium to share my findings and methodologies. All data and code used for the experiments are openly provided, ensuring reproducibility and verifiability of the research._
