# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Rood_Zwarte_Bomen.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Rood_Zwarte_Bomen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Rood_Zwarte_Bomen.dir/flags.make

CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.o: CMakeFiles/Rood_Zwarte_Bomen.dir/flags.make
CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.o -c "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/main.cpp"

CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/main.cpp" > CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.i

CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/main.cpp" -o CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.s

# Object files for target Rood_Zwarte_Bomen
Rood_Zwarte_Bomen_OBJECTS = \
"CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.o"

# External object files for target Rood_Zwarte_Bomen
Rood_Zwarte_Bomen_EXTERNAL_OBJECTS =

Rood_Zwarte_Bomen: CMakeFiles/Rood_Zwarte_Bomen.dir/main.cpp.o
Rood_Zwarte_Bomen: CMakeFiles/Rood_Zwarte_Bomen.dir/build.make
Rood_Zwarte_Bomen: CMakeFiles/Rood_Zwarte_Bomen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Rood_Zwarte_Bomen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Rood_Zwarte_Bomen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Rood_Zwarte_Bomen.dir/build: Rood_Zwarte_Bomen

.PHONY : CMakeFiles/Rood_Zwarte_Bomen.dir/build

CMakeFiles/Rood_Zwarte_Bomen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Rood_Zwarte_Bomen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Rood_Zwarte_Bomen.dir/clean

CMakeFiles/Rood_Zwarte_Bomen.dir/depend:
	cd "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen" "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen" "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/cmake-build-debug" "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/cmake-build-debug" "/Users/arneverhaeghe/Documents/IW 4/IW 4/Semester 1/Algoritmen II/git/ogla2/Arne/01_Rood-Zwarte-Bomen/cmake-build-debug/CMakeFiles/Rood_Zwarte_Bomen.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Rood_Zwarte_Bomen.dir/depend

