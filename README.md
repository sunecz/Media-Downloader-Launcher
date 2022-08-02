# Media-Downloader-Launcher
Launcher for [Media Downloader](https://github.com/sunecz/Media-Downloader). This application launches the `media-downloader.jar` file using a custom JRE located in the `jre` directory.

## How to build
Building can be done manually using CMake and Make or by using the building script `build.sh` and Docker. A custom version of the [multiarch/crossbuild](https://github.com/multiarch/crossbuild) Docker image is used to build the launcher.

### Manually
Simply run:
```
mkdir build && cd build && cmake .. && make
```
This will create `build` directory and build the program into it. This method will create the launcher binaries only for the host system. Note that build essentials, such as `clang` or `gcc` (and more), are required.

### Using the docker image
First, install [Docker Desktop application](https://www.docker.com/products/docker-desktop/) and start it up. Then you need to build the custom docker image, which can be done by running the following command from the repository's root directory:
```
docker build --no-cache -t multiarch/crossbuild .
```

After the docker image is successfully built, you can run the build script:
```
./build.sh
```
This will create `build` directory and three subdirectories, each for one of these operating systems (all 64-bit): Windows (`windows-x64`), Linux (`linux-x64`) and Mac OS X (`osx-x64`).

# Related repositories
- Application: https://github.com/sunecz/Media-Downloader
- Default plugins: https://github.com/sunecz/Media-Downloader-Default-Plugins
- DRM plugin: https://github.com/sunecz/Media-Downloader-DRM-Plugin
