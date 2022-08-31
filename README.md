# Parking Lot Management System with Auto License Plate Recognition

<b>Prerequisites</b>
- QT Framework 5.14 or higher
- OpenCV 4.2.0 or higher
- OpenALPR 2.3.0 or higher

<b>Building Project</b>
<br> To build the project, you need to build required external libraries above and point their path in ParkYerimDesktop.pro file (in LIBS subfield). Alternatively, you can point precompiled libraries that are present in libexternal directory.
<br>
<br><b>Running the application</b>

1. To run the application, add required dlls in the same directory with ParkYerimDesktop.exe
<br>Required .dll files to be in the same directory with ParkYerimDesktop.exe after building;
<br>liblept170.dll
<br>openalpr.dll
<br>opencv_core420.dll
<br>opencv_ffmpeg300_64.dll
<br>opencv_highgui420.dll
<br>opencv_imgproc420.dll
<br>opencv_video420.dll
<br>opencv_videoio420.dll
<br>opencv_world300.dll
<br>These binaries can be found in <b>/libexternal/precompiled</b> folder
<br><br><b>Note:</b> These binaries are compiled in <b>Release</b> mode, therefore the project wont be built or run in Debug configuration.If you want to run the application in Debug mode then you will have to build OpenCV and OpenALPR in MSVC15 Debug configuration using Visual Studio. After building these external libraries in Debug configuration, you must edit .pro file and rename the dependencies (in LIBS subfield) as their Debug compilation output names (i.e: opencv_video420d.dll, not opencv_video420.dll).


2. Configuring OpenALPR runtime data
<br>In order to run Auto License Plate Recognition functions, you must copy <b>runtime_data</b> folder and <b>openalpr.conf</b> file in <b>/libexternal/openalpr_x64</b> and paste them to project build directory.
