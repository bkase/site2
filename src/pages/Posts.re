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
          // using paddingTop not marginTop since marginTop screws up body
          paddingTop(`rem(6.)),
          paddingLeft(`zero),
          paddingRight(`zero),
        ],
      ),
    ]);
};

let () = SyntaxHighlighting.draw();

module Metadata = {
  type t = {description: option(string)};

  module Processed = {
    type t = {
      description: string,
      title: string,
    };
  };

  module ChildrenItem = {
    type inner = {children: string};
    type t = {props: inner};
  };

  let process = (t: t, children: array(ChildrenItem.t)): Processed.t => {
    let description =
      switch (t.description) {
      | None =>
        failwith("Implement whenever there's a blog post with no description")
      | Some(description) => description
      };
    let title = children[0].props.children;
    {Processed.title, description};
  };
};

[@react.component]
let make = (~meta: Metadata.t, ~children) => {
  React.useEffect(() => {
    Control.scrollable();
    None;
  });

  let metadata: Metadata.Processed.t = Metadata.process(meta, children);

  <Page
    title={metadata.title}
    description={metadata.description}
    extraHead=BlogComponents.Katex.head>
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
            "HalfImageWrapper": HalfImageWrapper.make,
          }>
          {Obj.magic(children)}
        </Next.MDXProvider>
      </div>
    </div>
  </Page>;
  // let router = Next.Router.useRouter();
};

let default = make;
