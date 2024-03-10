install(
    TARGETS codebreaker_exe
    RUNTIME COMPONENT codebreaker_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
