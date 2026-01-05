
package org.aocday7;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class QuantumTimelineTest {

    @Test
    void testSingleSplitterTimelines() {
        String input = """
                ..S..
                .....
                ..^..
                .....
                """;

        var result = Solution.solveProblem2(input);
        assertEquals(2, result);
    }

    @Test
    void test3SplittersTimelines() {
        String input = """
                ..S..
                .....
                ..^..
                .....
                .^.^.
                .....
                """;

        var result = Solution.solveProblem2(input);
        assertEquals(4, result);
    }

    @Test
    void testDiamond4SplittersTimelines() {
        String input = """
                ..S..
                .....
                ..^..
                .....
                .^.^.
                .....
                ..^..
                .....
                """;

        var result = Solution.solveProblem2(input);
        assertEquals(6, result);
    }
}
