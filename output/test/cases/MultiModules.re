module ReducerComponent = {
  type action =
    | Tick;
  type state = {count: int};

  [@react.component]
  let make = (~prop1, ~prop2=?, ~prop3=1, ()) =>
    ReactCompat.useRecordApi({
      ...ReactCompat.component,

      initialState: () => {count: prop3},
      reducer: (action, state) => {
        switch (action) {
        | Tick => ReasonReact.Update({count: state.count + 1})
        };
      },
      render: ({send, state}) =>
        <div>
          {state.count->Js.String.make->ReasonReact.string}
          <button onClick={_ => send(Tick)}>
            "ok"->ReasonReact.string
          </button>
        </div>,
    });
};

module ReducerComponentWithChildren = {
  type action =
    | Tick;
  type state = {count: int};

  [@react.component]
  let make = (~prop1, ~prop2=?, ~prop3=1, ~children, ()) => {
    let children = React.Children.toArray(children);
    ReactCompat.useRecordApi({
      ...ReactCompat.component,

      initialState: () => {count: prop3},
      reducer: (action, state) => {
        switch (action) {
        | Tick => ReasonReact.Update({count: state.count + 1})
        };
      },
      render: ({send, state}) =>
        <div>
          {state.count->Js.String.make->ReasonReact.string}
          <button onClick={_ => send(Tick)}>
            "ok"->ReasonReact.string
          </button>
          {switch (children) {
           | [|child|] => child
           | _ => ReasonReact.null
           }}
        </div>,
    });
  };
};

module StatelessComponent = {
  [@react.component]
  let make = (~prop1, ~prop2=?, ~prop3=1, ()) => {
    let derived = prop3 + 2;
    React.useEffect0(() => Js.log(1));

    <div> {derived->Js.String.make->ReasonReact.string} </div>;
  };
};

module StatelessComponentWithChildren = {
  [@react.component]
  let make = (~prop1, ~prop2=?, ~prop3=1, ~children, ()) => {
    let children = React.Children.toArray(children);
    React.useEffect0(() => Js.log(1));

    <div>
      {prop3->Js.String.make->ReasonReact.string}
      {switch (children) {
       | [|child|] => child
       | _ => ReasonReact.null
       }}
    </div>;
  };
};

module StatelessComponentWithoutLifecycle = {
  [@react.component]
  let make = (~prop1, ~prop2=?, ~prop3=1, ()) =>
    <div> {prop3->Js.String.make->ReasonReact.string} </div>;
};

module StatelessComponentWithoutLifecycleWithChildren = {
  [@react.component]
  let make = (~prop1, ~prop2=?, ~prop3=1, ~children, ()) => {
    let children = React.Children.toArray(children);

    <div>
      {prop3->Js.String.make->ReasonReact.string}
      {switch (children) {
       | [|child|] => child
       | _ => React.null
       }}
    </div>;
  };
};

module type X = {type t;};

module Functor = (T: X) => {
  [@react.component]
  let make = (~prop1: T.t, ~prop2=?, ~prop3=1, ()) =>
    <div> {prop3->Js.String.make->ReasonReact.string} </div>;
};

module FunctorWithChildren = (T: X) => {
  [@react.component]
  let make = (~prop1: T.t, ~prop2=?, ~prop3=1, ~children, ()) => {
    let children = React.Children.toArray(children);

    <div>
      {prop3->Js.String.make->ReasonReact.string}
      {switch (children) {
       | [|child|] => child
       | _ => React.null
       }}
    </div>;
  };
};
