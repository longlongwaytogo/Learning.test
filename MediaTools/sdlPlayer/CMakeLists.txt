
INCLUDE_DIRECTORIES("./thirdParty/SDL2-2.0.8/include")
INCLUDE_DIRECTORIES("./thirdParty\\SDL2_mixer-2.0.2\\include")

LINK_DIRECTORIES("./thirdParty/SDL2-2.0.8/lib/x64")
LINK_DIRECTORIES("./thirdParty\\SDL2_mixer-2.0.2\\lib\\x64")
LINK_LIBRARIES("SDL2main.lib" "SDL2.lib" "SDL2_Mixer.lib")

add_executable(sdlMp3Player main.cpp)