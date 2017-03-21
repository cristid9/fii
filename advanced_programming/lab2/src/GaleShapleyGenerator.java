import java.util.*;

public class GaleShapleyGenerator {
    private Problem problem;
    private List<Project> projects;
    private List<Student> students;
    private Map<Student, Boolean> matchedStudents;
    private Map<Student, Integer> studentOptionsCount;
    private Map<Project, List<Student>> matchings;

    /**
     * Builds a new instance and sets the members appropriately.
     * @param p The problem based upon we should generate the matching.
     */
    public GaleShapleyGenerator(Problem p) {
        this.problem = p;

        students = p.getStudents();
        projects = p.getProjects();

        matchedStudents = new HashMap<>();
        studentOptionsCount = new HashMap<>();
        matchings = new HashMap<>();

        for (Student s : students) {
            matchedStudents.put(s, false);
            studentOptionsCount.put(s, s.getPreferences().size());
        }
        generateMatching();
    }

    /**
     * Prints the generated matching.
     */
    public void printMatching() {
        for (Map.Entry<Project, List<Student>> matching : matchings.entrySet()) {
            System.out.println(matching + ": ");
        }
    }

    /**
     * Generates the matching.
     */
    private void generateMatching() {
        Student s = findUnmatchedStudent();
        Project p = s.getPreferences().get(0);


        while (!areAllMatched()) {

            if (matchings.containsKey(p)) {
                matchings.get(p).add(s);
            } else {
                List<Student> sts = new ArrayList<>();
                sts.add(s);
                matchings.put(p, sts);
            }

            matchedStudents.put(s, true);


            if (matchings.get(p).size() > p.getCapacity()) {
                Student worst = getWorstStudent(p);
                matchings.get(p).remove(worst);
                matchedStudents.put(worst, false);
            }

            if (matchings.get(p).size() == p.getCapacity()) {
                Student worst = getWorstStudent(p);
                boolean reached = false;
                for (Student std : p.getPreferences()) {
                    if (std.equals(s)) {
                        reached = true;
                        continue;
                    }
                    if (reached) {
                        matchings.get(p).remove(std);
                        matchedStudents.put(std, false);

                    }
                }
            }

            s = findUnmatchedStudent();
            if (s != null) {
                p = s.getPreferences().get(0);
            }
        }
    }

    /**
     * Checks if there are unmatched students.
     * @return `true` if so, `false` otherwise.
     */
    private boolean areAllMatched() {
        boolean matchedStd = true;
        for (Map.Entry<Student, Boolean> entry : matchedStudents.entrySet()) {
            if (!entry.getValue()) {
                matchedStd = false;
                break;
            }
        }

        return matchedStd;
    }

    /**
     * Finds the first students who doesn't have assigned a project.
     * @return The first Student wihout a project.
     */
    private Student findUnmatchedStudent() {
        for (Map.Entry<Student, Boolean> entry : matchedStudents.entrySet()) {
            if (!entry.getValue()) {
                return entry.getKey();
            }
        }

        return null;
    }

    /**
     * Gets the worst ranked student fro the preferences list of a project.
     * @param p The targeted project.
     * @return The resulting student.
     */
    private Student getWorstStudent(Project p) {
        List<Student> reversedPreferences = p.getPreferences();
        Collections.reverse(reversedPreferences);
        for (Student s : reversedPreferences) {
            if (matchings.get(p).contains(s)) {
                return s;
            }
        }

        return null;
    }

}
