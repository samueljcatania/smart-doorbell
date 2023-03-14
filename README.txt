Prerequisites:
Please make sure that GTK-3.0 and OpenCV are installed. OpenCV with GTK3 dependencies is required to run this program.
IMPORTANT: Make sure that no other versions of GTK such as GTK 2.0 are installed. This will cause conflicts in
building and linking OpenCV.

Instructions for installing the required packages (Ubuntu/Debian)
Installing GTK-3.0
1. To install GTK-3.0, run this command:
sudo apt-get install libgtk-3-dev

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


Notes about running the program:
Recorded footage files are saved to the working directory.

