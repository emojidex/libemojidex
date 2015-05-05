libemojidex
===========
emojidex libraries in C++. 
Built with portability in mind this library should easily enable back-end integration on desktop, 
server and mobile platforms.

Building
========

1. Install dependencies (cmake, boost system, boost filesystem, SSL development packages/headers)
2. Get submodules with:
  ```
  git submodule update --init --recursive"
  ```
3. Create the build directory, eg:
  ```
  mkdir build
  cd build
  ```
4. Run cmake, enabling the interfaces you want:  
  Libs only, no interfaces:
  ```
  cmake ..
  ```

  Java interfaces:
  ```
  cmake -DJAVABUILD=true ..
  ```
5. Build with "make" on \*nix or import into your IDE and build.

Packaged Builds
===============

Android [NDK] Build
-------------------
※Build script is a simple Bash script, so you'll need bash + all build tools required for a normal build
1. Install the [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html)
2. Run the build script, prefixing with an "NDK_ROOT" environment variable or setting it in advance:
  ```
  cd natives/android
  NDK_ROOT=$HOME/android-ndk ./build.sh
  ```

iOS Build
---------
* Coming Soon

License
=======
emojidex and emojidex tools are licensed under the [emojidex Open License](https://www.emojidex.com/emojidex/emojidex_open_license).

©2013 the emojidex project / Genshin Souzou K.K. [Phantom Creation Inc.]
