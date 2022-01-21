## Installation (For Ubuntu)

`git clone https://github.com/PierreLeBlond/Orangutan.git --recursive`

```
mkdir build
cd build
cmake ..
make
```

### Dependencies

#### OpenGL

Install `libgl1-mesa-dev` package.

#### libpng

```
cd ext/libpng
./configure
make check
make install
```
