module type Component = {
  let className: string;
  let element: React.element;
};

module Wrap = (C: Component) => {
  let className = C.className;
  let make = props => {
    ReasonReact.cloneElement(C.element, ~props, [||]);
  };
};

open Css;

let headerStyle = style([display(`flex), marginBottom(`rem(0.5))]);

open Style;

module H1 =
  Wrap({
    let className =
      merge([
        headerStyle,
        style([
          alignItems(`baseline),
          fontSize(Sizes.Mobile.h1),
          Typeface.futura,
          fontWeight(`medium),
          textTransform(`uppercase),
          marginBottom(`rem(3.5)),
          // nudge to adjust for futura starting rightwards
          marginLeft(`px(-2)),
          media(
            MediaQuery.tablet,
            [fontSize(Sizes.h1), marginBottom(`rem(6.5))],
          ),
        ]),
      ]);
    let element = <h1 className />;
  });

module H2 =
  Wrap({
    let className =
      merge([
        headerStyle,
        style([alignItems(`baseline), fontWeight(`light)]),
      ]);
    let element = <h2 className />;
  });

module P =
  Wrap({
    let className =
      style([
        alignItems(`baseline),
        Typeface.pragmata,
        fontSize(Sizes.Mobile.body),
        lineHeight(`abs(1.4)),
        marginBottom(`em(1.0)),
        media(MediaQuery.tablet, [fontSize(Sizes.body)]),
      ]);
    let element = <p className />;
  });
