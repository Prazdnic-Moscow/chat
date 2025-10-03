cmake_minimum_required(VERSION 3.16)
project(my_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BCRYPT_LIB "/usr/local/lib/libbcrypt.a")
set(BCRYPT_INCLUDE_DIR "/usr/local/include")

find_package(Drogon REQUIRED)
find_package(Jsoncpp REQUIRED)


add_executable(${PROJECT_NAME}
    main.cc
    Controller/UserController.cc
    Service/UserService.cc
    Repository/UserRepository.cc
)

# Include пути
target_include_directories(${PROJECT_NAME} PRIVATE
    .
    /usr/local/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Drogon::Drogon
    jsoncpp
    /usr/local/lib/libbcrypt.a
)