set(LIB_NAME_BASE oapv)

file(GLOB LIB_INC "../inc/*.h")
file(GLOB LIB_API_SRC "oapv.c")
file(GLOB LIB_BASE_SRC "oapv_*.c")
file(GLOB LIB_BASE_INC "oapv_*.h" )
file(GLOB LIB_SSE_SRC "../src/sse/oapv_*.c")
file(GLOB LIB_SSE_INC "../src/sse/oapv_*.h" )
file(GLOB LIB_NEON_SRC "../src/neon/oapv_*.c")
file(GLOB LIB_NEON_INC "../src/neon/oapv_*.h" )
file(GLOB LIB_AVX_SRC "../src/avx/oapv_*.c")
file(GLOB LIB_AVX_INC "../src/avx/oapv_*.h" )

include(GenerateExportHeader)

# Create an interface library for common dependencies and compile definitions
add_library(${LIB_NAME_BASE}_interface INTERFACE)

# Set common interface properties
target_include_directories(${LIB_NAME_BASE}_interface INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../inc>
  $<INSTALL_INTERFACE:include>
)

# Add common compile definitions to interface
target_compile_definitions(${LIB_NAME_BASE}_interface INTERFACE
  $<$<BOOL:${ARM}>:ARM=1>
  $<$<BOOL:${X86}>:X86=1>
  $<$<BOOL:${UNIVERSAL}>:UNIVERSAL=1>
  $<$<PLATFORM_ID:Linux>:LINUX>
  $<$<PLATFORM_ID:Darwin>:MACOS>
  $<$<PLATFORM_ID:Windows>:WINDOWS>
)

# Add math library dependency for Unix-like systems
if(UNIX OR MINGW)
  target_link_libraries(${LIB_NAME_BASE}_interface INTERFACE m)
endif()


message("SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" lowercase_CMAKE_SYSTEM_PROCESSOR)

if(${lowercase_CMAKE_SYSTEM_PROCESSOR} MATCHES "^(arm|aarch)")
  message("  ARM processor")
  #  add_definitions(-mfloat-abi=softfp -mfpu=neon)
  add_definitions(-DARM=1)
  set(ARM "TRUE")
elseif(${lowercase_CMAKE_SYSTEM_PROCESSOR} MATCHES "^(x86|ia64|i386|i686|amd64)")
  message("  X86 processor")
  add_definitions(-DX86=1)
  set(X86 "TRUE")
endif()

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "64")
  message("  64-bit")
  add_compile_definitions(_IS64BIT)
endif()

if(ARM)
  set(SOURCE_FILES ${LIB_API_SRC} ${LIB_INC} ${LIB_BASE_SRC} ${LIB_BASE_INC} ${LIB_NEON_SRC} ${LIB_NEON_INC})
elseif(UNIVERSAL)
  set(SOURCE_FILES ${LIB_API_SRC} ${LIB_INC} ${LIB_BASE_SRC} ${LIB_BASE_INC} ${LIB_SSE_SRC} ${LIB_SSE_INC} ${LIB_AVX_SRC} ${LIB_AVX_INC} ${LIB_NEON_SRC} ${LIB_NEON_INC})
elseif(X86)
  set(SOURCE_FILES ${LIB_API_SRC} ${LIB_INC} ${LIB_BASE_SRC} ${LIB_BASE_INC} ${LIB_SSE_SRC} ${LIB_SSE_INC} ${LIB_AVX_SRC} ${LIB_AVX_INC})
else()
  set(SOURCE_FILES ${LIB_API_SRC} ${LIB_INC} ${LIB_BASE_SRC} ${LIB_BASE_INC})
endif()

