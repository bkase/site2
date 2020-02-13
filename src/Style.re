module Typeface = {
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
    let body = `rem(1.125); // 18px
  };
};

module Colors = {
  let navy = alpha => `rgba((1, 4, 62, alpha));
  let black = `hex("000219");
  let green = `hex("1B998B");
  let orange = `hex("FC9E4F");

  module Content = {
    let linkAccent = green;
    let copy = navy(1.);
  };

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

module P = {
  open Css;

  let base =
    style([
      alignItems(`baseline),
      Typeface.pragmata,
      lineHeight(`abs(1.4)),
    ]);

  let withBottom = merge([base, style([marginBottom(`em(1.0))])]);
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
