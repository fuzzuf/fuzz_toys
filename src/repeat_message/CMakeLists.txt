add_executable( fuzz_toys-repeat_message repeat_message.c )
install(
  TARGETS fuzz_toys-repeat_message
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/"
)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/cfg
  RENAME fuzz_toys-repeat_message.cfg
  DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/"
)

