#include <iostream>
#include <string>
using namespace std;

class Grade {
private:
    string subject;
    double grade;

public:
    // Constructors
    Grade() : subject(""), grade(-1.0) {}
    Grade(const string& subject, double grade) : subject(subject), grade(grade) {}

    // Accessor methods
    string getSubject() const {
        return subject;
    }

    double getGrade() const {
        return grade;
    }
};

class Student {
private:
    string firstName;
    string lastName;
    int age;
    string studentID;
    Grade* grades;
    int numGrades;
    double mathGrade;
    double russianGrade;
    double physicsGrade;

public:
    // Constructors
    Student() : firstName(""), lastName(""), age(0), studentID(""), grades(nullptr), numGrades(0),
        mathGrade(-1.0), russianGrade(-1.0), physicsGrade(-1.0) {}

    Student(const string& firstName, const string& lastName, int age, const string& studentID)
        : firstName(firstName), lastName(lastName), age(age), studentID(studentID), grades(nullptr), numGrades(0),
        mathGrade(-1.0), russianGrade(-1.0), physicsGrade(-1.0) {}

    Student(const string& firstName, const string& lastName, int age, const string& studentID,
        const Grade* studentGrades, int numStudentGrades)
        : firstName(firstName), lastName(lastName), age(age), studentID(studentID), numGrades(numStudentGrades),
        mathGrade(-1.0), russianGrade(-1.0), physicsGrade(-1.0) {
        grades = new Grade[numGrades];
        for (int i = 0; i < numGrades; i++) {
            grades[i] = studentGrades[i];
        }
        updateGrades();
    }

    // Destructor
    ~Student() {
        delete[] grades;
    }

    // Methods to add a grade
    void addGrade(const Grade& grade) {
        if (numGrades == 0) {
            grades = new Grade[1];
            grades[0] = grade;
            numGrades = 1;
        }
        else {
            Grade* temp = new Grade[numGrades + 1];
            for (int i = 0; i < numGrades; i++) {
                temp[i] = grades[i];
            }
            temp[numGrades] = grade;
            numGrades++;
            delete[] grades;
            grades = temp;
        }
        updateGrades();
    }

    // Calculate and update average grades
    void updateGrades() {
        mathGrade = russianGrade = physicsGrade = -1.0;
        for (int i = 0; i < numGrades; i++) {
            if (grades[i].getSubject() == "Математика") {
                mathGrade = grades[i].getGrade();
            }
            else if (grades[i].getSubject() == "Русский") {
                russianGrade = grades[i].getGrade();
            }
            else if (grades[i].getSubject() == "Физика") {
                physicsGrade = grades[i].getGrade();
            }
        }
    }

    // Accessor methods
    double getAverageGrade() const {
        int numSubjects = 0;
        double sum = 0.0;

        if (mathGrade >= 0.0) {
            sum += mathGrade;
            numSubjects++;
        }
        if (russianGrade >= 0.0) {
            sum += russianGrade;
            numSubjects++;
        }
        if (physicsGrade >= 0.0) {
            sum += physicsGrade;
            numSubjects++;
        }

        if (numSubjects == 0) {
            return -1.0; // Нет оценок
        }

        return sum / numSubjects;
    }

    void printStudentInfo() const {
        cout << "Имя: " << firstName << endl;
        cout << "Фамилия: " << lastName << endl;
        cout << "Возраст: " << age << endl;
        cout << "Номер студенческого билета: " << studentID << endl;
        cout << "Оценки:" << endl;
        if (mathGrade >= 0.0) {
            cout << "Математика: " << mathGrade << endl;
        }
        if (russianGrade >= 0.0) {
            cout << "Русский: " << russianGrade << endl;
        }
        if (physicsGrade >= 0.0) {
            cout << "Физика: " << physicsGrade << endl;
        }
        double average = getAverageGrade();
        if (average >= 0.0) {
            cout << "Средний балл: " << average << endl;
        }
        else {
            cout << "Средний балл: Нет данных" << endl;
        }
    }
};

int main() {
    int numStudents;
    cout << "Введите количество студентов: ";
    cin >> numStudents;

    // Динамический массив объектов класса Student
    Student* studentsArray = new Student[numStudents];

    // Создание студентов и добавление оценок
    for (int i = 0; i < numStudents; i++) {
        string firstName, lastName, studentID;
        int age;
        cout << "Введите имя студента " << i + 1 << ": ";
        cin >> firstName;
        cout << "Введите фамилию студента " << i + 1 << ": ";
        cin >> lastName;
        cout << "Введите возраст студента " << i + 1 << ": ";
        cin >> age;
        cout << "Введите номер студенческого билета студента " << i + 1 << ": ";
        cin >> studentID;

        int numGrades;
        cout << "Сколько оценок у студента " << i + 1 << "? ";
        cin >> numGrades;

        Grade* studentGrades = new Grade[numGrades];
        for (int j = 0; j < numGrades; j++) {
            string subject;
            double grade;
            cout << "Введите предмет и оценку для студента " << i + 1 << " (например, 'Математика 4.5'): ";
            cin >> subject >> grade;
            studentGrades[j] = Grade(subject, grade);
        }

        studentsArray[i] = Student(firstName, lastName, age, studentID, studentGrades, numGrades);

        // Освободить память, выделенную для массива оценок
        delete[] studentGrades;
    }

    // Вывод информации о студентах
    for (int i = 0; i < numStudents; i++) {
        cout << "Информация о студенте " << i + 1 << ":" << endl;
        studentsArray[i].printStudentInfo();
        cout << endl;
    }

    // Освобождение динамической памяти
    delete[] studentsArray;

    return 0;
}
