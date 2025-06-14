macro(sdk_generate_library)
  if(${ARGC})
    set(library_name ${ARGV0})
  else()
    get_filename_component(library_name ${CMAKE_CURRENT_LIST_DIR} NAME)
  endif()

  set(library_name "lib${library_name}")
  message(STATUS "[register library : ${library_name}], path:${CMAKE_CURRENT_LIST_DIR}")

  set(CURRENT_STATIC_LIBRARY ${library_name})
  add_library(${library_name} STATIC)
  set_property(GLOBAL APPEND PROPERTY SDK_LIBS ${library_name})
  target_link_libraries(${library_name} PUBLIC sdk_intf_lib)
  add_library(${library_name}_high_priority_intf_lib INTERFACE)
  target_link_libraries(${library_name} PUBLIC ${library_name}_high_priority_intf_lib)
  set_target_properties(${library_name} PROPERTIES
    PREFIX ""
    OUTPUT_NAME "${library_name}"
    SUFFIX ".a"
  )
endmacro()

function(sdk_library_add_sources)
  foreach(arg ${ARGV})
    if(IS_DIRECTORY ${arg})
      message(FATAL_ERROR "sdk_library_add_sources() was called on a directory")
    endif()

    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()

    target_sources(${CURRENT_STATIC_LIBRARY} PRIVATE ${path})
  endforeach()
endfunction()

function(sdk_library_add_sources_ifdef feature)
  if(${${feature}})
    sdk_library_add_sources(${ARGN})
  endif()
endfunction()

function(sdk_add_include_directories)
  foreach(arg ${ARGV})
    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()

    target_include_directories(sdk_intf_lib INTERFACE ${path})
  endforeach()
endfunction()

function(sdk_add_private_include_directories)
  foreach(arg ${ARGV})
    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()

    target_include_directories(${CURRENT_STATIC_LIBRARY} PRIVATE ${path})
  endforeach()
endfunction()

function(sdk_add_system_include_directories)
  foreach(arg ${ARGV})
    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()

    target_include_directories(sdk_intf_lib SYSTEM INTERFACE ${path})
  endforeach()
endfunction()

function(sdk_add_include_directories_ifdef feature)
  if(${${feature}})
    sdk_add_include_directories(${ARGN})
  endif()
endfunction()

function(sdk_add_private_include_directories_ifdef feature)
  if(${${feature}})
    sdk_add_private_include_directories(${ARGN})
  endif()
endfunction()

function(sdk_add_system_include_directories_ifdef feature)
  if(${${feature}})
    sdk_add_system_include_directories(${ARGN})
  endif()
endfunction()

function(sdk_add_compile_definitions)
  target_compile_definitions(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_private_compile_definitions)
  target_compile_definitions(${CURRENT_STATIC_LIBRARY} PRIVATE ${ARGV})
endfunction()

function(sdk_add_compile_definitions_ifdef feature)
  if(${${feature}})
    sdk_add_compile_definitions(${ARGN})
  endif()
endfunction()

function(sdk_add_private_compile_definitions_ifdef feature)
  if(${${feature}})
    sdk_add_private_compile_definitions(${ARGN})
  endif()
endfunction()

function(sdk_add_compile_options)
  target_compile_options(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_private_compile_options)
  target_compile_options(${CURRENT_STATIC_LIBRARY} PRIVATE ${ARGV})
endfunction()

function(sdk_add_high_prior_compile_options)
  target_compile_options(${CURRENT_STATIC_LIBRARY}_high_priority_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_compile_options_ifdef feature)
  if(${${feature}})
    sdk_add_compile_options(${ARGN})
  endif()
endfunction()

function(sdk_add_private_compile_options_ifdef feature)
  if(${${feature}})
    sdk_add_private_compile_options(${ARGN})
  endif()
endfunction()

function(sdk_add_link_options)
  target_link_options(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_private_link_options)
  target_link_options(${CURRENT_STATIC_LIBRARY} PRIVATE ${ARGV})
endfunction()

function(sdk_add_link_options_ifdef feature)
  if(${${feature}})
    sdk_add_link_options(${ARGN})
  endif()
endfunction()

