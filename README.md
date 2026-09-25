# MCPE 0.8.1
An attempt to decompile MCPE 0.8.1 and to make it possible to run it on different platforms. Currently it should be possible to run it on linux and windows. The project is not affiliated with mojang or microsoft.

## Building

## Cloning the repo and extracting sounds
* Clone the repo with `--recursive` flag(or use `git submodule init` and `git submodule update` after cloning if you forgot to add it)
* GitHub Actions runs `python3 tools/get_sound_data.py tools/original/libminecraftpe.so` automatically and generates `minecraftpe/impl/pcm_data.c`
* Move `pcm_data.c` to `./minecraftpe/impl/`

### Linux
Requires SDL1(`libsdl1.2-dev` and `libsdl1.2debian`), OpenAL(`libopenal-dev` and `libopenal1`), OpenGL(`libgl1-mesa-dev`), zlib (`zlib1g` and `zlib1g-dev`), curl (`libcurl4` and `libcurl4-openssl-dev`).
You must also have original 0.8.1 apk file to extract sounds(won't compile without them) and obtain assets(the compiled file will crash or not work properly without them).
* ```
  mkdir build
  cd build
  cmake ..
  make
  ```
* the output should be `minecraftpe/build/minecraftpe08decomp`

### Android
Use https://github.com/oldminecraftcommunity/MCPE-0.8.1-Android

### Windows
Windows version does not require OpenAL(it uses DirectSound instead). See [.github/workflows/main.yml](https://github.com/oldminecraftcommunity/MCPE-0.8.1/blob/master/.github/workflows/main.yml#L37) for a way to cross compile it for windows on linux. **Building on windows was not tested!**

### Running
* extract `assets` from real MCPE 0.8.1 apk into the folder you're running the executable from
* run compiled executable

### Prebuilt versions
There are prebuilt versions available in github actions(they are probably getting autoremoved every 3 months, so should probably move them later into releases<?>). The prebuilt versions do not contain assets or sounds, so you have to extract them yourself. Use `python tools/pcm2wav.py <path/to/libminecraftpe.so>` to extract sounds from `libminecraftpe.so` into `sounds` folder and move it to the same directory where `assets` and executable file is located.

## Some additional info:
* Original APK used ndk r8d(first with gcc 4.7 toolchain needed for c++11) or r8e(last version that doesnt include fix for http://code.google.com/p/android/issues/detail?id=41755)
* JSON library that was probably used by Mojang: https://chromium.googlesource.com/external/jsoncpp/+/6921bf1feef6f1fb83935ae3943f07753488311d/jsoncpp <check commit later>
* RakNet: https://web.archive.org/web/20260101222408if_/http://www.raknet.com/raknet/downloads/RakNet_PC-4.036.zip (might be some other version, modified by mojang)
* GZIP stuff - zlib 1.2.3(bundled with android by default?), based on https://zlib.net/zpipe.c
* STB - https://web.archive.org/web/20131009042610/http://nothings.org/stb_image.c
* GLM - 0.9.4.6, https://github.com/g-truc/glm/commit/15b19a10be774975aee34c1cb277178999261e5f <?>(might be older, this is the latest release that was possibly used by mojang(0.9.5.0 brach contains commits after 0.8.1 release date))
* OpenAES - probably 0.7.0 - 0.8.1 (the only difference between them is in cmd version, 0.6.0 contains methods that are not present in original)

