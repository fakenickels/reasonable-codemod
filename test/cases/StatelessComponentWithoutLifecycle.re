let component = ReasonReact.statelessComponent("Test");
let make = (~prop1, ~prop2=?, ~prop3=1, _) => {
  ...component,
  render: _ => <div> {prop3->Js.String.make->ReasonReact.string} </div>,
};
