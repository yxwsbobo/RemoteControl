# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_BINARY_DIR = D:\ClionProjects\KinRemoteControl\cmake-build-debug

# Include any dependencies generated for this target.
include Source/CommonStruct/CMakeFiles/CommonStruct.dir/depend.make

# Include the progress variables for this target.
include Source/CommonStruct/CMakeFiles/CommonStruct.dir/progress.make

# Include the compile flags for this target's objects.
include Source/CommonStruct/CMakeFiles/CommonStruct.dir/flags.make

Source/CommonStruct/CMakeFiles/CommonStruct.dir/main.cpp.obj: Source/CommonStruct/CMakeFiles/CommonStruct.dir/flags.make
Source/CommonStruct/CMakeFiles/CommonStruct.dir/main.cpp.obj: Source/CommonStruct/CMakeFiles/CommonStruct.dir/includes_CXX.rsp
Source/CommonStruct/CMakeFiles/CommonStruct.dir/main.cpp.obj: ../Source/CommonStruct/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\KinRemoteControl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Source/CommonStruct/CMakeFiles/CommonStruct.dir/main.cpp.obj"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct && C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\CommonStruct.dir\main.cpp.obj -c D:\ClionProjects\KinRemoteControl\Source\CommonStruct\main.cpp

Source/CommonStruct/CMakeFiles/CommonStruct.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CommonStruct.dir/main.cpp.i"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct && C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\KinRemoteControl\Source\CommonStruct\main.cpp > CMakeFiles\CommonStruct.dir\main.cpp.i

Source/CommonStruct/CMakeFiles/CommonStruct.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CommonStruct.dir/main.cpp.s"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct && C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\KinRemoteControl\Source\CommonStruct\main.cpp -o CMakeFiles\CommonStruct.dir\main.cpp.s

# Object files for target CommonStruct
CommonStruct_OBJECTS = \
"CMakeFiles/CommonStruct.dir/main.cpp.obj"

# External object files for target CommonStruct
CommonStruct_EXTERNAL_OBJECTS =

../bin/GNU/Debug/libCommonStruct.a: Source/CommonStruct/CMakeFiles/CommonStruct.dir/main.cpp.obj
../bin/GNU/Debug/libCommonStruct.a: Source/CommonStruct/CMakeFiles/CommonStruct.dir/build.make
../bin/GNU/Debug/libCommonStruct.a: Source/CommonStruct/CMakeFiles/CommonStruct.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ClionProjects\KinRemoteControl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\..\bin\GNU\Debug\libCommonStruct.a"
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct && $(CMAKE_COMMAND) -P CMakeFiles\CommonStruct.dir\cmake_clean_target.cmake
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CommonStruct.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Source/CommonStruct/CMakeFiles/CommonStruct.dir/build: ../bin/GNU/Debug/libCommonStruct.a

.PHONY : Source/CommonStruct/CMakeFiles/CommonStruct.dir/build

Source/CommonStruct/CMakeFiles/CommonStruct.dir/clean:
	cd /d D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct && $(CMAKE_COMMAND) -P CMakeFiles\CommonStruct.dir\cmake_clean.cmake
.PHONY : Source/CommonStruct/CMakeFiles/CommonStruct.dir/clean

Source/CommonStruct/CMakeFiles/CommonStruct.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ClionProjects\KinRemoteControl D:\ClionProjects\KinRemoteControl\Source\CommonStruct D:\ClionProjects\KinRemoteControl\cmake-build-debug D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct D:\ClionProjects\KinRemoteControl\cmake-build-debug\Source\CommonStruct\CMakeFiles\CommonStruct.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Source/CommonStruct/CMakeFiles/CommonStruct.dir/depend

