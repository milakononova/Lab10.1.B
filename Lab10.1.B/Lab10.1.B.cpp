#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

enum Specialty { KN, INF, ME, FI, TN };

union Grade
{
    int programming;
    int numericalMethods;
    int pedagogy;
};

struct Student
{
    string surname;
    int course{};
    Specialty specialty{};
    int physics{};
    int mathematics{};
    Grade grade{};
};

void Create(Student* s, int N)
{
    int specialty;

    for (int i = 0; i < N; i++)
    {
        cout << "\nStudent #" << i + 1 << endl;

        cout << "Surname: ";
        cin >> s[i].surname;

        cout << "Course: ";
        cin >> s[i].course;

        cout << "Specialty (0-KN, 1-INF, 2-ME, 3-FI, 4-TN): ";
        cin >> specialty;

        s[i].specialty = static_cast<Specialty>(specialty);

        cout << "Physics: ";
        cin >> s[i].physics;

        cout << "Mathematics: ";
        cin >> s[i].mathematics;

        switch (s[i].specialty)
        {
        case KN:
            cout << "Programming: ";
            cin >> s[i].grade.programming;
            break;

        case INF:
            cout << "Numerical methods: ";
            cin >> s[i].grade.numericalMethods;
            break;

        default:
            cout << "Pedagogy: ";
            cin >> s[i].grade.pedagogy;
        }
    }
}

void Print(const Student* s, int N)
{
    const char* specialties[] =
    {
        "KN", "INF", "ME", "FI", "TN"
    };

    string line =
        "+----+----------------+-------+-----------+---------+---------+---------+---------+---------+";

    cout << "\nSTUDENT LIST\n";
    cout << line << endl;

    cout << "| " << left << setw(3) << "No"
        << "| " << setw(15) << "Surname"
        << "| " << setw(6) << "Course"
        << "| " << setw(10) << "Specialty"
        << "| " << setw(8) << "Physics"
        << "| " << setw(8) << "Math"
        << "| " << setw(8) << "Program"
        << "| " << setw(8) << "Num.Met"
        << "| " << setw(8) << "Pedagogy"
        << "|" << endl;

    cout << line << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << left << setw(3) << i + 1
            << "| " << setw(15) << s[i].surname
            << "| " << setw(6) << s[i].course
            << "| " << setw(10) << specialties[s[i].specialty]
            << "| " << setw(8) << s[i].physics
            << "| " << setw(8) << s[i].mathematics;

        switch (s[i].specialty)
        {
        case KN:
            cout << "| " << setw(8) << s[i].grade.programming
                << "| " << setw(8) << "-"
                << "| " << setw(8) << "-";
            break;

        case INF:
            cout << "| " << setw(8) << "-"
                << "| " << setw(8) << s[i].grade.numericalMethods
                << "| " << setw(8) << "-";
            break;

        default:
            cout << "| " << setw(8) << "-"
                << "| " << setw(8) << "-"
                << "| " << setw(8) << s[i].grade.pedagogy;
            break;
        }

        cout << "|" << endl;
        cout << line << endl;
    }
}

void CountGood(const Student* s, int N, int count[])
{
    for (int i = 0; i < 5; i++)
        count[i] = 0;

    for (int i = 0; i < N; i++)
    {
        if (s[i].physics == 4)
            count[0]++;

        if (s[i].mathematics == 4)
            count[1]++;

        switch (s[i].specialty)
        {
        case KN:
            if (s[i].grade.programming == 4)
                count[2]++;
            break;

        case INF:
            if (s[i].grade.numericalMethods == 4)
                count[3]++;
            break;

        default:
            if (s[i].grade.pedagogy == 4)
                count[4]++;
            break;
        }
    }
}

double PercentExcellent(const Student* s, int N)
{
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (s[i].physics == 5 && s[i].mathematics == 5)
            count++;
    }

    return 100.0 * count / N;
}

#ifndef UNIT_TEST
int main()
{
    int N;

    cout << "Number of students: ";
    cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    int count[5];

    CountGood(s, N, count);

    cout << "\nTASK 1. Number of good grades:\n";

    cout << "+--------------------+-------+\n";
    cout << "| Subject            | Count |\n";
    cout << "+--------------------+-------+\n";

    cout << "| " << left << setw(19) << "Physics"
        << "| " << setw(6) << count[0] << "|\n";

    cout << "| " << setw(19) << "Mathematics"
        << "| " << setw(6) << count[1] << "|\n";

    cout << "| " << setw(19) << "Programming"
        << "| " << setw(6) << count[2] << "|\n";

    cout << "| " << setw(19) << "Numerical methods"
        << "| " << setw(6) << count[3] << "|\n";

    cout << "| " << setw(19) << "Pedagogy"
        << "| " << setw(6) << count[4] << "|\n";

    cout << "+--------------------+-------+\n";

    cout << "\nTASK 2. Percentage of excellent students:\n";

    cout << fixed << setprecision(2);
    cout << "Physics and mathematics: "
        << PercentExcellent(s, N) << "%" << endl;

    delete[] s;

    return 0;
}
#endif