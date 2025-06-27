# SDLGPU3

This example is a little different from the others, because `cimgui` doesn't come with bindings for the SDLGPU3 backend out of the box. Instead, this example shows how to generate the necessary bindings during cmake's configure time, then add the compiled library as a target for your application to link to.

For the generation phase from cmake you need LuaJIT to be present.

## Building

From the build directory of your choice:

`cmake path_to_example_sdlgpu3`

and after

`make`

