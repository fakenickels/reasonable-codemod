[@react.component]
let make = (~prop1, ~prop2=?, ~prop3=1, ()) =>
  <div> {prop3->Js.String.make->ReasonReact.string} </div>;
