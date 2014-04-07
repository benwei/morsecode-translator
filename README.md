# Morse Code Translator
This is a morse code library and command line tool written in C with C99 compatible.

## tested platform
* debian 7.0 i386 with gcc version 4.7.2 (Debian 4.7.2-5)
* osx 10.9.2 with Apple LLVM version 5.1 (clang-503.0.38)

## HowTo

* support built-in C compiler

 ```
 make
 ```

* build with CROSS_COMPILE

 ```
 make CROSS_COMPILE=arm-linux-gnueabihf- 
 ```

* tests
 - if you build on host, the build script will also trigger the tests

 - run tests only


 ```
 make tests
 ```
* samples

 - cli input sample
 
 ```
    ./morse "`cat input_sample.txt`"

 ````
 - output:

 ````
 HELLO/WORLD
 ````

## License
* [The BSD 2-Clause License](http://opensource.org/licenses/BSD-2-Clause)

