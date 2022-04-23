# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-src"
  "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-build"
  "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-subbuild/raylib_cpp-populate-prefix"
  "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-subbuild/raylib_cpp-populate-prefix/tmp"
  "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-subbuild/raylib_cpp-populate-prefix/src/raylib_cpp-populate-stamp"
  "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-subbuild/raylib_cpp-populate-prefix/src"
  "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-subbuild/raylib_cpp-populate-prefix/src/raylib_cpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/evan/Projects/Public/Roguelib/testing/build/_deps/raylib_cpp-subbuild/raylib_cpp-populate-prefix/src/raylib_cpp-populate-stamp/${subDir}")
endforeach()
