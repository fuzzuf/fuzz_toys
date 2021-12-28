add_executable( fuzz_toys-csv_small csv_small.cpp )
install( TARGETS fuzz_toys-csv_small RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/cfg RENAME fuzz_toys-csv_small.cfg DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )

