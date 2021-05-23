appFile=./app
libGLFW=./Libs/libglfw3.a
Lib=./Libs

if test -f "$Libs"; then
    echo
else
    mkdir Libs
fi

if test -f "$libGLFW"; then
    echo
else 
    cd Libs
    rm -rf *
    git clone https://github.com/glfw/glfw.git GLFW
    cd GLFW && mkdir build && cd build
    cmake .. && make
    cd src
    l
    mv libglfw3.a ../../../
    cd ../../..
    rm -rf GLFW
fi


if test -f "$appFile"; then
    rm app
fi

export DYLD_LIBRARY_PATH=Libs

make
./app
