
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
using namespace std;

// Read one validated score [0,100]
int getScore(int index) {
 int s;
 while (true) {
     cout << "Enter score #" << index << " (0-100): ";
     if (cin >> s && s >= 0 && s <= 100) return s;
     cout << "Invalid. Please enter an integer between 0 and 100.\n";
     cin.clear();
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
 }
}

int findLowest(int a, int b, int c, int d, int e) {
 int lowest = a;
 if (b < lowest) lowest = b;
 if (c < lowest) lowest = c;
 if (d < lowest) lowest = d;
 if (e < lowest) lowest = e;
 return lowest;
}

double calcAverage(int a, int b, int c, int d, int e) {
 int lowest = findLowest(a, b, c, d, e);
 int sum = a + b + c + d + e - lowest;
 return static_cast<double>(sum) / 4.0;
}

void displayOutput(double avg, const vector<int>& scores, int lowest) {
 cout << "\nScores: ";
 for (int s : scores) cout << s << " ";
 cout << "\nLowest dropped: " << lowest << '\n';
 cout << fixed << setprecision(2);
 cout << "Average of top 4: " << avg << "\n";
}

int main() {
 vector<int> scores(5);
 for (int i = 0; i < 5; ++i) scores[i] = getScore(i + 1);

 int a = scores[0], b = scores[1], c = scores[2], d = scores[3], e = scores[4];
 int lowest = findLowest(a, b, c, d, e);
 double avg = calcAverage(a, b, c, d, e);

 displayOutput(avg, scores, lowest);
 return 0;
}
//checking write access