pwd

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
    ls -al
    mv libglfw3.a ../../../
    cd ../../..
    rm -rf GLFW
    cd ..
fi


if test -f "$appFile"; then
    rm app

else 
    echo Compiling...
fi

export DYLD_LIBRARY_PATH=Libs
make mac 
