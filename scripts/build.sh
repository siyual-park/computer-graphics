echo "Build start"

cd external/gl3w
python gl3w_gen.py
cd ../..

mkdir build
cd build
cmake ..
make
