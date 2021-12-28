add_executable( fuzz_toys-brainf_ck brainf_ck.cpp )
if( ENABLE_STRICT_BRAINF_CK )
  target_compile_definitions( fuzz_toys-brainf_ck PRIVATE FUZZ_TOYS_STRICT_BRAINF_CK )
endif()
install( TARGETS fuzz_toys-brainf_ck RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )
install( FILES ${CMAKE_CURRENT_BINARY_DIR}/cfg RENAME fuzz_toys-brainf_ck.cfg DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBEXECDIR}/fuzz_toys/" )


