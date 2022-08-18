# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build

# Include any dependencies generated for this target.
include esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/depend.make

# Include the progress variables for this target.
include esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/flags.make

esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.obj: esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/flags.make
esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.obj: ../components/esp32-MPU-driver/src/MPU.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.obj"
	cd /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver && /root/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.obj -c /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/components/esp32-MPU-driver/src/MPU.cpp

esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.i"
	cd /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver && /root/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/components/esp32-MPU-driver/src/MPU.cpp > CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.i

esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.s"
	cd /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver && /root/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/components/esp32-MPU-driver/src/MPU.cpp -o CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.s

# Object files for target __idf_esp32-MPU-driver
__idf_esp32__MPU__driver_OBJECTS = \
"CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.obj"

# External object files for target __idf_esp32-MPU-driver
__idf_esp32__MPU__driver_EXTERNAL_OBJECTS =

esp-idf/esp32-MPU-driver/libesp32-MPU-driver.a: esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/src/MPU.cpp.obj
esp-idf/esp32-MPU-driver/libesp32-MPU-driver.a: esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/build.make
esp-idf/esp32-MPU-driver/libesp32-MPU-driver.a: esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libesp32-MPU-driver.a"
	cd /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp32-MPU-driver.dir/cmake_clean_target.cmake
	cd /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp32-MPU-driver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/build: esp-idf/esp32-MPU-driver/libesp32-MPU-driver.a

.PHONY : esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/build

esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/clean:
	cd /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp32-MPU-driver.dir/cmake_clean.cmake
.PHONY : esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/clean

esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/depend:
	cd /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/components/esp32-MPU-driver /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver /home/paulo/esp-idf/ESP32_RTC_GYROSCOPE/build/esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esp32-MPU-driver/CMakeFiles/__idf_esp32-MPU-driver.dir/depend

