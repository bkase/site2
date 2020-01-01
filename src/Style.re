module Typeface: {
  let pragmata: Css.rule;
  let arame: Css.rule;
  let futura: Css.rule;
} = {
  let labels = [
    (`bold, `italic, "Bold Italic"),
    (`normal, `italic, "Italic"),
    (`normal, `normal, "Regular"),
    (`bold, `normal, "Bold"),
  ];

  let () = {
    // fonts load via side-effect
    let _face: list(string) =
      labels
      |> List.map(((weight, style, suffix)) =>
           Css.fontFace(
             ~fontFamily="PragmataPro",
             ~src=[
               `localUrl("PragmataPro " ++ suffix),
               `localUrl("PragmataPro-" ++ suffix),
             ],
             ~fontWeight=weight,
             ~fontStyle=style,
             (),
           )
         );

    ();
  };

  let _arame: string =
    Css.fontFace(
      ~fontFamily="0Arame",
      ~src=[`localUrl("Arame-Regular")],
      ~fontWeight=`normal,
      ~fontStyle=`normal,
      (),
    );

  let pragmata = Css.fontFamily("PragmataPro, \"Courier New\", monospace");
  let arame = Css.fontFamily("\"0Arame\", sans-serif");
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
    let body = `rem(1.); // 16px
  };
};

module Colors = {
  let navy = alpha => `rgba((1, 4, 62, alpha));
  let black = `hex("000219");
};

module MediaQuery = {
  let extraLarge = "(min-width: 75rem)";
  let tablet = "(min-width: 49.75rem)";
  let halfTablet = "(min-width: 36.5rem)";
};
