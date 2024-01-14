#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Person {
private:
    string firstName;
    string lastName;
    long long id;
    int birthYear;

public:
    Person() : id(0), birthYear(0) {}

    Person(string firstName, string lastName, long long id, int birthYear)
        : firstName(firstName), lastName(lastName), id(id), birthYear(birthYear) {}

    virtual ~Person() {
        cout << "Person object has been destroyed." << endl;
    }

    string getFirstName() const {
        return firstName;
    }

    void setFirstName(const string& newFirstName) {
        firstName = newFirstName;
    }

    string getLastName() const {
        return lastName;
    }

    void setLastName(const string& newLastName) {
        lastName = newLastName;
    }

    long long getId() const {
        return id;
    }

    void setId(long long newId) {
        id = newId;
    }

    int getBirthYear() const {
        return birthYear;
    }

    void setBirthYear(int newBirthYear) {
        birthYear = newBirthYear;
    }

    virtual void display() const {
        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "ID: " << id << endl;
        cout << "Birth Year: " << birthYear << endl;
    }
};

class Student : public Person {
private:
    int studentId;
    int grade;
    vector<string> courses;

public:
    Student() : studentId(0), grade(0) {}

    Student(string firstName, string lastName, long long id, int birthYear, int studentId, int grade)
        : Person(firstName, lastName, id, birthYear), studentId(studentId), grade(grade) {}

    ~Student() {
        cout << "Student object has been destroyed." << endl;
    }

    int getStudentId() const {
        return studentId;
    }

    void setStudentId(int newStudentId) {
        studentId = newStudentId;
    }

    int getGrade() const {
        return grade;
    }

    void setGrade(int newGrade) {
        grade = newGrade;
    }

    void addCourse(const string& course) {
        courses.push_back(course);
    }

    void display() const override {
        Person::display();
        cout << "Student ID: " << studentId << endl;
        cout << "Grade: " << grade << endl;
        cout << "Courses: ";
        for (const auto& course : courses) {
            cout << course << " ";
        }
        cout << endl;
    }
};

class Teacher : public Person {
private:
    string courseName;
    int hoursPerWeek;
    double hourlyRate;

public:
    Teacher() : hoursPerWeek(0), hourlyRate(0.0) {}

    Teacher(string firstName, string lastName, long long id, int birthYear, string courseName, int hoursPerWeek, double hourlyRate)
        : Person(firstName, lastName, id, birthYear), courseName(courseName), hoursPerWeek(hoursPerWeek), hourlyRate(hourlyRate) {}

    ~Teacher() {
        cout << "Teacher object has been destroyed." << endl;
    }

    string getCourseName() const {
        return courseName;
    }

    void setCourseName(const string& newCourseName) {
        courseName = newCourseName;
    }

    int getHoursPerWeek() const {
        return hoursPerWeek;
    }

    void setHoursPerWeek(int newHoursPerWeek) {
        hoursPerWeek = newHoursPerWeek;
    }

    double getHourlyRate() const {
        return hourlyRate;
    }

    void setHourlyRate(double newHourlyRate) {
        hourlyRate = newHourlyRate;
    }

    void display() const override {
        Person::display();
        cout << "Course Name: " << courseName << endl;
        cout << "Hours Per Week: " << hoursPerWeek << endl;
        cout << "Hourly Rate: " << hourlyRate << endl;
    }
};

void writeFile(const Person& person) {
    ofstream file("teachers.txt", ios::app);
    if (file.is_open()) {
        file << "First Name: " << person.getFirstName() << endl;
        file << "Last Name: " << person.getLastName() << endl;
        file << "ID: " << person.getId() << endl;
        file << "Birth Year: " << person.getBirthYear() << endl;
        file << endl;
        file.close();
    } else {
        cout << "Error: Unable to open the file." << endl;
    }
}

double calculateSalary(const Teacher& teacher) {
    const int weeksInMonth = 4;
    return teacher.getHoursPerWeek() * weeksInMonth * teacher.getHourlyRate();
}

Student createStudent() {
    string firstName, lastName;
    long long id;
    int birthYear, studentId, grade;

    cout << "Enter Student Information" << endl;
    cout << "First Name: ";
    getline(cin, firstName);
    cout << "Last Name: ";
    getline(cin, lastName);
    cout << "ID: ";
    cin >> id;
    cout << "Birth Year: ";
    cin >> birthYear;
    cout << "Student ID: ";
    cin >> studentId;
    cout << "Grade: ";
    cin >> grade;

    Student student(firstName, lastName, id, birthYear, studentId, grade);

    cin.ignore();

    string course;
    cout << "Courses (Enter 'q' to finish): ";
    while (true) {
        cin >> course;
        if (course == "q") {
            break;
        }
        student.addCourse(course);
    }

    return student;
}

Teacher createTeacher() {
    string firstName, lastName;
    long long id;
    int birthYear;
    string courseName;
    int hoursPerWeek;
    double hourlyRate;

    cout << "Enter Teacher Information" << endl;
    cout << "First Name: ";
    getline(cin, firstName);
    cout << "Last Name: ";
    getline(cin, lastName);
    cout << "ID: ";
    cin >> id;
    cout << "Birth Year: ";
    cin >> birthYear;
    cout << "Course Name: ";
    cin.ignore(); 
    getline(cin, courseName);
    cout << "Hours Per Week: ";
    cin >> hoursPerWeek;
    cout << "Hourly Rate: ";
    cin >> hourlyRate;

    Teacher teacher(firstName, lastName, id, birthYear, courseName, hoursPerWeek, hourlyRate);

    return teacher;
}

int main() {
    Student student = createStudent();
    Teacher teacher = createTeacher();
    double salary = calculateSalary(teacher);

    student.display();
    teacher.display();

    cout << "Teacher's Salary: $" << salary << endl;

    writeFile(teacher);

    return 0;
}
