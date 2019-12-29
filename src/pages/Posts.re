// This is the layout for the docs MDX pages

module Style = {
  open Css;

  let content =
    style([
      maxWidth(`rem(43.)),
      marginLeft(`rem(1.)),
      selector(
        "p > code, li > code",
        [
          boxSizing(`borderBox),
          padding2(~v=`px(2), ~h=`px(6)),
          borderRadius(`px(4)),
        ],
      ),
    ]);

  let page =
    style([
      display(`block),
      justifyContent(`center),
      margin(`auto),
      marginTop(`rem(4.)),
      padding2(~v=`zero, ~h=`rem(2.)),
    ]);
};

[@react.component]
let make = (~children) => {
  <Page>

      <div className=Style.page>
        <p> {React.string("Side nav")} </p>
        <div className=Style.content>
          <Next.MDXProvider
            components={
              "h1": BlogComponents.H1.make,
              "h2": BlogComponents.H2.make,
            }>
            children
          </Next.MDXProvider>
        </div>
      </div>
    </Page>;
    // let router = Next.Router.useRouter();
};

let default = make;
