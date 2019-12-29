[@react.component]
let make = (~links) => {
  <ul>
    {ReasonReact.array(
       links |> List.map(link => <li> link </li>) |> Array.of_list,
     )}
  </ul>;
};
