module Typeface: {
  let pragmata: Css.rule;
  let arame: Css.rule;
  let futura: Css.rule;
} = {
  let _arame: unit =
    // bs-css font face doesn't support woff and woff2 annotations
    Css.(
      global(
        "@font-face",
        [
          fontFamily("Arame"),
          unsafe(
            "src",
            {|
        local('Arame-Regular'),
        url('/static/fonts/arame/ArameRegular.woff2') format('woff2'),
        url('/static/fonts/arame/ArameRegular.woff') format('woff'),
        url('/static/fonts/arame/ArameRegular.ttf') format('truetype');
        |},
          ),
          fontWeight(`normal),
          fontStyle(`normal),
        ],
      )
    );

  // fonts load via side-effect
  let _pragmataPro: unit =
    Css.(
      global(
        "@font-face",
        [
          fontFamily("PragmataPro"),
          unsafe(
            "src",
            {|
        local('PragmataPro'),
        url('/static/fonts/essential-pragmatapro/EssentialPro.woff2') format('woff2'),
        url('/static/fonts/essential-pragmatapro/EssentialPro.woff') format('woff');
        |},
          ),
          fontWeight(`normal),
          fontStyle(`normal),
        ],
      )
    );

  let pragmata = Css.fontFamily("PragmataPro, \"Courier New\", monospace");
  let arame = Css.fontFamily("Arame, sans-serif");
  let futura =
    Css.fontFamily(
      "Futura-CondensedMedium, AvenirNextCondensed-Medium, HelveticaNeue-CondensedBold, \"Ubuntu Condensed\", \"Liberation Sans Narrow\", \"Franklin Gothic Demi Cond\", \"Arial Narrow\", sans-serif-condensed, Arial, \"Trebuchet MS\", \"Lucida Grande\", Tahoma, Verdana, sans-serif",
    );
};

module Sizes = {
  // computed via a golden-ratio typographic scale
  // 24 * ((2*φ)^(i/3)) forall 0<i<3
  let nav = `rem(3.3125); // 53px
  let h1 = `rem(4.875); // 78px
  let body = `rem(1.5); // 24px
  module Mobile = {
    let nav = `rem(2.0625); // 33px
    let h1 = `rem(3.); // 48px
    let body = body; // 16px
  };
};

module Colors = {
  let navy = alpha => `rgba((1, 4, 62, alpha));
  let black = `hex("000219");
  let green = `hex("1B998B");
  let orange = `hex("FC9E4F");

  module Code = {
    let comment = navy(0.25);
    let punctuation = black;
    let property = black;
    let selector = black;
    let operator = black;
    let string = green;
    let keyword = orange;
    let function_ = black;
    let variable = black;
  };
};

module MediaQuery = {
  let extraLarge = "(min-width: 75rem)";
  let largeWithMargins = "(min-width: 70.75rem)";
  let tablet = "(min-width: 49.75rem)";
  let halfTablet = "(min-width: 36.5rem)";
};

module Control = {
  let scrollable = () =>
    Css.(
      global(
        "body",
        [
          overflow(`scroll),
          width(`percent(100.)),
          height(`percent(100.)),
        ],
      )
    );

  let no_scrollable = () =>
    Css.(
      global(
        "body",
        [
          overflow(`hidden),
          width(`percent(100.)),
          height(`percent(100.)),
        ],
      )
    );
};
