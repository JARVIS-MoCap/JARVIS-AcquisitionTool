# JARVIS-AcquisitionTool

<p align="center">
<img src="docs/JARVIS_AcquisitionTool.png" alt="banner" width="70%"/>
</p>

This is the official Github Repository for the **JARVIS Annotation Tool**. To find out more about our 3D markerless motion capture toolbox have a look at 
**[our website](https://jarvis-mocap.github.io/jarvis-docs/)**.

All you need to get started is a set of supported cameras (currently only FLIR machine vision cameras are supported) and an Arduino Uno (or similar).
The AcquisitionTool lets you capture videos at high framerates and resolutions using **online JPEG compression**. It also lets you **adjust all the settings** ony our cameras and handles **synchronization**.

**Installing our prebuild packages is easy!** Just go to **[our downloads page](https://jarvis-mocap.github.io/jarvis-docs//2021-10-29-downloads.html)** and grab the installer for your operating system. We currently support Ubuntu 20.04 and 18.04 and plan to add support for Windows very soon. Installers for the current and previous versions can also be found under **[Releases](https://github.com/JARVIS-MoCap/JARVIS-AcquisitionTool/releases)**.

After installation please run the USB configuration script by running

      sudo sh configure_usb_settings.sh
      
from inside the **JARVIS-AcquisitionTool** directory. This will make sure you have the correct permissions and USB buffer settings to use your FLIR cameras.


# Building from Source

## Linux

### Installing the dependencies
To be able to build the tool install all the dependencies with

      sudo apt get install libxcb-xinerama0, libdouble-conversion-dev, gstreamer1.0-libav, ffmpeg, libxcb-xinput0, libpcre2-dev
      
### Cloning the repository
Next clone our repository with 

     git clone --recursive https://github.com/JARVIS-MoCap/JARVIS-AcquisitionTool.git
     
Go into the repository and create a build directory

    cd JARVIS-AcquisitionTool && mkdir build && cd build
    
Run cmake (replace XX04 by either 2004 or 1804) depending on your Ubuntu Version. If you do not have a CUDA enabled GPU select False for `-DUSE_CUDA`.

     cmake -DUBUNTU_VERSION=xx04 -DUSE_CUDA=True/False ..

Run make to build the tool (replace x by the number of available cores on your CPU)

     make -jx
     
If you want to create a debian package go to the deployment folder and run (replace XX04 by your Ubuntu Version)

     sh deploy_Ubuntu_XX04.sh

And finally install with (replacing the Xs with the numbers in the package you created)

     sudo apt install ./JARVIS-AnnotationTool_X.X-X_amd64_XX04.deb
     
If you want to remove it run

     sudo dpkg -r AnnotationTool

## Windows
coming soon...
      
