type action =
  | Tick;
type state = {count: int};

[@react.component]
let make = (~prop1, ~prop2=?, ~prop3=1, ~children as something, ()) => {
  let something = React.Children.toArray(something);
  let (state, send) =
    ReactUpdate.useReducerWithMapState(
      () => {count: prop3},
      (action, state) =>
        switch (action) {
        | Tick => ReasonReact.Update({count: state.count + 1})
        },
    );

  <div>
    {state.count->Js.String.make->ReasonReact.string}
    <button onClick={_ => send(Tick)}> "ok"->ReasonReact.string </button>
    {switch (something) {
     | [|child|] => child
     | _ => ReasonReact.null
     }}
  </div>;
};
