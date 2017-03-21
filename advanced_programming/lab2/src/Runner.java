
public class Runner {

    public static void main(String[] args) {
        Problem problem = new Problem(4, 3);

        Student s1 = new Student("S1", "s1@info.uaic.ro");
        Student s2 = new Student("S2", "s2@info.uaic.ro");
        Student s3 = new Student("S3", "s3@info.uaic.ro");
        Student s4 = new Student("S4", "s4@info.uaic.ro");

        Project p1 = new Project("P1", 2);
        Project p2 = new Project("P2", 2);
        Project p3 = new Project("P3", 2);

        s1.setPreferences(p1, p2, p3);
        s2.setPreferences(p2, p1, p3);
        s3.setPreferences(p3, p2, p1);
        s4.setPreferences(p1);

        p1.setPreferences(s1, s2, s3, s4);
        p2.setPreferences(s2, s1, s3);
        p3.setPreferences(s3, s2, s1);

        problem.setProjects(p1, p2, p3);
        problem.setStudents(s1, s2, s3, s4);

        // De afisat si preferintele
//        System.out.println(problem);

//        MatchingGenerator matchingGenerator = new MatchingGenerator(problem);
//        matchingGenerator.printMatching();
        GaleShapleyGenerator gp = new GaleShapleyGenerator(problem);
        gp.printMatching();

    }
}
