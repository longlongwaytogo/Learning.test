SET(TargetName OCityPlanApp)
aux_source_directory(. src)
add_executable( ${TargetName} ${src})
target_link_libraries(${TargetName} KernelCommon)




