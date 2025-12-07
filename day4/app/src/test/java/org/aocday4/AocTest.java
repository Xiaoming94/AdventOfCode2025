package org.aocday4;

import org.junit.Test;
import static org.junit.Assert.*;

public class AocTest {
    static final String EXAMPLE_INPUT = """
        ..xx.xx@x.
        x@@.@.@.@@
        @@@@@.x.@@
        @.@@@@..@.
        x@.@@@@.@x
        .@@@@@@@.@
        .@.@.@.@@@
        x.@@@.@@@@
        .@@@@@@@@.
        x.x.@@@.x.
        """;

    @Test public void testProblem1Solution() {
        var result = Solution.solveProblem1(EXAMPLE_INPUT);
        assertEquals(13, result);
    }
}
