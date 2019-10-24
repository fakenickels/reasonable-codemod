type action =
  | Tick;
type state = {count: int};
let component = ReasonReact.reducerComponent("Test");
let make = (~prop1, ~prop2=?, ~prop3=1, _) => {
  ...component,
  initialState: () => {count: prop3},
  reducer: (action, state) => {
    switch (action) {
    | Tick => ReasonReact.Update({count: state.count + 1})
    };
  },
  didMount: ({send}) => {
    send(Tick);
    send(Tick);
    send(Tick);
  },
  render: ({send, state}) =>
    <div>
      {state.count->Js.String.make->ReasonReact.string}
      <button onClick={_ => send(Tick)}> "ok"->ReasonReact.string </button>
    </div>,
};
