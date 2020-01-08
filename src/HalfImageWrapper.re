open Css;
open Style;

[@react.component]
let make = (~children) => {
  <div
    className={style([
      width(`percent(100.)),
      media(MediaQuery.halfTablet, [width(`percent(50.)), margin(`auto)]),
    ])}>
    children
  </div>;
};

let default = make;
