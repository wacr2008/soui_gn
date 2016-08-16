call env.bat

call ninja -C out/Release  gen_demo_resource
call ninja -C out/Debug    gen_demo_resource

call All.sln