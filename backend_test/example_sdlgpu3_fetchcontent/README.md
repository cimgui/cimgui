# SDLGPU3

This example is a little different from the others, because `cimgui` doesn't come with bindings for the SDLGPU3 backend out of the box. Instead, this example shows how to generate the necessary bindings during cmake's configure time, then add the compiled library as a target for your application to link to.

## Building

```sh
cmake -B build . && cmake --build build
```
