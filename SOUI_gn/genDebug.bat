call env.bat

call python %~dp0src\config\com_gen.py shared_library 
call python %~dp0src\config\core_gen.py shared_library 

if "%VM_BUILD%" == "" goto devBuild
gn gen out/Debug "--args=treat_warnings_as_errors=true fatal_linker_warnings=false is_debug=true  use_system_yasm=true is_official_build=false is_component_build=true target_os=\"win\" target_cpu=\"x86\""
goto end
:devBuild
gn gen --ide=vs2015 out/Debug "--args=treat_warnings_as_errors=true fatal_linker_warnings=false is_debug=true  use_system_yasm=true is_official_build=false is_component_build=true target_os=\"win\" target_cpu=\"x86\""
:end
