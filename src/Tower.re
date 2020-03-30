open Style;

module Style = {
  open Css;

  let container = style([
    border(`px(1), `solid, `rgb(0,0,0))
  ]);

  let ol = merge([
    BlogComponents.bodyStyle,
    style([
      marginLeft(`rem(0.25)),
      unsafe("width", "fit-content"),
      border(`px(3), `solid, Colors.navy(0.4)),
    ])
  ]);

  let topBorder = style([
     borderTop(`px(3), `solid, Colors.navy(0.4))
  ]);

  let li = i =>  {
    let s =
    style([
       listStyle(`none, `inside, `none),
       paddingLeft(`rem(1.)),
       paddingRight(`rem(1.)),
    ]);
    if (i == 0) {
      s
    } else {
      merge([s, topBorder])
    }
  };
};

module T = {
  type d = { children: string }
  type c = { props: d }
  type b = { children: array(c) }
  type a = { props: b }
};

[@react.component]
let make = (~children) => {
  let cs: T.a = Obj.magic(children);
  let strings = cs.props.children |> Array.map((c : T.c) => c.props.children);

  <div>
    <ol className=Style.ol>
      {strings |> Array.mapi((i, s) => {
        <li className={Style.li(i)} key=s> {React.string(s)} </li>
          }) |> React.array}
    </ol>
  </div>
}

