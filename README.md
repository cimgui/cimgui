# cimgui [![Build Status](https://travis-ci.org/Extrawurst/cimgui.svg)](https://travis-ci.org/Extrawurst/cimgui)

![sample](https://raw.github.com/extrawurst/cimgui/master/Screen Shot 2015-04-09.png)
![new menus api](https://raw.github.com/extrawurst/cimgui/master/menus-api.gif)

This is a thin c-api wrapper for the excellent C++ intermediate gui [imgui](https://github.com/ocornut/imgui).
Most of the functions have wrapper counterparts now, missing stuff is added on a as-needed basis (PR welcome).
This library is intended as a intermediate layer to be able to use imgui from other languages that can interface with C (like D - see [D-binding](https://github.com/Extrawurst/DerelictImgui))

Notes:
* currently this wrapper is based on version [1.45 of imgui](https://github.com/ocornut/imgui/releases/tag/v1.45)
* does not compile with pure C compiler yet (for writing bindings in languages that are able to use C-ABI it is enough though, see D-bindings)

# usage

* clone
* make using makefile on linux/osx
* use whatever method is in ImGui c++ namespace in the original [imgui.h](https://github.com/ocornut/imgui/blob/master/imgui.h) by prepending `ig`
* methods have the same parameter list and return values (where possible)
