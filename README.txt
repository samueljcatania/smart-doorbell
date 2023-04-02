Prerequisites:
Required Dependencies:
- GTK-3.0
- OpenCV (with GTK3 dependencies)
- Wt 4.9.1

IMPORTANT: Make sure that no other versions of GTK such as GTK 2.0 are installed. This will cause conflicts in
building and linking OpenCV.

=============================================================================================================

Instructions for installing the required packages (Ubuntu/Debian)

=============================================================================================================

Installing GTK-3.0

1. To install GTK-3.0, run this command:
sudo apt-get install libgtk-3-dev


=============================================================================================================

Installing OpenCV with GTK 3.0 Dependencies:

1. Install the required dependencies:
sudo apt-get install build-essential cmake git libgtk-3-dev \
libavcodec-dev libavformat-dev libswscale-dev \
libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev \
libjpeg-dev libpng-dev libtiff-dev libwebp-dev libopenexr-dev \
libeigen3-dev libtbb-dev python3-dev python3-numpy \
python3-matplotlib python3-pip python3-pyqt5 python3-pyqt5.qtopengl

2. Download the latest version of OpenCV:
git clone https://github.com/opencv/opencv.git
cd opencv
git checkout 4.5.4


3. Create a build directory inside the OpenCV directory and navigate to it:
mkdir build
cd build

4.Run 'cmake' with the 'WITH_GTK_3 flag set to ON'
cmake -DWITH_GTK=ON -DWITH_GTK3=ON ..

5. Build and install OpenCV
make
sudo make install

=============================================================================================================

Installing Wt 4.9.1

1. Download Wt 4.9.1 and extract the files: https://www.webtoolkit.eu/wt/download

2. After extracting the files, run the following commands to build Wt 4.9.1:
cd wt-4.9.1
mkdir build; cd build
cmake ..
make
make -C examples

3. Run the following commands within the wt-4.9.1 folder to install.
sudo make install
sudo ldconfig

More specific instructions based on platform can be accessed here: https://redmine.webtoolkit.eu/projects/wt/wiki/Wt_Installation

=============================================================================================================
RUNNING THE PROGRAM

After installing GTK 3.0 and OpenCV, navigate to the working directory. You can compile the program by following these commands in your terminal:
make
./group17
make clean

=============================================================================================================
Notes about running the program:
Recorded footage files are saved to a folder called 'recordings' in the project directory. 
IMPORTANT: please create a 'recordings' folder before first run. 
Please use the following command line arguments when running the program: --docroot . --http-address 0.0.0.0 --http-port 8080
If you change the http-address to your inet IP address, then you will be able to access the WebApp from any other device on the network. 

