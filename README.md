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
