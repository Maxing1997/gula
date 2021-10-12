special thanks to [muduo](https://github.com/chenshuo/muduo)

GULA is a multithreaded C++ network library based on the reactor pattern.

Use of this source code is governed by a BSD-style license that can be found in the License file.

Requires:
- Linux kernel version >= 2.6.28.
- GCC >= 4.7 or Clang >= 3.5
- Boost (for boost::any only.)

Tested on:
- Unbuntu 18.04 
Install required packages:
```
$ sudo apt install g++ cmake make libboost-dev
```
> To develop with the Boost libraries in Ubuntu/Debian, you need to install the libboost-all-dev package:
> sudo apt-get install libboost-all-dev


To build, run:
```
sudo chmod +x ./build.sh
./build.sh
```


