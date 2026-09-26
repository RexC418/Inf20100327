import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.jar.JarFile;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Arrays;
import java.util.Random;

public final class Main {
    private static final int[][] CHUNKS={
        {0,0},{1,0},{-1,0},{0,-1},{-1,-1},{37,-91},{-1024,2048},
        {784426,-784426},{784427,784426},{-784427,-784426},{1000000,-1000000},
        {-2000000,3000000},{524287,-524288}
    };

    private static final double[][] SAMPLES={
        {0.0,0.0,0.0},{1.25,2.5,3.75},{-1.25,2.5,-3.75},{12.125,-4.5,99.75},
        {-1234.5,0.125,6789.25},{255.999,1.5,-255.999},{256.0,-2.75,256.125},
        {-256.125,3.25,-256.0},{1023.5,-31.75,-1024.25},{4096.125,64.5,-4096.875},
        {1000000.25,12.75,-1000000.5},{10000000000.25,63.0,-10000000000.5},
        {12550823.75,63.0,-12550823.75},{12550824.0,63.0,-12550824.0},
        {12550824.25,63.0,-12550824.25},{-12550824.5,0.0,12550824.75},
        {2147483000.25,-2147483000.75,2147483647.25},
        {-2147483648.0,-2147483647.75,2147483647.75}
    };

    private static final double[][] TERRAIN_SAMPLES={
        {0.0,0.0,0.0},{0.0,15.999,0.0},{0.0,16.0,0.0},{0.0,31.5,0.0},
        {0.0,63.0,0.0},{0.0,64.0,0.0},{0.0,127.0,0.0},{-1.0,63.0,-1.0},
        {16.0,63.0,-16.0},{-1234.5,63.5,6789.25},{1000000.25,63.0,-1000000.5},
        {12550823.75,63.0,-12550823.75},{12550824.0,63.0,-12550824.0},
        {12550824.25,63.0,-12550824.25},{2147483000.25,63.0,-2147483000.75},
        {-2147483648.0,0.0,2147483647.75}
    };
    private static String hex64(long value) {
        return String.format("%016x", value);
    }

    private static String hex32(int value) {
        return String.format("%08x", value);
    }

    private static long fnv1a(byte[] data) {
        long hash = 0xcbf29ce484222325L;
        for (byte value : data) {
            hash ^= (value & 0xffL);
            hash *= 0x100000001b3L;
        }
        return hash;
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

        int[] bounds = {1, 2, 3, 7, 16, 31, 32, 255, 256, 257, 1023, 1024, 65535, 65536, 1048575, 1048576, 1073741824, 2147483647};
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
        Object generator=ctor.newInstance(new Random(seed));
        System.out.println("PERLIN seed="+seed);
        for(int i=0;i<SAMPLES.length;++i){
            double value=(double)noise.invoke(generator,SAMPLES[i][0],SAMPLES[i][1],SAMPLES[i][2]);
            System.out.println("sample."+i+"="+hex64(Double.doubleToRawLongBits(value)));
        }
    }

