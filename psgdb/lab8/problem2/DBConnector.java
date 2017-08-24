import oracle.jdbc.pool.OracleDataSource;

import java.sql.Connection;
import java.sql.SQLException;

public class DBConnector {
    String jdbcUrl = " jdbc:oracle:thin:@127.0.0.1:1521:XE";
    String userid = "student";
    String password = "STUDENT";
    Connection conn;


    public DBConnector() {

        try {
            Class.forName("oracle.jdbc.OracleDriver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        OracleDataSource ds = null;

        try {
            ds = new OracleDataSource();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        ds.setURL(jdbcUrl);

        try {
            conn = ds.getConnection(userid, password);
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }

    public Connection getDBConnection() throws SQLException {
        return conn;
    }
}