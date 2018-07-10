cmake_minimum_required(VERSION 2.8.11)
project(QRegexWidget)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Find the PCRE library
find_library(pcre2 REQUIRED)

set(qregexwidget_SRC
  src/main.cpp
  src/qregexwidget.cpp
)

# Create code from a list of Qt designer ui files.
#set(CMAKE_AUTOUIC ON) # use this if you have CMake 3.x instead of the following
qt5_wrap_ui(qregexwidget_SRC src/qregexwidget.ui)

# Tell CMake to create the helloworld executable
add_executable(qregexwidget ${qregexwidget_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(qregexwidget Qt5::Widgets pcre2-8)

# Install the executable
install(TARGETS qregexwidget DESTINATION bin)
