#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include <util/CStringStream.hpp>
#include <util/StringStreamLite.hpp>
#include <util/BufferView.hpp>
#include <util/UniqueArray.hpp>
#include <util/ArraySupplier.hpp>
#include <util/ByteSplitter.hpp>
#include <util/TimeHandler.hpp>
#include <util/FilesystemTree.hpp>
#include <util/Types.hpp>
#include <util/Chars.h>
#include <util/SPIDevice.hpp>
#include <util/CVersion.h>

int main()
{
    stdio_init_all();

    MultiPtr<int, 2> int_ptr;

    CStringStream<256> css;

    css << "hello";

    css << 8 << 9;

    StringStreamLite ssl;

    ssl << 9 << 8 << 7 << "test";

    std::unique_ptr<int[]> ar = std::make_unique<int[]>(5);
    
    UniqueArray<int> arr = make_unique_array<int>(std::move(ar), 5);

    FilesystemTree fs;
    FilesystemNodeData user_folder = {"users", true};
    fs.AddNode(user_folder);
    fs.RemoveNode(user_folder);

    ByteSplitter<uint32_t, uint8_t> split;

    ArraySupplier<int, 5> as;
    as[0] = 0;
    as[1] = 1;

    // as.At<90>() = 7; // Will fail

    // use At<idx>() for compile-time and runtime, use [idx] for only runtime

    TimeHandler th;
    printf("Delta time: %llu\n", th.Update());

    th = TimeHandler(); // reset

    const char16_t* str16 = u"test";
    size_t str16_len = strlen16(str16);

    size_t bytes_used;
    char32_t codepoint = utf8_decode("my text", &bytes_used); // returns 'm'

    SPIDevice spidev = SPIDevice(10, 11, 12, 13);
    spidev.PrioritizeDevice();

    while (1)
    {
        printf("%s\n", css.GetCString());
        printf("%s\n", ssl.GetCString());
    }

}