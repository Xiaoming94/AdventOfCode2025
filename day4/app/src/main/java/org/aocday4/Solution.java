package org.aocday4;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.IntStream;
import java.util.List;
import java.util.ArrayList;

public class Solution {
    public static long solveProblem1(String input) {
        var solutionInternal = new SolutionInternal();
        return solutionInternal.findAccessibleToiletPaper(input);
    }

}

class SolutionInternal {
    public SolutionInternal() {
        searchDirections = new ArrayList<>();
        for (int i = -1; i <= 1; i += 1) {
            for (int j = -1; j <= 1; j += 1) {
                // Skipping zero cause that will be the object you are looking at rn
                if (!(i == 0 && j == 0)) {
                    searchDirections.add(new Position(i, j));
                }
            }
        }
    }

    boolean isAccessibleToiletPaper(Position pos) {
        // Assuming key is valid:
        var token = storageMap.get(pos);
        if (token == Token.Dot) {
            return false;
        }

        var posX = pos.x();
        var posY = pos.y();
        int adjacentPapers = 0;

        for (var dpos : searchDirections) {
            var newPosx = posX + dpos.x();
            var newPosy = posY + dpos.y();
            var posToCheck = new Position(newPosx, newPosy);
            if (storageMap.containsKey(posToCheck)) {
                adjacentPapers += storageMap.get(posToCheck) == Token.Paper ? 1 : 0;
            }
            if (adjacentPapers == 4) {
                return false;
            }
        }
        return true;
    }

    long findAccessibleToiletPaper(String input) {
        this.parseInput(input);

        return storageMap
            .keySet()
            .stream()
            .filter(pos -> isAccessibleToiletPaper(pos))
            .count();
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
                                storageMap.put(new Position(i, j), token);
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
    }

    private Map<Position, Token> storageMap = new HashMap<>();

    private List<Position> searchDirections;

}
