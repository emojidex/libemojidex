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
4. Run cmake:  
  ```
  cmake ..
  ```
5. Build with "make" on \*nix or import into your IDE and build.

Java Native Interface
---------------------

1. Follow steps 1 - 3 from normal build.
2. Run cmake with the JAVA flag set to true:
  ```
  cmake -DJAVA=true ..
  ```
3. Run "make" or compile on your native environment.

Ruby Native Extension
---------------------

1. Follow steps 1 - 3 from normal build.
2. Run cmake with the RUBY flag set to true:
  ```
  cmake -DRUBY=true ..
  ```
3. Run "make" or compile on your native environment.

Packaged Builds
===============

Android [NDK] Build
-------------------
※Build script is a simple Bash script, so you'll need bash + all build tools required for a normal build
1. Install the [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html)
2. Follow steps 1 - 3 from normal build.
3. Run cmake with the ANDROID flag set to true:
  ```
  cmake -DANDROID=true ..
  ```
4. Run "make" or compile on your native environment.

iOS Build
---------
* Coming Soon

License
=======
emojidex and emojidex tools are licensed under the [emojidex Open License](https://www.emojidex.com/emojidex/emojidex_open_license).

©2013 the emojidex project / Genshin Souzou K.K. [Phantom Creation Inc.]
