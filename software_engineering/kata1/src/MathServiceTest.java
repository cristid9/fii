import org.junit.Test;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * Contains unitests for `MathService`.
 */
public class MathServiceTest {

    @Test
    public void leap_year_should_be_divisible_by_four() {
        assertTrue(MathService.isLeapYear(2016));
    }

    @Test
    public void nonleap_year_should_not_be_divisible_by_four() {
        assertFalse(MathService.isLeapYear(3));
    }

    @Test
    public void leap_year_should_not_be_divisible_by_100() {
        assertTrue(MathService.isLeapYear(2020));
    }

    @Test
    public void nonleap_year_should_be_divisible_by_100() {
        assertFalse(MathService.isLeapYear(1800));
    }

    @Test
    public void leap_year_should_be_divisible_by_400() {
        assertTrue(MathService.isLeapYear(2400));
    }

    @Test
    public void nonleap_year_should_not_be_divisible_by_400() {
        assertFalse(MathService.isLeapYear(1800));
    }
}
