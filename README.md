# ParkYerimDesktop
Desktop Automation for Smart Car Parking systems using QT Framework C++ and OpenCV computer vision libraries

<b>NOTE:</b> This project is still in development.

<b>Prerequisites</b>
- QT Framework 5.14
- MSVC15 (2017) build tools
- OpenCV 4.2.0
- OpenALPR 2.3.0

<b>Building Project</b>
<br> To build the project, you need to build required external libraries above and point their path in ParkYerimDesktop.pro file. Alternatively, you can point precompiled libraries that are in libexternal directory.
<br> To run the project, add required dlls in the same directory with ParkYerimDesktop.exe

<br>
Required .dll files to be in the same directory with ParkYerimDesktop.exe after building;
<br>liblept170.dll
<br>openalpr.dll
<br>opencv_core420.dll
<br>opencv_ffmpeg300_64.dll
<br>opencv_highgui420.dll
<br>opencv_imgproc420.dll
<br>opencv_video420.dll
<br>opencv_videoio420.dll
<br>opencv_world300.dll
<br>These files can be found in /libexternal/precompiled folder
