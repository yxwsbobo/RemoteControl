# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ClionProjects\KinRemoteControl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ClionProjects\KinRemoteControl\cmake-build-release

# Include any dependencies generated for this target.
include Source/RCMaster/CMakeFiles/RCMaster.dir/depend.make

# Include the progress variables for this target.
include Source/RCMaster/CMakeFiles/RCMaster.dir/progress.make

# Include the compile flags for this target's objects.
include Source/RCMaster/CMakeFiles/RCMaster.dir/flags.make

Source/RCMaster/CMakeFiles/RCMaster.dir/RCMaster.cpp.obj: Source/RCMaster/CMakeFiles/RCMaster.dir/flags.make
Source/RCMaster/CMakeFiles/RCMaster.dir/RCMaster.cpp.obj: Source/RCMaster/CMakeFiles/RCMaster.dir/includes_CXX.rsp
Source/RCMaster/CMakeFiles/RCMaster.dir/RCMaster.cpp.obj: ../Source/RCMaster/RCMaster.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\KinRemoteControl\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Source/RCMaster/CMakeFiles/RCMaster.dir/RCMaster.cpp.obj"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\RCMaster.dir\RCMaster.cpp.obj -c D:\ClionProjects\KinRemoteControl\Source\RCMaster\RCMaster.cpp

Source/RCMaster/CMakeFiles/RCMaster.dir/RCMaster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RCMaster.dir/RCMaster.cpp.i"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\KinRemoteControl\Source\RCMaster\RCMaster.cpp > CMakeFiles\RCMaster.dir\RCMaster.cpp.i

Source/RCMaster/CMakeFiles/RCMaster.dir/RCMaster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RCMaster.dir/RCMaster.cpp.s"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\KinRemoteControl\Source\RCMaster\RCMaster.cpp -o CMakeFiles\RCMaster.dir\RCMaster.cpp.s

# Object files for target RCMaster
RCMaster_OBJECTS = \
"CMakeFiles/RCMaster.dir/RCMaster.cpp.obj"

# External object files for target RCMaster
RCMaster_EXTERNAL_OBJECTS =

../bin/GNU/Release/libRCMaster.a: Source/RCMaster/CMakeFiles/RCMaster.dir/RCMaster.cpp.obj
../bin/GNU/Release/libRCMaster.a: Source/RCMaster/CMakeFiles/RCMaster.dir/build.make
../bin/GNU/Release/libRCMaster.a: Source/RCMaster/CMakeFiles/RCMaster.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ClionProjects\KinRemoteControl\cmake-build-release\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\..\bin\GNU\Release\libRCMaster.a"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster && $(CMAKE_COMMAND) -P CMakeFiles\RCMaster.dir\cmake_clean_target.cmake
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RCMaster.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Source/RCMaster/CMakeFiles/RCMaster.dir/build: ../bin/GNU/Release/libRCMaster.a

.PHONY : Source/RCMaster/CMakeFiles/RCMaster.dir/build

Source/RCMaster/CMakeFiles/RCMaster.dir/clean:
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster && $(CMAKE_COMMAND) -P CMakeFiles\RCMaster.dir\cmake_clean.cmake
.PHONY : Source/RCMaster/CMakeFiles/RCMaster.dir/clean

Source/RCMaster/CMakeFiles/RCMaster.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ClionProjects\KinRemoteControl D:\ClionProjects\KinRemoteControl\Source\RCMaster D:\ClionProjects\KinRemoteControl\cmake-build-release D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster D:\ClionProjects\KinRemoteControl\cmake-build-release\Source\RCMaster\CMakeFiles\RCMaster.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Source/RCMaster/CMakeFiles/RCMaster.dir/depend

