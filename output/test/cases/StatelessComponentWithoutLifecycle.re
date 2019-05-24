let component = ReasonReact.statelessComponent("Test");
[@react.component]
let make = (~prop1, ~prop2=?, ~prop3=1, ()) =>
  ReactCompat.useRecordApi({
    ...component,
    render: _ => <div> {prop3->Js.String.make->ReasonReact.string} </div>,
  });
