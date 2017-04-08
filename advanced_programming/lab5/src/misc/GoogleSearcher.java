package misc;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class GoogleSearcher {

    public static List<String> search(String searchString) throws IOException {
        URL url = new URL(
                "https://www.googleapis.com/customsearch/v1?key="
                        + "AIzaSyAh3Tt9CaZM3IMH5pjyR-2jrL9g1d0Ug-s"
                        + "&cx=013036536707430787589:_pqjad5hr1a&q="
                        + searchString + "&alt=json");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        conn.setRequestProperty("Accept", "application/json");
        BufferedReader br = new BufferedReader(new InputStreamReader(
                (conn.getInputStream())));

        List<String> results = new ArrayList<>();

        String output;
        System.out.println("Output from Server .... \n");
        while ((output = br.readLine()) != null) {
            if (output.matches("(.*)title(.*)")) {

                results.add(output);
            }
        }

        conn.disconnect();


        return results;
    }

}
