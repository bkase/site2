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

  let topLink = merge([linkBase, style([color(Colors.navy(1.0))])]);

  let otherLink = merge([linkBase, style([color(Colors.navy(0.25))])]);

  let list =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      lineHeight(`abs(1.0)),
      flexWrap(`wrap),
      marginTop(`rem(3.)),
      marginBottom(`rem(1.5)),
      media(MediaQuery.tablet, [flexWrap(`nowrap), marginBottom(`zero)]),
      media(
        MediaQuery.extraLarge,
        [
          display(`block),
          marginLeft(`rem(4.875)),
          marginTop(`rem(2.125)),
        ],
      ),
    ]);

  let growOnSwitch =
    style([
      flexBasis(`percent(40.)),
      media(MediaQuery.flexMobileSwitch, [flexBasis(`auto)]),
    ]);
};

let curry = (f, x, y) => f((x, y));

[@react.component]
let make = (~topLink, ~links) => {
  <ul className=Style.list>
    {ReasonReact.array(
       {let bottomLis =
          links
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
                 {ReasonReact.string(link)}
               </li>
             );
        [
          <li className=Css.(merge([Style.topLink, Style.growOnSwitch]))>
            {ReasonReact.string(topLink)}
          </li>,
          ...bottomLis,
        ]
        |> Array.of_list},
     )}
  </ul>;
};
