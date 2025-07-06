local PLUGIN_FILE = [[
#include <OBSE/OBSE.h>
OBSE_EXPORT constinit auto OBSEPlugin_Version = []() noexcept {
    OBSE::PluginVersionData v{};
    v.PluginVersion({ ${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, 0 });
    v.PluginName("${PLUGIN_NAME}");
    v.AuthorName("${PLUGIN_AUTHOR}");
    v.UsesAddressLibrary(${OPTION_ADDRESS_LIBRARY});
    v.UsesSigScanning(${OPTION_SIG_SCANNING});
    v.IsLayoutDependent(${OPTION_LAYOUT_DEPENDENT});
    v.HasNoStructUse(${OPTION_NO_STRUCT_USE});
    v.CompatibleVersions({ OBSE::RUNTIME_LATEST });
    return v;
}();
]]

local PLUGIN_RC_FILE = [[
#include <winres.h>

1 VERSIONINFO
FILEVERSION ${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, 0
PRODUCTVERSION ${PROJECT_VERSION_MAJOR}, ${PROJECT_VERSION_MINOR}, ${PROJECT_VERSION_PATCH}, 0
FILEFLAGSMASK 0x17L
#ifdef _DEBUG
    FILEFLAGS 0x1L
#else
    FILEFLAGS 0x0L
#endif
FILEOS 0x4L
FILETYPE 0x1L
FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904b0"
        BEGIN
            VALUE "FileDescription", "${PLUGIN_DESCRIPTION}"
            VALUE "FileVersion", "${PLUGIN_VERSION}.0"
            VALUE "InternalName", "${PLUGIN_NAME}"
            VALUE "LegalCopyright", "${PLUGIN_AUTHOR} | ${PLUGIN_LICENSE}"
            VALUE "ProductName", "${PROJECT_NAME}"
            VALUE "ProductVersion", "${PROJECT_VERSION}.0"
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x409, 1200
    END
END]]

-- git submodule usage:
-- add_deps("commonlibob64")
-- add_rules("commonlibob64.plugin", {
--     name = "PluginName",
--     author = "Author Name",
--     description = "Plugin Description"
-- })

-- define rules
rule("commonlibob64.plugin")
    add_deps("win.sdk.resource")

    on_config(function(target)
        import("core.base.semver")
        import("core.project.depend")
        import("core.project.project")

        target:set("arch", "x64")
        target:set("kind", "shared")

        target:add("installfiles", target:targetfile(), { prefixdir = "OblivionRemastered/Binaries/Win64/OBSE/Plugins" })
        target:add("installfiles", target:symbolfile(), { prefixdir = "OblivionRemastered/Binaries/Win64/OBSE/Plugins" })

        if os.getenv("XSE_TES4_MODS_PATH") then
            target:set("installdir", path.join(os.getenv("XSE_TES4_MODS_PATH"), target:name()))
        elseif os.getenv("XSE_TES4_GAME_PATH") then
            target:set("installdir", os.getenv("XSE_TES4_GAME_PATH"))
        end

        local conf = target:extraconf("rules", "commonlibob64.plugin")
        local conf_dir = path.join(target:autogendir(), "rules", "commonlibob64", "plugin")

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

        local conf_map = {
            PLUGIN_AUTHOR           = conf.author or "",
            PLUGIN_DESCRIPTION      = conf.description or "",
            PLUGIN_LICENSE          = (target:license() or "Unknown") .. " License",
            PLUGIN_NAME             = conf.name or target:name(),
            PLUGIN_VERSION          = target:version() or "0.0.0",
            PLUGIN_VERSION_MAJOR    = semver.new(target:version() or "0.0.0"):major(),
            PLUGIN_VERSION_MINOR    = semver.new(target:version() or "0.0.0"):minor(),
            PLUGIN_VERSION_PATCH    = semver.new(target:version() or "0.0.0"):patch(),
            PROJECT_NAME            = project.name() or "",
            PROJECT_VERSION         = project.version() or "0.0.0",
            PROJECT_VERSION_MAJOR   = semver.new(project.version() or "0.0.0"):major(),
            PROJECT_VERSION_MINOR   = semver.new(project.version() or "0.0.0"):minor(),
            PROJECT_VERSION_PATCH   = semver.new(project.version() or "0.0.0"):patch(),
            OPTION_ADDRESS_LIBRARY  = conf.options.address_library,
            OPTION_LAYOUT_DEPENDENT = conf.options.layout_dependent,
            OPTION_NO_STRUCT_USE    = conf.options.no_struct_use,
            OPTION_SIG_SCANNING     = conf.options.sig_scanning,
        }

        local conf_parse = function(a_str)
            return a_str:gsub("(%${([^\n]-)})", function(_, a_var)
                local result = conf_map[a_var:trim()]
                if type(result) ~= "string" then
                    result = tostring(result)
                end
                assert(result ~= nil, "cannot get variable(%s)", a_var)
                return result
            end)
        end

        local add_file = function(a_path, a_data)
            local file_path = path.join(conf_dir, a_path)
            depend.on_changed(function()
                local file = io.open(file_path, "w")
                if file then
                    file:write(conf_parse(a_data), "\n")
                    file:close()
                end
            end, { dependfile = target:dependfile(file_path), files = project.allfiles()})
            target:add("files", file_path)
        end

        add_file("plugin.cpp", PLUGIN_FILE)
        add_file("version.rc", PLUGIN_RC_FILE)
    end)

    on_install(function(target)
        local srcfiles, dstfiles = target:installfiles()
        if srcfiles and #srcfiles > 0 and dstfiles and #dstfiles > 0 then
            for idx, srcfile in ipairs(srcfiles) do
                os.trycp(srcfile, dstfiles[idx])
            end
        end
    end)

    on_package(function(target)
        import("core.project.config")
        import("core.project.project")
        import("utils.archive")

        local archive_name = target:name() .. "-" .. (target:version() or "0.0.0") .. ".zip"
        print("packing %s .. ", archive_name)

        local root_dir = path.join(os.tmpdir(), "packages", project.name() or "", target:name())
        os.tryrm(root_dir)

        local srcfiles, dstfiles = target:installfiles(root_dir)
        if srcfiles and #srcfiles > 0 and dstfiles and #dstfiles > 0 then
            for idx, srcfile in ipairs(srcfiles) do
                os.trycp(srcfile, dstfiles[idx])
            end
        else
            return
        end

        local archive_path = path.join(config.buildir(), "packages", archive_name)
        local old_dir = os.cd(root_dir)
        local archive_files = os.files("**")
        os.cd(old_dir)
        archive.archive(path.absolute(archive_path), archive_files, { curdir = root_dir })
    end)

    after_build(function(target)
        import("core.project.depend")
        import("core.project.project")
        import("core.project.task")

        depend.on_changed(function()
            local srcfiles, dstfiles = target:installfiles()
            if srcfiles and #srcfiles > 0 and dstfiles and #dstfiles > 0 then
                task.run("install", { target = target:name() })
            end
        end, { changed = target:is_rebuilt(), files = { target:targetfile() } })
    end)
