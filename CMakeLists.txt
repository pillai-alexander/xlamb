cmake_minimum_required(VERSION 3.21)

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  xlamb
  VERSION 0.0.1
  DESCRIPTION "eXtensible Lazt Agent-based Model Builder"
  LANGUAGES CXX
)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project-level options
option(XLAMB_WARNINGS_AS_ERRORS         "Build with warnings treated as errors" OFF)
option(XLAMB_PEDANTIC_WARNINGS          "Build with as many reasonable warnings enabled" OFF)
option(XLAMB_ENABLE_CLANG_TIDY          "Enable clang-tidy support" OFF)
option(XLAMB_ENABLE_CPPCHECK            "Enable cppcheck support" OFF)
option(XLAMB_ENABLE_SANITIZER_ADDRESS   "Enable address sanitizer" OFF)
option(XLAMB_ENABLE_SANITIZER_LEAK      "Enable leak sanitizer" OFF)
option(XLAMB_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
option(XLAMB_ENABLE_SANITIZER_MEMORY    "Enable memory sanitizer" OFF)
option(XLAMB_ENABLE_TESTS               "Build with tests" OFF)

if(PROJECT_IS_TOP_LEVEL)
  set(XLAMB_WARNINGS_AS_ERRORS ON)
  set(XLAMB_PEDANTIC_WARNINGS ON)
  # set(XLAMB_ENABLE_CLANG_TIDY ON)
  # set(XLAMB_ENABLE_CPPCHECK ON)
  # set(XLAMB_ENABLE_SANITIZER_ADDRESS ON)
  # set(XLAMB_ENABLE_SANITIZER_LEAK ON)
  # set(XLAMB_ENABLE_SANITIZER_UNDEFINED ON)
  # set(XLAMB_ENABLE_TESTS ON)
endif()

include(cmake/CPM.cmake)

CPMAddPackage("gh:gabime/spdlog@1.15.0")
# CPMAddPackage("gh:CLIUtils/CLI11@2.4.2")
# CPMAddPackage("gh:google/googletest@1.15.2")

# If the environment has these set, pull them into proper variables.
set(CLANG_WARNINGS ${CLANG_COMPILE_FLAGS})
set(GCC_WARNINGS   ${GCC_COMPILE_FLAGS})

if(XLAMB_WARNINGS_AS_ERRORS)
  list(APPEND CLANG_WARNINGS -Werror)
  list(APPEND GCC_WARNINGS -Werror)
endif()

if(XLAMB_PEDANTIC_WARNINGS)
  list(APPEND CLANG_WARNINGS
    -Wall
    -Wextra # reasonable and standard
    -Wshadow # warn the user if a variable declaration shadows one from a parent context
    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
    -Wold-style-cast # warn for c-style casts
    -Wcast-align # warn for potential performance problem casts
    -Wunused # warn on anything being unused
    -Woverloaded-virtual # warn if you overload (not override) a virtual function
    -Wpedantic # warn if non-standard C++ is used
    -Wconversion # warn on type conversions that may lose data
    -Wsign-conversion # warn on sign conversions
    -Wnull-dereference # warn if a null dereference is detected
    -Wdouble-promotion # warn if float is implicit promoted to double
    -Wformat=2 # warn on security issues around functions that format output (ie printf)
    -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
    -fcolor-diagnostics
  )

  list(APPEND GCC_WARNINGS
    -Wall
    -Wextra # reasonable and standard
    -Wshadow # warn the user if a variable declaration shadows one from a parent context
    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
    -Wold-style-cast # warn for c-style casts
    -Wcast-align # warn for potential performance problem casts
    -Wunused # warn on anything being unused
    -Woverloaded-virtual # warn if you overload (not override) a virtual function
    -Wpedantic # warn if non-standard C++ is used
    -Wconversion # warn on type conversions that may lose data
    -Wsign-conversion # warn on sign conversions
    -Wnull-dereference # warn if a null dereference is detected
    -Wdouble-promotion # warn if float is implicit promoted to double
    -Wformat=2 # warn on security issues around functions that format output (ie printf)
    -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
    -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
    -Wduplicated-cond # warn if if / else chain has duplicated conditions
    -Wduplicated-branches # warn if if / else branches have duplicated code
    -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    -Wuseless-cast # warn if you perform a cast to the same type
    -Wsuggest-override # warn if an overridden member function is not marked 'override' or 'final'
    -fdiagnostics-color=always
  )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:${CLANG_WARNINGS}>")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:${GCC_WARNINGS}>")
