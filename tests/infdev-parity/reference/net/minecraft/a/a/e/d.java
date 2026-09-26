package net.minecraft.a.a.e;

import net.minecraft.a.a.f;

/**
 * Parent-classloader stub for the original Chunk class. The original Infdev
 * constructor performs world-dependent work before the terrain provider has
 * finished writing the 32768-byte block array. That constructor is irrelevant
 * to terrain bytes, so the harness replaces it with a byte-array holder while
 * executing the original provider bytecode from the 20100327 JAR.
 */
public class d {
    private final byte[] blocks;
    public final int x;
    public final int z;

    public d(f world, byte[] blocks, int x, int z) {
        this.blocks = blocks;
        this.x = x;
        this.z = z;
    }
}
