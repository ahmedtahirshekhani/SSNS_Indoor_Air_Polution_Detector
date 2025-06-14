# Set the project name for this submodule (optional, just for organization)
project(sps30_driver)

# Specify the language standard (using C11 in this case)
set(CMAKE_C_STANDARD 11)

# Include Zephyr modules and toolchain
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Include necessary directories for header files
# We add the current directory and the 'sensirion' directory which is in the same folder
target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # Current directory where the CMakeLists.txt resides
    ${CMAKE_CURRENT_SOURCE_DIR}/sensirion  # Directory containing sensirion_common.h and sensirion_i2c.h
)

# Add the source files for the SPS30 driver
# Ensure these files are listed correctly in your project
target_sources(app PRIVATE
    sps30.c               # Main source file for the SPS30 sensor
    sensirion_common.c    # Common code for sensor communication
    sensirion_i2c.c       # I2C-specific code for sensor communication
    sensirion_hw_i2c_implementation.c
)

# Include any necessary configuration files (optional, if required)
target_sources(app PRIVATE
    default_config.inc    # Sensor-specific config file (make sure this is needed)
    Kconfig               # Zephyr/Kconfig configuration file for the driver (make sure this exists)
)

# If you have other libraries or dependencies, link them here
# For example, if you use I2C drivers, you can link them explicitly
# target_link_libraries(app PRIVATE zephyr::drivers::i2c)
