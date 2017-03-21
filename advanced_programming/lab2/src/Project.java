import java.util.ArrayList;
import java.util.List;

public class Project {
    public String name;
    public int capacity;
    public List<Student> preferences;

    /**
     * Builds a new instance.
     * @param name The name of the project.
     * @param capacity The capacity of the project.
     */
    public Project(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
        preferences = new ArrayList<Student>();
    }

    /**
     * Getter for `capacity`.
     * @return Capacity of this Project.
     */
    public int getCapacity() {
        return capacity;
    }

    /**
     * Sets the list of preferences
     * @param preferencesList A variable argument list of Students.
     */
    public void setPreferences(Student... preferencesList) {
        for (Student preference : preferencesList) {
            preferences.add(preference);
        }
    }

    /**
     * Getter over the list of preferences
     * @return A list of students.
     */
    public List<Student> getPreferences() {
        return preferences;
    }

    /**
     * Gets the String representation of the current instance.
     * @return The string representation of the current instance.
     */
    @Override
    public String toString() {
        return "P(" + name + " " + String.valueOf(capacity) + ")";
    }

    /**
     * Ovveride over super.equals.
     * @param s The instance to compare against.
     * @return True if equal, false otherwise.
     */
    @Override
    public boolean equals(Object s) {
        if (toString().equals(s.toString())) {
            return true;
        }
        return false;
    }
}
