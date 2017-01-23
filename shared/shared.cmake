#------------------------------------
# Kernel library

#general
SET(SOURCE_FILES_SHARED_LIB
        shared/PSTDFile.cpp
        shared/InvalidationData.cpp
        shared/Colors.cpp
        shared/PSTDFileAccess.cpp
        shared/GeometryImport.cpp)
#export
SET(SOURCE_FILES_SHARED_LIB ${SOURCE_FILES_SHARED_LIB}
        shared/export/Export.cpp shared/export/Image.cpp
        shared/export/HDF5Export.cpp)

add_library(OpenPSTD-shared SHARED ${SOURCE_FILES_SHARED_LIB})

# make sure the functions are hidden by default
set_target_properties(OpenPSTD-shared PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)

# add export header
generate_export_header(OpenPSTD-shared)

# create extra Qt5 code
set_target_properties(OpenPSTD-shared PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON)

target_include_directories(OpenPSTD-shared PUBLIC ${Qt5_INCLUDE_DIRS})
target_include_directories(OpenPSTD-shared PUBLIC unqlite)
target_include_directories(OpenPSTD-shared PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(OpenPSTD-shared PUBLIC ${HDF5_INCLUDE})

target_link_libraries(OpenPSTD-shared OpenPSTD)
target_link_libraries(OpenPSTD-shared unqlite)
target_link_libraries(OpenPSTD-shared ${Qt5_LIBRARIES})
target_link_libraries(OpenPSTD-shared ${HDF5_HL_LIBRARY})
target_link_libraries(OpenPSTD-shared ${HDF5_LIBRARY})
target_link_libraries(OpenPSTD-shared ${Boost_LIBRARIES})
