#
# Copyright (c) 2026 CNRS
# Authors: Florent Lamiraux
#

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# 1. Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

set(MODULE pyhpp/toppra)
set(LIBNAME "bindings")
set(SOURCE_FILES pyhpp/toppra/toppra.cc pyhpp/toppra/bindings.cc)

string(REGEX REPLACE "[/-]" "_" TARGET_NAME "${MODULE}")
add_library(${TARGET_NAME} SHARED ${SOURCE_FILES})
set_target_properties(
    ${TARGET_NAME}
    PROPERTIES
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}
        LIBRARY_OUTPUT_NAME ${LIBNAME}
)
target_link_boost_python(${TARGET_NAME} PUBLIC)
target_link_libraries(${TARGET_NAME} PUBLIC eigenpy::eigenpy PRIVATE hpp-toppra)

install(TARGETS ${TARGET_NAME} DESTINATION ${PYTHON_SITELIB}/${MODULE})

# Write __init__.py file
file(
    WRITE ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}/__init__.py
    "from .${LIBNAME} import *"
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}/__init__.py
    DESTINATION ${PYTHON_SITELIB}/${MODULE}
)