function(sdk_add_private_link_options_ifdef feature)
  if(${${feature}})
    sdk_add_private_link_options(${ARGN})
  endif()
endfunction()

function(sdk_add_link_libraries)
  target_link_libraries(sdk_intf_lib INTERFACE ${ARGV})
endfunction()

function(sdk_add_link_libraries_ifdef feature)
  if(${${feature}})
    sdk_add_link_libraries(${ARGN})
  endif()
endfunction()

function(sdk_add_subdirectory_ifdef feature dir)
  if(${${feature}})
    add_subdirectory(${dir})
  endif()
endfunction()

function(sdk_add_static_library)
  foreach(arg ${ARGV})
    if(IS_DIRECTORY ${arg})
      message(FATAL_ERROR "sdk_add_static_library() was called on a directory")
    endif()

    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()

    get_filename_component(library_name ${path} NAME_WE)
    message(STATUS "[register extern library : ${library_name}], path:${CMAKE_CURRENT_LIST_DIR}")
    set_property(GLOBAL APPEND PROPERTY SDK_LIBS ${path})
  endforeach()
endfunction()

function(sdk_add_static_library_ifdef feature)
  if(${${feature}})
    sdk_add_static_library(${ARGN})
  endif()
endfunction()

macro(sdk_ifndef define val)
  if(NOT DEFINED ${define})
    set(${define} ${val})
  endif()
endmacro()

function(sdk_set_linker_script ld)
  if(IS_ABSOLUTE ${ld})
    set(path ${ld})
  else()
    set(path ${CMAKE_CURRENT_SOURCE_DIR}/${ld})
  endif()

  set_property(GLOBAL PROPERTY LINKER_SCRIPT ${path})
endfunction()

macro(sdk_set_vscode_dir dir)
  if(IS_ABSOLUTE ${dir})
    set(VSCODE_DIR ${dir})
  else()
    set(VSCODE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
  endif()
endmacro()

macro(sdk_set_main_file)
  if(IS_ABSOLUTE ${ARGV0})
    set(path ${ARGV0})
  else()
    set(path ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0})
  endif()

  set(CURRENT_MAIN_FILE ${path})
endmacro()

