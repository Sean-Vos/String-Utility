workspace("String Utility")
    configurations({"Debug", "Release"})
    location("./Build")

    project("StringUtility")
        kind("ConsoleApp")
        language("C++")
        files ({
            "Source/StringUtility.hpp",
            "Test/Tests.cpp"
        })

        includedirs({
            "Source/"
        })