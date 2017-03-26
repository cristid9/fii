public class PhonePrefixesService {

    public String getPrefix(Country country) {
        PrefixContext ctx = new PrefixContext();
        return ctx.doExecute(country);
    }
}
