import java.io.File;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.jar.JarFile;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Arrays;
import java.util.Random;

public final class Main {
    private static String hex64(long value) {
        return String.format("%016x", value);
    }

    private static String hex32(int value) {
        return String.format("%08x", value);
    }

    private static Method findPerlinNoiseMethod(Class<?> clazz) {
        for (Method m : clazz.getDeclaredMethods()) {
            Class<?>[] p = m.getParameterTypes();
            if (m.getReturnType() == double.class &&
                p.length == 3 &&
                p[0] == double.class && p[1] == double.class && p[2] == double.class) {
                m.setAccessible(true);
                return m;
            }
        }
        throw new IllegalStateException("Could not find Perlin 3D noise method in " + clazz.getName()
                + ": " + Arrays.toString(clazz.getDeclaredMethods()));
    }

    private static Method findOctavesRegionMethod(Class<?> clazz) {
        for (Method m : clazz.getDeclaredMethods()) {
            Class<?>[] p = m.getParameterTypes();
            if (m.getReturnType() == double[].class &&
                Arrays.equals(p, new Class<?>[]{
                    double[].class, int.class, int.class, int.class,
                    int.class, int.class, int.class,
                    double.class, double.class, double.class})) {
                m.setAccessible(true);
                return m;
            }
        }
        throw new IllegalStateException("Could not find octave region method in " + clazz.getName()
                + ": " + Arrays.toString(clazz.getDeclaredMethods()));
    }

    private static Method findOctaves3DMethod(Class<?> clazz) {
        for (Method m : clazz.getDeclaredMethods()) {
            Class<?>[] p = m.getParameterTypes();
            if (m.getReturnType() == double.class &&
                p.length == 3 &&
                p[0] == double.class && p[1] == double.class && p[2] == double.class) {
                m.setAccessible(true);
                return m;
            }
        }
        throw new IllegalStateException("Could not find octave 3D scalar method in " + clazz.getName()
                + ": " + Arrays.toString(clazz.getDeclaredMethods()));
    }

    private static Method findOctaves2DMethod(Class<?> clazz) {
        for (Method m : clazz.getDeclaredMethods()) {
            Class<?>[] p = m.getParameterTypes();
            if (m.getReturnType() == double.class &&
                p.length == 2 &&
                p[0] == double.class && p[1] == double.class) {
                m.setAccessible(true);
                return m;
            }
        }
        throw new IllegalStateException("Could not find octave 2D scalar method in " + clazz.getName()
                + ": " + Arrays.toString(clazz.getDeclaredMethods()));
    }

    private static Constructor<?> findConstructor(Class<?> clazz, Class<?>... expected) {
        for (Constructor<?> c : clazz.getDeclaredConstructors()) {
            if (Arrays.equals(c.getParameterTypes(), expected)) {
                c.setAccessible(true);
                return c;
            }
        }
        throw new IllegalStateException("Could not find constructor " + clazz.getName() + Arrays.toString(expected));
    }

    private static void emitRandom(long seed) {
        Random random = new Random(seed);

        System.out.println("RNG seed=" + seed);
        for (int i = 0; i < 32; ++i)
            System.out.println("nextInt." + i + "=" + random.nextInt());

        int[] bounds = {1, 2, 3, 7, 16, 31, 32, 255, 256, 1024, 65535, 1048576, 2147483647};
        for (int bound : bounds) {
            random.setSeed(seed);
            StringBuilder line = new StringBuilder();
            for (int i = 0; i < 32; ++i) {
                if (i != 0) line.append(',');
                line.append(random.nextInt(bound));
            }
            System.out.println("nextIntBound." + bound + "=" + line);
        }

        random.setSeed(seed);
        for (int i = 0; i < 16; ++i)
            System.out.println("nextLong." + i + "=" + hex64(random.nextLong()));

        random.setSeed(seed);
        for (int i = 0; i < 16; ++i)
            System.out.println("nextFloat." + i + "=" + hex32(Float.floatToRawIntBits(random.nextFloat())));

        random.setSeed(seed);
        for (int i = 0; i < 16; ++i)
            System.out.println("nextDouble." + i + "=" + hex64(Double.doubleToRawLongBits(random.nextDouble())));
    }

    private static void emitPerlin(long seed, Constructor<?> ctor, Method noise) throws Exception {
        Object generator = ctor.newInstance(new Random(seed));

        double[][] samples = {
            {0.0, 0.0, 0.0},
            {1.25, 2.5, 3.75},
            {-1.25, 2.5, -3.75},
            {12.125, -4.5, 99.75},
            {-1234.5, 0.125, 6789.25},
            {12550824.0, 63.0, -12550824.0}
        };

        System.out.println("PERLIN seed=" + seed);
        for (int i = 0; i < samples.length; ++i) {
            double value = (double) noise.invoke(generator, samples[i][0], samples[i][1], samples[i][2]);
            System.out.println("sample." + i + "=" + hex64(Double.doubleToRawLongBits(value)));
        }
    }

    private static void emitOctaves(long seed, Constructor<?> ctor, Method noise3, Method noise2) throws Exception {
        double[][] samples = {
            {0.0, 0.0, 0.0},
            {1.25, 2.5, 3.75},
            {-1.25, 2.5, -3.75},
            {12.125, -4.5, 99.75},
            {-1234.5, 0.125, 6789.25},
            {12550824.0, 63.0, -12550824.0}
        };

        System.out.println("OCTAVES seed=" + seed + " octaves=8");

        Object generator3 = ctor.newInstance(new Random(seed), 8);
        for (int i = 0; i < samples.length; ++i) {
            double value = (double) noise3.invoke(generator3, samples[i][0], samples[i][1], samples[i][2]);
            System.out.println("sample3." + i + "=" + hex64(Double.doubleToRawLongBits(value)));
        }

        Object generator2 = ctor.newInstance(new Random(seed), 8);
        for (int i = 0; i < samples.length; ++i) {
            double value = (double) noise2.invoke(generator2, samples[i][0], samples[i][1]);
            System.out.println("sample2." + i + "=" + hex64(Double.doubleToRawLongBits(value)));
        }
    }
    private static long fnv1a(byte[] data) {
        long hash = 0xcbf29ce484222325L;
        for (byte value : data) {
            hash ^= (value & 0xffL);
            hash *= 0x100000001b3L;
        }
        return hash;
    }

