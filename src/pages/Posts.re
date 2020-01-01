// This is the layout for the docs MDX pages

open Style;

module Style = {
  open Css;

  let () =
    global(
      "html",
      [
        fontSize(`percent(120.)),
        media(MediaQuery.tablet, [fontSize(`percent(100.))]),
      ],
    );

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
      paddingLeft(`rem(1.5)),
      paddingRight(`rem(1.5)),
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

[@react.component]
let make = (~children) => {
  <Page>

      <div className=Style.page>
        <Nav topLink={Some(`Blog)} />
        <div className=Style.content>
          <Next.MDXProvider
            components={
              "h1": BlogComponents.H1.make,
              "h2": BlogComponents.H2.make,
              "p": BlogComponents.P.make,
              "a": BlogComponents.A.make,
            }>
            children
          </Next.MDXProvider>
        </div>
      </div>
    </Page>;
    // let router = Next.Router.useRouter();
};

let default = make;
