-- set minimum xmake version
set_xmakever("3.0.0")

-- set project constants
set_project("commonlibob64")
set_languages("c++23")
set_warnings("allextra")
set_encodings("utf-8")

-- add common rules
add_rules("mode.debug", "mode.releasedbg")

-- include subprojects
includes("lib/commonlib-shared")
includes("xmake-rules.lua")

-- define targets
target("commonlibob64", function ()
    -- set target kind
    set_kind("static")

    -- set build by default
    set_default(os.scriptdir() == os.projectdir())

    -- add packages
    add_deps("commonlib-shared", { public = true })

    -- add source files
    add_files("src/**.cpp")

    -- add header files
    add_includedirs("include", { public = true })
    add_headerfiles(
        "include/(OBSE/**.h)",
        "include/(RE/**.h)",
        "include/(UE/**.h)"
    )

    -- add extra files
    add_extrafiles("res/commonlibob64.natvis")

    -- set precompiled header
    set_pcxxheader("include/OBSE/Impl/PCH.h")
end)
