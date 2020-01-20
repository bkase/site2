open Style;

module Style = {
  open Css;

  module MediaQuery' = {
    let fullFace = "(min-width: 89rem)";
  };

  let title =
    style([
      media(
        MediaQuery.extraLarge,
        [marginTop(`rem(6.)), marginLeft(`rem(4.875))],
      ),
    ]);

  let body =
    style([
      maxWidth(`rem(14.25)),
      media(MediaQuery.halfTablet, [maxWidth(`rem(20.))]),
      media(MediaQuery.tablet, [maxWidth(`rem(33.75))]),
      media(
        MediaQuery.extraLarge,
        [
          maxWidth(`rem(28.25)),
          marginLeft(`rem(5.875)),
          marginTop(`rem(1.3125)),
        ],
      ),
    ]);

  let content =
    style([
      paddingLeft(`rem(1.375)),
      paddingRight(`rem(1.375)),
      media(
        MediaQuery.tablet,
        [paddingLeft(`rem(2.1875)), paddingRight(`rem(2.1875))],
      ),
      media(
        MediaQuery.extraLarge,
        [
          paddingLeft(`zero),
          paddingRight(`zero),
          display(`flex),
          marginTop(`rem(-3.)) // I don't know why we need this
        ],
      ),
    ]);

  let img =
    style([
      zIndex(-1),
      opacity(0.7),
      position(`absolute),
      bottom(`px(-240)),
      left(`px(100)),
      width(`px(558)),
      media(
        MediaQuery.halfTablet,
        [width(`px(760)), left(`px(200)), bottom(`px(-313))],
      ),
      media(
        MediaQuery.tablet,
        [width(`px(880)), left(`px(373)), bottom(`px(-363))],
      ),
      media(MediaQuery.extraLarge, [left(`px(618))]),
      media(MediaQuery'.fullFace, [right(`px(-44)), left(`unset)]),
    ]);

  let extraPMarginBottom = marginBottom(`rem(2.5));

  let topP =
    style([
      extraPMarginBottom,
      media(MediaQuery.halfTablet, [maxWidth(`rem(20.))]),
      media(MediaQuery.tablet, [maxWidth(`none)]),
    ]);

  let innerP =
    style([
      maxWidth(`rem(12.5)),
      extraPMarginBottom,
      media(MediaQuery.halfTablet, [maxWidth(`rem(20.))]),
      media(MediaQuery.tablet, [maxWidth(`none)]),
    ]);
};

let s = s => ReasonReact.string(s);

module P =
  BlogComponents.P.R({
    let config = `Smaller;
  });
module A =
  BlogComponents.A.R({
    let config = `Smaller;
  });
module H1 = BlogComponents.H1.R;

[@react.component]
let make = () => {
  React.useEffect(() => {
    Control.no_scrollable();
    Some(Control.scrollable);
  });

  <Page title="Brandon Kase">
    <div
      className=Css.(
        style([
          height(`percent(100.)),
          width(`percent(100.)),
          overflow(`hidden),
        ])
      )>
      <div
        className=Css.(
          merge([
            Style.title,
            style([
              display(`none),
              media(MediaQuery.extraLarge, [display(`block)]),
            ]),
          ])
        )>
        <H1> {s("Brandon Kase")} </H1>
      </div>
      <div className=Style.content>
        <img
          className=Style.img
          src="/static/Brandon_kase.jpg"
          srcSet="/static/Brandon_kase@2x.jpg 2x"
        />
        <Nav topLink=None />
        <div
          className=Css.(
            merge([
              Style.title,
              style([
                display(`block),
                media(MediaQuery.extraLarge, [display(`none)]),
              ]),
            ])
          )>
          <H1> {s("Brandon Kase")} </H1>
        </div>
        <div className=Style.body>
          <P className=Style.topP>
            {s("Head of product engineering at o(1) labs, building the ")}
            <A href="https://codaprotocol.com"> {s("coda protocol")} </A>
            {s(".")}
          </P>
          <P className=Style.innerP>
            {s("Typed functional programming for life. Find me ")}
            <A
              href="https://www.youtube.com/results?search_query=brandon+kase">
              {s("proselytizing")}
            </A>
            {s(" at a conference near you. Dm me on ")}
            <A href="https://twitter.com/bkase_"> {s("twitter")} </A>
            {s(". I use ")}
            <A href="https://github.com/bkase"> {s("github")} </A>
            {s(" to build stuff on the side. In theory, there will be ")}
            <A href="/posts/sample"> {s("blog")} </A>
            {s({j|\u00A0posts.|j})}
          </P>
        </div>
      </div>
    </div>
  </Page>;
};
