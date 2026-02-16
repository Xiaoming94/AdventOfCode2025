/**
 * Class for the solution of Advent of Code day7;
 *
 * In general, this solution uses an internal hashmap to store mapData
 * And then using a queue to keep track of what lasers are still traversing.
 */

package org.aocday7;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.stream.IntStream;

public class Solution {
    /**
     * Function for solving problem 1
     *
     * Uses a simple laser simulation to find the numbers of splits according to the
     * problem specification of https://adventofcode.com/2025/day/7
     *
     * @param input Multiline string representation of the map
     * @return solution for problem1, i.e. the number of unique splits
     */
    public static long solveProblem1(String input) {
        var tachyonBeamTracer = new TachyonBeamTracer();
        tachyonBeamTracer.createTachyonMap(input);
        return tachyonBeamTracer.calcTotalSplits();
    }

    public static long solveProblem2(String input) {
        var tachyonBeamTracer = new TachyonBeamTracer();
        tachyonBeamTracer.createTachyonMap(input);
        return tachyonBeamTracer.calcQuantumBeamTimelines();
    }
}

record Coordinate(int x, int y) {}

class CoordComparator implements Comparator<Coordinate>
{
    public int compare(Coordinate lhs, Coordinate rhs) {
        if (lhs.equals(rhs)) {
            return EQUALS;
        }
        return lhs.y() >= rhs.y() ? GREATER : LESS;
    }

    public boolean equals(Object obj) {
        return obj.equals(this);
    }

    private static final int LESS = -1;
    private static final int EQUALS = 0;
    private static final int GREATER = 1;
}

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

    private Coordinate moveLaser(Coordinate currentLaserPos) {
        return new Coordinate(currentLaserPos.x(), currentLaserPos.y() + 1);
    }

    private long runBeamSimulation() {
        Queue<Coordinate> lasersToRun = new ArrayDeque<>();
        lasersToRun.addAll(startingPositions);
        Set<Coordinate> visitedStartingNodes = new HashSet<>();
        Set<Coordinate> hittedSplitters = new HashSet<>();
        while(!lasersToRun.isEmpty()) {
            var laserPosition = lasersToRun.remove();
            while(tachyonBeamMap.containsKey(laserPosition) &&
                    tachyonBeamMap.get(laserPosition) != MapSymbol.SPLIT) {
                var nextPosition = moveLaser(laserPosition);
                // Look ahead
                var nextSymbol = tachyonBeamMap.get(nextPosition);
                if (nextSymbol == MapSymbol.SPLIT) {
                    hittedSplitters.add(nextPosition);
                    var laserLeft = new Coordinate(nextPosition.x()-1, nextPosition.y());
                    if (visitedStartingNodes.add(laserLeft)) {
                        lasersToRun.add(laserLeft);
                    }

                    var laserRight = new Coordinate(nextPosition.x()+1, nextPosition.y());
                    if (visitedStartingNodes.add(laserRight)) {
                        lasersToRun.add(laserRight);
                    }
                }

                laserPosition = nextPosition;
            }
        }
        return hittedSplitters.size();

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

    public long calcTotalSplits() {
        return runBeamSimulation();
    }

    public long calcQuantumBeamTimelines() {
        return 0;
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