macro(project name)
  if(CPU_ID)
    set(proj_name ${name}_${CHIP}_${CPU_ID})
  else()
    set(proj_name ${name}_${CHIP})
  endif()

  _project(${proj_name} ASM C CXX)

  set(HEX_FILE ${build_dir}/${proj_name}.hex)
  set(BIN_FILE ${build_dir}/${proj_name}.bin)
  set(MAP_FILE ${build_dir}/${proj_name}.map)
  set(ASM_FILE ${build_dir}/${proj_name}.asm)

  add_executable(${proj_name}.elf ${CURRENT_MAIN_FILE})
  target_link_libraries(${proj_name}.elf sdk_intf_lib)
  get_property(LINKER_SCRIPT_PROPERTY GLOBAL PROPERTY LINKER_SCRIPT)

  if(EXISTS ${LINKER_SCRIPT_PROPERTY})
    set_target_properties(${proj_name}.elf PROPERTIES LINK_FLAGS "-T${LINKER_SCRIPT_PROPERTY} -Wl,-Map=${MAP_FILE}")
    set_target_properties(${proj_name}.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT_PROPERTY})
  endif()

  get_property(SDK_LIBS_PROPERTY GLOBAL PROPERTY SDK_LIBS)
  # message(STATUS "SDK_LIBS_PROPERTY:")
  # foreach(lib ${SDK_LIBS_PROPERTY})
  #     message(STATUS "  ${lib}")
  # endforeach()

  # Get the base name and sort.
  set(BASIC_NAMES_LIST "")
  set(PRIO_BASIC_NAMES_LIST "")
  set(LAST_NAMES_LIST "")
  set(LAST_NAMES_LIST2 "")
  foreach(lib ${SDK_LIBS_PROPERTY})
    set(BASIC_NAMES "")
    get_filename_component(lib_name ${lib} NAME_WE)
    string(REGEX MATCH "libqcc74x_fhost.*|libqcc74x_macsw.*|liblwip|libfreertos|libc" BASIC_NAMES ${lib_name})
    string(REGEX MATCH "libbtblecontroller_qcc743_ble1m2s1bredr1.*|libbtblecontroller_qcc743_ble1m2s1bredr0.*|libblestack.*" IS_BLUETOOTH ${lib_name})
    string(REGEX MATCH "liblhal.*|libstd.*|libsys.*" IS_BASIC_LIB ${lib_name})
    if(BASIC_NAMES)
        list(APPEND PRIO_BASIC_NAMES_LIST ${lib_name})
    elseif(IS_BLUETOOTH)
        list(APPEND LAST_NAMES_LIST ${lib_name})
    elseif(IS_BASIC_LIB)
        list(APPEND LAST_NAMES_LIST2 ${lib_name})
    else()
        list(APPEND BASIC_NAMES_LIST ${lib_name})
    endif()
  endforeach()
  list(SORT BASIC_NAMES_LIST)
  list(SORT PRIO_BASIC_NAMES_LIST)
  list(SORT LAST_NAMES_LIST)
  list(SORT LAST_NAMES_LIST2)
  # Restoring full paths based on the sorted results by name.
  set(SORTED_SDK_LIBS "")
  foreach(name ${PRIO_BASIC_NAMES_LIST} ${BASIC_NAMES_LIST} ${LAST_NAMES_LIST} ${LAST_NAMES_LIST2})
    foreach(lib ${SDK_LIBS_PROPERTY})
        get_filename_component(lib_name ${lib} NAME_WE)
        if(lib_name STREQUAL name)
            if(NOT lib IN_LIST SORTED_SDK_LIBS)     # Check if the library is already in the sorted list
                list(APPEND SORTED_SDK_LIBS ${lib}) # Add the original path to the sorted list
                break()
            endif()
        endif()
    endforeach()
  endforeach()

  # message(STATUS "List of all libraries in the order of connection:")
  # foreach(lib ${SORTED_SDK_LIBS})
  #     message(STATUS "  ${lib}")
  # endforeach()

  # update SDK_LIBS
  set_property(GLOBAL PROPERTY SDK_LIBS ${SORTED_SDK_LIBS})
  # link
  target_link_libraries(${proj_name}.elf -Wl,--whole-archive ${SORTED_SDK_LIBS} app -Wl,--no-whole-archive)

  if(OUTPUT_DIR)
    add_custom_command(TARGET ${proj_name}.elf POST_BUILD
      COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${proj_name}.elf> ${BIN_FILE}
      COMMAND ${CMAKE_OBJDUMP} -d -S $<TARGET_FILE:${proj_name}.elf> >${ASM_FILE}

      # COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${proj_name}.elf> ${HEX_FILE}
      # COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${proj_name}.elf>
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${proj_name}.elf> ${OUTPUT_DIR}/${name}/${proj_name}.elf
      COMMAND ${CMAKE_COMMAND} -E copy ${ASM_FILE} ${OUTPUT_DIR}/${name}/${proj_name}.asm
      COMMAND ${CMAKE_COMMAND} -E copy ${MAP_FILE} ${OUTPUT_DIR}/${name}/${proj_name}.map
      COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} ${OUTPUT_DIR}/${name}/${proj_name}.bin
      COMMAND ${CMAKE_COMMAND} -E copy ${BIN_FILE} ${OUTPUT_DIR}/project.bin
      COMMENT "Generate ${BIN_FILE}\r\n"
    )

  else()
    add_custom_command(TARGET ${proj_name}.elf POST_BUILD
      COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${proj_name}.elf> ${BIN_FILE}
      COMMAND ${CMAKE_OBJDUMP} -d -S $<TARGET_FILE:${proj_name}.elf> >${ASM_FILE}

      # COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${proj_name}.elf> ${HEX_FILE}
      # COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${proj_name}.elf>
      COMMENT "Generate ${BIN_FILE}\r\n"
    )
  endif()

  include(${QCC74x_SDK_BASE}/cmake/qcc74x_flash.cmake)
  include(${QCC74x_SDK_BASE}/cmake/footprint.cmake)
  include(${QCC74x_SDK_BASE}/cmake/gen_c_cpp_properties_json.cmake)
endmacro()
