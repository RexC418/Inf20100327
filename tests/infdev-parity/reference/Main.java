import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Arrays;
import java.util.Comparator;
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
        throw new IllegalStateException("Could not find Perlin 3D noise method in " + clazz.getName());
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
        throw new IllegalStateException("Could not find octave 3D scalar method in " + clazz.getName());
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
        throw new IllegalStateException("Could not find octave 2D scalar method in " + clazz.getName());
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
        Object generator = ctor.newInstance(new Random(seed), 8);
        for (int i = 0; i < samples.length; ++i) {
            double value = (double) noise3.invoke(generator, samples[i][0], samples[i][1], samples[i][2]);
            System.out.println("sample3." + i + "=" + hex64(Double.doubleToRawLongBits(value)));
        }

        Object generator2 = ctor.newInstance(new Random(seed), 8);
        for (int i = 0; i < samples.length; ++i) {
            double value = (double) noise2.invoke(generator2, samples[i][0], samples[i][1]);
            System.out.println("sample2." + i + "=" + hex64(Double.doubleToRawLongBits(value)));
        }
    }

    public static void main(String[] args) throws Exception {
        Class<?> perlinClass = Class.forName("NoiseGeneratorPerlin");
        Class<?> octavesClass = Class.forName("NoiseGeneratorOctaves");

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
        }
    }
}
