# cimgui [![Build Status](https://travis-ci.org/Extrawurst/cimgui.svg)](https://travis-ci.org/Extrawurst/cimgui)

![sample](screenshot.png)

This is a thin c-api wrapper for the excellent C++ intermediate gui [imgui](https://github.com/ocornut/imgui).
Most of the functions have wrapper counterparts now, missing stuff is added on a as-needed basis (PR welcome).
This library is intended as a intermediate layer to be able to use imgui from other languages that can interface with C (like D - see [D-binding](https://github.com/Extrawurst/DerelictImgui))

Notes:
* currently this wrapper is based on version [1.53 of imgui](https://github.com/ocornut/imgui/releases/tag/v1.53)
* does not compile with pure C compiler yet (for writing bindings in languages that are able to use C-ABI it is enough though, see D-bindings)

# usage

* clone
* make using makefile on linux/osx
* use whatever method is in ImGui c++ namespace in the original [imgui.h](https://github.com/ocornut/imgui/blob/master/imgui.h) by prepending `ig`
* methods have the same parameter list and return values (where possible)

# example bindings based on cimgui

* [DerelictImgui](https://github.com/Extrawurst/DerelictImgui)
* [ImGui.NET](https://github.com/mellinoe/ImGui.NET)
* [ImGuiCS](https://github.com/0x0ade/ImGuiCS)
* [imgui-rs](https://github.com/Gekkio/imgui-rs)
* [imgui-pas](https://github.com/dpethes/imgui-pas)
* [odin-dear_imgui](https://github.com/ThisDrunkDane/odin-dear_imgui)
