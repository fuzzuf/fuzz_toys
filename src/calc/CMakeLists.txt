add_executable( fuzz_toys-calc calc.cpp )
install( TARGETS fuzz_toys-calc RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/cfg RENAME fuzz_toys-calc.cfg DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )
