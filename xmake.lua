add_requires("glfw")
add_requires("vulkansdk", { configs = { shared = true, utils = { "slang", "shaderc_combined", "spirv-cross-core", "spirv-cross-cpp", "spirv-cross-glsl", "spirv-cross-hlsl", "dxcompiler" } } })

set_policy("run.autobuild", true)
add_rules("mode.debug", "mode.release")
set_rundir(".")

includes("Vendor/imgui-docking/xmake.lua")
target("ImGuiExample")
    set_kind("binary")
    add_deps("imgui")
    local target = "CustomTreeNode"
    add_includedirs(target .. "/src")
    add_files(target .. "/src/**.cpp")
    add_packages("glfw")
    add_packages("vulkansdk")