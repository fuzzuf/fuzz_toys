add_executable( fuzz_toys-gcd gcd.cpp )
install(
  TARGETS fuzz_toys-gcd
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/"
)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/cfg
  RENAME fuzz_toys-gcd.cfg
  DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/"
)

