  type action =
    | Tick;
  type state = {count: int};
  let component:
    ReasonReact.componentSpec(
      state,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      action,
    );
  let make:
    (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, 'c) =>
    ReasonReact.componentSpec(
      state,
      state,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      action,
    );
