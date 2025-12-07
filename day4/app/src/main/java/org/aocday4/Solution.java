package org.aocday4;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.stream.IntStream;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Stream;

public class Solution {
    public static long solveProblem1(String input) {
        var solutionInternal = new SolutionInternal(input);
        return solutionInternal.findAccessibleToiletPaper();
    }

    public static long solveProblem2(String input) {
        var solutionInternal = new SolutionInternal(input);
        return solutionInternal.countTotalRemovePaper();
    }

}

class SolutionInternal {
    public SolutionInternal(String input) {
        searchDirections = new ArrayList<>();
        for (int i = -1; i <= 1; i += 1) {
            for (int j = -1; j <= 1; j += 1) {
                // Skipping zero cause that will be the object you are looking at rn
                if (!(i == 0 && j == 0)) {
                    searchDirections.add(new Position(i, j));
                }
            }
        }
        this.parseInput(input);
    }

    boolean isAccessibleToiletPaper(Position pos) {
        // Assuming key is valid:
        var token = storageMap.get(pos);
        if (token == Token.Dot) {
            return false;
        }

        var countPaperFound = searchDirections
            .stream()
            .map(pos::add)
            .filter(storageMap::containsKey)
            .filter(posToCheck -> storageMap.get(posToCheck) == Token.Paper)
            .count();

        return countPaperFound < 4;
    }

    long findAccessibleToiletPaper() {

        return storageMap
            .keySet()
            .stream()
            .filter(this::isAccessibleToiletPaper)
            .count();
    }

    Stream<Position> filterRemovablePaper(Set<Position> positions) {
        return positions.stream().filter(this::isAccessibleToiletPaper);
    }

    long countTotalRemovePaper() {
        int totalPapersToRemove = 0;
        var foundRemoveablePaper = filterRemovablePaper(storageMap.keySet()).toList();

        while (! foundRemoveablePaper.isEmpty()) {
            totalPapersToRemove += foundRemoveablePaper.size();
            for (var pos : foundRemoveablePaper) {
                storageMap.replace(pos, Token.Dot);
            }
            foundRemoveablePaper = filterRemovablePaper(storageMap.keySet()).toList();
        }

        return totalPapersToRemove;
    }

    void parseInput(String input) {
        var lines = input.split("\n");
        IntStream
                .range(0, lines.length)
                .forEach(i -> {
                    var lineArray = lines[i].toCharArray();
                    IntStream
                            .range(0, lineArray.length)
                            .forEach(j -> {
                                var token = charToToken(lineArray[j]);
                                storageMap.put(new Position(j, i), token);
                            });
                });

    }

    Token charToToken(char c) {
        switch (c) {
            case '.':
                return Token.Dot;
            case '@':
                return Token.Paper;
        }
        return Token.Dot;
    }

    private enum Token {
        Dot,
        Paper,
    }

    private record Position(int x, int y) {
        Position add(Position other) {
            var newX = this.x() + other.x();
            var newY = this.y() + other.y();
            return new Position(newX, newY);
        }
    }

    private Map<Position, Token> storageMap = new HashMap<>();

    private List<Position> searchDirections;

}
