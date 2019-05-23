type action =
  | Tick;
type state = {count: int};
let component = ReasonReact.reducerComponent("Test");
[@react.component]
let make = (~prop1, ~prop2=?, ~prop3=1, ()) =>
  ReactCompat.useRecordApi({
    ...component,
    initialState: () => {count: prop3},
    reducer: (action, state) => {
      switch (action) {
      | Tick => ReasonReact.Update({count: state.count + 1})
      };
    },
    render: ({send, state}) =>
      <div>
        {prop1
         ->Belt.Array.map(item => item->Js.String.slice(~from=0, ~to_=1, _))
         ->React.string}
        {let prop4 = prop1
         React.null}
        {state.count->Js.String.make->ReasonReact.string}
        <button onClick={_ => send(Tick)}> "ok"->ReasonReact.string </button>
      </div>,
  });
