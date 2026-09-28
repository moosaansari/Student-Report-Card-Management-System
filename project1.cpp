#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <conio.h>


using namespace std;

class student
{
    int rollno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;

    void calculate();

public:
    void showdata();
    void getdata();
    int retrollno();
};

void student::calculate()
{
    per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;

    if (per >= 80)
        grade = 'A';
    else if (per >= 70)
        grade = 'B';
    else if (per >= 60)
        grade = 'C';
    else if (per >= 50)
        grade = 'D';
    else if (per >= 40)
        grade = 'E';
    else if (per >= 33)
        grade = 'F';
    else
        grade = 'X';  
}

void student::getdata()
{
    system("CLS");

    cout << "\nEnter The Roll Number of Student: ";
    cin >> rollno;

    cout << "\nEnter The Name of Student: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "\nEnter The Marks in Physics out of 100: ";
    cin >> p_marks;

    cout << "\nEnter The Marks in Chemistry out of 100: ";
    cin >> c_marks;

    cout << "\nEnter The Marks in Maths out of 100: ";
    cin >> m_marks;

    cout << "\nEnter The Marks in English out of 100: ";
    cin >> e_marks;

    cout << "\nEnter The Marks in Computer Science out of 100: ";
    cin >> cs_marks;

    calculate();
}

void student::showdata()
{
    system("CLS");

    cout << "\t---------------------------";
    cout << "\n\t      STUDENT DETAIL\n";
    cout << "\t---------------------------";

    cout << "\n\n\tRoll Number             : " << rollno;
    cout << "\n\n\tName                    : " << name;
    cout << "\n\n\tMarks in Physics        : " << p_marks;
    cout << "\n\n\tMarks in Chemistry      : " << c_marks;
    cout << "\n\n\tMarks in Maths          : " << m_marks;
    cout << "\n\n\tMarks in English        : " << e_marks;
    cout << "\n\n\tMarks in Computer Science: " << cs_marks;
    cout << "\n\n\tPercentage              : " << per << "%";

    if (grade == 'X')
        cout << "\n\n\tGrade                   : FAIL...!!!";
    else
        cout << "\n\n\tGrade                   : " << grade;
}

int student::retrollno()
{
    return rollno;
}

// CREATE RECORD
void write_student()
{
    student st;
    ofstream outFile("student.dat", ios::binary | ios::app);

    if (!outFile)
    {
        cout << "\nFile could not be opened!";
        getch();
        return;
    }

    st.getdata();

    outFile.write(reinterpret_cast<char*>(&st), sizeof(student));
    outFile.close();

    cout << "\n\nStudent Record Has Been Created Successfully.";
    getch();
}

// SEARCH / DISPLAY RECORD
void display_sp(int n)
{
    system("CLS");

    student st;
    ifstream inFile("student.dat", ios::binary);

    if (!inFile)
    {
        cout << "\nFile could not be opened!";
        getch();
        return;
    }

    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(student)))
    {
        if (st.retrollno() == n)
        {
            st.showdata();
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found)
        cout << "\n\n\tRECORD DOES NOT EXIST...!!!";

    getch();
}

// MODIFY RECORD
void modify_student(int n)
{
    system("CLS");

    student st;
    bool found = false;

    fstream File("student.dat",
                 ios::binary | ios::in | ios::out);

    if (!File)
    {
        cout << "\n\n\tFile could not be opened!";
        getch();
        return;
    }

    while (File.read(reinterpret_cast<char*>(&st), sizeof(student)))
    {
        if (st.retrollno() == n)
        {
            st.showdata();

            cout << "\n\n\tPlease Enter The New Details Of Student\n";
            getch();

            st.getdata();

            File.seekp(-static_cast<streamoff>(sizeof(student)), ios::cur);

            File.write(reinterpret_cast<char*>(&st), sizeof(student));

            cout << "\n\n\tRecord Updated Successfully.";

            found = true;
            break;
        }
    }

    File.close();

    if (!found)
        cout << "\n\n\tRecord Not Found.";

    getch();
}

