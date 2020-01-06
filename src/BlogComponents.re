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

open Style;

module Katex = {
  let head =
    ReasonReact.array([|
      <link
        rel="stylesheet"
        href="https://cdn.jsdelivr.net/npm/katex@0.11.1/dist/katex.min.css"
        integrity="sha384-zB1R0rpPzHqg7Kpt0Aljp8JPLqbXI3bhnPWROx27a9N0Ll6ZP/+DiW/UqRcLbRjq"
        crossorigin=true
      />,
      <script
        defer=true
        src="https://cdn.jsdelivr.net/npm/katex@0.11.1/dist/katex.min.js"
        integrity="sha384-y23I5Q6l+B6vatafAwxRu/0oK/79VlbSz7Q9aiSZUvyWYIYsd+qj+o24G5ZU2zJz"
        crossorigin=true
      />,
      <script
        defer=true
        src="https://cdn.jsdelivr.net/npm/katex@0.11.1/dist/contrib/auto-render.min.js"
        integrity="sha384-kWPLUVMOks5AQFrykwIup5lo0m3iMkkHrD0uJ4H5cjeGihAutqP0yW0J6dpFiVkI"
        crossorigin=true
        onLoad=[%raw {|"renderMathInElement(document.body);"|}]
      />,
    |]);
};

module H1 = {
  include Wrap({
    let className =
      style([
        display(`flex),
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
      style([
        display(`flex),
        alignItems(`baseline),
        Typeface.pragmata,
        fontSize(`px(38)),
        fontWeight(`normal),
        marginBottom(`rem(1.0)),
        paddingTop(`rem(0.5)),
        paddingBottom(`rem(0.5)),
      ]);
    let element = <h2 className />;
  });

let pStyle =
  style([
    alignItems(`baseline),
    Typeface.pragmata,
    lineHeight(`abs(1.4)),
    marginBottom(`em(1.0)),
  ]);

let bodyStyle = merge([pStyle, style([fontSize(Sizes.body)])]);

let changedSize = size =>
  style(
    switch (size) {
    | `Smaller => [
        fontSize(`rem(1.)),
        media(MediaQuery.tablet, [fontSize(Sizes.body)]),
      ]
    | `Bigger => [fontSize(Sizes.body)]
    },
  );

module P = {
  include Wrap({
    let className = bodyStyle;
    let element = <p className />;
  });

  let className' = pStyle;

  module R = (FontChange: {let config: [ | `Smaller | `Bigger];}) => {
    [@react.component]
    let make = (~className="", ~children) => {
      <p
        className={merge([
          className',
          className,
          changedSize(FontChange.config),
        ])}>
        children
      </p>;
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

  module R = (FontChange: {let config: [ | `Smaller | `Bigger];}) => {
    [@react.component]
    let make = (~href, ~children) => {
      <a className={merge([className, changedSize(FontChange.config)])} href>
        children
      </a>;
    };
  };
};

let listStyle =
  style([
    marginLeft(`rem(2.25)),
    media(MediaQuery.largeWithMargins, [marginLeft(`zero)]),
  ]);

module Ul =
  Wrap({
    let className = merge([bodyStyle, listStyle]);

    let element = <ul className />;
  });

module Ol =
  Wrap({
    let className = merge([bodyStyle, listStyle]);

    let element = <ol className />;
  });

module Img =
  Wrap({
    let className = style([width(`percent(100.))]);

    let element = <img className />;
  });

module Code =
  Wrap({
    let className =
      merge([
        pStyle, // for some reason rems are interpretted differently here :(
        style([
          display(`block),
          overflow(`scroll),
          fontSize(`px(24)),
          backgroundColor(Style.Colors.navy(0.03)),
          paddingLeft(`px(16)),
          paddingRight(`px(16)),
          paddingTop(`px(8)),
          paddingBottom(`px(8)),
          Css.borderRadius(`px(16)),
          marginLeft(`px(-8)),
          marginRight(`zero),
          media(
            MediaQuery.halfTablet,
            [marginLeft(`px(-16)), marginRight(`zero)],
          ),
        ]),
      ]);

    let element = <CodeBlock extraClassName=className className />;
  });
