add_executable( fuzz_toys-sort sort.cpp )
install( TARGETS fuzz_toys-sort RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/cfg RENAME fuzz_toys-sort.cfg DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )
