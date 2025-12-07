package org.aocday4;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class AocTest {
    static final String EXAMPLE_INPUT = """
        ..@@.@@@@.
        @@@.@.@.@@
        @@@@@.@.@@
        @.@@@@..@.
        @@.@@@@.@@
        .@@@@@@@.@
        .@.@.@.@@@
        @.@@@.@@@@
        .@@@@@@@@.
        @.@.@@@.@.
        """;

    @Test public void testProblem1Solution() {
        var result = Solution.solveProblem1(EXAMPLE_INPUT);
        assertEquals(13, result);
    }

    @Test public void testProblem2Solution() {
        var result = Solution.solveProblem2(EXAMPLE_INPUT);
        assertEquals(43, result);
    }
}
