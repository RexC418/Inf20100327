# Original MCPE 0.8.1 library

Place your own original ARMv7 `libminecraftpe.so` from MCPE 0.8.1 in this directory with exactly this filename:

`libminecraftpe.so`

It is used only as input to `tools/get_sound_data.py` to reconstruct `minecraftpe/impl/pcm_data.c` during the GitHub Actions build.

Do not replace the generated `libminecraftpe.so` in the APK with this file. The APK must contain the library produced by compiling this source tree.

For a public repository, do not upload proprietary game binaries. Use a private repository or otherwise provide the file through a private build mechanism.
