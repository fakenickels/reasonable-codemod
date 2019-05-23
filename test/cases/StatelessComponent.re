let component = ReasonReact.statelessComponent("Test");
let make = (~prop1, ~prop2=?, ~prop3=1, _) => {
  let derived = prop3 + 2;
  {
    ...component,
    didMount: _ => {
      Js.log(1);
    },
    render: _ => <div> {derived->Js.String.make->ReasonReact.string} </div>,
  }
};
