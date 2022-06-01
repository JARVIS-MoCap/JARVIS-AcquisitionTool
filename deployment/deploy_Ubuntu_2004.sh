mkdir ../build
cd ../build
cmake .. -DUSE_CUDA=True
make -j12
make install
cd ../deployment
dpkg-deb --build --root-owner-group deb_packages/JARVIS-AcquisitionTool_1.0-1_amd64_2004
mv deb_packages/JARVIS-AcquisitionTool_1.0-1_amd64_2004.deb .
