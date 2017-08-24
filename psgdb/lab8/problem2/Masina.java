import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Masina {
    private static DBConnector db = new DBConnector();
    private String culoare;
    private String marca;

    public String getCuloare() {
        return culoare;
    }

    public String getMarca() {
        return marca;
    }

    public Masina(String culoare, String marca) {
        this.culoare = culoare;
        this.marca = marca;
    }

    public void serialize() {
        try {
            Connection conn = db.getDBConnection();

            Statement statement = conn.createStatement();
            statement.executeUpdate("delete from masinaRepository where 1 = 1");
            statement.executeUpdate("select factoryMasina('" + culoare + "', '" + marca + "') from dual");

            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Masina deserialize() {
        try {
            Connection connection = db.getDBConnection();
            Statement statement = connection.createStatement();

            ResultSet rs = statement.executeQuery("select getColor() as color from dual");
            rs.next();

            String color = rs.getString("color");

            ResultSet rs2 = statement.executeQuery("select getMarca() as marca from dual");
            rs2.next();

            String marca = rs2.getString("marca");

            return new Masina(color, marca);

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }

    public static void main(String[] args) {
        Masina masina = new Masina("albastru", "logan");
        masina.serialize();

        Masina masina2 = Masina.deserialize();
        System.out.println(masina2.getCuloare());
        System.out.println(masina2.getMarca());
    }
}



