import java.util.ArrayList;
import java.util.List;

public class Problem {
    public List<Student> students;
    public List<Project> projects;
    public int numberOfStudents;
    public int numberOfProjects;

    /**
     * Builds a new instance of Problem.
     * @param numberOfStudents Number of students.
     * @param numberOfProjects Number of projects
     */
    public Problem(int numberOfStudents, int numberOfProjects) {
        this.numberOfStudents = numberOfStudents;
        this.numberOfProjects = numberOfProjects;
        students = new ArrayList<Student>();
        projects = new ArrayList<Project>();
    }

    /**
     * Set the list of students.
     * @param studentsList Variable arguments list of students.
     */
    public void setStudents(Student... studentsList) {
        for (Student student : studentsList) {
            students.add(student);
        }
    }

    /**
     * Getter for the list of preferences.
     * @return A list of students.
     */
    public List<Student> getStudents() {
        return students;
    }

    /**
     * Sets the list of Projects.
     * @param projectsList A variable arguments list of projects.
     */
    public void setProjects(Project... projectsList) {
        for (Project project : projectsList) {
            projects.add(project);
        }
    }

    public List<Project> getProjects() {
        return projects;
    }

    @Override
    public String toString() {
        StringBuilder stringAcumulator = new StringBuilder();

        for (Student student : students) {
            stringAcumulator.append(student.toString() + ":");
        }

        stringAcumulator.append("::");

        for (Project project : projects) {
            stringAcumulator.append(project.toString() + ":");
        }

        return stringAcumulator.toString();
    }

    @Override
    public boolean equals(Object p) {
        if (toString().equals(p.toString())) {
            return true;
        }
        return false;
    }
}
