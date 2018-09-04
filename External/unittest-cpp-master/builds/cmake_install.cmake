# Install script for directory: D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/UnitTest++")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/Debug/UnitTest++.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/Release/UnitTest++.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/MinSizeRel/UnitTest++.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/RelWithDebInfo/UnitTest++.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++" TYPE FILE FILES
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/AssertException.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/CheckMacros.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/Checks.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/CompositeTestReporter.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/Config.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/CurrentTest.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/DeferredTestReporter.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/DeferredTestResult.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/ExceptionMacros.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/ExecuteTest.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/HelperMacros.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/MemoryOutStream.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/ReportAssert.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/ReportAssertImpl.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/RequireMacros.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/RequiredCheckException.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/RequiredCheckTestReporter.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/Test.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestDetails.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestList.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestMacros.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestReporter.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestReporterStdout.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestResults.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestRunner.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestSuite.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/ThrowingTestReporter.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TimeConstraint.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/TimeHelpers.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/UnitTest++.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/UnitTestPP.h"
    "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/XmlTestReporter.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++/Win32" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/UnitTest++/Win32/TimeHelpers.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/cmake/UnitTest++Config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++/UnitTest++Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++/UnitTest++Targets.cmake"
         "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/CMakeFiles/Export/lib/cmake/UnitTest++/UnitTest++Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++/UnitTest++Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++/UnitTest++Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/CMakeFiles/Export/lib/cmake/UnitTest++/UnitTest++Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/CMakeFiles/Export/lib/cmake/UnitTest++/UnitTest++Targets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/CMakeFiles/Export/lib/cmake/UnitTest++/UnitTest++Targets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/CMakeFiles/Export/lib/cmake/UnitTest++/UnitTest++Targets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/UnitTest++" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/CMakeFiles/Export/lib/cmake/UnitTest++/UnitTest++Targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files/UnitTest++/lib/pkgconfig/UnitTest++.pc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Program Files/UnitTest++/lib/pkgconfig" TYPE FILE FILES "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/UnitTest++.pc")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Library/Documents/Job/Forschungsmaster/Projekte/EyeCandy3D/External/unittest-cpp-master/builds/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
