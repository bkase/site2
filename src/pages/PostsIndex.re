open Style;

module Style = {
  open Css;

  let itemLink =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      alignItems(`center),
      width(`percent(100.)),
      color(Colors.Content.copy),
      textDecoration(`underline),
      hover([color(Colors.Content.linkAccent), textDecoration(`none)]),
      fontSize(`rem(1.5)),
      media(MediaQuery.halfTablet, [fontSize(`rem(2.))]),
      media(MediaQuery.tablet, [fontSize(`rem(2.5))]),
      paddingTop(`rem(0.5)),
      paddingBottom(`rem(0.5)),
      marginBottom(`em(0.5)),
      // nudge to adjust for aramo blank area on left
      marginLeft(`px(1)),
    ]);

  let underlined =
    style([textDecoration(`underline), hover([textDecoration(`none)])]);

  let ul =
    style([
      marginTop(`rem(1.)),
      listStyle(`none, `inside, `none),
      media(MediaQuery.halfTablet, [marginTop(`rem(1.5))]),
      media(MediaQuery.tablet, [marginTop(`rem(2.625))]),
    ]);

  let date =
    merge([
      P.base,
      style([
        textDecoration(`none),
        fontSize(`rem(1.)),
        media(MediaQuery.halfTablet, [fontSize(`rem(1.5))]),
        media(MediaQuery.tablet, [fontSize(`rem(2.))]),
        marginRight(`rem(2.)),
      ]),
    ]);

  let title =
    merge([
      P.base,
      style([
        // nudge such that alignItems(center) aligns at baseline on mobile
        marginTop(`px(2)),
        textAlign(`right),
        fontSize(`rem(1.5)),
        media(MediaQuery.halfTablet, [fontSize(`rem(2.))]),
        media(MediaQuery.tablet, [fontSize(`rem(2.5))]),
      ]),
    ]);
};

module A =
  BlogComponents.A.R({
    let config = `Smaller;
  });
module H1 = BlogComponents.H1.R;

module Item = {
  [@react.component]
  let make = (~link, ~date, ~title) => {
    let _date = date;
    let prettyDate: string = [%raw
      "Props.date.toLocaleDateString(undefined, { month: \"2-digit\", day: \"2-digit\", year: \"2-digit\" })"
    ];

    <a href=link className=Style.itemLink>
      <p className=Style.date> {React.string(prettyDate)} </p>
      <p className=Style.title> {React.string(title)} </p>
    </a>;
  };
};

module Subscribe = {
  module Style = {
    open Css;

    let title =
      merge([
        P.withBottom,
        style([
          width(`percent(100.)),
          fontSize(`rem(1.)),
          padding2(~v=`rem(0.5), ~h=`rem(0.75)),
          border(`px(3), `solid, Colors.navy(0.1)),
          media(
            MediaQuery.halfTablet,
            [
              fontSize(`rem(1.5)),
              padding2(~v=`rem(0.75), ~h=`rem(1.)),
              border(`px(5), `solid, Colors.navy(0.1)),
            ],
          ),
          media(
            MediaQuery.tablet,
            [
              fontSize(`rem(2.)),
              padding2(~v=`rem(1.), ~h=`rem(1.5)),
              border(`px(7), `solid, Colors.navy(0.1)),
            ],
          ),
        ]),
      ]);
    let container =
      style([
        display(`flex),
        justifyContent(`spaceBetween),
        width(`percent(100.)),
        alignItems(`center),
        marginTop(`zero),
        media(MediaQuery.extraLarge, [marginTop(`rem(1.5))]),
      ]);
    let link =
      style([
        color(Colors.Content.linkAccent),
        hover([textDecoration(`none)]),
      ]);
  };

  [@react.component]
  let make = () => {
    <div className=Style.container>
      <p className=Style.title>
        {React.string("You can subscribe to an ")}
        <a href="/static/blog-rss.xml" className=Style.link>
          {React.string("rss feed")}
        </a>
        {React.string({j| and soon a mailing\u00A0list.|j})}
      </p>
    </div>;
  };
};

[@react.component]
let make = () => {
  React.useEffect(() => {
    Control.scrollable();
    None;
  });

  <Page title="Blog Posts" description="The ramblings of Brandon Kase">
    <div className=Posts.Style.page>
      <Nav topLink={Some(`Blog)} />
      <div className=Posts.Style.content>
        <Subscribe />
        <ul className=Style.ul>
          {PostsIndexContent.posts
           |> List.map(post =>
                <li key=post##urlPath>
                  <Item
                    link=post##urlPath
                    date={Js.Date.fromString(post##date)}
                    title=post##title
                  />
                </li>
              )
           |> Array.of_list
           |> React.array}
        </ul>
      </div>
    </div>
  </Page>;
};
