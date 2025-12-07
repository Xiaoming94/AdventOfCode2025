package org.aocday4;

import java.util.Scanner;

public class Main {
    static String readInput() {
        Scanner sc = new Scanner(System.in);
        var input = new String();
        while (sc.hasNextLine()) {
            input += sc.nextLine() + "\n";
        }
        return input;
    }

    public static void main(String[] args) {
        var input = readInput();
        System.out.println(String.format("input is: %s", input));
        System.out.println(String.format("Solution for problem 1: %d", Solution.solveProblem1(input)));
    }
}
