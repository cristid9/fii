import java.util.HashMap;
import java.util.Map;

public class PrefixContext {
    Map<Country, IPrefixStrategy> prefixes =  new HashMap<>();

    public PrefixContext() {
        prefixes.put(Country.BELGIUM, new BelgiumPrefix());
        prefixes.put(Country.ENGLAND, new EnglandPrefix());
        prefixes.put(Country.FRANCE, new FrancePrefix());
        prefixes.put(Country.NEDERLANDS, new NederlandsPrefix());
    }

    public String doExecute(Country country) {
        return prefixes.get(country).getPrefix();
    }

}
