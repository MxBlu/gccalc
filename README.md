# GC Calculator for Hackmud

**Based on math as of late 2016**, a calculator for doing math in Hackmud.

## Compiling

This project has no dependencies, compile using your preferred C compiler using provided make scripts or otherwise.

## Usage

This calculator takes in and returns values in the format that the game accepts for GC values, providing a simple way to do basic calculations which would otherwise be difficult due conversion of units (e.g. 130GC * 8 = 1K8GC != 1080GC as far as game logic is concerned).

The calculator runs its own shell style prompt

```
-------MxBlue's GC Calculator-------

Usage: <operator> <GC string>
GC Strings should be in the xxxTxxxBxxxMxxxKxxxGC
Example: 10GC, 10B10KGC

Operators:
   '+'  Add
   '-'  Subtract
   '*'  Multiply by number
   'c'  Clear current total
   'q'  Quit

> _
```

As seen above, supported operations are addition (+), subtraction (-) and multiplication (*).
The calculator uses state based logic, with the running total starting at 0. Commands are to be formatted `[operation][value]`.

For example, to perform 200GC + 900GC:
```
> +200GC
200GC

> +900GC
1K100GC

> _
```

The running total can be cleared with the operation 'c'.