endif()

if(XLAMB_ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    # construct the clang-tidy command line
    set(CLANG_TIDY_OPTIONS
      ${CLANGTIDY}
      -extra-arg=-Wno-unknown-warning-option
      -extra-arg=-Wno-ignored-optimization-argument
      -extra-arg=-Wno-unused-command-line-argument
      -p
      -extra-arg=-std=c++${CMAKE_CXX_STANDARD}
    )

    # set warnings as errors
    if(XLAMB_WARNINGS_AS_ERRORS)
      list(APPEND CLANG_TIDY_OPTIONS -warnings-as-errors=*)
    endif()

    message("-- Also setting clang-tidy globally")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_OPTIONS})
  else()
    message(${WARNING_MESSAGE} "clang-tidy requested but executable not found")
  endif()
endif()

if(XLAMB_ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    set(SUPPRESS_DIR "*:${CMAKE_CURRENT_BINARY_DIR}/_deps/*.h")
    message(STATUS "CPPCHECK_OPTIONS suppress: ${SUPPRESS_DIR}")

    set(CPPCHECK_TEMPLATE "gcc")
    set(CMAKE_CXX_CPPCHECK
      ${CPPCHECK}
      --template=${CPPCHECK_TEMPLATE}
      --enable=style,performance,warning,portability
      --inline-suppr
      # We cannot act on a bug/missing feature of cppcheck
      --suppress=cppcheckError
      --suppress=internalAstError
      # if a file does not have an internalAstError, we get an unmatchedSuppression error
      --suppress=unmatchedSuppression
      # noisy and incorrect sometimes
      --suppress=passedByValue
      # ignores code that cppcheck thinks is invalid C++
      --suppress=syntaxError
      --suppress=preprocessorErrorDirective
      --inconclusive
      --suppress=${SUPPRESS_DIR}
      --std=c++${CMAKE_CXX_STANDARD}
    )

    if(XLAMB_WARNINGS_AS_ERRORS)
      list(APPEND CMAKE_CXX_CPPCHECK --error-exitcode=2)
    endif()
  else()
    message(${WARNING_MESSAGE} "cppcheck requested but executable not found")
  endif()
endif()

if(XLAMB_ENABLE_SANITIZER_ADDRESS
   OR XLAMB_ENABLE_SANITIZER_LEAK
   OR XLAMB_ENABLE_SANITIZER_MEMORY
   OR XLAMB_ENABLE_SANITIZER_UNDEFINED)
  set(SANITIZERS "")

  if(XLAMB_ENABLE_SANITIZER_ADDRESS)
    list(APPEND SANITIZERS "address")
  endif()

  if(XLAMB_ENABLE_SANITIZER_LEAK)
    list(APPEND SANITIZERS "leak")
  endif()

  if(XLAMB_ENABLE_SANITIZER_UNDEFINED)
    list(APPEND SANITIZERS "undefined")
  endif()

  if(XLAMB_ENABLE_SANITIZER_MEMORY)
    if("address" IN_LIST SANITIZERS OR "leak" IN_LIST SANITIZERS)
      message(WARNING "Memory sanitizer does not work with Address or Leak sanitizer enabled")
    else()
      list(APPEND SANITIZERS "memory")
    endif()
  endif()

  list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)

  if(LIST_OF_SANITIZERS)
    if(NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
      add_compile_options(-fsanitize=${LIST_OF_SANITIZERS})
      add_link_options(-fsanitize=${LIST_OF_SANITIZERS})
    endif()
  endif()
endif()

add_subdirectory(src)

include(CTest)

if(XLAMB_ENABLE_TESTS AND PROJECT_IS_TOP_LEVEL)
  message("-- Building tests")
  add_subdirectory(test)
endif()