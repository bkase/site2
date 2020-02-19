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
        key="katex-css"
        rel="stylesheet"
        href="https://cdn.jsdelivr.net/npm/katex@0.11.1/dist/katex.min.css"
        integrity="sha384-zB1R0rpPzHqg7Kpt0Aljp8JPLqbXI3bhnPWROx27a9N0Ll6ZP/+DiW/UqRcLbRjq"
        crossorigin=true
      />,
      <script
        defer=true
        key="katex-js"
        src="https://cdn.jsdelivr.net/npm/katex@0.11.1/dist/katex.min.js"
        integrity="sha384-y23I5Q6l+B6vatafAwxRu/0oK/79VlbSz7Q9aiSZUvyWYIYsd+qj+o24G5ZU2zJz"
        crossorigin=true
      />,
      <script
        defer=true
        key="katex-auto"
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
          [fontSize(Sizes.h1), marginBottom(`rem(6.375))],
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

let headingStyle =
  style([
    display(`flex),
    alignItems(`baseline),
    Typeface.pragmata,
    fontWeight(`normal),
    marginBottom(`rem(1.0)),
    paddingTop(`rem(0.5)),
    paddingBottom(`rem(0.5)),
  ]);

module H2 =
  Wrap({
    let className =
      merge([
        headingStyle,
        style([
          fontSize(`px(29)),
          media(MediaQuery.tablet, [fontSize(`px(38))]),
        ]),
      ]);
    let element = <h2 className />;
  });

let copySized =
  style([
    fontSize(Sizes.Mobile.body),
    media(MediaQuery.tablet, [fontSize(Sizes.body)]),
  ]);

module H3 =
  Wrap({
    let className =
      merge([headingStyle, copySized, style([fontWeight(`bold)])]);
    let element = <h3 className />;
  });

let bodyStyle = merge([P.withBottom, copySized]);

let changedSize = size =>
  style(
    switch (size) {
    | `Smaller => [
        fontSize(`rem(1.)),
        media(MediaQuery.tablet, [fontSize(Sizes.body)]),
      ]
    | `Bigger => [fontSize(Sizes.body)]
    | `CustomRem(mobile, larger) => [
        fontSize(`rem(mobile)),
        media(MediaQuery.tablet, [fontSize(`rem(larger))]),
      ]
    },
  );

module A = {
  include Wrap({
    let className =
      merge([
        bodyStyle,
        style([color(Style.Colors.green), hover([textDecoration(`none)])]),
      ]);
    let element = <a className />;
  });

  module R =
         (
           FontChange: {
             let config: [ | `Smaller | `Bigger | `CustomRem(float, float)];
           },
         ) => {
    [@react.component]
    let make = (~href, ~children) => {
      <a className={merge([className, changedSize(FontChange.config)])} href>
        children
      </a>;
    };
  };
};

module Sup = {
  include Wrap({
    let className =
      merge([
        bodyStyle,
        style([
          color(Style.Colors.green),
          display(`inlineBlock),
          marginTop(`em(-1.)), // make line height not go crazy here
          marginBottom(`em(0.)), // make line height not go crazy here
          hover([textDecoration(`none)]),
        ]),
      ]);
    let element = <sup className />;
  });

  module A =
    A.R({
      let config = `CustomRem((1., 1.125));
    });
  module R = {
    [@react.component]
    let make = (~id="", ~children) => {
      let content = children##props##children;
      let href = children##props##href;
      <sup className id> <A href> content </A> </sup>;
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

module Ol = {
  include Wrap({
    let className = merge([bodyStyle, listStyle]);

    let element = <ol className />;
  });

  module A =
    A.R({
      let config = `CustomRem((1.25, 1.5));
    });
  module R = {
    [@react.component]
    let make = (~children) => {
      let withBackRefIn:
        option(
          (. ((. React.element, string) => React.element)) => React.element,
        ) = [%raw
        {|
        (function() {
          const b0 = !Props.children;
          if (b0) {
            return undefined;
          }

          const b1 = !Props.children.length;
          if (b1) {
            return undefined;
          }

          const nextChildrenLength = Props.children[0].props.children.length;
          const b2 = !nextChildrenLength;
          if (b2) {
            return undefined;
          }

          const hasProps = Props.children[0].props.children[nextChildrenLength-1].props;
          if (!hasProps) {
            return undefined;
          }

          const name = Props.children[0].props.children[nextChildrenLength-1].props.className;
          const isFootnote = name == "footnote-backref";
          return (f => {
            const children_ = [...children];
            return children_.map(child => {
              const nextChildrenLength = child.props.children.length;
              return (
                 React.createElement("li",
                                     { "id": child.props.id },
                 child.props.children.map((inner, i) => {
                  if (i === nextChildrenLength-1) {
                    return f(inner.props.children, inner.props.href);
                  } else {
                    return inner;
                  }
              })
                 )
                 );
            });
          });
        })()
      |}
      ];
      switch (withBackRefIn) {
      | Some(f) =>
        <ol className>
          {f(. (. content, href) =>
             <span
               className={style([
                 paddingLeft(`rem(0.5)),
                 paddingRight(`rem(0.5)),
               ])}>
               <A href> content </A>
             </span>
           )}
        </ol>
      | None => <ol className> children </ol>
      };
    };
  };
};

module Img =
  Wrap({
    let className = style([width(`percent(100.))]);

    let element = <img className />;
  });

module Hr =
  Wrap({
    let className =
      style([
        width(`percent(100.)),
        border(`zero, `none, `rgb((0, 0, 0))),
        backgroundColor(Style.Colors.navy(0.5)),
        height(`px(3)),
      ]);

    let element = <hr className />;
  });

module InlineCode =
  Wrap({
    let className =
      merge([
        bodyStyle,
        style([
          backgroundColor(Style.Colors.navy(0.05)),
          paddingLeft(`rem(0.5)),
          paddingRight(`rem(0.5)),
          paddingTop(`rem(0.15)),
          paddingBottom(`rem(0.15)),
          borderRadius(`px(8)),
        ]),
      ]);

    let element = <code className />;
  });

module Code =
  Wrap({
    let className =
      merge([
        P.withBottom, // for some reason rems are interpretted differently here :(
        style([
          display(`block),
          overflow(`scroll),
          fontSize(`px(18)),
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
          media(MediaQuery.tablet, [fontSize(`px(24))]),
        ]),
      ]);

    let element = <CodeBlock extraClassName=className className />;
  });

module P = {
  include Wrap({
    let className = bodyStyle;
    let element = <p className />;
  });

  let className' = P.withBottom;

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
