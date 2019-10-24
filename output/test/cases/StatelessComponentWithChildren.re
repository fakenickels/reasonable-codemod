[@react.component]
let make = (~prop1, ~prop2=?, ~prop3=1, ~children, ()) => {
  let children = React.Children.toArray(children);
  ReactCompat.useMount(() => Js.log(1));

  <div>
    {prop3->Js.String.make->ReasonReact.string}
    {switch (children) {
     | [|child|] => child
     | _ => ReasonReact.null
     }}
  </div>;
};
