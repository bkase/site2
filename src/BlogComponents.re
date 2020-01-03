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

module H1 = {
  include Wrap({
    let className =
      merge([
        headerStyle,
        style([
          alignItems(`baseline),
          fontSize(Sizes.Mobile.h1),
          Typeface.futura,
          fontWeight(`medium),
          textTransform(`uppercase),
          marginBottom(`rem(2.125)),
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

  module R = {
    [@react.component]
    let make = (~children) => {
      <h1 className> children </h1>;
    };
  };
};

module H2 =
  Wrap({
    let className =
      merge([
        headerStyle,
        style([alignItems(`baseline), fontWeight(`light)]),
      ]);
    let element = <h2 className />;
  });

let bodyStyle =
  style([
    alignItems(`baseline),
    Typeface.pragmata,
    fontSize(Sizes.Mobile.body),
    lineHeight(`abs(1.4)),
    marginBottom(`em(1.0)),
    media(MediaQuery.tablet, [fontSize(Sizes.body)]),
  ]);

module P = {
  include Wrap({
    let className = bodyStyle;
    let element = <p className />;
  });

  let className' = className;

  module R = {
    [@react.component]
    let make = (~className="", ~children) => {
      <p className={merge([className', className])}> children </p>;
    };
  };
};

module A = {
  include Wrap({
    let className =
      merge([
        bodyStyle,
        style([color(Style.Colors.green), hover([textDecoration(`none)])]),
      ]);
    let element = <a className />;
  });

  module R = {
    [@react.component]
    let make = (~href, ~children) => {
      <a className href> children </a>;
    };
  };
};
