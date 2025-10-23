#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    string name;
    vector<int> marks;
    double average;
    int highest;
    int lowest;
};

void inputStudentData(vector<Student>& students);
void computeResults(vector<Student>& students);
void saveToFile(const vector<Student>& students);
void saveToCSV(const vector<Student>& students);

int main() {
    vector<Student> students;
    inputStudentData(students);
    computeResults(students);
    saveToFile(students);
    saveToCSV(students);
    cout << "\nAll results saved to data/student_results.txt ✅\n";
    return 0;
}

void inputStudentData(vector<Student>& students) {
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    students.resize(n);

    for (int i = 0; i < n; ++i) {
        cout << "\nEnter name of student " << i + 1 << ": ";
        cin >> students[i].name;
        cout << "Enter 5 marks: ";
        students[i].marks.resize(5);
        for (int j = 0; j < 5; ++j) cin >> students[i].marks[j];
    }
}

void computeResults(vector<Student>& students) {
    for (auto& s : students) {
        int sum = 0;
        s.highest = s.marks[0];
        s.lowest = s.marks[0];
        for (int m : s.marks) {
            sum += m;
            if (m > s.highest) s.highest = m;
            if (m < s.lowest) s.lowest = m;
        }
        s.average = static_cast<double>(sum) / s.marks.size();
    }
}

void saveToFile(const vector<Student>& students) {
    ofstream file("../data/student_results.txt");
    for (const auto& s : students) {
        file << s.name << ": Highest =" << s.highest
             << " Lowest =" << s.lowest
             << " Average =" << fixed << setprecision(2)
             << s.average << "\n";
    }
    file.close();
}

void saveToCSV(const vector<Student>& students) {
    ofstream csv("../data/student_results.csv");
    csv << "Name,Highest,Lowest,Average\n";
    for (const auto& s : students) {
        csv << s.name << ","
            << s.highest << ","
            << s.lowest << ","
            << fixed << setprecision(2) << s.average << "\n";
    }
    csv.close();
    cout << "Results also saved to data/student_results.csv ✅\n";
}
