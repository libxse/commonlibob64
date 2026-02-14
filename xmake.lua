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

    -- add flags (clang-cl: disable warnings) (public)
    add_cxxflags(
        "clang_cl::-Wno-undefined-bool-conversion",
        { public = true }
    )
end)

rule("commonlibob64.plugin", function()
    add_deps("commonlib.plugin")

    on_load(function(target)
        target:data_set("commonlib.plugin.config", target:extraconf("rules", "commonlibob64.plugin"))
    end)

    on_config(function(target)
        target:add("deps", "commonlibob64")

        target:add("configfiles", path.join(os.scriptdir(), "res/commonlibob64-plugin.cpp.in"))
        target:add("files", path.join(target:configdir(), "commonlibob64-plugin.cpp"))

        local conf = target:extraconf("rules", "commonlibob64.plugin")
        if conf.options then
            if conf.options.sig_scanning then
                conf.options.address_library = false
            else
                conf.options.sig_scanning = false
                if conf.options.address_library == nil then
                    conf.options.address_library = true
                end
            end
            if conf.options.no_struct_use then
                conf.options.layout_dependent = false
            else
                conf.options.no_struct_use = false
                if conf.options.layout_dependent == nil then
                    conf.options.layout_dependent = true
                end
            end
        else
            conf.options = {
                sig_scanning = false,
                address_library = true,
                no_struct_use = false,
                layout_dependent = true
            }
        end

        target:set("configvar", "COMMONLIBOB64_OPTION_SIG_SCANNING", tostring(conf.options.sig_scanning))
        target:set("configvar", "COMMONLIBOB64_OPTION_ADDRESS_LIBRARY", tostring(conf.options.address_library))
        target:set("configvar", "COMMONLIBOB64_OPTION_NO_STRUCT_USE", tostring(conf.options.no_struct_use))
        target:set("configvar", "COMMONLIBOB64_OPTION_LAYOUT_DEPENDENT", tostring(conf.options.layout_dependent))

        if os.getenv("XSE_TES4_MODS_PATH") then
            target:set("installdir", path.join(os.getenv("XSE_TES4_MODS_PATH"), target:name()))
        elseif os.getenv("XSE_TES4_GAME_PATH") then
            target:set("installdir", os.getenv("XSE_TES4_GAME_PATH"))
        end

        target:add("installfiles", target:targetfile(), { prefixdir = "OblivionRemastered/Binaries/Win64/OBSE/Plugins" })
        target:add("installfiles", target:symbolfile(), { prefixdir = "OblivionRemastered/Binaries/Win64/OBSE/Plugins" })
    end)
end)
