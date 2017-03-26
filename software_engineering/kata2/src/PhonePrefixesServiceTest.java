import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;

public class PhonePrefixesServiceTest {
    private PhonePrefixesService service;

    @Before
    public void setUp() {
        service = new PhonePrefixesService();
    }

    @After
    public void tearDown() {
        service = null;
    }

    @Test
    public void when_country_is_belgium_prefix_should_be_32() {
        String result = service.getPrefix(Country.BELGIUM);

        assertEquals("+32", result);
    }

    @Test
    public void when_country_is_england_prefix_should_be_41() {
        String result = service.getPrefix(Country.ENGLAND);

        assertEquals("+41", result);
    }

    @Test
    public void when_country_is_france_prefix_should_be_31() {
        String result = service.getPrefix(Country.FRANCE);

        assertEquals("+31", result);
    }

    @Test
    public void when_country_is_nederlands_prefix_should_be_33() {
        String result = service.getPrefix(Country.NEDERLANDS);

        assertEquals("+33", result);
    }

}
