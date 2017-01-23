#------------------------------------
# Test

# Source files of the CLI and GUI(no Kernel and no Shared, they are linked)
set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST} ${SOURCE_FILES_GUI} ${SOURCE_FILES_CLI})

set(SOURCE_FILES_TEST_DG
        test/Kernel/DG/DG.cpp
        test/Kernel/DG/DG2D.cpp
        test/Kernel/DG/Advec.cpp
        test/Kernel/DG/Maxwell.cpp
        test/Kernel/DG/LEE.cpp
        test/Kernel/DG/LEE2D.cpp
        test/Kernel/DG/JacobiGQ.cpp
        test/Kernel/DG/JacobiGL.cpp
        test/Kernel/DG/JacobiP.cpp
        test/Kernel/DG/WarpFactor.cpp
        test/Kernel/DG/Vandermonde.cpp
        test/Kernel/DG/DMatrix.cpp
        test/Kernel/DG/GeometricFactors.cpp
        test/Kernel/DG/Lift.cpp
        test/Kernel/DG/Simplex.cpp
        test/Kernel/DG/Coordinates.cpp
        test/Kernel/DG/Nodes.cpp
        test/Kernel/DG/Grad.cpp
        )

#set(SOURCE_FILES_TEST_DG test/Kernel/DG/DG2D.cpp test/Kernel/DG/LEE2D.cpp)

message(STATUS "${DG_TEST_ONLY}")
if(DG_TEST_ONLY)
    message(WARNING "DG only")
    #only DG tests
    set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST_DG})
else()
    if(OPENPSTD_TEST_FILE)
        message(STATUS "Test file: ${OPENPSTD_TEST_FILE}")
        # the single test file that must be compiled
        set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST} ${OPENPSTD_TEST_FILE})
    else()
        message(STATUS "Test file: ALL")

        # Shared test files
        set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST} test/Shared/GeometryImport.cpp )
        # GUI test files
        set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST} test/GUI/Edges-test.cpp test/GUI/LongOperationRunner-test.cpp)
        # Kernel test files
        set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST}
                test/Kernel/kernel_functions.cpp
                test/Kernel/Speaker.cpp
                test/Kernel/Scene.cpp
                test/Kernel/Geometry.cpp
                test/Kernel/Domain.cpp
                test/Kernel/WisdomCache.cpp)
        # DG test files
        set(SOURCE_FILES_TEST ${SOURCE_FILES_TEST} ${SOURCE_FILES_TEST_DG})
    endif()
endif()

add_executable(OpenPSTD-test test/main.cpp ${SOURCE_FILES_TEST})

if(NOT ${DG_TEST_ONLY})
    # create extra Qt5 code
    set_target_properties(OpenPSTD-test
            PROPERTIES AUTOMOC ON
            AUTOUIC ON
            AUTORCC ON)
endif()

target_include_directories(OpenPSTD-test PUBLIC ${Qt5_INCLUDE_DIRS})
target_include_directories(OpenPSTD-test PUBLIC unqlite)
target_include_directories(OpenPSTD-test PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(OpenPSTD-test PUBLIC ${EIGEN_INCLUDE})
target_include_directories(OpenPSTD-test PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(OpenPSTD-test OpenPSTD)
target_link_libraries(OpenPSTD-test OpenPSTD-shared)
target_link_libraries(OpenPSTD-test ${Boost_LIBRARIES})
target_link_libraries(OpenPSTD-test ${Qt5_LIBRARIES})
target_link_libraries(OpenPSTD-test unqlite)
target_link_libraries(OpenPSTD-test ${OPENGL_LIBRARIES})
