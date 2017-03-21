import java.util.ArrayList;
import java.util.List;

public class Student {
    private String name;
    private String email;
    private List<Project> preferences;

    /**
     * Builds a new instance of `Student`.
     * @param name Name of this student.
     * @param email Mail of this student.
     */
    public Student(String name, String email) {
        this.name = name;
        this.email = email;
        preferences = new ArrayList<Project>();
    }

    /**
     * Setter method.
     * @param preferencesArguments A variable argument lists of students.
     */
    public void setPreferences(Project... preferencesArguments) {
        for (Project currentPreference : preferencesArguments) {
            preferences.add(currentPreference);
        }
    }

    /**
     * Getter for preferences.
     * @return A list of projects.
     */
    public List<Project> getPreferences() {
        return preferences;
    }

    /**
     * Gets the string representation of this object.
     * @return The string representation of this object.
     */
    @Override
    public String toString() {
        return "S(" + name +  " " + email + ")";
    }

    /**
     * Overload over the super.equals.
     * @param s An insstance to compare against.
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
