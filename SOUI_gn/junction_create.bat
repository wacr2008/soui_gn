call env.bat
junction -s %APP_PATH%\build %ROOT_PATH%\Live\build
junction -s %APP_PATH%\build_overrides %ROOT_PATH%\Live\build_overrides
junction -s %APP_PATH%\buildtools %ROOT_PATH%\Live\buildtools
junction -s %APP_PATH%\tools %ROOT_PATH%\Live\tools
junction -s %APP_PATH%\testing %ROOT_PATH%\Live\testing
junction -s %APP_PATH%\third_party %ROOT_PATH%\Live\third_party
junction -s %APP_PATH%\src\libyuv %ROOT_PATH%\Live\src\libyuv
