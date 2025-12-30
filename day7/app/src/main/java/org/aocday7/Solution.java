/**
 * Class for the solution of Advent of Code day7;
 */

package org.aocday7;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.IntStream;

public class Solution {
    public static int solveProblem1(String input) {
        new TachyonBeamTracer().createTachyonMap(input);
        return 0;
    }
}

record Coordinate(int x, int y) {}

enum MapSymbol {
    SPLIT,
    DOT,
    START,
}

class TachyonBeamTracer {
    private MapSymbol toMapSymbol(char inputChar) throws IllegalArgumentException {
        switch(inputChar) {
            case '.' : return MapSymbol.DOT;
            case '^' : return MapSymbol.SPLIT;
            case 'S' : return MapSymbol.START;
        };

        throw new IllegalStateException(String.format("Invalid input character %s", inputChar));
    }

    public void createTachyonMap(String input) {
        var inputLinesArr = input
            .lines()
            .toArray(String[]::new);

        IntStream.range(0, inputLinesArr.length)
            .forEach(i -> {
                var line = inputLinesArr[i].toCharArray();
                IntStream.range(0, line.length)
                    .forEach(j -> {
                        var parsedMapSymbol = toMapSymbol(line[j]);
                        var coordinate = new Coordinate(j, i);
                        if ( parsedMapSymbol == MapSymbol.START ) {
                            startingPositions.add(coordinate);
                        }
                        this.tachyonBeamMap.put(coordinate, parsedMapSymbol);
                    });
            });

    }

    public MapSymbol getItemAt(int x, int y) {
        var lookupCoordinate = new Coordinate(x, y);
        return tachyonBeamMap.get(lookupCoordinate);
    }

    public List<Coordinate> getStartingPositions() {
        return this.startingPositions;
    }

    private Map<Coordinate, MapSymbol> tachyonBeamMap = new HashMap<>();
    private List<Coordinate> startingPositions = new ArrayList<>();
}
