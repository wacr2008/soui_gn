ninja -C out/Release_static All -j5
ninja -C out/Debug_static All -j5

ninja -C out/Release_static post_build_static -j5
