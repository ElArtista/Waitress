#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <Waitress/Resolver.hpp>

TEST_CASE("Resolvers should convert the identifiers to uri's correctly", "[Resolver]")
{
    SECTION ("ForwardResolver should act like an identity resolver")
    {
        Waitress::FwResolver fwResv;
        REQUIRE(fwResv.Resolve("someId") == "someId");
    }

    SECTION ("JsonResolver should return uri's according to the passed json configuration")
    {
        Waitress::JsonResolver jsonResv;
        const std::string json(
            R"foo(
            [
                {
                    "id": "someId1",
                    "path": "somePath1"
                },
                {
                    "id": "someId2",
                    "path": "somePath2"
                },
                {
                    "id": "someId3",
                    "path": "somePath3"
                },
                {
                    "id": "someId4",
                    "path": "somePath4"
                },
                {
                    "id": "someId5",
                    "path": "somePath5"
                }
            ]
            )foo");
        jsonResv.LoadIdMap(std::move(json));
        REQUIRE(jsonResv.Resolve("someId3") == "somePath3");
    }
}
