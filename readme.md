# About

What started as a student opengl graphic engine project is now aiming to generate various ibl textures, like .ktx2 full float textures based on https://cloud.needle.tools/articles/fasthdr-environment-maps


# Installation

## Arch linux

`git clone https://github.com/PierreLeBlond/Orangutan.git --recursive` \
or \
`git clone https://github.com/PierreLeBlond/Orangutan.git` \
`git submodule update --init --recursive`

```
cmake .
make
./Orangutan
```

## Dependencies

### assimp

assimp is expected to be found under `/usr/`
Should it be not the case, you can modify `./cmake/Findassimp.cmake`

#### archlinux

`sudo pacman -S assimp`

### libktx

https://github.khronos.org/KTX-Software/index.html

#### archlinux

`yay ktx-sotfware`
