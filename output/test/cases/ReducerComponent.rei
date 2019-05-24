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
[@react.component]
let make: (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
