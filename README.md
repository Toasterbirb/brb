# brb

The goal of this project is to create a C++ standard library for Linux without using any libraries (not even the C or C++ standard libraries). If everything goes as planned, there should be zero includes in this repository that refer to files outside of this repository.

> [!WARNING]
> There are zero, absolutely none, nada, security guarantees with this library

brb is somewhat opionated and will not necessarily follow any existing standards. Some notable changes include:
- The main function signature is `mu8 brb_main()`
- Fundamental types like int, float etc. are undefined
    - As a replacement there are fixed width shortened type names that follow the following format: i8, u8, i16, u16 and so on
    - As a side effect, including pretty much any header that isn't made with brb in mind will probably error out. Thus this part is subject to change if needed
- All fundamental types are const by default. If mutable variables are needed, add m to the beginning of the type i.e. mi8, mu8, mi16, mu16 and so on
    - As a side effect from how this is implemented (macros .\_.), fundamental return types always need to be mutable

## Building
Build the project with g++ by running `make`. To speed up the build, you can try using the -j flag.
```sh
make -j$(nproc)
```

## Building a project that uses brb
As of now, the following compiler flags are needed (on gcc) to disable the standard libraries and exceptions etc.
```
-fno-stack-protector -Wno-builtin-declaration-mismatch -nostdlib -nostdlib++ -fno-exceptions
```
Then simply build the library against a staticly linked build of the brb library

## Installation
To install brb to /usr/local/bin, run the following
```sh
make install
```
You can customize the installation prefix with the PREFIX variable like so
```sh
make PREFIX=/usr install
```

## Uninstall
```sh
make uninstall
```
