Advent of Code 2025 Day1
=======

The theme of this day is basically handling a circular set of integers and rotating them.

The knob can be thought of as a circular set of numbers 0 - 99 that "loops around"
So the correct usage of things like `%` operator correctly became crucial.

Worth noting that rust doesn't have a *true mathematical* modulo operator, so I relied on the rem_euclide(base) function that of the integer types to perform some of the modulo operations (i.e. when you loop around negatively).

## Why use the enum Instruction type?

I generally don't like to work with chars or strings directly since that will mean that I will have to match with a default everytime instead of using a type with finite domain.

This is actually a theme throughout all of my solutions, that I like to transform them into a type that I can work with internally.

Also, making this type allowed me to use some operator overloading that helped in simplifying the code.
