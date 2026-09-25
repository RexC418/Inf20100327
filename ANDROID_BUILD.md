# Android APK build

The repository contains the modified MCPE 0.8.1 native source. The Android packaging layer is taken from the public `oldminecraftcommunity/MCPE-0.8.1-Android` project at build time.

The original 0.8.1 Android package's proprietary resources are deliberately not included. To make the GitHub Actions APK job succeed, provide these files from your own legally obtained MCPE 0.8.1 APK:

- `android-res/` — extracted `res/` directory
- `android-assets/` — extracted `assets/` directory
- `minecraftpe/impl/pcm_data.c` — generated with `tools/get_sound_data.py` from the ARMv7 `libminecraftpe.so`

Then push to GitHub and run **Actions → Android APK (MCPE 0.8.1 Infdev)**. The generated APK is uploaded as the `mcpe-0.8.1-infdev-apk` artifact.

The Android wrapper uses NativeActivity and loads the native library named `minecraftpe`, matching the decompiled 0.8.1 project. The wrapper project documents the same preparation requirements. 
