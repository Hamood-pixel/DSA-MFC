📊 MFC Sorting Visualizer
An interactive desktop application built with C++ and Microsoft Foundation Class (MFC) that visualizes the execution of various sorting algorithms in real-time. This project demonstrates advanced UI management, timer-based logic, and algorithmic efficiency.

🚀 Overview
The application generates a random dataset and provides a frame-by-frame animation of sorting processes. It utilizes a custom drawing engine within the OnPaint handler to render data bars that update dynamically as the algorithm progresses.

✨ Key Features
Real-time Visualization: Smooth animation of data movements.

Supported Algorithms: * Bubble Sort: Visualizes the largest elements "bubbling" to the end.

Selection Sort: Highlights the search for the minimum element.

Insertion Sort: Demonstrates building a sorted sub-array.

Merge Sort (Iterative): Shows the merging of sub-problems.

Quick Sort (Iterative): Displays pivot-based partitioning.

Visual Indicators:

Blue: Unsorted/Idle elements.

Red: Elements currently being compared or swapped.

Green: Elements confirmed to be in their final sorted position.

Performance Metrics: Accurate timing using a high-resolution clock displayed in milliseconds.

🛠️ Technical Implementation
Non-Blocking UI: Algorithms are implemented as "step-functions" called by a WM_TIMER event. This prevents the Windows GUI from freezing during heavy computation.

GDI Drawing: Uses CPaintDC and FillSolidRect for high-performance 2D graphics.

Modern C++: Leverages <algorithm> for data shuffling and <numeric> for sequence generation.

⚙️ How to Run
1. Prerequisites
Visual Studio 2022 (Recommended).

MFC Support: Ensure the "C++ MFC for latest v143 build tools" component is installed via the Visual Studio Installer.

2. Installation & Build
Clone the Repository:

Bash
git clone https://github.com/Hamood-pixel/MFCAssignment.git
Open Project: Launch Visual Studio and open MFCAssignment.sln.

Configure: Set the Solution Configuration to Release and Platform to x64 for best performance.

Build: Press Ctrl + Shift + B to build the solution.

Run: Press F5 to start the application.

📝 Usage
Select Algorithm: Use the dropdown ComboBox to choose your preferred sorting method.

Start: Click the Start Sort button. The text will change to "Stop Sort" to allow pausing.

Reset: Click Reset at any time to shuffle the bars and start fresh.

Monitor: Watch the Progress Bar and Timer to track the algorithm's completion.

Developed by: Hamood Ur Rehman

Institution: National University of Sciences and Technology (NUST)

School: School of Electrical Engineering and Computer Science (SEECS)
