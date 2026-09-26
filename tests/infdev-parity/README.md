# Infdev 20100327 parity harness

This directory contains a differential test between the original Infdev 20100327 Java bytecode and the C++ port.

## Golden reference

The oracle is the original `inf-20100327.jar`, downloaded by CI and verified with SHA-256:

`c696d187821b9034046e4572dfdb579a60b80530ff02598aadb6322e8ad8b247`

The C++ implementation is never used to generate the Java reference values. Both implementations receive the same seed, coordinates and generation order.

## Current comparison layers

CI compares:

1. Java `Random` output: `nextInt`, bounded `nextInt`, `nextLong`, `nextFloat`, `nextDouble`.
2. Infdev Perlin output: raw IEEE-754 double bits at normal, negative, large-coordinate and Far Lands samples.
3. Infdev octave noise output: 2D and 3D raw double bits.
4. Terrain density: scalar samples, including negative coordinates and Far Lands.
5. Terrain density grid: raw IEEE-754 doubles over many chunk positions.
6. Final terrain chunk bytes: all 32,768 block IDs for every tested 16x16x128 chunk.

The text streams are compared with `diff -u`; the binary streams are compared with `cmp`. Therefore a normal floating-point tolerance is deliberately not used: a different bit pattern is a failure.

## Tested seeds and coordinates

The suite includes positive, negative, zero, extreme signed 64-bit seeds and large deterministic seeds. It also tests negative chunk coordinates and positions around the Infdev Far Lands boundary.

## What a PASS means

A passing run proves that the tested C++ terrain core produces the same observable values and final terrain block bytes as the original 20100327 Java generator for the complete test matrix.

It does not by itself prove gameplay-side behavior such as MCPE chunk persistence, network streaming, biome decoration or the full population system. Those are separate layers and should be tested against the original implementation with their own oracles.

## Failure debugging

On a mismatch CI prints the first textual difference and, for binary mismatches, decodes the first differing byte back to its seed, chunk and offset. The failure artifact also contains both oracle outputs and the diagnostic files.