// DELETE RECORD
void delete_student(int n)
{
    system("CLS");

    student st;
    bool found = false;

    ifstream inFile("student.dat", ios::binary);

    if (!inFile)
    {
        cout << "\n\n\tFile could not be opened!";
        getch();
        return;
    }

    ofstream outFile("Temp.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&st), sizeof(student)))
    {
        if (st.retrollno() != n)
        {
            outFile.write(reinterpret_cast<char*>(&st), sizeof(student));
        }
        else
        {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("student.dat");
    rename("Temp.dat", "student.dat");

    if (found)
        cout << "\n\n\tRecord Deleted Successfully.";
    else
        cout << "\n\n\tRecord Not Found.";

    getch();
}

// RESULT MENU
void result()
{
    char ch;
    int rollno;

    system("CLS");

    cout << "\n\n\n\tRESULT MENU";
    cout << "\n\n\t1. Student Report Card";
    cout << "\n\n\t2. Back to Main Menu";
    cout << "\n\n\tEnter Choice (1/2): ";

    cin >> ch;

    switch (ch)
    {
        case '1':
            cout << "\n\n\tEnter Roll Number Of Student: ";
            cin >> rollno;
            display_sp(rollno);
            break;

        case '2':
            break;

        default:
            cout << "\n\n\tInvalid Choice!";
            getch();
    }
}

// CRUD MENUG
void entry_menu()
{
    char ch;
    int num;

    system("CLS");

    cout << "\n\n\n\tENTRY MENU";
    cout << "\n\n\t1. CREATE STUDENT RECORD";
    cout << "\n\n\t2. SEARCH STUDENT RECORD";
    cout << "\n\n\t3. MODIFY STUDENT RECORD";
    cout << "\n\n\t4. DELETE STUDENT RECORD";
    cout << "\n\n\t5. BACK TO MAIN MENU";

    cout << "\n\n\tPlease Enter Your Choice (1-5): ";
    cin >> ch;

    switch (ch)
    {
        case '1':
            write_student();
            break;

        case '2':
            cout << "\n\n\tPlease Enter Roll Number: ";
            cin >> num;
            display_sp(num);
            break;

        case '3':
            cout << "\n\n\tPlease Enter Roll Number: ";
            cin >> num;
            modify_student(num);
            break;

        case '4':
            cout << "\n\n\tPlease Enter Roll Number: ";
            cin >> num;
            delete_student(num);
            break;

        case '5':
            break;

        default:
            cout << "\n\n\tInvalid Choice!";
            getch();
    }
}

// PASSWORD FUNCTION
bool password()
{
    system("CLS");

    string pass;
    char ch;

    cout << "\n\n\n";
    cout << "\t--------------------------------------------\n";
    cout << "\tSTUDENT REPORT CARD MANAGEMENT SYSTEM LOGIN\n";
    cout << "\t--------------------------------------------\n";

    cout << "\n\tEnter Password: ";

    ch = _getch();

    while (ch != 13)
    {
        // Backspace
        if (ch == 8)
        {
            if (!pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pass.push_back(ch);
            cout << '*';
        }

        ch = _getch();
    }

    if (pass == "12345")
    {
        cout << "\n\n\tAccess Granted!";
        getch();
        return true;
    }

    cout << "\n\n\tAccess Denied! Wrong Password.";
    getch();

    return false;
}

// MAIN FUNCTION
int main()
{
    while (!password())
    {
        // Keep asking until correct password
    }

    char ch;

    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);

    do
    {
        system("CLS");

        cout << "\t--------------------------------------------";
        cout << "\n\t STUDENT REPORT CARD MANAGEMENT SYSTEM\n";
        cout << "\t--------------------------------------------";

        cout << "\n\n\t\t** MAIN MENU **";

        cout << "\n\n\t1. RESULT MENU";
        cout << "\n\n\t2. CRUD MENU";
        cout << "\n\n\t3. EXIT";

        cout << "\n\n\tPlease Select Your Option: ";
        cin >> ch;

        switch (ch)
        {
            case '1':
                result();
                break;

            case '2':
                entry_menu();
                break;

            case '3':
                system("CLS");
                cout << "\n\n\t--------------------------------------------";
                cout << "\n\t STUDENT REPORT CARD MANAGEMENT SYSTEM";
                cout << "\n\t--------------------------------------------";
                cout << "\n\n\tThank You!\n\n";
                break;

            default:
                cout << "\n\n\tError! Wrong Choice Entered!";
                getch();
        }

    } while (ch != '3');

    return 0;
}