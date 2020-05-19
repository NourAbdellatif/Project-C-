
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class subject {
private:
    string subjectName;
    float subjectMark;
public:
    string getName() {
        return subjectName;
    }
    float getMark() {
        return subjectMark;
    }
    void setName(string name) {
        subjectName = name;
    }
    void setMark(float mark) {
        subjectMark=mark;
    }
};
class Student {
private:
    int studentNumber, numSubjects,countSubjects;
    string studentName;
    subject* subjects;
    char grade;
    struct address
    {
        string city, area, zipcode;
    };
    struct address studentAddress;
    
public:
    Student(string name, int number, int s,string city,string area,string zipcode) {
        studentName = name;
        studentNumber = number;
        studentAddress.area = area;
        studentAddress.city = city;
        studentAddress.zipcode = zipcode;
        subjects = new subject[s];
        grade=calculateScore();
        countSubjects = 0;
        numSubjects = s;
    }
    void printSubjects() {
        for (int i = 0; i < countSubjects; i++) {
            cout << subjects[i].getName()<< " " << subjects[i].getMark() << " " ;
        }
    }
    void setNumber(int n) {
        studentNumber = n;
    }
    char getGrade() {
        return grade;
    }
    void setName(string name) {
        studentName = name;
    }
    void setGrade(char grade) {
        this->grade=grade;
    }
    void setAddress(string c, string a, string z) {
        studentAddress.area = a;
        studentAddress.city = c;
        studentAddress.zipcode = z;
    }
    void printAddress() {
        cout << studentAddress.area << " " << studentAddress.city << " " << studentAddress.zipcode << " ";
    }
    char calculateScore() {
        float sum = 0;
        for (int i = 0; i < numSubjects; i++) {
            sum = sum + subjects[i].getMark();
        }
        float average = sum / (numSubjects);
        if (average < 50) {
            grade = 'F';
        }
        else if (average < 65) {
            grade = 'D';
        }
        else if (average < 75) {
            grade = 'C';
        }
        else if (average < 85) {
            grade = 'B';
        }
        else {
            grade = 'A';
        }
        return grade;
    }
    int getNumber() {
        return studentNumber;
    }
    string getName() {
        return studentName;
    }
    void addSubject(subject sub) {
        subjects[countSubjects++] = sub;
    }
    
};
class System {
private:
    Student** students;
    int numStudents;
public:
    System() {
        numStudents = 0;
        students = new Student*[200];
    }
    int getnumStudents() {
        return numStudents;
    }
    void setnumStudents(int n) {
        numStudents = n;
    }
    void setGrade(int sn,char g) {
        Student* stu=search(sn);
        stu->setGrade(g);
    }
    Student* search(int sn) {
        for (int i = 0; i < numStudents; i++) {
            if (sn == students[i]->getNumber()) {
                cout << "Record Found" << endl;
                cout << students[i]->getName() << " " << students[i]->getNumber() << "  ";
                students[i]->printAddress();
                students[i]->printSubjects();
                cout << endl;
                return students[i];
            }
        }
        cout << "Record Not Found" << endl;
        return NULL;
    }
    Student* search(string sn) {
        for (int i = 0; i < numStudents; i++) {
            if (sn == students[i]->getName()) {
                cout << "Record Found" << endl;
                cout << students[i]->getName() << " " << students[i]->getNumber() << "  ";
                students[i]->printAddress();
                students[i]->printSubjects();
                cout << endl;
                return students[i];
            }
        }
        cout << "Record Not Found" << endl;
        return NULL;
    }
    void modify(int sn) {
        Student* test=search(sn);
        if (test) {
            cout << "What do u want to update?" << endl;
            cout << "1- Name" << endl << "2-Number" << endl << "3-address" << endl << "4-Grade" << endl<<"5-Subject"<<endl;
            int n;
            cin >> n;
            string name1,name2,fullName;
            string a, c, z;
            switch (n)
            {
            case 1:
                cout << "Input new name(first name, last name):" << endl;
                cin >> name1 >> name2;
                fullName = name1 +" "+ name2;
                test->setName(fullName);
                cout << "Record Updated" << endl;
                break;
            case 2:
                cout << "Input new number:" << endl;
                int number;
                cin >> number;
                test->setNumber(number);
                cout << "Record Updated" << endl;
                break;
            case 3:
                cout << "Input new address(city, area, zipcode):" << endl;
                cin >> c >> a >> z;
                test->setAddress(c, a, z);
                cout << "Record Updated" << endl;
                break;
            case 4:
                cout << "Input new grade: " << endl;
                char grade;
                cin >> grade;
                setGrade(test->getNumber(), grade);
                cout << "Record Updated" << endl;
                break;
            default:
                cout << "Wrong number" << endl;
                break;
            }

        }  

    }
    void deletes(int snum) {
        for (int i = 0; i < numStudents; i++) {
            if (snum==students[i]->getNumber()) {
                Student* temp = students[i];
                students[i]=students[numStudents-1];
                delete temp;
                numStudents--;
                cout << "Deleted" << endl;
                return;
            }
        }
        cout << "Not found" << endl;
    }
    void add(ifstream &student) {
        if (numStudents < 200) {
                string name1, name2, fullName, area, city, zipcode,s;
                int id, numSubjects,mark;
                student >> name1 >> name2 >> id >> city >> area >> zipcode >> numSubjects;
                subject* subjects = new subject[numSubjects];
                fullName = name1 + ' ' + name2;
                Student* ns = new Student(fullName, id, numSubjects, city, area, zipcode);
                for (int i = 0; i < numSubjects; i++) {
                    student >> s >> mark;
                    subjects[i].setName(s);
                    subjects[i].setMark(mark);
                    ns->addSubject(subjects[i]);
                }
                students[numStudents++] = ns;
        }
        else {
            cout << "No space" << endl;
        }
    }
    void display() {
        for (int i = 0; i <numStudents; i++) {
            cout << students[i]->getName() << " "<< students[i]->getNumber() << "  ";
            students[i]->printAddress();
            students[i]->printSubjects();
            students[i]->calculateScore();
            cout<<" The student's Grade is:"<<students[i]->getGrade();
            cout << endl;
        }
    }
    void displayStudent(int sn) {
        Student* stu = search(sn);
        if (stu) {
            cout << stu->getName() << " " << stu->getNumber() << "  ";
            stu->printAddress();
            stu->printSubjects();
            cout << endl;
        }
    }
};

int main()
{
    char x='y';
    System file;
    ifstream text;
    text.open("students.txt");
    while (x == 'y') {
        cout << "Welcome to CUFE Student system, How can I help you?" << endl;
        cout << "1-Add" << endl << "2-Delete" << endl << "3-Modify" << endl << "4-Search" << endl;
        int n;
        cin >> n;
        int stun;
        switch (n)
        {
        case 1:
            file.add(text);
            break;
        case 2:
            cout << "Insert number of student to be deleted" << endl;
            cin >> stun;
            file.deletes(stun);
            break;
        case 3:
            cout << "Insert number of student to be modified" << endl;
            cin >> stun;
            file.modify(stun);
            break;
        case 4:
            cout << "Insert number of student you want to search for" << endl;
            cin >> stun;
            file.search(stun);
            break;
        }
        file.display();
        cout << "Do you want to continue? (Yes: y/No: n)" << endl;
        cin >> x;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
