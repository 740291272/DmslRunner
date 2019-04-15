cmake_minimum_required(VERSION 3.10)


include_directories(Dmsl)

add_executable(DmslRunner
        main.cpp
        Dmsl/DMSLVM.cpp
        Dmsl/DMSLUtils.cpp
        Dmsl/DMSLPrecompiler.cpp
        Dmsl/DMSLCompiler.cpp
        Dmsl/DataActor.cpp
        )

INSTALL(DmslRunner
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION libstatic
)