/**
 * Unit tests for the TachyonBeamMap internal type
 */

package org.aocday7;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class TachyonBeamMapTest {
    @Test
    void parseOnly1Start() {
        final String input = "S";
        var myBeamTracer = new TachyonBeamTracer();
        myBeamTracer.createTachyonMap(input);
        assertEquals(1, myBeamTracer.getStartingPositions().size());
    }

    @Test
    void testSimpleMap() {
        final String input = ".S.";
        var myBeamTracer = new TachyonBeamTracer();
        myBeamTracer.createTachyonMap(input);
        assertEquals(MapSymbol.DOT, myBeamTracer.getItemAt(0, 0));
        assertEquals(MapSymbol.START, myBeamTracer.getItemAt(1, 0));
        assertEquals(MapSymbol.DOT, myBeamTracer.getItemAt(2, 0));
    }

    @Test
    void testMulitLineMap() {
        final String input = """
                .S.
                ^.^
                """;
        var myBeamTracer = new TachyonBeamTracer();
        myBeamTracer.createTachyonMap(input);
        assertEquals(MapSymbol.START, myBeamTracer.getItemAt(1, 0));
        assertEquals(MapSymbol.SPLIT, myBeamTracer.getItemAt(0, 1));
        assertEquals(MapSymbol.DOT, myBeamTracer.getItemAt(0, 0));
        assertEquals(MapSymbol.DOT, myBeamTracer.getItemAt(1, 1));
    }

    @Test
    void testSingleSplit() {
        final String input = """
                .S.
                ...
                .^.
                ...
                """;

        var splits = Solution.solveProblem1(input);
        assertEquals(1, splits);
    }
}