if(OAPV_BUILD_STATIC_LIB)
  add_library(${LIB_NAME_BASE} STATIC ${SOURCE_FILES})

  # Link to interface library for common dependencies
  target_link_libraries(${LIB_NAME_BASE} PUBLIC ${LIB_NAME_BASE}_interface)

  # This will cause the export macros to expand to nothing when building the static library.
  target_compile_definitions(${LIB_NAME_BASE} PUBLIC OAPV_STATIC_DEFINE)

  set_target_properties(${LIB_NAME_BASE} PROPERTIES FOLDER lib
                                                    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

  # Set target-specific include directories using modern CMake with generator expressions
  target_include_directories(${LIB_NAME_BASE} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../inc>
    $<$<BOOL:${ARM}>:$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/neon>>
    $<$<BOOL:${X86}>:$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sse>>
    $<$<BOOL:${X86}>:$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/avx>>
    $<INSTALL_INTERFACE:include>
  )
endif()

if(OAPV_BUILD_SHARED_LIB)
  add_library(${LIB_NAME_BASE}_dynamic SHARED ${SOURCE_FILES})
  
  # Link to interface library for common dependencies
  target_link_libraries(${LIB_NAME_BASE}_dynamic PUBLIC ${LIB_NAME_BASE}_interface)
  
  set_target_properties(${LIB_NAME_BASE}_dynamic PROPERTIES VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} SOVERSION ${VERSION_MAJOR})
  set_target_properties(${LIB_NAME_BASE}_dynamic PROPERTIES OUTPUT_NAME ${LIB_NAME_BASE})

  # @todo Consider using WINDOWS_EXPORT_ALL_SYMBOLS instead of generate_export_header
  # @see https://cmake.org/cmake/help/latest/prop_tgt/WINDOWS_EXPORT_ALL_SYMBOLS.html#prop_tgt:WINDOWS_EXPORT_ALL_SYMBOLS
  #if(MSVC)
    # @see https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
    # @see https://cmake.org/cmake/help/v3.3/module/GenerateExportHeader.html
    #
    #set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    #set(BUILD_SHARED_LIBS TRUE)
  #endif()

  # Generate export macros for libraries
  generate_export_header(${LIB_NAME_BASE}_dynamic
                         BASE_NAME OAPV
                         EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/oapv/oapv_exports.h)

  # Set target-specific include directories using modern CMake with generator expressions
  target_include_directories(${LIB_NAME_BASE}_dynamic PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../inc>
    $<$<BOOL:${ARM}>:$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/neon>>
    $<$<BOOL:${X86}>:$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sse>>
    $<$<BOOL:${X86}>:$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/avx>>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
endif()

source_group("base\\header" FILES ${LIB_BASE_INC} ${LIB_INC})
source_group("base\\source" FILES ${LIB_BASE_SRC} ${LIB_API_SRC})
source_group("base\\sse\\header" FILES ${LIB_SSE_INC})
source_group("base\\sse\\source" FILES ${LIB_SSE_SRC})
source_group("base\\neon\\header" FILES ${LIB_NEON_INC})
source_group("base\\neon\\source" FILES ${LIB_NEON_SRC})
source_group("base\\avx\\header" FILES ${LIB_AVX_INC})
source_group("base\\avx\\source" FILES ${LIB_AVX_SRC})

set(SSE ${LIB_SSE_SRC})
set(AVX ${LIB_AVX_SRC})
set(NEON ${LIB_NEON_SRC} ${LIB_NEON_INC})

# Apply target-specific compiler flags using modern CMake
if(OAPV_BUILD_STATIC_LIB)
  if(MSVC)
    target_compile_definitions(${LIB_NAME_BASE} PUBLIC ANY _CRT_SECURE_NO_WARNINGS)
  elseif(UNIX OR MINGW)
    if (ARM)
      target_compile_options(${LIB_NAME_BASE} PRIVATE $<$<COMPILE_LANGUAGE:C>:-flax-vector-conversions>)
    elseif (X86 OR UNIVERSAL)
      target_compile_options(${LIB_NAME_BASE} PRIVATE 
        $<$<COMPILE_LANGUAGE:C>:-msse4.1>
        $<$<COMPILE_LANGUAGE:C>:-mavx2>
      )
    endif()

    if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
      target_compile_definitions(${LIB_NAME_BASE} PUBLIC ANY MACOS)
    else()
      target_compile_definitions(${LIB_NAME_BASE} PUBLIC ANY LINUX)
    endif()
  endif()
endif()

if(OAPV_BUILD_SHARED_LIB)
  if(MSVC)
    target_compile_definitions(${LIB_NAME_BASE}_dynamic PUBLIC ANY _CRT_SECURE_NO_WARNINGS)
    set_target_properties(${LIB_NAME_BASE}_dynamic PROPERTIES FOLDER lib
                                                              RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  elseif(UNIX OR MINGW)
    if (ARM)
      target_compile_options(${LIB_NAME_BASE}_dynamic PRIVATE $<$<COMPILE_LANGUAGE:C>:-flax-vector-conversions>)
    elseif (X86 OR UNIVERSAL)
      target_compile_options(${LIB_NAME_BASE}_dynamic PRIVATE 
        $<$<COMPILE_LANGUAGE:C>:-msse4.1>
        $<$<COMPILE_LANGUAGE:C>:-mavx2>
      )
    endif()

    set_target_properties(${LIB_NAME_BASE}_dynamic PROPERTIES FOLDER lib
                                                              LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  endif()
endif()

# Install rules
#
# Set DCMAKE_INSTALL_PREFIX to change default install prefix
# e.g cmake .. -DSET_PROF=BASE -DCMAKE_INSTALL_PREFIX='/home/user/bin/'
include(GNUInstallDirs)

# List the headers we want to declare as public for installation.
set(OAPV_PUBLIC_HEADERS "${LIB_INC}")
set(OAPV_PRIVATE_HEADERS "${LIB_BASE_INC}" "${LIB_SSE_INC}" "${LIB_AVX_INC}" "${LIB_NEON_INC}")

# Install static library and public headers
#
# Static library (liboapv.a or oapv.lib) will be installed to <prefix>/lib/oapv
# Public headers will be installed to <prefix>/include/oapv
#
if(OAPV_BUILD_STATIC_LIB)
  set_target_properties(${LIB_NAME_BASE} PROPERTIES PUBLIC_HEADER "${OAPV_PUBLIC_HEADERS}")
  install(TARGETS ${LIB_NAME_BASE}
          ARCHIVE COMPONENT Development DESTINATION ${CMAKE_INSTALL_LIBDIR}/${LIB_NAME_BASE}
          PUBLIC_HEADER COMPONENT Development DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME_BASE}
  )
endif()

# Install shared library
#
# On non-DLL platforms shared library (liboapv.so) will be installed to <prefix>/lib/oapv.
# On DLL platforms the shred DLL (oapv.dll) will be installed to <prefix>/bin and its import library will be installed to <prefix>/lib/oapv/import
#
if(OAPV_BUILD_SHARED_LIB)
  set_target_properties(${LIB_NAME_BASE}_dynamic PROPERTIES PUBLIC_HEADER "${OAPV_PUBLIC_HEADERS}")
  install(TARGETS ${LIB_NAME_BASE}_dynamic
          RUNTIME COMPONENT Libraries DESTINATION ${CMAKE_INSTALL_BINDIR}
          LIBRARY
            COMPONENT Libraries DESTINATION ${CMAKE_INSTALL_LIBDIR}
            NAMELINK_COMPONENT Development DESTINATION ${CMAKE_INSTALL_LIBDIR}
          ARCHIVE COMPONENT Development DESTINATION ${CMAKE_INSTALL_LIBDIR}/${LIB_NAME_BASE}/import
          PUBLIC_HEADER COMPONENT Development DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME_BASE}
  )

  install(FILES
    ${PROJECT_BINARY_DIR}/include/oapv/oapv_exports.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME_BASE}
  )
endif()

if(NOT MSVC)
    if(OAPV_BUILD_SHARED_LIB)
        set(EXTRA_CFLAGS "")
        set(EXTRA_CFLAGS_PRIVATE "-DOAPV_STATIC_DEFINE")
    else()
        set(EXTRA_CFLAGS "-DOAPV_STATIC_DEFINE")
        set(EXTRA_CFLAGS_PRIVATE "")
    endif()
    configure_file(
      "${CMAKE_SOURCE_DIR}/pkgconfig/${LIB_NAME_BASE}.pc.in"
      "${CMAKE_BINARY_DIR}/${LIB_NAME_BASE}.pc" @ONLY)

    install(FILES
      "${CMAKE_BINARY_DIR}/${LIB_NAME_BASE}.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    )
endif()
