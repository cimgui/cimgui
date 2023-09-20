const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "cimgui",
        .root_source_file = null,
        .target = target,
        .optimize = optimize,
    });

    lib.linkLibC();
    lib.addIncludePath(.{ .path = "." });

    lib.addCSourceFiles(&.{
        "cimgui.cpp",
        "./imgui/imgui.cpp",
        "./imgui/imgui_draw.cpp",
        "./imgui/imgui_demo.cpp",
        "./imgui/imgui_tables.cpp",
        "./imgui/imgui_widgets.cpp",
    }, &.{
        "-fno-exceptions",
        "-fno-rtti",
    });

    b.installArtifact(lib);
}
