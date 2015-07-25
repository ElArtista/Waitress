![ProjectBanner][banner]
# Waitress

A templated C++ resource manager library for every need

## <a name="toc"/> Table of Contents
 * [Table Of Contents](#toc)
 * [Team Members](#team)
 * [Requirements](#requirements)
 * [Usage](#usage)
 * [Building the Samples](#building)
 * [Changelog](#changelog)
 * [Contributing](#contributing)
 * [Licensing](#licensing)

## <a name="team"/> Team Members
 * "Agorgianitis Loukas" <agorglouk@gmail.com>

## <a name="requirements"/> Requirements
 * For using the library any modern C++ compiler with decent C++11 support must be used
 * For building the samples, Python 2.7 is required

## <a name="usage"/> Usage
 * TODO

## <a name="building"/> Building
 1. Clone the project and cd to the directory of the sample you want to build.
 2. Run:  
    ```
    python waf distclean configure --check-c-compiler=<CC> --check-cxx-compiler=<CXX>
    ```  
    where CC and CXX combination can either be {msvc,msvc} | {gcc, g++} | {clang, clang++} and after that run:  
    ```
    python waf clean build install --variant=<VARIANT> --arch=<ARCH>
    ```  
    where VARIANT can be either Release|Debug and ARCH can be either x86|x64.
 3. Built binaries will reside in the ```bin\<ARCH>\<VARIANT>``` subdirectory of the sample directory.

## <a name="changelog"/> Change Log
 * TODO: Track Major release history after first release

## <a name="contributing"/> Contributing
 * For bug fixes, any well checked pull requests are welcome

## <a name="licensing"/> Licensing
Read [LICENSE](LICENSE.md)  

Copyright (C) 2015 Agorgianitis Loukas <agorglouk@gmail.com>  
All rights reserved.

[banner]: doc/assets/Logo.png
