/**
 * Class for the solution of Advent of Code day7;
 *
 * In general, this solution uses an internal hashmap to store mapData
 * And then using a queue to keep track of what lasers are still traversing.
 */

package org.aocday7;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.PriorityQueue;
import java.util.Queue;
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

    public static String solveProblem2(String input) {
        var tachyonBeamTracer = new TachyonBeamTracer();
        tachyonBeamTracer.createTachyonMap(input);
        return tachyonBeamTracer.calcQuantumBeamTimelines();
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

    private Optional<Coordinate> propagateLaser(Coordinate pos) {
        var nodesInMap = this.tachyonBeamMap.keySet();
        return nodesInMap
            .stream()
            .filter(coord -> this.tachyonBeamMap.get(coord) == MapSymbol.SPLIT )
            .filter(coord -> coord.x() == pos.x() && coord.y() > pos.y())
            .sorted(Comparator.comparingInt(Coordinate::y))
            .findFirst();

    }

    private Map<Coordinate, BigInteger> runBeamSimulation() {
        Queue<Coordinate> splitters = new PriorityQueue<>(Comparator.comparingInt(Coordinate::y));
        var nodesInMap = this.tachyonBeamMap.keySet();
        splitters.addAll(
            nodesInMap
                .stream()
                .filter(coord -> {
                    var mapData = this.tachyonBeamMap.get(coord);
                    return mapData == MapSymbol.SPLIT || mapData == MapSymbol.START;
                })
                .toList()
        );

        Map<Coordinate, BigInteger> hittedSplitters = new HashMap<>();

        while(!splitters.isEmpty()) {
            var current = splitters.poll();
            // Starting positions
            if (tachyonBeamMap.get(current) == MapSymbol.START) {
                propagateLaser(current).ifPresent(
                    coord -> {
                        var hits = BigInteger.ONE;
                        if (hittedSplitters.containsKey(coord)){
                            hits = hits.add(hittedSplitters.get(coord));
                        }
                        hittedSplitters.put(coord, hits);
                    }
                );
            }

            //Splitters
            if (tachyonBeamMap.get(current) == MapSymbol.SPLIT) {
                if (!hittedSplitters.containsKey(current)) {
                    continue;
                }
                var timeLinesOnBranch = hittedSplitters.get(current);
                var laserLeft = new Coordinate(current.x() - 1, current.y());
                var laserRight = new Coordinate(current.x() + 1, current.y());
                Arrays
                    .stream(new Coordinate[]{laserLeft, laserRight})
                    .forEach(
                        laser -> propagateLaser(laser)
                        .ifPresent(
                            coord -> {
                                var hits = hittedSplitters.getOrDefault(coord, BigInteger.ZERO).add(timeLinesOnBranch);
                                hittedSplitters.put(coord, hits);
                            }
                        )
                    );
            }
        }

        return hittedSplitters;
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
        var result = runBeamSimulation();
        return result.size();
    }

    public String calcQuantumBeamTimelines() {
        var result = runBeamSimulation();
        return result
            .values()
            .stream()
            .reduce(BigInteger.ONE, (lhs, rhs) -> lhs.add(rhs))
            .toString();
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
