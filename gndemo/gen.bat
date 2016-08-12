
gn gen --ide=vs2013 out/Debug "--args=is_debug=true is_official_build=false target_os=\"win\" target_cpu=\"x86\""

gn gen --ide=vs2013 out/Release "--args=is_debug=false is_official_build=true target_os=\"win\" target_cpu=\"x86\""

