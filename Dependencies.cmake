include(cmake/CPM.cmake)

function(toy_setup_dependencies)

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.5.2")
  endif()

endfunction()