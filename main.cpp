#include "iostream"
#include "iomanip"
#include "fstream"

using namespace std;
class student{
    int rollNo;
    char name[50];
    int Month_day, authorizeDay, unAuthorizeDay ;
    double average;
    char exam_pass;

public:
    void getData();
    void showData() const;
    void calculate();
    int retrollno() const;
};

void student::calculate()
{
    average = Month_day*3.8;
    if(average>=80){
        exam_pass='Y';
    } else if (average <79){
        exam_pass='N';
    } else{
        exam_pass='N';
    }

}

void student::getData()
{
    cout << "\nEnter student's roll number"; cin >> rollNo;
    cout << "\n\nEnter Student Name";
    cin.ignore();
    cin.getline(name,50);
    cout << "\n\nEnter attended Day:"; cin >> Month_day;
    cout << "\n\nEnter Authorized Day:"; cin >> authorizeDay;
    cout << "\n\nEnter UnAuthorized Day"; cin >> unAuthorizeDay;
    calculate();
}

void student::showData() const
{
    cout << "\nRoll number of student :" << rollNo;
    cout << "\nStudent Name       :" <<name;
    cout << "\n\nAttended Day     :" << Month_day;
    cout << "\n\nAuthorized Day   :" << authorizeDay;
    cout << "\n\nUnAuthorized Day :" << unAuthorizeDay;
    cout << "\nPercentage       :" <<average;
    cout << "\nExam Accept      :" << exam_pass;

}
int student::retrollno() const {
    return rollNo;
}

//new create function
void create_student();
void display_sp(int);
void display_all(int);
void delete_student(int);
void change_student(int);

int main()
{
    char ch;
    cout<<setprecision(2);
    do {
        char ch;
        int num;
        cout << "\n\n\n\tMENU";
        cout << "\n\n\n\t1.Create student record";
        cout << "\n\n\n\t2.Search student record";
        cout << "\n\n\n\t3.Display all student";
        cout << "\n\n\n\t4.Delete student record";
        cout << "\n\n\n\t5.Update student record";
        cout << "\n\n\n\t6.Exit";
        cout << "\n\nWhat is your choice(1/2/3/4/5/6)";
        cin >>ch;
        ::system("cls");

        switch (ch)
        {
            case '1': create_student();
                break;
            case '2': cout << "\nRoll number of student :"; cin >> num;

                 display_sp(num);
                break;
            case '3': display_all(num);
                break;
            case '4': cout << "\nRoll number of student :"; cin >> num;
                delete_student(num);
                break;
            case '5': cout << "\nRoll number of student :"; cin >> num;
                //change_student(num);
                break;
            case '6': cout << "Exiting, Thank you!";
                ::exit(0);
        }

    } while ( ch!=6);
    return 0;
}

void create_student(){
    student stud;
    ofstream oFile;
    oFile.open("student.txt",ios::binary|ios::app);
    stud.getData();
    oFile.write(reinterpret_cast < char *>(&stud), sizeof (student));
    oFile.close();
    cout << "\n\nStudent record has been Created";
    cin.ignore();
    cin.get();
}

void display_all(int){
    student stud;
    ifstream iFile;
    iFile.open("student.txt",ios::binary);
    if(!iFile){
        cout << "File Could not be Open !! Press Any Key to Exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDisplaying All Records\n\n";
    while (iFile.read(reinterpret_cast < char  *>(&stud),sizeof (student))){
        stud.showData();
        cout << "\n\n=============================================\n";
    }
    iFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n){
    student stud;
    ifstream inFile;
    inFile.open("student.txt",ios::binary);
    if(!inFile){
        cout << "File Could not be Open !! Press Any Key to Exit";
        cin.ignore();
        cin.get();
        return;
    }
   bool flag = false;
    while (inFile.read(reinterpret_cast<char *>(&stud),sizeof (student))){
        if(stud.retrollno()==n){
            stud.showData();
            flag= true;
        }
    }
    inFile.close();
    if(flag == false)
        cout << "\n\nRecord dose not exit";
    cin.ignore();
    cin.get();
}
void delete_student(int n){
    student stud;
    ifstream iFile;
    iFile.open("student.txt",ios::binary);
    if(!iFile){
        cout << "File Could not be Open !! Press Any Key to Exit";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("temp.txt",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast < char *>(&stud),sizeof (student))){
        if (stud.retrollno()!=n){
            oFile.write(reinterpret_cast < char *>(&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();

    remove("student.txt");
    ::rename("temp.txt","student.txt");
    cout << "\n\n\tRecord Deleted";
    cin.ignore();
    cin.get();
}