    private static void emitOctaves(long seed, Constructor<?> ctor, Method noise3, Method noise2) throws Exception {
        System.out.println("OCTAVES seed="+seed+" octaves=8");
        Object generator3=ctor.newInstance(new Random(seed),8);
        for(int i=0;i<SAMPLES.length;++i){
            double value=(double)noise3.invoke(generator3,SAMPLES[i][0],SAMPLES[i][1],SAMPLES[i][2]);
            System.out.println("sample3."+i+"="+hex64(Double.doubleToRawLongBits(value)));
        }
        Object generator2=ctor.newInstance(new Random(seed),8);
        for(int i=0;i<SAMPLES.length;++i){
            double value=(double)noise2.invoke(generator2,SAMPLES[i][0],SAMPLES[i][1]);
            System.out.println("sample2."+i+"="+hex64(Double.doubleToRawLongBits(value)));
        }
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

    private static void writeU32BE(DataOutputStream out,int value)throws IOException{out.writeByte((value>>>24)&255);out.writeByte((value>>>16)&255);out.writeByte((value>>>8)&255);out.writeByte(value&255);}
    private static void writeI64BE(DataOutputStream out,long value)throws IOException{out.writeLong(value);}
    private static void writeDoubleBE(DataOutputStream out,double value)throws IOException{out.writeLong(Double.doubleToRawLongBits(value));}

    private static void emitDensityComponents(long seed,Constructor<?> providerCtor,Class<?> octavesClass,Method noise3)throws Exception{
        Object provider=providerCtor.newInstance(null,seed);
        java.lang.reflect.Field lowField=provider.getClass().getDeclaredField("b");
        java.lang.reflect.Field highField=provider.getClass().getDeclaredField("c");
        java.lang.reflect.Field selectorField=provider.getClass().getDeclaredField("d");
        lowField.setAccessible(true);highField.setAccessible(true);selectorField.setAccessible(true);
        Object lowGen=lowField.get(provider), highGen=highField.get(provider), selectorGen=selectorField.get(provider);
        final double x=12550824.0,y=63.0,z=-12550824.0;
        final double offset=y*4.0-64.0;
        final double selector=((Double)noise3.invoke(selectorGen,x*684.412/80.0,y*684.412/400.0,z*684.412/80.0))/2.0;
        final Method octave3=findOctaves3DMethod(octavesClass);
        final double low=((Double)octave3.invoke(lowGen,x*684.412,y*984.412,z*684.412))/512.0-offset;
        final double high=((Double)octave3.invoke(highGen,x*684.412,y*984.412,z*684.412))/512.0-offset;
        System.out.println("TERRAIN_COMPONENTS seed="+seed);
        System.out.println("offset="+hex64(Double.doubleToRawLongBits(offset)));
        System.out.println("selector="+hex64(Double.doubleToRawLongBits(selector)));
        System.out.println("low="+hex64(Double.doubleToRawLongBits(low)));
        System.out.println("high="+hex64(Double.doubleToRawLongBits(high)));
    }

    private static void emitDensitySamples(long seed,Constructor<?> ctor,Method density)throws Exception{
        Object provider=ctor.newInstance(null,seed);
        System.out.println("TERRAIN_DENSITY seed="+seed);
        for(int i=0;i<TERRAIN_SAMPLES.length;++i){
            double value=(double)density.invoke(provider,TERRAIN_SAMPLES[i][0],TERRAIN_SAMPLES[i][1],TERRAIN_SAMPLES[i][2]);
            System.out.println("sample."+i+"="+hex64(Double.doubleToRawLongBits(value)));
        }
    }

    private static void emitTerrain(long seed,Constructor<?> ctor,Method density,Method chunkMethod,DataOutputStream out)throws Exception{
        emitDensitySamples(seed,ctor,density);
        System.out.println("TERRAIN_DENSITY_GRID seed="+seed);
        writeI64BE(out,seed);
        Object provider=ctor.newInstance(null,seed);
        for(int[] c:CHUNKS){
            writeU32BE(out,c[0]);writeU32BE(out,c[1]);
            for(int xc=0;xc<4;++xc)for(int zc=0;zc<4;++zc)for(int y=0;y<33;++y){
                double x=c[0]*4.0+xc,z= c[1]*4.0+zc;
                writeDoubleBE(out,(double)density.invoke(provider,x,y,z));
                writeDoubleBE(out,(double)density.invoke(provider,x,y,z+1.0));
                writeDoubleBE(out,(double)density.invoke(provider,x+1.0,y,z));
                writeDoubleBE(out,(double)density.invoke(provider,x+1.0,y,z+1.0));
            }
        }
        System.out.println("TERRAIN_CHUNK seed="+seed);
        writeI64BE(out,seed);
        for(int[] c:CHUNKS){
            Object instance=ctor.newInstance(null,seed);
            Object chunk=chunkMethod.invoke(instance,c[0],c[1]);
            byte[] blocks=findChunkBytes(chunk);
            System.out.println("chunk."+c[0]+"."+c[1]+".size="+blocks.length);
            System.out.println("chunk."+c[0]+"."+c[1]+".fnv64="+hex64(fnv1a(blocks)));
            writeU32BE(out,c[0]);writeU32BE(out,c[1]);writeU32BE(out,blocks.length);out.write(blocks);
        }
        System.out.println("TERRAIN_DONE seed="+seed);
    }

    public static void main(String[] args) throws Exception {
        if(args.length!=2) throw new IllegalArgumentException("Usage: Main <inf-20100327.jar> <oracle.bin>");
        File jarFile=new File(args[0]);
        // Force the harness stubs into the parent classloader before the original
        // 20100327 classes are loaded. The provider bytecode itself still comes
        // directly from the original JAR.
        Class.forName("net.minecraft.a.a.f");
        Class.forName("net.minecraft.a.a.e.d");
        JarFile jar=new JarFile(jarFile);
        URLClassLoader loader=new URLClassLoader(new URL[]{jarFile.toURI().toURL()},Main.class.getClassLoader());
        Class<?> perlinClass=Class.forName("net.minecraft.a.a.c.a.a",true,loader);
        Class<?> octavesClass=Class.forName("net.minecraft.a.a.c.a.c",true,loader);
        Class<?> providerClass=Class.forName("net.minecraft.a.a.c.a",true,loader);
        Constructor<?> perlinCtor=findConstructor(perlinClass,Random.class);
        Constructor<?> octavesCtor=findConstructor(octavesClass,Random.class,int.class);
        Method perlinNoise=findPerlinNoiseMethod(perlinClass);
        Method octaves3D=findOctaves3DMethod(octavesClass);
        Method octaves2D=findOctaves2DMethod(octavesClass);
        Constructor<?> providerCtor=findProviderConstructor(providerClass);
        Method density=findDensityMethod(providerClass);
        Method chunkMethod=findChunkMethod(providerClass);
        long[] seeds={
            0L,1L,-1L,2L,-2L,3L,-3L,42L,12345L,-12345L,
            987654321012345678L,-987654321012345678L,
            81985529216486895L,-81985529216486896L,
            6148914691236517205L,-6148914691236517206L,
            Long.MIN_VALUE,Long.MAX_VALUE,9223372036854775806L,-9223372036854775807L,
            1311768467463790320L,2623536924927580640L
        };
        DataOutputStream out=new DataOutputStream(new FileOutputStream(args[1]));
        out.writeInt(0x49464431);out.writeInt(seeds.length);
        for(long seed:seeds){
            emitRandom(seed);emitPerlin(seed,perlinCtor,perlinNoise);emitOctaves(seed,octavesCtor,octaves3D,octaves2D);
            emitDensityComponents(seed,providerCtor,octavesClass,octaves3D);
            emitTerrain(seed,providerCtor,density,chunkMethod,out);
        }
        out.flush();out.close();loader.close();jar.close();
    }
}
