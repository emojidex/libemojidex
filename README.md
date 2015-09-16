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
6. Simply link against the compiled library to use libemojidex.

Java Native Interface
---------------------

1. Follow steps 1 - 3 from normal build.
2. Run cmake with the JAVA flag set to true:
  ```
  cmake -DJAVA=true ..
  ```
3. Run "make" or compile on your native environment.
4. Optional: run "make jar" to put the resulting JNI library in a JAR file

Objective C Native Interface
----------------------------

**NOTE:** This is for a language level Objective C build, not specifically for iOS.

> Linux Prerequisites: gobjc++ libgnustep-base-dev

1. Follow steps 1 - 3 for normal build.
2. Run cmake with the OBJC flag set to true:
  ```
  cmake -DOBJC=true ..
  ```
3. Run "make" or compile on your native environment.
4. Run "make objc" or build the "objc" profile.

Packaged Builds
===============

Android [NDK] Build
-------------------
**NOTE:** A Ruby script handles compilation of required axiliary libraries and dependencies.  
	You will need Ruby installed and in your path to perform compilation.
1. Install the [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html)
2. Follow steps 1 - 3 from normal build.
3. Run cmake with the ANDROID flag set to true:
  ```
  cmake -DANDROID=true ..
  ```
4. Optional: Run "make" or compile on your native environment. This only creates a static .a libary for ARM.
5. Run "make android". This creates the JNI bindings and compiles so libraries for arm, arm64, x86, x86\_64 and mips.
6. *coming soon*

iOS Build
---------
* Coming Soon

License
=======
emojidex and emojidex tools are licensed under the [emojidex Open License](https://www.emojidex.com/emojidex/emojidex_open_license).

©2013 the emojidex project / Genshin Souzou K.K. [Phantom Creation Inc.]
