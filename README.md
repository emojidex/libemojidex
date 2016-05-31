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
  git submodule update --init --recursive
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
5. Build with `make` on \*nix or import into your IDE and build.
6. Simply link against the compiled library to use libemojidex.

Specs and Testing
-----------------

libemojidex features a full spec suite. Simply ```make test``` or, after building, run 
```./spec/libemojidex_spec```. For detailed output you can call with ```--log_level=message``` 
like ```./spec/libemojidex_spec --log_level=message```.

If you wish to test premium only endpoints or options, such as the 'newest' and 'popular' indexes 
you must prefix the test command with "EMOJIDEX_AUTH_TOKEN=1234567890abcdef", replacing the 
numbers with your auth_token (which can be found in your user settings on emojidex.com). Free 
premium accounts are available for anyone working on emojidex code or integrating clients into 
their software - simply e-mail info@emojidex.com with your username and a short description of 
what you are working on.

Java Native Interface
---------------------

1. Follow steps 1 - 3 from normal build.
2. Run cmake with the JAVA flag set to true:
  ```
  cmake -DJAVA=true ..
  ```
3. Run `make` or compile on your native environment.
4. Optional: run `make jar` to put the resulting JNI library in a JAR file

Android [NDK] Build
-------------------
**WARNING:** Due to incompatibilities in either the Android build system or Dalvik VM, and Android 
build requires Java 7. Building with Java 8 seems to result in a variety of compatibility issues. 
Google reports Java 8 compatibility to be a work in progress - so this warning may at some point 
be invalid. If you try Java 8 and successfully build, please submit an issue informing us.

**NOTE:** A Ruby script handles compilation of required auxiliary libraries and dependencies.  
You will need Ruby installed and in your path to perform compilation.

1. You must use the CrystaX NDK. The standard Android NDK lacks too many features. You can obtain 
the CrystaX NDK from [here](https://www.crystax.net/android/ndk).
2. Follow steps 1 - 3 from normal build.
3. Run cmake with the ANDROID flag set to true:
  ```
  cmake -DANDROID=true ..
  ```
4. Run `make`. This will only generate a static ARM library which will not be very useful on its 
own, but will also prime the build system for the next step.
5. Run `make android`. This creates the JNI bindings and compiles so libraries for arm, x86 and 
mips. You can bundle these raw sources and generated libraries in your app *OR* more conveniently 
build and bundle a JAR in step 6.
6. *Optional* run `make android_jar` to bundle all generated sources and libraries into an 
easy-to-use JAR.

Objective C Native Interface
----------------------------

**NOTE:** This is for a language level Objective C build, not specifically for iOS.

> Linux Prerequisites: gobjc++ libgnustep-base-dev

1. Follow steps 1 - 3 for normal build.
2. Run cmake with the OBJC flag set to true:
  ```
  cmake -DOBJC=true ..
  ```
3. Run `make` or compile on your native environment.
4. Run `make objc` or build the `objc` profile.

iOS Build
---------
* Coming Soon

Other Languages
===============
Some languages can be rolled out of the box with SWIG that we have not yet ported to. If you 
would like us to port to a specific language please post an issue on GitHub.

Ruby
----
Due to deficiencies in the Ruby implementation of SWIG and in order to avoid complexities 
of native compilation on varied environments, Ruby interfaces are provided by the "emojidex" gem 
in pure Ruby. See [emojidex/emojidex](https://github.com/emojidex/emojidex).

JavaScript / CoffeeScript
-------------------------
JS is a strange beast for natives and generally we don't see much usage for libemojidex-like 
functionality in JS. Instead we developed a light-weight component/module based implementation 
called [emojidex-web-client](https://github.com/emojidex/emojidex-web-client). If you want to a 
full set of tools to implement emojidex on your web site or in your JavaScript app check out 
[emojidex-web](https://github.com/emojidex/emojidex-web) which has a variety of front end tools 
and widgets and wraps the client in such a way that you have access to it, but don't actually 
need to directly deal with it.

License
=======
emojidex and emojidex tools are licensed under the [emojidex Open License](https://www.emojidex.com/emojidex/emojidex_open_license).

©2013 the emojidex project / Genshin Souzou K.K. [Phantom Creation Inc.]
