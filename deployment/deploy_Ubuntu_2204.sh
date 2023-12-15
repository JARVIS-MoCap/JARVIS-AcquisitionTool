mkdir ../build
cd ../build
cmake .. -DUBUNTU_VERSION=2204 -DUSE_CUDA=True -DCMAKE_BUILD_TYPE=RELEASE
cmake --build . --parallel 16
cmake --install .
cd ../deployment
dpkg-deb --build --root-owner-group deb_packages/JARVIS-AcquisitionTool_1.2-1_amd64_2204
mv deb_packages/JARVIS-AcquisitionTool_1.2-1_amd64_2204.deb .
