#include <SFML/Graphics/StencilMode.hpp>

#include <catch2/catch_test_macros.hpp>

#include <GraphicsUtil.hpp>
#include <type_traits>

TEST_CASE("[Graphics] sf::StencilMode")
{
    SECTION("Type traits")
    {
        STATIC_CHECK(std::is_copy_constructible_v<sf::StencilMode>);
        STATIC_CHECK(std::is_copy_assignable_v<sf::StencilMode>);
        STATIC_CHECK(std::is_nothrow_move_constructible_v<sf::StencilMode>);
        STATIC_CHECK(std::is_nothrow_move_assignable_v<sf::StencilMode>);
    }

    SECTION("Construction")
    {
        SECTION("Default constructor")
        {
            const sf::StencilMode stencilMode;
            CHECK(stencilMode.stencilComparison == sf::StencilMode::Comparison::Always);
            CHECK(stencilMode.stencilUpdateOperation == sf::StencilMode::UpdateOperation::Keep);
            CHECK(stencilMode.stencilReference == 0);
            CHECK(stencilMode.stencilMask == ~0u);
            CHECK(stencilMode.stencilOnly == false);
        }

        SECTION("Verbose constructor")
        {
            const sf::StencilMode
                stencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true);
            CHECK(stencilMode.stencilComparison == sf::StencilMode::Comparison::Equal);
            CHECK(stencilMode.stencilUpdateOperation == sf::StencilMode::UpdateOperation::Replace);
            CHECK(stencilMode.stencilReference == 1);
            CHECK(stencilMode.stencilMask == 0u);
            CHECK(stencilMode.stencilOnly == true);
        }
    }

    SECTION("Operators")
    {
        SECTION("operator==")
        {
            CHECK(sf::StencilMode() == sf::StencilMode());
            CHECK(sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true) ==
                  sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true));

            CHECK_FALSE(
                sf::StencilMode() ==
                sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true));
            CHECK_FALSE(
                sf::StencilMode(sf::StencilMode::Comparison::Greater, sf::StencilMode::UpdateOperation::Invert, 0, ~0u, false) ==
                sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true));
        }

        SECTION("operator!=")
        {
            CHECK_FALSE(sf::StencilMode() != sf::StencilMode());
            CHECK_FALSE(
                sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true) !=
                sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true));

            CHECK(sf::StencilMode() !=
                  sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true));
            CHECK(sf::StencilMode(sf::StencilMode::Comparison::Greater, sf::StencilMode::UpdateOperation::Invert, 0, ~0u, false) !=
                  sf::StencilMode(sf::StencilMode::Comparison::Equal, sf::StencilMode::UpdateOperation::Replace, 1, 0u, true));
        }
    }
}
