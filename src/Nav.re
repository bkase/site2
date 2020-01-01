open Style;

module Style = {
  open Css;

  let linkBase =
    style([
      Typeface.arame,
      fontSize(Sizes.Mobile.nav),
      listStyleType(`none),
      marginBottom(`rem(2.)),
      media(
        MediaQuery.tablet,
        [fontSize(Sizes.nav), marginBottom(`rem(5.875))],
      ),
    ]);

  let topLink = hideOnLarge =>
    merge([
      linkBase,
      style([
        color(Colors.navy(1.0)),
        ...if (hideOnLarge) {
             [
               display(`block),
               media(MediaQuery.extraLarge, [display(`none)]),
             ];
           } else {
             [];
           },
      ]),
    ]);

  let otherLink = merge([linkBase, style([color(Colors.navy(0.25))])]);

  let list =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      lineHeight(`abs(1.0)),
      flexWrap(`wrap),
      paddingTop(`rem(3.)),
      marginBottom(`rem(1.5)),
      media(MediaQuery.tablet, [flexWrap(`nowrap), marginBottom(`zero)]),
      media(
        MediaQuery.extraLarge,
        [
          display(`block),
          marginLeft(`rem(4.875)),
          paddingTop(`rem(2.125)),
        ],
      ),
    ]);

  let growOnSwitch =
    style([
      flexBasis(`percent(50.)),
      media(MediaQuery.halfTablet, [flexBasis(`auto)]),
    ]);

  let navLink =
    style([
      color(Colors.navy(0.25)),
      textDecoration(`none),
      hover([color(Colors.green)]),
    ]);
};

let unpage = x =>
  switch (x) {
  | `Home => "BKASE"
  | `Blog => "BLOG"
  | `Videos => "VIDEOS"
  | `Projs => "PROJS"
  };

let otherPages = page => {
  let x = Option.value(page, ~default=`Home);
  [`Home, `Blog, `Videos, `Projs] |> List.filter(x' => x != x');
};

let href = page => {
  switch (page) {
  | `Home => Links.home
  | `Blog => Links.blog
  | `Videos => Links.video
  | `Projs => Links.projs
  };
};

let curry = (f, x, y) => f((x, y));

[@react.component]
let make = (~topLink) => {
  <ul className=Style.list>
    {ReasonReact.array(
       {let bottomList =
          otherPages(topLink)
          |> List.mapi((i, link) =>
               <li
                 className=Css.(
                   merge([
                     Style.otherLink,
                     ...if (i mod 2 == 1) {
                          [Style.growOnSwitch];
                        } else {
                          [];
                        },
                   ])
                 )>
                 <a className=Style.navLink href={href(link)}>
                   {ReasonReact.string(unpage(link))}
                 </a>
               </li>
             );
        {let topResolve = Option.value(topLink, ~default=`Home);
         [
           <li
             className=Css.(
               merge([
                 Style.topLink(Option.is_none(topLink)),
                 Style.growOnSwitch,
               ])
             )>
             {ReasonReact.string(unpage(topResolve))}
           </li>,
           ...bottomList,
         ]}
        |> Array.of_list},
     )}
  </ul>;
};
