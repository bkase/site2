open Style;
module Style = {
  open Css;

  let container = style([marginBottom(`rem(1.))]);

  let figure =
    style([
      display(`flex),
      width(`percent(100.)),
      justifyContent(`spaceBetween),
      alignItems(`center),
      flexWrap(`wrap),
      marginTop(`rem(0.5)),
      media(MediaQuery.halfTablet, [flexWrap(`nowrap)]),
    ]);

  let bar =
    style([
      display(`flex),
      before([
        unsafe("content", "'.'"),
        width(`rem(0.625)),
        flex(`none),
        display(`block),
        backgroundColor(Style.Colors.navy(0.25)),
        marginRight(`rem(1.)),
        marginBottom(`rem(1.5)),
      ]),
    ]);

  let iframe =
    style([
      before([
        unsafe("content", "\"\""),
        display(`block),
        paddingTop(`percent(100.)),
        /* initial ratio of 1:1*/
      ]),
      border(`px(3), `solid, Colors.navy(0.1)),
      flexGrow(1.),
      marginRight(`rem(1.)),
    ]);

  let caption =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      flexGrow(1.),
      marginTop(`rem(0.5)),
      media(MediaQuery.halfTablet, [marginTop(`zero)]),
    ]);
};

[@react.component]
let make = (~gameSrc, ~children) => {
  let (height, setHeight) = React.useState(() => 0);
  let (loaded, setLoaded) = React.useState(() => false);
  let (timeout, setTimeout) = React.useState(() => false);
  let iframeRef = React.useRef(Js.Nullable.null);

  // delay 500ms after iframe loads before querying for height
  React.useEffect1(
    () => {
      switch (loaded, timeout, React.Ref.current(iframeRef)) {
      | (true, true, iframeRef) when !Js.Nullable.isNullable(iframeRef) =>
        let iframeContentWindow = Obj.magic(iframeRef)##contentWindow;
        let iframeDocument = iframeContentWindow##document;
        iframeContentWindow##addEventListener(
          "resize",
          {
            setHeight(_ => iframeDocument##documentElement##scrollHeight);
          },
        );
      | (true, false, _) =>
        let _ = Js.Global.setTimeout(() => setTimeout(_ => true), 500);
        ();
      | _ => ()
      };
      None;
    },
    [|loaded, timeout|],
  );

  <div className=Style.container>
    <figure className=Style.figure>
      <iframe
        style={
                if (height != 0) {
                  ReactDOMRe.Style.make(
                    ~height=Js.Int.toString(height) ++ "px",
                    (),
                  );
                } else {
                  ReactDOMRe.Style.make();
                }
              }
        className=Style.iframe
        ref={ReactDOMRe.Ref.domRef(iframeRef)}
        src=gameSrc
        onLoad={_ => setLoaded(_ => true)}
      />
      <div className=Style.caption>
        <figcaption className=Style.bar> children </figcaption>
      </div>
    </figure>
  </div>;
};
