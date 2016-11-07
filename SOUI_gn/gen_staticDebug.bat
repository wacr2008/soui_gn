call env.bat

call python %~dp0src\config\com_gen.py static_library 
call python %~dp0src\config\core_gen.py static_library 
 
 
xcopy /e /y /r /i %~dp0src\demos\Emoji\Resource\*.* %~dp0out\Debug\Resource 


if "%VM_BUILD%" == "" goto devBuild
gn gen out/Debug "--args=is_debug=true  enable_safeseh=true use_system_yasm=true is_official_build=false is_component_build=false target_os=\"win\" target_cpu=\"x86\""
goto end
:devBuild
gn gen --ide=vs2013 out/Debug "--args=is_debug=true  enable_safeseh=true use_system_yasm=true is_official_build=false is_component_build=false target_os=\"win\" target_cpu=\"x86\""
:end