    private static Method findDensityMethod(Class<?> clazz) {
        for (Method m : clazz.getDeclaredMethods()) {
            Class<?>[] p = m.getParameterTypes();
            if (m.getReturnType() == double.class &&
                Arrays.equals(p, new Class<?>[]{double.class, double.class, double.class})) {
                m.setAccessible(true);
                return m;
            }
        }
        throw new IllegalStateException("Could not find terrain density method in " + clazz.getName());
    }

    private static Constructor<?> findProviderConstructor(Class<?> clazz) {
        for (Constructor<?> c : clazz.getDeclaredConstructors()) {
            Class<?>[] p = c.getParameterTypes();
            if (p.length == 2 && p[1] == long.class) {
                c.setAccessible(true);
                return c;
            }
        }
        throw new IllegalStateException("Could not find provider(World,long) constructor in " + clazz.getName());
    }

    private static Method findChunkMethod(Class<?> clazz) {
        for (Method m : clazz.getDeclaredMethods()) {
            Class<?>[] p = m.getParameterTypes();
            if (Arrays.equals(p, new Class<?>[]{int.class, int.class}) &&
                !Modifier.isStatic(m.getModifiers())) {
                m.setAccessible(true);
                if (!m.getName().equals("b"))
                    continue;
                return m;
            }
        }
        throw new IllegalStateException("Could not find terrain chunk method in " + clazz.getName());
    }

    private static byte[] findChunkBytes(Object chunk) throws Exception {
        Class<?> c = chunk.getClass();
        while (c != null) {
            for (java.lang.reflect.Field f : c.getDeclaredFields()) {
                if (f.getType() != byte[].class)
                    continue;
                f.setAccessible(true);
                Object value = f.get(chunk);
                if (value instanceof byte[] && ((byte[]) value).length == 32768)
                    return (byte[]) value;
            }
            c = c.getSuperclass();
        }
        throw new IllegalStateException("Could not find 32768-byte chunk block array in " + chunk.getClass().getName());
    }

    private static void emitTerrain(long seed, Class<?> providerClass) throws Exception {
        Constructor<?> ctor = findProviderConstructor(providerClass);
        Method density = findDensityMethod(providerClass);

        double[][] densitySamples = {
            {0.0, 0.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {-1.0, 17.0, -1.0},
            {1234.25, 63.0, -987.75},
            {12550824.0, 63.0, -12550824.0}
        };

        System.out.println("TERRAIN_DENSITY seed=" + seed);
        Object provider = ctor.newInstance(null, seed);
        for (int i = 0; i < densitySamples.length; ++i) {
            double value = (double) density.invoke(provider,
                    densitySamples[i][0], densitySamples[i][1], densitySamples[i][2]);
            System.out.println("sample." + i + "=" + hex64(Double.doubleToRawLongBits(value)));
        }

        Method chunkMethod = findChunkMethod(providerClass);
        int[][] chunks = {
            {0, 0},
            {1, 0},
            {-1, 0},
            {0, -1},
            {-1, -1},
            {37, -91},
            {-1024, 2048}
        };

        System.out.println("TERRAIN_CHUNK seed=" + seed);
        for (int[] coord : chunks) {
            Object instance = ctor.newInstance(null, seed);
            Object chunk = chunkMethod.invoke(instance, coord[0], coord[1]);
            byte[] blocks = findChunkBytes(chunk);
            System.out.println("chunk." + coord[0] + "." + coord[1] + ".size=" + blocks.length);
            System.out.println("chunk." + coord[0] + "." + coord[1] + ".fnv64=" + hex64(fnv1a(blocks)));
        }
    }

    public static void main(String[] args) throws Exception {
        if (args.length != 1)
            throw new IllegalArgumentException("Usage: Main <inf-20100327.jar>");

        File jarFile = new File(args[0]);
        JarFile jar = new JarFile(jarFile);
        URLClassLoader loader = new URLClassLoader(
                new URL[] { jarFile.toURI().toURL() },
                Main.class.getClassLoader());

        Class<?> perlinClass = Class.forName("net.minecraft.a.a.c.a.a", true, loader);
        Class<?> octavesClass = Class.forName("net.minecraft.a.a.c.a.c", true, loader);
        Class<?> providerClass = Class.forName("net.minecraft.a.a.c.a", true, loader);

        Constructor<?> perlinCtor = findConstructor(perlinClass, Random.class);
        Constructor<?> octavesCtor = findConstructor(octavesClass, Random.class, int.class);
        Method perlinNoise = findPerlinNoiseMethod(perlinClass);
        Method octaves3D = findOctaves3DMethod(octavesClass);
        Method octaves2D = findOctaves2DMethod(octavesClass);

        long[] seeds = {
            0L,
            1L,
            -1L,
            12345L,
            987654321012345678L,
            Long.MIN_VALUE,
            Long.MAX_VALUE
        };

        for (long seed : seeds) {
            emitRandom(seed);
            emitPerlin(seed, perlinCtor, perlinNoise);
            emitOctaves(seed, octavesCtor, octaves3D, octaves2D);
            emitTerrain(seed, providerClass);
        }

        loader.close();
        jar.close();
    }
}
