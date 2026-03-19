#ifndef "HALLS_H"
#define "HALLS_H"

// Hall class definition
class Hall {
private:
    std::string name;
    int capacity;
    std::vector<Student> students;

public:
    Hall(const std::string& hallName, int hallCapacity);
    void addStudent(const Student& student);
    void removeStudent(const Student& student);
    const std::string& getName() const;
    int getCapacity() const;
    const std::vector<Student>& getStudents() const;
};

#endif // "HALLS_H"