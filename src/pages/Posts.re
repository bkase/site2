// This is the layout for the docs MDX pages

open Style;

module Style = {
  open Css;

  let content =
    style([
      media(
        MediaQuery.extraLarge,
        [
          maxWidth(`rem(56.625)),
          marginLeft(`rem(5.75)),
          marginRight(`rem(4.875)),
        ],
      ),
    ]);

  let page =
    style([
      maxWidth(`rem(56.625)),
      margin(`auto),
      paddingLeft(`rem(1.0)),
      paddingRight(`rem(1.0)),
      media(
        MediaQuery.halfTablet,
        [paddingLeft(`rem(1.5)), paddingRight(`rem(1.5))],
      ),
      media(
        MediaQuery.tablet,
        [paddingLeft(`rem(2.375)), paddingRight(`rem(2.375))],
      ),
      media(
        MediaQuery.extraLarge,
        [
          maxWidth(`vw(100.)),
          display(`flex),
          marginTop(`rem(6.)),
          paddingLeft(`zero),
          paddingRight(`zero),
        ],
      ),
    ]);
};

let () = SyntaxHighlighting.draw();

[@react.component]
let make = (~children) => {
  React.useEffect(() => {
    Control.scrollable();
    None;
  });

  <Page extraHead=BlogComponents.Katex.head>
    <div className=Style.page>
      <Nav topLink={Some(`Blog)} />
      <div className=Style.content>
        <Next.MDXProvider
          components={
            "h1": BlogComponents.H1.make,
            "h2": BlogComponents.H2.make,
            "p": BlogComponents.P.make,
            "a": BlogComponents.A.make,
            "code": BlogComponents.Code.make,
            "inlineCode": BlogComponents.InlineCode.make,
            "ul": BlogComponents.Ul.make,
            "ol": BlogComponents.Ol.R.make,
            "hr": BlogComponents.Hr.make,
            "img": BlogComponents.Img.make,
            "sup": BlogComponents.Sup.R.make,
          }>
          children
        </Next.MDXProvider>
      </div>
    </div>
  </Page>;
  // let router = Next.Router.useRouter();
};

let default = make;
