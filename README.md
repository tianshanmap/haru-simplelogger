# How to write a dynamic library in C++ containing a variadic template function.
When a C++ variadic function (or template) is "not in the dylib" 
(resulting in a linker error like undefined reference), 
it usually means the compiler couldn't generate the specific function code during the build process.
## The Cause
Templates are not code yet: If you are using C++ variadic templates 
(template<typename... Args>), they are just blueprints. 
The compiler cannot put them into a compiled .dylib or .so file unless a specific type is used in that exact .cpp file.
Not in the Header: 
If the template implementation is hidden away in a .cpp file instead of fully defined in the .h/.hpp header file, 
the compiler won't be able to instantiate it 
when compiling other parts of your project.

## To fix
Move the Implementation to the HeaderYou must place the entire definition 
(not just the declaration) of your variadic template function inside the header file. 
This allows the compiler to generate the code for whatever types are used wherever the header is included.

# How to use the simeplelogger library
## CmakeLists.txt
```
include(FetchContent)
FetchContent_Declare(
        simplelogger
        GIT_REPOSITORY https://github.com/tianshanmap/haru-simplelogger.git
        GIT_TAG main # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_MakeAvailable(simplelogger)
target_link_libraries(opencv-web simplelogger)

```
## cpp source code
```aiignore
#include <simplelogger/simplelogger.hpp>
```
## inspect a dylib on mac
```aiignore
developer@Mac cmake-build-debug % nm -l libsimplelogger.dylib 
0000000000001030 T __ZN4haru12SimpleLogger12getTimestampEv
00000000000010f8 T __ZN4haru12SimpleLogger3addEii
0000000000001140 T __ZN4haru12SimpleLogger6recordENSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEi
00000000000011d4 t __ZNSt3__111char_traitsIcE6lengthB8ne200100EPKc
                 U __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm
00000000000010c4 t __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1B8ne200100ILi0EEEPKc
0000000000001158 t __ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne200100ILi0EEEPKc
0000000000001224 t __ZNSt3__116__non_trivial_ifILb1ENS_9allocatorIcEEEC2B8ne200100Ev
0000000000001238 t __ZNSt3__118__constexpr_strlenB8ne200100IcEEmPKT_
00000000000011a8 t __ZNSt3__19allocatorIcEC1B8ne200100Ev
00000000000011f8 t __ZNSt3__19allocatorIcEC2B8ne200100Ev
                 U ___stack_chk_fail
                 U ___stack_chk_guard
                 U _localtime
                 U _strftime
                 U _strlen
                 U _time
```
