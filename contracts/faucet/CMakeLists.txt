add_contract(faucet_contract faucet ${CMAKE_CURRENT_SOURCE_DIR}/src/faucet.cpp)

target_include_directories(faucet
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(faucet
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/faucet.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/faucet.contracts.md @ONLY )

target_compile_options( faucet PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )