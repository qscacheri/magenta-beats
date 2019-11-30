/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   closed_wav;
    const int            closed_wavSize = 13432;

    extern const char*   kick_wav;
    const int            kick_wavSize = 134300;

    extern const char*   open_wav;
    const int            open_wavSize = 28882;

    extern const char*   snare_wav;
    const int            snare_wavSize = 10056;

    extern const char*   JosefinSansLight_ttf;
    const int            JosefinSansLight_ttfSize = 81764;

    extern const char*   down_arrow_png;
    const int            down_arrow_pngSize = 8591;

    extern const char*   up_arrow_png;
    const int            up_arrow_pngSize = 9201;

    extern const char*   flame_svg;
    const int            flame_svgSize = 1594;

    extern const char*   snow_flake_svg;
    const int            snow_flake_svgSize = 8923;

    extern const char*   magenta_on_svg;
    const int            magenta_on_svgSize = 636;

    extern const char*   user_on_svg;
    const int            user_on_svgSize = 633;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 11;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
