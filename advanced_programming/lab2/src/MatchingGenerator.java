import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MatchingGenerator {
    public Problem problem;
    public Map<Project, List<Student>> matchings;

    /**
     * Builds a new instance of MatchingGenerator.
     * @param p Based on this problem a matching will be generated.
     */
    public MatchingGenerator(Problem p) {
        this.problem = p;
        matchings = new HashMap<>();
        generateMatching();
    }

    /**
     * Prints the generated matching.
     */
    public void printMatching() {
        for (Map.Entry<Project, List<Student>> matching : matchings.entrySet()) {
            System.out.println(matching.getKey() + ": ");
            for (Student s : matching.getValue()) {
                System.out.println("\t" + s);
            }
        }
    }

    /**
     * Helper method, checks if one student is already enrolled in a project.
     * @param candidate The desired student.
     * @return `true` if this student is not enrolled in a project,
     *         `false` otherwise.
     */
    private boolean isAddableStudent(Student candidate) {
        for (Map.Entry<Project, List<Student>> matching : matchings.entrySet()) {
            for (Student s : matching.getValue()) {
                if (s.equals(candidate)) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Generates the matching and stores the result in `matchings`.
     */
    private void generateMatching() {
        for (Student s : problem.getStudents()) {
            for (Project p : s.getPreferences()) {
                if (p.getPreferences().contains(s) && isAddableStudent(s)) {
                    if (matchings.containsKey(p)) {
                        if (matchings.get(p).size() !=  p.getCapacity()) {
                            matchings.get(p).add(s);
                        }
                    } else {
                        List<Student> students = new ArrayList<Student>();
                        students.add(s);
                        matchings.put(p, students);
                    }
                }
            }
        }
    }


}
